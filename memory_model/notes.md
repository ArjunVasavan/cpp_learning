## What is the C++ Memory Model?

It answers two questions:
1. **Where** does each variable live in memory?
2. **How** do multiple threads see shared memory?

Let's take them one at a time.

---

## Part 1 — Memory Segments

Every C++ program has these segments:

```
High address
┌─────────────────┐
│     Stack       │  ← local variables, function call frames
├─────────────────┤
│       ↓         │  grows downward
│                 │
│       ↑         │  grows upward
├─────────────────┤
│      Heap       │  ← new / malloc
├─────────────────┤
│      BSS        │  ← uninitialized globals/statics (zeroed at startup)
├─────────────────┤
│      Data       │  ← initialized globals/statics
├─────────────────┤
│      Text       │  ← your compiled code (read only)
└─────────────────┘
Low address
```

```cpp
int g1 = 10;          // Data segment — initialized global
int g2;               // BSS  segment — uninitialized global (zero)
const char* s = "hi"; // Text segment — string literal

void foo() {
    int x = 5;        // Stack — local variable
    int* p = new int; // p is on stack, *p is on Heap
    static int c = 0; // Data segment — static local
}
```

---

## Stack vs Heap — deep comparison

```cpp
void stackExample() {
    int arr[1000];   // 4000 bytes on stack — fast, auto freed
}                    // arr destroyed here automatically

void heapExample() {
    int* arr = new int[1000];  // 4000 bytes on heap — manual management
    // ... use arr
    delete[] arr;              // must free manually, else memory leak
}
```

| | Stack | Heap |
|---|---|---|
| Size | Small (~1-8MB) | Large (RAM limit) |
| Speed | Very fast | Slower (allocator overhead) |
| Lifetime | Scope-based, automatic | Manual (`new`/`delete`) |
| Fragmentation | Never | Can fragment |
| Embedded use | Preferred | Avoid or use carefully |

**Embedded note:** Many embedded systems disable heap entirely — stack only. Memory fragmentation on a microcontroller with 8KB RAM is fatal.

---

## Storage Classes

```cpp
// 1. auto (default for locals)
void foo() {
    int x = 10;  // auto storage — lives on stack, dies with function
}

// 2. static local — lives for entire program duration
void counter() {
    static int count = 0;  // initialized once, persists between calls
    count++;
    std::cout << count << "\n";
}

// 3. static global — file scope only
static int filePrivate = 5;  // not visible outside this .cpp file

// 4. extern — defined elsewhere
extern int definedInOtherFile;  // declaration only, no memory here
```

```cpp
int main() {
    counter();  // prints 1
    counter();  // prints 2
    counter();  // prints 3
}
```

---

## Part 2 — Multithreading Memory Model

This is where it gets deep. When multiple threads access shared memory, things get unexpected.

### The Problem — Data Race

```cpp
#include <thread>

int counter = 0;  // shared variable

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;  // NOT atomic — data race
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << counter << "\n";  // expected 200000, get something random
}
```

`counter++` is actually **three operations**:
```
load  counter into register
add   1
store back to counter
```

Two threads can interleave these — one thread's write overwrites the other's. This is **undefined behavior** in C++.

---

## `std::atomic` — the fix

```cpp
#include <atomic>
#include <thread>

std::atomic<int> counter = 0;  // guaranteed atomic operations

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;  // atomic — no data race
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << counter << "\n";  // always 200000
}
```

---

## Memory Ordering — the deep part

Even with atomics, the **order** in which memory operations become visible to other threads is not guaranteed by default. The CPU and compiler reorder instructions for performance.

```cpp
// Thread 1
data = 42;         // store data
ready = true;      // signal ready

// Thread 2
while (!ready);    // wait for signal
use(data);         // is data guaranteed to be 42 here?
```

**Answer: NO** — without proper ordering, the CPU might reorder the stores so `ready = true` happens before `data = 42`.

C++ gives you memory order controls:

```cpp
#include <atomic>

std::atomic<bool> ready(false);
int data = 0;

// Thread 1
void producer() {
    data = 42;
    ready.store(true, std::memory_order_release);  // all writes before this are visible
}

// Thread 2
void consumer() {
    while (!ready.load(std::memory_order_acquire));  // sees all writes from release
    std::cout << data << "\n";  // guaranteed to print 42
}
```

The six memory orders from weakest to strongest:

```
memory_order_relaxed   — no ordering guarantee, just atomicity
memory_order_consume   — rarely used
memory_order_acquire   — no reads/writes can move before this load
memory_order_release   — no reads/writes can move after this store
memory_order_acq_rel   — both acquire and release (for read-modify-write)
memory_order_seq_cst   — total sequential order (default, strongest, slowest)
```

For most cases use the default (`seq_cst`) unless you're squeezing every cycle out of a hot path.

---

## `volatile` — what it is and isn't

Common confusion in embedded:

```cpp
volatile int* reg = (volatile int*)0x40000000;  // hardware register
*reg = 1;  // write
int x = *reg;  // read
```

`volatile` tells the compiler: **don't optimize away this read/write** — the value can change outside the program's control (hardware register, ISR).

**What `volatile` does NOT do:**
- It does not make operations atomic
- It does not prevent data races between threads
- It is **not** a substitute for `std::atomic` in multithreaded code

```cpp
volatile int x = 0;

// Thread 1: x++   — still NOT atomic, still a data race
// Use std::atomic<int> for thread safety
```

In embedded C++ — use `volatile` for hardware registers, `std::atomic` for shared thread data.

---

## Stack Overflow

```cpp
void infinite() {
    int arr[10000];   // 40KB pushed on stack each call
    infinite();       // recursive — stack grows until crash
}
```

On embedded systems with 8KB stack this happens fast. Common causes:
- Deep/infinite recursion
- Large local arrays
- Deep interrupt nesting

---

## Complete picture

```cpp
#include <iostream>
#include <atomic>
#include <thread>

// Data segment
int globalInit = 100;

// BSS
int globalUninit;

std::atomic<int> sharedCounter(0);  // safe shared state

void worker(int id) {
    // Stack
    int localVar = id * 10;

    // Static local — shared across all calls, atomic needed if multithreaded
    static int callCount = 0;
    callCount++;

    sharedCounter += localVar;
}

int main() {
    // Heap
    int* heapArr = new int[5]{1,2,3,4,5};

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join();
    t2.join();

    std::cout << "counter: " << sharedCounter << "\n";  // always 30

    delete[] heapArr;
}
```

---

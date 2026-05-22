# Lock-free and Wait-free Atomics — Interview Guide

---

## The 3 Levels of Thread Safety

```
lock-based → threads can BLOCK each other
lock-free  → system always makes progress, but one thread may retry
wait-free  → every thread always finishes in bounded steps
```

---

## 1. Lock-based (Mutex)

- Uses `std::mutex` to protect shared data
- One thread locks — all others **stop and wait**
- If lock holder gets paused by OS, everyone waits
- **Blocking** — threads can be stuck indefinitely

```cpp
// ============================================================
// lock-based
// - uses mutex to protect shared data
// - other threads block and wait when mutex is locked
// - simple to write but can cause contention and deadlocks
// ============================================================

#include <mutex>

std::mutex m;
int counter = 0;

void increment() {
    m.lock();       // other threads STOP here and wait
    counter++;      // only one thread runs this at a time
    m.unlock();     // now other threads can proceed
}
```

**Problems with locks:**
- **Deadlock** — two threads wait for each other forever
- **Priority inversion** — low priority thread holds lock, high priority thread waits
- **Contention** — many threads fighting for one lock = slow

---

## 2. Lock-free

- Uses atomics — **no mutex, no blocking**
- Guarantee: **at least one thread always makes progress**
- A thread may retry in a loop but it never blocks others
- Other threads are never forced to wait
- **Not guaranteed** that every thread finishes quickly — just that someone always moves forward

```cpp
// ============================================================
// lock-free
// - uses atomics instead of mutex
// - no thread blocks another thread
// - at least one thread always makes progress
// - a thread MAY retry but never blocks
// ============================================================

#include <atomic>

std::atomic<int> counter{0};

void increment() {
    // fetch_add is lock-free — no mutex needed
    // no thread blocks another
    counter.fetch_add(1, std::memory_order_relaxed);
}
```

### Lock-free with CAS retry loop

```cpp
struct Node {
    int val;
    Node* next;
};

std::atomic<Node*> head{nullptr};

void push(int val) {
    Node* newNode = new Node{val, nullptr};

    do {
        newNode->next = head.load();           // read current head
    } while (!head.compare_exchange_weak(      // try to set new head
                newNode->next,                 // expected
                newNode));                     // desired
    // if another thread changed head between load and CAS,
    // CAS fails → we retry
    // lock-free ✅ — system always progresses
    // wait-free ❌ — THIS thread may retry many times
}
```

**Key point:** One thread might retry forever if others keep winning the CAS. But the system as a whole always moves forward — someone always succeeds.

---

## 3. Wait-free

- Strongest guarantee
- **Every thread finishes in a bounded number of steps** — no retries, no spinning
- No thread is ever starved
- Hardest to implement correctly
- Not always possible for every algorithm

```cpp
// ============================================================
// wait-free
// - every thread finishes in bounded steps
// - no retries, no spinning, no starvation
// - hardest to implement
// - example: simple atomic store/load with no retry loop
// ============================================================

std::atomic<int> value{0};

void writer(int val) {
    // store is wait-free — completes in ONE step
    // no retry, no loop, no waiting
    value.store(val, std::memory_order_release);
}

void reader() {
    // load is wait-free — completes in ONE step
    int val = value.load(std::memory_order_acquire);
    std::cout << val << "\n";
}
```

Simple atomic `store` and `load` are wait-free because they complete in a single step with no retry loop.

---

## Side by Side Comparison

```cpp
// lock-based — thread blocks
void increment_locked() {
    m.lock();           // ← other threads STOP here
    counter++;
    m.unlock();
}

// lock-free — no blocking, but may retry
void increment_lockfree() {
    int expected = counter.load();
    while (!counter.compare_exchange_weak(expected, expected + 1));
    //     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //     retries until it wins — but never blocks other threads
}

// wait-free — no blocking, no retry
void increment_waitfree() {
    counter.fetch_add(1, std::memory_order_relaxed);
    // ^^^^^^^^^^^^^^^^^^
    // completes in ONE step — always, guaranteed
}
```

---

## Comparison Table

| Property | Lock-based | Lock-free | Wait-free |
|---|---|---|---|
| Uses mutex | ✅ yes | ❌ no | ❌ no |
| Threads can block | ✅ yes | ❌ no | ❌ no |
| System always progresses | ❌ no | ✅ yes | ✅ yes |
| Every thread finishes in bounded steps | ❌ no | ❌ no | ✅ yes |
| Starvation possible | ✅ yes | ✅ yes | ❌ no |
| Complexity | Easy | Medium | Hard |
| Performance | Slowest | Fast | Fastest |

---

## Strength Scale

```
lock-based → lock-free → wait-free
weakest                   strongest
slowest                   fastest
easiest                   hardest
```

---

## How to Know if Something is Lock-free or Wait-free

```
Has a mutex or lock?
    → lock-based

Has a CAS retry loop (while !compare_exchange)?
    → lock-free (may retry, but no blocking)

Single atomic operation — store, load, fetch_add?
    → wait-free (always finishes in one step)
```

---

## Common Interview Questions

**Q: What is the difference between lock-free and wait-free?**
A: Lock-free guarantees that at least one thread always makes progress — no thread blocks another, but a thread may retry. Wait-free is stronger — every thread is guaranteed to finish in a bounded number of steps with no retries or starvation.

**Q: Is `fetch_add` lock-free or wait-free?**
A: Wait-free. It completes in a single atomic step with no retry loop.

**Q: Is a CAS retry loop lock-free or wait-free?**
A: Lock-free but not wait-free. The system always progresses because at least one CAS succeeds per round, but a single thread may retry many times if others keep winning.

**Q: Can a lock-free program have starvation?**
A: Yes. A thread in a CAS retry loop can theoretically be retried forever if other threads keep winning. Wait-free eliminates this.

**Q: Why use lock-free over mutex?**
A: Lock-free avoids deadlocks, priority inversion, and contention. It also allows progress even if a thread is paused by the OS mid-operation, since other threads are never blocked.

**Q: Is every atomic operation lock-free?**
A: Not necessarily. You can check with `is_lock_free()` on an atomic variable. For small types like int and bool, atomics are typically lock-free on modern hardware. For large types, the compiler may use an internal lock.

```cpp
std::atomic<int> x{0};
std::cout << x.is_lock_free() << "\n"; // 1 = true on most platforms
```

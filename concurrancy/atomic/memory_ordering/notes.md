# C++ Atomic Memory Ordering — Interview Guide

---

## What is an Atomic?

An atomic operation is **indivisible** — no other thread can see it halfway through.

```cpp
// normal int — NOT safe (data race)
int counter = 0;
counter++;  // 3 steps: READ, ADD, WRITE — can be interrupted

// atomic int — SAFE
std::atomic<int> counter{0};
counter.fetch_add(1);  // READ + ADD + WRITE as one unit
```

---

## What is Memory Ordering?

Atomicity fixes **torn operations**. But CPUs and compilers can **reorder** instructions for performance. Memory ordering controls **which writes become visible to which threads, and when**.

```
Atomicity   → fixes "half-done" operations
Memory Order → fixes visibility order across threads
```

---

## The 6 Memory Orderings

---

### 1. `memory_order_relaxed`

- **Weakest** ordering
- Only guarantees atomicity — no ordering or synchronization
- Compiler/CPU can reorder freely
- **Use when:** simple counters, statistics — you only care about the final value

```cpp
// ============================================================
// memory_order_relaxed
// - only atomicity guaranteed
// - no thread synchronization
// - fastest ordering
// ============================================================

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 1000; i++)
        // just increment atomically — order doesn't matter
        counter.fetch_add(1, std::memory_order_relaxed);
}
```

**Interview answer:** "Relaxed only ensures the operation itself is atomic. There are no guarantees about how this operation is ordered relative to other memory accesses in other threads."

---

### 2. `memory_order_release` + `memory_order_acquire`

- These **always work as a pair**
- `release` → used on **stores (writes)** — "I am done writing, data is ready"
- `acquire` → used on **loads (reads)** — "I will not read until this load completes"
- Together they create a **safe handoff point** between threads

```cpp
// ============================================================
// memory_order_release  — writer side
// memory_order_acquire  — reader side
// - release: nothing written BEFORE it can move AFTER it
// - acquire: nothing read AFTER it can move BEFORE it
// - use for: producer-consumer pattern
// ============================================================

int data = 0;
std::atomic<bool> ready{false};

void writer() {
    data = 42;                                    // write data first
    ready.store(true, std::memory_order_release); // publish — "data is ready"
}

void reader() {
    while (!ready.load(std::memory_order_acquire)); // wait for publish
    std::cout << data << "\n"; // guaranteed to see 42
}
```

**Without release/acquire — the bug:**
```
writer: ready = true   ← CPU reorders this first!
writer: data  = 42

reader: sees ready = true
reader: reads data = 0  ← not written yet!  BUG ❌
```

**With release/acquire — fixed:**
```
writer: data  = 42       ← guaranteed before release
writer: ready = true     ← release wall
                 ──────────────────────→
reader:          ready == true         ← acquire wall
reader:          data = 42  ✅
```

**Interview answer:** "Release-acquire creates a happens-before relationship. Everything written before the release store is guaranteed to be visible to the thread that does the acquire load."

---

### 3. `memory_order_acq_rel`

- Combination of acquire + release **in one operation**
- Only used on **read-modify-write (RMW)** operations: `fetch_add`, `exchange`, `compare_exchange`
- The READ part has acquire semantics
- The WRITE part has release semantics
- **Use when:** a middleman thread both reads AND writes atomically

```cpp
// ============================================================
// memory_order_acq_rel
// - acquire + release combined
// - only for RMW ops: fetch_add, exchange, compare_exchange
// - use for: middleman thread that reads and writes
// ============================================================

std::atomic<int> x{0};

void middleman() {
    int expected = 42;

    // compare_exchange reads x AND writes 100 atomically
    // acq_rel: acquire on the read side, release on the write side
    while (!x.compare_exchange_weak(expected, 100,
                                    std::memory_order_acq_rel)) {
        expected = 42; // reset and retry
    }
}
```

**Interview answer:** "acq_rel is used on read-modify-write operations when a thread needs both sides synchronized — it sees all writes before it (acquire) and makes its own write visible to others (release)."

---

### 4. `memory_order_seq_cst`

- **Strongest** ordering — Sequential Consistency
- All threads see **all** atomic operations in the **same global order**
- This is the **default** if you specify nothing
- Both acquire and release walls built in
- **Use when:** unsure which ordering to use, or correctness > performance

```cpp
// ============================================================
// memory_order_seq_cst
// - strongest ordering
// - all threads agree on one global order of all atomics
// - default if no ordering specified
// - slowest but always correct
// ============================================================

std::atomic<int> counter{0};

// these three are identical — seq_cst is the default
counter.fetch_add(1);
counter.fetch_add(1, std::memory_order_seq_cst);
```

**Interview answer:** "seq_cst gives a single total order of all atomic operations across all threads. Every thread will observe all seq_cst operations in the same order. It's the default and the safest, but also the most expensive."

---

### 5. `memory_order_consume` *(avoid in practice)*

- Weaker form of acquire
- Only orders operations **data-dependent** on the loaded value
- Compilers just promote it to acquire anyway
- **Not used in practice** — avoid it

---

## Quick Comparison Table

| Ordering | Load | Store | RMW | Strength | Use Case |
|---|---|---|---|---|---|
| `relaxed` | ✅ | ✅ | ✅ | Weakest | Simple counters |
| `consume` | ✅ | ❌ | ✅ | — | Avoid |
| `acquire` | ✅ | ❌ | ✅ | Medium | Reader side |
| `release` | ❌ | ✅ | ✅ | Medium | Writer side |
| `acq_rel` | ❌ | ❌ | ✅ | Strong | RMW middleman |
| `seq_cst` | ✅ | ✅ | ✅ | Strongest | Default, always safe |

---

## Strength Scale

```
relaxed → consume → acquire/release → acq_rel → seq_cst
weakest                                          strongest
fastest                                          slowest
```

---

## When to Use What — Decision Guide

```
Do you just need the increment/decrement to be safe?
    → relaxed

Is one thread writing data and another reading it?
    → release on writer, acquire on reader

Are you doing fetch_add/compare_exchange and need both sides synced?
    → acq_rel

Are you unsure or want to be safe?
    → seq_cst (default)
```

---

## Common Interview Questions

**Q: What is the default memory ordering in C++ atomics?**
A: `memory_order_seq_cst` — sequential consistency. It's the strongest and safest.

**Q: What is the difference between relaxed and seq_cst?**
A: Relaxed only guarantees atomicity with no ordering between threads. seq_cst guarantees a single global order visible to all threads.

**Q: When would you use memory_order_relaxed?**
A: For simple counters or statistics where you only care about the final value and not the order of operations between threads.

**Q: What is the release-acquire pair used for?**
A: Producer-consumer patterns. The writer uses release to "publish" data, and the reader uses acquire to safely "subscribe". Together they create a happens-before relationship.

**Q: What is the difference between acquire and acq_rel?**
A: acquire is only for loads (reads). acq_rel is for read-modify-write operations that need both acquire semantics on the read side and release semantics on the write side simultaneously.

**Q: Can you use release on a load operation?**
A: No. release is only valid on stores (writes). For loads you use acquire. For RMW operations you can use acq_rel or seq_cst.

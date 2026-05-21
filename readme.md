# C++

C++ is a general-purpose programming language built on top of C, adding object-oriented
programming, generic programming, and zero-overhead abstractions — without sacrificing
the low-level control that systems programming requires.

---

## Why C++ for Embedded Systems

C has been the language of embedded systems for decades, but as systems grow in complexity,
C++ offers real advantages without compromising performance.

**RAII** — resources are tied to object lifetimes. Memory, peripheral handles, and locks
are acquired and released automatically, reducing an entire class of bugs common in C.

**Stronger type system** — catches errors at compile time that C would silently allow,
critical in safety-sensitive embedded environments.

**Reusability** — classes and templates make driver and HAL code modular and reusable
across projects without macro hacks.

**Modern concurrency** — `std::thread` and synchronization primitives for RTOS-based
or multi-core embedded targets.

---

C++ is the standard in automotive, aerospace, robotics, and any embedded
domain where complexity demands more structure than bare C provides.

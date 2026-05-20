## Essential `std::` for Embedded — Must-Know Only

### 1. Fixed-Width Integers (`<cstdint>`) — #1 Priority
```cpp
std::uint8_t   // 8-bit register values
std::uint16_t  // 16-bit peripherals
std::uint32_t  // 32-bit registers
std::int32_t   // signed arithmetic
```
You'll use these **every single day**.

---

### 2. `std::array` — Replace all raw arrays
```cpp
std::array<uint8_t, 64> txBuffer{};
```
Same performance as `uint8_t buf[64]` but safer.

---

### 3. `std::atomic` — ISR ↔ Main communication
```cpp
std::atomic<bool> dataReady{false};  // set in ISR, read in main
```
Prevents race conditions without disabling interrupts.

---

### 4. `std::optional` — Replace magic sentinel values
```cpp
std::optional<uint16_t> readADC();  // returns empty if failed
```
No more `return -1` or `return 0xFFFF` to signal failure.

---

### 5. `std::span` (C++20) — Pass buffers cleanly
```cpp
void transmit(std::span<const uint8_t> data);  // no pointer + length pairs
```
Non-allocating, zero overhead.

---

### 6. `std::numeric_limits` — Hardware boundary checks
```cpp
std::numeric_limits<uint16_t>::max()  // 65535
std::numeric_limits<int16_t>::min()   // -32768
```
Avoids hardcoded magic numbers.

---

### 7. `std::bit_cast` (C++20) — Safe type punning
```cpp
float voltage = std::bit_cast<float>(rawRegisterUint32);
```
Replaces dangerous `reinterpret_cast` and `memcpy` hacks.

---

### 8. `std::clamp` — Sensor/actuator limiting
```cpp
duty = std::clamp(duty, 0, 255);  // keep PWM in range
```

---

### 9. `std::string_view` — Read-only strings, zero allocation
```cpp
void log(std::string_view msg);  // pass string literals safely
```
Never use `std::string` — it heap-allocates.

---

### 10. `std::lock_guard` — Safe mutex usage (RTOS)
```cpp
std::lock_guard<std::mutex> lock(myMutex);  // auto-unlocks on scope exit
```

---

## The Short List to Memorize

| Must Know | Why |
|---|---|
| `std::uint8_t` etc. | Hardware registers |
| `std::array` | Safe fixed buffers |
| `std::atomic` | ISR-safe shared variables |
| `std::optional` | Clean error returns |
| `std::span` | Pass buffers without pointer+length |
| `std::numeric_limits` | Boundary values |
| `std::bit_cast` | Safe type punning |
| `std::clamp` | Constrain values |
| `std::string_view` | Strings without heap |
| `std::lock_guard` | RTOS mutex safety |

That's it. **10 things.** Master these and you're well-equipped for most embedded C++ work.

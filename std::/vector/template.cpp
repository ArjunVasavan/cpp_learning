#include <iostream>
#include <stdexcept>
#include <algorithm>    // std::copy, std::move

template <typename T>
class MyVector {
private:
    T*     data_;       // pointer to heap-allocated array
    size_t size_;       // number of elements currently stored
    size_t capacity_;   // allocated slots

    // Grow storage to at least new_cap slots
    void reallocate(size_t new_cap) {
        T* new_data = new T[new_cap];
        // Move existing elements into new buffer
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_     = new_data;
        capacity_ = new_cap;
    }

public:
    // ── Constructors & destructor ────────────────────────────────────────
    MyVector()
        : data_(nullptr), size_(0), capacity_(0) {}

    explicit MyVector(size_t n, const T& val = T())
        : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) data_[i] = val;
    }

    // Copy constructor
    MyVector(const MyVector& other)
        : data_(new T[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Move constructor
    MyVector(MyVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }

    ~MyVector() { delete[] data_; }

    // ── Assignment operators ─────────────────────────────────────────────
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            size_     = other.size_;
            data_     = new T[capacity_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_           = other.data_;
            size_           = other.size_;
            capacity_       = other.capacity_;
            other.data_     = nullptr;
            other.size_     = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // ── Element access ───────────────────────────────────────────────────
    T& operator[](size_t i)             { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    T& at(size_t i) {
        if (i >= size_) throw std::out_of_range("MyVector::at — index out of range");
        return data_[i];
    }
    const T& at(size_t i) const {
        if (i >= size_) throw std::out_of_range("MyVector::at — index out of range");
        return data_[i];
    }

    T&       front()       { return data_[0]; }
    const T& front() const { return data_[0]; }
    T&       back()        { return data_[size_ - 1]; }
    const T& back()  const { return data_[size_ - 1]; }
    T*       data()        { return data_; }
    const T* data()  const { return data_; }

    // ── Capacity ─────────────────────────────────────────────────────────
    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty()    const { return size_ == 0; }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_) reallocate(new_cap);
    }

    void shrink_to_fit() {
        if (size_ < capacity_) reallocate(size_);
    }

    // ── Modifiers ────────────────────────────────────────────────────────
    void push_back(const T& val) {
        if (size_ == capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);   // double strategy
        data_[size_++] = val;
    }

    void push_back(T&& val) {
        if (size_ == capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(val);
    }

    void pop_back() {
        if (size_ > 0) --size_;
    }

    // Insert val before position index
    void insert(size_t index, const T& val) {
        if (index > size_) throw std::out_of_range("MyVector::insert — index out of range");
        if (size_ == capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        // Shift elements right
        for (size_t i = size_; i > index; --i)
            data_[i] = std::move(data_[i - 1]);
        data_[index] = val;
        ++size_;
    }

    // Erase element at position index
    void erase(size_t index) {
        if (index >= size_) throw std::out_of_range("MyVector::erase — index out of range");
        // Shift elements left
        for (size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);
        --size_;
    }

    void clear() { size_ = 0; }

    void resize(size_t new_size, const T& val = T()) {
        if (new_size > capacity_) reallocate(new_size);
        // Fill new slots if growing
        for (size_t i = size_; i < new_size; ++i) data_[i] = val;
        size_ = new_size;
    }

    // ── Iterators (raw pointer iterators) ────────────────────────────────
    T*       begin()        { return data_; }
    const T* begin()  const { return data_; }
    T*       end()          { return data_ + size_; }
    const T* end()    const { return data_ + size_; }
};

// ── Demo ─────────────────────────────────────────────────────────────────────
int main() {
    MyVector<int> v;
    v.reserve(8);

    for (int i = 1; i <= 5; ++i) v.push_back(i);  // {1,2,3,4,5}

    v.insert(2, 99);   // {1,2,99,3,4,5}
    v.erase(0);        // {2,99,3,4,5}
    v.pop_back();      // {2,99,3,4}

    std::cout << "size=" << v.size()
              << "  cap=" << v.capacity() << "\n";

    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    // Copy and move
    MyVector<int> copy  = v;
    MyVector<int> moved = std::move(v);

    std::cout << "copy[1]="  << copy[1]  << "\n";   // 99
    std::cout << "moved[1]=" << moved[1] << "\n";   // 99

    // at() bounds check
    try { moved.at(100); }
    catch (const std::out_of_range& e) { std::cout << e.what() << "\n"; }

    return 0;
}

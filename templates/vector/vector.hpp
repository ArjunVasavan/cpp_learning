// vector.h — Template Vector class declaration
#pragma once
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

template <typename T>
class Vector {
public:
    // Constructors & destructor
    Vector();
    explicit Vector(size_t size, const T& val = T());
    Vector(std::initializer_list<T> list);
    Vector(const Vector<T>& other);           // copy constructor
    Vector(Vector<T>&& other) noexcept;       // move constructor
    ~Vector();

    // Assignment
    Vector<T>& operator=(Vector<T> other);    // copy-and-swap

    // Element access
    T&       operator[](size_t i);
    const T& operator[](size_t i) const;
    T&       at(size_t i);
    const T& at(size_t i) const;
    T&       front();
    T&       back();

    // Capacity
    size_t  size()     const { return m_size; }
    size_t  capacity() const { return m_cap; }
    bool    empty()    const { return m_size == 0; }
    void    reserve(size_t n);

    // Modifiers
    void push_back(const T& val);
    void push_back(T&& val);
    void pop_back();
    void clear();
    void resize(size_t n, const T& val = T());

    // Iterators
    T*       begin()       { return m_data; }
    T*       end()         { return m_data + m_size; }
    const T* begin() const { return m_data; }
    const T* end()   const { return m_data + m_size; }

    void swap(Vector<T>& other) noexcept;

private:
    T*     m_data;
    size_t m_size;
    size_t m_cap;

    static constexpr size_t INITIAL_CAP = 4;
    void grow(size_t new_cap);
};

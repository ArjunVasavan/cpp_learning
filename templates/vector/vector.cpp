#include "vector.hpp"

// ── Constructors ──────────────────────────────────────────────

template <typename T>
Vector<T>::Vector()
    : m_data(nullptr), m_size(0), m_cap(0) {}

template <typename T>
Vector<T>::Vector(size_t size, const T& val)
    : m_data(new T[size]), m_size(size), m_cap(size) {
    std::fill(m_data, m_data + m_size, val);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
    : m_data(new T[list.size()]), m_size(list.size()), m_cap(list.size()) {
    std::copy(list.begin(), list.end(), m_data);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : m_data(new T[other.m_cap]), m_size(other.m_size), m_cap(other.m_cap) {
    std::copy(other.m_data, other.m_data + m_size, m_data);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap) {
    other.m_data = nullptr;
    other.m_size = other.m_cap = 0;
}

template <typename T>
Vector<T>::~Vector() { delete[] m_data; }

// ── Assignment (copy-and-swap) ────────────────────────────────

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> other) {
    swap(other);
    return *this;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_cap,  other.m_cap);
}

// ── Element access ────────────────────────────────────────────

template <typename T>
T& Vector<T>::operator[](size_t i) { return m_data[i]; }

template <typename T>
const T& Vector<T>::operator[](size_t i) const { return m_data[i]; }

template <typename T>
T& Vector<T>::at(size_t i) {
    if (i >= m_size) throw std::out_of_range("Vector::at — index out of range");
    return m_data[i];
}

template <typename T>
const T& Vector<T>::at(size_t i) const {
    if (i >= m_size) throw std::out_of_range("Vector::at — index out of range");
    return m_data[i];
}

template <typename T>
T& Vector<T>::front() { return m_data[0]; }

template <typename T>
T& Vector<T>::back()  { return m_data[m_size - 1]; }

// ── Capacity ──────────────────────────────────────────────────

template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n > m_cap) grow(n);
}

template <typename T>
void Vector<T>::grow(size_t new_cap) {
    T* new_data = new T[new_cap];
    std::move(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_cap  = new_cap;
}

// ── Modifiers ─────────────────────────────────────────────────

template <typename T>
void Vector<T>::push_back(const T& val) {
    if (m_size == m_cap)
        grow(m_cap == 0 ? INITIAL_CAP : m_cap * 2);
    m_data[m_size++] = val;
}

template <typename T>
void Vector<T>::push_back(T&& val) {
    if (m_size == m_cap)
        grow(m_cap == 0 ? INITIAL_CAP : m_cap * 2);
    m_data[m_size++] = std::move(val);
}

template <typename T>
void Vector<T>::pop_back() {
    if (m_size > 0) --m_size;
}

template <typename T>
void Vector<T>::clear() { m_size = 0; }

template <typename T>
void Vector<T>::resize(size_t n, const T& val) {
    if (n > m_cap) grow(n);
    if (n > m_size)
        std::fill(m_data + m_size, m_data + n, val);
    m_size = n;
}

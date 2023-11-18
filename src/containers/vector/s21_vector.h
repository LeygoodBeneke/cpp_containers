#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#define DEFAULT_CAPACITY 1

#include <initializer_list>
#include <memory>

namespace s21 {

template <class T, class Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  vector();
  vector(unsigned size);
  vector(vector&& v) noexcept;                             // +
  vector(const vector& v);                                 // +
  vector(std::initializer_list<value_type> const& items);  // +
  ~vector();                                               // +

  inline size_type size() const noexcept { return _size; }             // +
  inline size_type max_size() const { return _allocator.max_size(); }  // +
  void reserve(size_type size);                                        // -
  inline size_type capacity() const noexcept { return _capacity; }     // +
  inline bool empty() const noexcept { return _size == 0; }            // +
  void clear() noexcept { _size = 0; }                                 // +

  inline reference back();              // +
  inline const_reference back() const;  // +

  inline reference front();              // +
  inline const_reference front() const;  // +

  void push_back(const_reference value);  // +
  void push_back(T&& value);              // +
  void pop_back();                        // +
  void swap(vector& other) noexcept;      // +

  inline iterator begin() const noexcept { return _data; }        // +
  inline iterator end() const noexcept { return _data + _size; }  // +
  inline T* data() { return _data; };                             // +

  void shrink_to_fit() noexcept;  // +

  reference operator[](size_type i) const;                     // +
  value_type operator[](size_type i);                          // +
  vector& operator=(vector&& v) noexcept;                      // -
  vector& operator=(const vector& v);                          // -
  vector& operator=(std::initializer_list<value_type> ilist);  // -

 private:
  Allocator _allocator;
  iterator _data;
  size_type _size;
  unsigned _capacity;
};

template <class T, class Allocator>
vector<T, Allocator>::vector()
    : _allocator(std::allocator<value_type>()),
      _size(0),
      _capacity(DEFAULT_CAPACITY) {
  _data = _allocator.allocate(_capacity);
}

template <class T, class Allocator>
vector<T, Allocator>::vector(unsigned size) : _size(size), _capacity(size) {
  _data = _allocator.allocate(_capacity);
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);
}

template <class T, class Allocator>
vector<T, Allocator>::vector(vector&& v) noexcept {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);

  _data = v._data;
  _size = v._size;
  _capacity = v._capacity;

  v._data = nullptr;
  v._size = 0;
  v._capacity = 0;
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& v) {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);
  _size = v._size;
  _capacity = v._capacity;

  _data = _allocator.allocate(_capacity);
  for (size_t i = 0; i < _size; i++) _data[i] = v._data[i];
}

template <class T, class Allocator>
vector<T, Allocator>::vector(std::initializer_list<value_type> const& items)
    : _size(items.size()), _capacity(items.size()) {
  _data = _allocator.allocate(_capacity);
  size_type idx = 0;
  for (T item : items) {
    _data[idx] = items;
    idx++;
  }
}

template <class T, class Allocator>
T& vector<T, Allocator>::back() {
  if (_size == 0) throw "size is equal to zero";
  return _data[_size - 1];
}

template <class T, class Allocator>
const T& vector<T, Allocator>::back() const {
  if (_size == 0) throw "size is equal to zero";
  return _data[_size - 1];
}

template <class T, class Allocator>
T& vector<T, Allocator>::front() {
  if (_size == 0) throw "size is equal to zero";
  return *_data;
}

template <class T, class Allocator>
const T& vector<T, Allocator>::front() const {
  if (_size == 0) throw "size is equal to zero";
  return *_data;
}

template <class T, class Allocator>
inline void vector<T, Allocator>::pop_back() {
  if (_size == 0) throw "size is equal to zero";
  _allocator.destroy(_data + _size);
  _size--;
}

template <class T, class Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept {
  std::swap(_data, other._data);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back(const T& value) {
  if (_size >= _capacity) {
    T* new_data = _allocator.allocate(_capacity * 2 + _capacity == 0);

    for (size_t i = 0; i < _size; i++) new_data[i] = _data[i];
    _allocator.deallocate(_data, _capacity);
    _capacity *= 2;
    _data = new_data;
  }

  _data[_size] = value;
  _size++;
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back(T&& value) {
  if (_size >= _capacity) {
    T* new_data = _allocator.allocate(_capacity * 2 + _capacity == 0);

    for (size_t i = 0; i < _size; i++) new_data[i] = _data[i];
    _allocator.deallocate(_data, _capacity);
    _capacity *= 2;
    _data = new_data;
  }

  _data[_size] = std::move(value);
  _size++;
}

template <class T, class Allocator>
void vector<T, Allocator>::shrink_to_fit() noexcept {
  _allocator.deallocate(_data + _size, _capacity - _size);
  _capacity = _size;
}

template <class T, class Allocator>
T& s21::vector<T, Allocator>::operator[](size_type i) const {
  if (i >= _size) throw "Invalid vector index";
  return _data[i];
}

template <class T, class Allocator>
T s21::vector<T, Allocator>::operator[](size_type i) {
  if (i >= _size) throw "Invalid vector index";
  return _data[i];
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& v) noexcept {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);

  _data = v._data;
  _size = v._size;
  _capacity = v._capacity;

  v._data = nullptr;
  v._size = 0;
  v._capacity = 0;
  return *this;
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& v) {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);
  _size = v._size;
  _capacity = v._capacity;

  _data = _allocator.allocate(_capacity);
  for (size_t i = 0; i < _size; i++) _data[i] = v._data[i];

  return *this;
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(
    std::initializer_list<value_type> ilist) {
  return *this;
}

}  // namespace s21
#endif

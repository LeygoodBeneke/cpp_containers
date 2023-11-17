#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#define DEFAULT_CAPACITY 1

#include <memory>

namespace s21 {

template <class T, class Allocator = std::allocator<T>>
class vector {
 public:
  vector()
      : _allocator(std::allocator<T>()), _size(0), _capacity(DEFAULT_CAPACITY) {
    _data = _allocator.allocate(_capacity);
  }

  vector(unsigned size) : _size(size), _capacity(2 * size) {
    _data = _allocator.allocate(_capacity);
  }

  vector(vector&& victor) noexcept; // +-
  vector(vector& victor); // +-

  ~vector() {  // +
    for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
    _allocator.deallocate(_data, _capacity);
  }

  inline unsigned size() const noexcept { return _size; }          // +
  inline unsigned capacity() const noexcept { return _capacity; }  // +
  inline bool empty() const noexcept { return _size == 0; }        // +

  inline T back();         // +
  inline T& back() const;  // +

  inline T front();         // +
  inline T& front() const;  // +

  void push_back(const T& value);  // +
  void push_back(T&& value);       // +

  inline void pop_back();  // +

  inline T* begin() const noexcept { return _data; }        // +
  inline T* end() const noexcept { return _data + _size; }  // +
                                                            
  void shrink_to_fit() noexcept; // +

  T& operator[](unsigned int i) const;  // +
  T operator[](unsigned int i);         // +

 private:
  Allocator _allocator;
  T* _data;
  unsigned _size;
  unsigned _capacity;
};

template <class T, class Allocator>
vector<T, Allocator>::vector(vector&& victor) noexcept {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);

  _allocator = victor._allocator;
  _data = victor._data;
  _size = victor._size;
  _capacity = victor._capacity;

  victor._data = nullptr;
  victor._size = 0;
  victor._capacity = 1;
}

template <class T, class Allocator>
vector<T, Allocator>::vector(vector& victor) {
  for (size_t i = 0; i < _size; i++) _allocator.destroy(_data + i);
  _allocator.deallocate(_data, _capacity);
  _allocator = victor._allocator;
  _size = victor._size;
  _capacity = victor._capacity;

  _data = _allocator.allocate(_capacity);
  for (size_t i = 0; i < _size; i++) _data[i] = victor._data[i];
}

template <class T, class Allocator>
T vector<T, Allocator>::back() {
  if (_size == 0) throw "size is equal to zero";
  return _data[_size - 1];
}

template <class T, class Allocator>
T& vector<T, Allocator>::back() const {
  if (_size == 0) throw "size is equal to zero";
  return _data[_size - 1];
}

template <class T, class Allocator>
T vector<T, Allocator>::front() {
  if (_size == 0) throw "size is equal to zero";
  return *_data;
}

template <class T, class Allocator>
T& vector<T, Allocator>::front() const {
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
void vector<T, Allocator>:: shrink_to_fit() noexcept {
    _allocator.deallocate(_data + _size, _capacity - _size);
    _capacity = _size;
}

template <class T, class Allocator>
T& s21::vector<T, Allocator>::operator[](unsigned int i) const {
  if (i >= _size) throw "Invalid vector index";
  return _data[i];
}

template <class T, class Allocator>
T s21::vector<T, Allocator>::operator[](unsigned int i) {
  if (i >= _size) throw "Invalid vector index";
  return _data[i];
}

}  // namespace s21
#endif

#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
 public:
  Deque() : map_(new T*[initial_capacity]), map_size_(initial_capacity),
            head_(initial_capacity / 2), tail_(initial_capacity / 2), size_(0) {}

  ~Deque() {
    if (map_) {
      for (size_t i = 0; i < map_size_; ++i) {
        delete[] map_[i];
      }
      delete[] map_;
    }
  }

  Deque(const Deque& other) : map_(new T*[other.map_size_]),
                               map_size_(other.map_size_), head_(other.head_),
                               tail_(other.tail_), size_(other.size_) {
    for (size_t i = 0; i < map_size_; ++i) {
      map_[i] = new T[block_size];
      if (i >= head_ / block_size && i <= tail_ / block_size) {
        size_t start = (i == head_ / block_size) ? head_ % block_size : 0;
        size_t end = (i == tail_ / block_size) ? tail_ % block_size + 1 : block_size;
        size_t other_block_index = i - (head_ / block_size) + (other.head_ / block_size);
        for (size_t j = start; j < end; ++j) {
          map_[i][j] = other.map_[other_block_index][j];
        }
      }
    }
  }

  Deque& operator=(const Deque& other) {
    if (this == &other) {
      return *this;
    }

    for (size_t i = 0; i < map_size_; ++i) {
      delete[] map_[i];
    }
    delete[] map_;

    map_ = new T*[other.map_size_];
    map_size_ = other.map_size_;
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    for (size_t i = 0; i < map_size_; ++i) {
      map_[i] = new T[block_size];
      if (i >= head_ / block_size && i <= tail_ / block_size) {
        size_t start = (i == head_ / block_size) ? head_ % block_size : 0;
        size_t end = (i == tail_ / block_size) ? tail_ % block_size + 1 : block_size;
        size_t other_block_index = i - (head_ / block_size) + (other.head_ / block_size);
        for (size_t j = start; j < end; ++j) {
          map_[i][j] = other.map_[other_block_index][j];
        }
      }
    }
    return *this;
  }

  void push_back(const T& value) {
    if ((tail_ + 1) % (map_size_ * block_size) == head_) {
      reallocate(map_size_ * 2);
    }
    size_t block_index = tail_ / block_size;
    size_t index_in_block = tail_ % block_size;
    if (!map_[block_index]) {
      map_[block_index] = new T[block_size];
    }
    map_[block_index][index_in_block] = value;
    tail_ = (tail_ + 1) % (map_size_ * block_size);
    ++size_;
  }

  void push_front(const T& value) {
    if (head_ == 0) {
      reallocate(map_size_ * 2);
      head_ = map_size_ * block_size;
      tail_ = (tail_ + map_size_ * block_size) % (map_size_ * block_size);
    }
    --head_;
    size_t block_index = head_ / block_size;
    size_t index_in_block = head_ % block_size;
    if (!map_[block_index]) {
      map_[block_index] = new T[block_size];
    }
    map_[block_index][index_in_block] = value;
    ++size_;
  }

  T pop_back() {
    if (empty()) {
      throw std::out_of_range("Deque is empty");
    }
    --tail_;
    --size_;
    size_t block_index = tail_ / block_size;
    size_t index_in_block = tail_ % block_size;
    return map_[block_index][index_in_block];
  }

  T pop_front() {
    if (empty()) {
      throw std::out_of_range("Deque is empty");
    }
    T value = map_[head_ / block_size][head_ % block_size];
    head_ = (head_ + 1) % (map_size_ * block_size);
    --size_;
    return value;
  }

  size_t size() const { return size_; }
  size_t capacity() const { return map_size_ * block_size; }
  bool empty() const { return size_ == 0; }

 private:
  static const size_t initial_capacity = 4;
  static const size_t block_size = 64;
  T** map_;
  size_t map_size_;
  size_t head_;
  size_t tail_;
  size_t size_;

  void reallocate(size_t new_map_size) {
    T** new_map = new T*[new_map_size];
    size_t new_head = (new_map_size * block_size) / 4;
    size_t new_tail = new_head + size_;

    for (size_t i = 0; i < new_map_size; ++i) {
      new_map[i] = nullptr;
    }

    for (size_t i = 0; i < size_; ++i) {
      size_t old_index = (head_ + i) % (map_size_ * block_size);
      size_t new_block_index = (new_head + i) / block_size;
      size_t new_index_in_block = (new_head + i) % block_size;
      size_t old_block_index = old_index / block_size;
      size_t old_index_in_block = old_index % block_size;

      if (!new_map[new_block_index]) {
        new_map[new_block_index] = new T[block_size];
      }
      new_map[new_block_index][new_index_in_block] = map_[old_block_index][old_index_in_block];
    }

    for (size_t i = 0; i < map_size_; ++i) {
      delete[] map_[i];
    }
    delete[] map_;

    map_ = new_map;
    map_size_ = new_map_size;
    head_ = new_head;
    tail_ = new_tail;
  }
};
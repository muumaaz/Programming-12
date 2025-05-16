#include "string.hpp"
#include <cstring>

String::String() : size_(0), capacity_(0), object_(nullptr) {}

String::String(size_t size, char character)
    : object_(new char[size + 1]), size_(size), capacity_(size) {
  for (size_t i = 0; i < size; ++i) {
    object_[i] = character;
  }
  object_[capacity_] = '\0';
}

String::String(const char* str)
    : object_(new char[strlen(str) + 1]),
      size_(strlen(str)),
      capacity_(strlen(str)) {
  for (size_t i = 0; i < size_; ++i) {
    object_[i] = str[i];
  }
  object_[capacity_] = '\0';
}

String::String(const String& str)
    : object_(new char[str.Size() + 1]),
      size_(str.Size()),
      capacity_(str.Size()) {
  for (size_t i = 0; i < str.Size(); ++i) {
    object_[i] = str.Data()[i];
  }
  object_[capacity_] = '\0';
}

String::~String() { delete[] object_; }

String& String::operator=(const String& str) {
  if (this == &str) {
    return *this;
  }
  delete[] object_;
  size_ = str.size_;
  capacity_ = str.capacity_;
  object_ = new char[capacity_ + 1];
  object_[size_] = '\0';
  for (size_t i = 0; i < size_; ++i) {
    object_[i] = str.object_[i];
  }
  return *this;
}

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

void String::PushBack(char character) {
  if (capacity_ == 0) {
    capacity_ = 1;
    object_ = new char[2];
  }
  if (capacity_ == size_) {
    char* object_copy = new char[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
      object_copy[i] = object_[i];
    }
    delete[] object_;
    object_ = new char[capacity_ * 2 + 1];
    for (size_t i = 0; i < capacity_; ++i) {
      object_[i] = object_copy[i];
    }
    capacity_ = capacity_ * 2;
    delete[] object_copy;
    object_[size_] = '\0';
  }
  object_[size_++] = character;
  object_[size_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap <= capacity_) {
    return;
  }
  char* object_copy = new char[capacity_];
  for (size_t i = 0; i < capacity_; ++i) {
    object_copy[i] = object_[i];
  }
  delete[] object_;
  object_ = new char[new_cap + 1];
  for (size_t i = 0; i < capacity_; ++i) {
    object_[i] = object_copy[i];
  }
  capacity_ = new_cap;
  delete[] object_copy;
  object_[size_] = '\0';
}

char& String::operator[](size_t i) { return object_[i]; }

const char& String::operator[](size_t i) const { return object_[i]; }

std::ostream& operator<<(std::ostream& self, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    self << str[i];
  }
  return self;
}
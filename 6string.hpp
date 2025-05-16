#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>

class String {
 public:
  String();

  String(size_t size, char character);

  String(const char* str);

  String(const String& str);

  ~String();

  String& operator=(const String& str);

  void PushBack(char character);

  void Reserve(size_t new_cap);

  char& operator[](size_t i);

  const char& operator[](size_t i) const;

  [[nodiscard]] size_t Size() const;

  [[nodiscard]] size_t Capacity() const;

  [[nodiscard]] const char* Data() const;

  [[nodiscard]] char* Data();

  friend std::ostream& operator<<(std::ostream& self, const String& str);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* object_ = nullptr;
};
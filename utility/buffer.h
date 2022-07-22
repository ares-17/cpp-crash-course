#include <cstddef>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

struct Buffer {

  Buffer(int size, std::string name)
      : size{size}, pos{0}, name{name}, buffer{new int[size]} {}

  // copy constructor
  Buffer(const Buffer &other) : Buffer(other.size, other.name){};

  // move constructor
  Buffer(Buffer &&other) noexcept
      : pos{other.pos}, name{other.name}, buffer{other.buffer},
        size{other.size} {
    other.buffer = nullptr;
    other.size = 0;
    other.pos = 0;
    other.name = "Unnamed";
  };

  ~Buffer() {
    delete[] this->buffer;
    std::cout << std::endl << "GoodBye";
  }

  void next_value(int value) {
    if (this->pos == size) {
      throw std::length_error{"errore di lunghezza"};
    }

    this->buffer[pos] = value;
    this->pos++;
  }

  void changeAt(int index, int value) {
    if (index > size)
      throw std::length_error{"errore di lunghezza"};

    this->buffer[index] = value;
  }

  void const printBuffer() {
    std::cout << std::endl << name << " : ";
    for (auto index = 0; index < size; index++) {
      std::cout << buffer[index];
    }
    std::cout << " , pos " << this->pos;
    std::cout << " , size " << this->size << std::endl;
  }

protected:
  int *buffer;
  int size;
  int pos;
  std::string name;
  Buffer(int pos) : pos{0} {};
};
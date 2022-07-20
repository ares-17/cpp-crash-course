#include "../utility/buffer.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <utility>

struct MoveAssignment : Buffer {
  MoveAssignment(int size, std::string name = "Unnamed") : Buffer(size, name){};
  MoveAssignment(const MoveAssignment &other) = delete;
  MoveAssignment &operator=(const MoveAssignment &other) = delete;

  MoveAssignment &operator=(MoveAssignment &&other) {
    if (this == &other)
      return *this;

    delete[] buffer;
    this->pos = other.pos;
    this->size = other.size;
    this->name = other.name;
    this->buffer = other.buffer;

    other.pos = 0;
    other.buffer = new int[0];
    other.name = "Unnamed";
    other.size = 0;
    return *this;
  }
};

int main() {
  MoveAssignment ma{5, "first"};
  ma.next_value(8);

  ma.printBuffer();
  MoveAssignment ma1{3};
  ma1 = std::move(ma);
  std::cout << "After move assignment...";

  ma.printBuffer();
  ma1.printBuffer();
}
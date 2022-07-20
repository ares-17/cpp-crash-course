#include "../utility/buffer.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

/*
    L'esempio mostra un esempio di definizione di un costruttore di copia.
    Nel caso in cui questo non fosse definito utilizzando quello di default
    ci sarebbe un'eccezione. L'eccezione viene generata visto che tutti gli
   elementi sono inseriti in un unico array.
*/

struct CopyExample : Buffer {

  CopyExample(int size, std::string name = "Unnamed") : Buffer(size, name) {}

  // rispetta i principi di indipendenza ed equivalenza ?
  CopyExample(const CopyExample &other) : Buffer(other) {
    for (auto index = 0; index < size; index++) {
      buffer[index] = other.buffer[index];
    }
  }
};

int main() {
  CopyExample ce{3};
  ce.next_value(1);
  ce.next_value(2);

  CopyExample ce1{ce};

  std::cout << "Are identical :";
  ce.printBuffer();
  ce1.printBuffer();

  std::cout << "After some changes...";

  ce1.next_value(3);
  ce.changeAt(0, 8);

  ce.printBuffer();
  ce1.printBuffer();
}
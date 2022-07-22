#include "../utility/buffer.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

/*
    L'operazione di copia porta con se' vari side-effect come :
        1. Il valore precedente della destinazione può non esser esplicitamente
            deallocato e può causare memory leak , come nel caso precedente dove
            è presente una referenza ad un array ( variabile dinamica ) ;
        2. Se la sorgente ha membri di tipo referenze , come nell’esempio ,
            allora sia sorgente che destinazione punteranno allo stesso spazio
   di memoria , causando probabilmente il bug double free.

    RICORDA di allocare prima l'oggetto di destinazione dell'operazione !
*/
struct CopyAssignment : Buffer {

  CopyAssignment(int size, std::string name) : Buffer(size, name) {}

  CopyAssignment &operator=(const CopyAssignment &other) {
    if (this == &other)
      return *this;

    const auto new_buffer = new int[other.size];
    delete[] this->buffer;
    buffer = new_buffer;
    pos = other.pos;
    size = other.size;

    for (auto index = 0; index < size; index++) {
      buffer[index] = other.buffer[index];
    }
    return *this;
  }
};

int main() {
  CopyAssignment ca{5, "A"};
  ca.next_value(2);
  ca.next_value(5);
  ca.printBuffer();

  CopyAssignment ca1{2, "B"};
  ca1 = ca;
  std::cout << "On copy assignment ...";
  ca1.printBuffer();

  ca1.next_value(7);
  std::cout << "After some changes...";
  ca.printBuffer();
  ca1.printBuffer();
}
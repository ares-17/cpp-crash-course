#include <iostream>

struct BaseInterface {
  // virtual non obbliga l'implementazione , piuttosto permette l'override
  virtual ~BaseInterface() = default;
  virtual void optionalImplementation() {
    std::cout << "Optional implementation method in BaseInterface" << std::endl;
  };
  virtual void implementationRequired() = 0;
};

struct DerivedClass : BaseInterface {
  void implementationRequired() override {
    std::cout << "Required" << std::endl;
  }
  ~DerivedClass() {
    // rimuovendo il distruttore di BaseInterface questo non verra' invocato
    std::cout << "GoodBye" << std::endl;
  }
};

int main() {
  DerivedClass dc{};
  dc.optionalImplementation();
  dc.implementationRequired();
}
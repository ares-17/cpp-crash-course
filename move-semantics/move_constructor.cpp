#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "../utility/buffer.h"

struct MoveConstructor : Buffer {
    MoveConstructor(int size , std::string name) : Buffer(size,  name){};
    MoveConstructor(const MoveConstructor& other) = delete;
    MoveConstructor(MoveConstructor&& other) : Buffer(std::move(other)){}
};

int main(){
    MoveConstructor mc {5, "first"};
    mc.next_value(2);
    mc.next_value(6);

    mc.printBuffer();

    MoveConstructor mc1 { std::move(mc) };
    std::cout << "After move constructor...";

    mc.printBuffer();
    mc1.printBuffer();
}
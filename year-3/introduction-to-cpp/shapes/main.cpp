/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include "rectangle.h"
#include "circle.h"

int main() {
    Rectangle ra(5, 10), rb(2, 3);
    Circle ca(5), cb(7);

    std::cout << ra << std::endl << rb << std::endl;
    std::cout << ca << std::endl << cb << std::endl;

    return 0;
}
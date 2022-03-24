/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#include "shape.h"

bool operator==(const Shape &a, const Shape &b) { return a.area() == b.area(); }

bool operator<(const Shape &a, const Shape &b) { return a.area() < b.area(); }

std::ostream &operator<<(std::ostream &stream, const Shape &shape) {
    shape.print(stream);
    return stream;
}
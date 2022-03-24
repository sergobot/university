/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#include <ostream>

#include "circle.h"

constexpr auto M_PI = 3.14159265358979323846;

const std::string Circle::common_name = "Circle";
size_t Circle::last_id = 0;

Circle::Circle(double r) : m_r(r), m_id(++last_id) {}

std::string Circle::name() const {
    return Circle::common_name;
}

double Circle::area() const {
    return M_PI * m_r * m_r;
}

size_t Circle::id() const {
    return m_id;
}

void Circle::print(std::ostream &stream) const {
    stream << name() << " #" << id() << " with the area of " << area() << " squares";
}
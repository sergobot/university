/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#include <ostream>

#include "rectangle.h"

const std::string Rectangle::common_name = "Rectangle";
size_t Rectangle::last_id = 0;

Rectangle::Rectangle(double w, double h) : m_w(w), m_h(h), m_id(++last_id) {
}

std::string Rectangle::name() const {
    return Rectangle::common_name;
}

double Rectangle::area() const {
    return m_h * m_w;
}

size_t Rectangle::id() const {
    return m_id;
}

void Rectangle::print(std::ostream &stream) const {
    stream << name() << " #" << id() << " with the area of " << area() << " squares";
}
/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#ifndef UNIVERSITY_RECTANGLE_H
#define UNIVERSITY_RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    static size_t last_id;
    static const std::string common_name;

    double m_w, m_h;
    size_t m_id;

public:
    Rectangle(double w, double h);

    std::string name() const override;

    double area() const override;

    size_t id() const override;

protected:
    void print(std::ostream &stream) const override;
};


#endif //UNIVERSITY_RECTANGLE_H

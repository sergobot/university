/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#ifndef UNIVERSITY_CIRCLE_H
#define UNIVERSITY_CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    static size_t last_id;
    static const std::string common_name;

    double m_r;
    size_t m_id;

public:
    Circle(double r);

    std::string name() const override;

    double area() const override;

    size_t id() const override;

protected:
    void print(std::ostream &stream) const override;
};


#endif //UNIVERSITY_CIRCLE_H

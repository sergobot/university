/* Copyright 2021, Sergey Popov (i@sergobot.com) */

#ifndef UNIVERSITY_SHAPE_H
#define UNIVERSITY_SHAPE_H

#include <string>

class Shape {
public:
    virtual ~Shape() = default;

    virtual std::string name() const = 0;

    virtual double area() const = 0;

    virtual size_t id() const = 0;

    friend std::ostream &operator<<(std::ostream &stream, const Shape &shape);

protected:
    virtual void print(std::ostream &stream) const = 0;
};


#endif //UNIVERSITY_SHAPE_H

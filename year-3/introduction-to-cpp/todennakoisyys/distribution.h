#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <vector>
#include <cstdlib>

/**
 * @brief The Distribution class is abstract to provide common interface for
 * several other distribution classes.
 */
template<typename TPoint>
class Distribution
{
public:
    virtual size_t size() const  = 0;
    virtual const TPoint& operator[](size_t i) const = 0;
};

#endif // DISTRIBUTION_H

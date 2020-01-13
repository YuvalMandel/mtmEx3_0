//
// Created by jonathan_pc on 1/12/2020.
//

//
// Created by jonathan_pc on 1/12/2020.
//
#include "UniqueArray.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <cmath>

class integer{
private:
    double x;
public:
    explicit integer(double x) : x(x){}
    bool operator==(const integer& integer) const {
        return (integer.x == this->x);
    }
};

struct CompareIntP {
    bool operator() (const int* p1, const int* p2) const {
        return (*p1 == *p2);
    }
};



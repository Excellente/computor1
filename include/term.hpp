#ifndef TERM_H
#define TERM_H

#include "common.hpp"

class Term{
    private:
        int _sign;
        int _flag;
        char _base;
        float _coeff;
        float _exponent;

    public:
        Term();
        ~Term();
        float abs(float x);
        Term &operator+(const Term &rhs);
        Term &operator=(const Term &rhs);
};

#endif
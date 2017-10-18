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
        void toString();
        float abs(float x);

        char getBase();
        float getExponent();
        float getCoefficient();
        void setBase(char s);
        void setExponent(float e);
        void setCoefficient(float f);

        Term &operator+(const Term &rhs);
        Term &operator=(const Term &rhs);
};

#endif
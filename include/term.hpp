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
        ~Term();
        Term(int sign);
        void toString();
        float abs(float x);

        int getSign();
        char getBase();
        float getExponent();
        float getCoefficient();
        void setSign(int s);
        void setBase(char b);
        void setExponent(float e);
        void setCoefficient(float f);

        Term &operator+(const Term &rhs);
        Term &operator=(const Term &rhs);
        void operator+=(const Term &rhs);
};

#endif
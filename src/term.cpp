#include "term.hpp"

Term::~Term(){}

float Term::abs(float x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

Term::Term()
{
    _flag = 0;
    _sign = 0;
    _base = 'b';
    _coeff = 0.0f;
    _exponent = 0.0f;
}

Term &Term::operator=(const Term &rhs)
{
    _sign = rhs._sign;
    _flag = rhs._flag;
    _base = rhs._base;
    _coeff = rhs._coeff;
    _exponent = rhs._exponent;
    return (*this);
}

Term &Term::operator+(const Term &rhs)
{
    if (_sign == rhs._sign)
    {
        _coeff += rhs._coeff;
        if (_coeff == 0)
            _sign = 0;
    }
    else
    {
        _coeff -= rhs._sign;
        if (_coeff < 0)
        {
            _coeff = abs(_coeff);
            _sign = 1;
        }
        else
            _sign = 0;
    }
    return (*this);
}
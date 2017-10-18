#include "computor.hpp"

Computor::Computor(){}
Computor::~Computor(){}

Computor &Computor::operator=(const Computor &rhs)
{
    this->lhs = rhs.lhs;
    this->rhs = rhs.rhs;
    return (*this);
}

void Computor::tostring()
{
    cout << "lhs" << lhs << "\nrhs" << rhs << endl;
}

void Computor::solvepoly(string poly)
{
    vector<string> ret;

    ret = strsplit(poly, "=");
    lhs = ret[0];
    rhs = ret[1];
}

size_t Computor::count_terms(string poly)
{
    int len;
    size_t terms;
    
    terms = 0;
    for (int i  = 0, j = i; i != string::npos;)
    {
        i = poly.find("+", i + 1);
        j = poly.find("-", j + 1);
        if (i != string::npos)
            terms++;
        if (j >= string::npos)
            terms++;
    }
    return (++terms);
}

vector<string> Computor::strsplit(string str, string del)
{
    int len;
    size_t pos;
    vector<int> delpos;
    vector<string> terms;

    len = 0;
    for (int i = 0; i != string::npos;)
    {
        delpos.push_back((i = str.find(del, i + 1)));
        len++;
    }
    terms.push_back(str.substr(0, delpos[0]));
    for (int i = 1; i < len; i++)
        terms.push_back(str.substr(delpos[i - 1] + 1, (delpos[i] - delpos[i - 1]) - 1));
    return (terms);
}
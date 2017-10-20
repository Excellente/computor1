#include "computor.hpp"

Computor::Computor(string exp) : _exp(exp){
    vector<string> ret;

    ret = strsplit("=");
    _reduced = "";
    _lhs = ret[0];
    _rhs = ret[1];
}

Computor::~Computor(){
}

Computor &Computor::operator=(const Computor &rhs)
{
    this->_lhs = rhs._lhs;
    this->_rhs = rhs._rhs;
    return (*this);
}

void Computor::tostring()
{
    cout << "lhs = " << _lhs << "\nrhs = " << _rhs <<
    "\nreduced form = " << _reduced << endl;
}

void Computor::solvepoly()
{
}

void Computor::assign_term(string p, Term *t)
{
    string::size_type sz;

    t->setCoefficient(stof(p, &sz));
    sz = p.find("^") + 1;
    t->setExponent(stof(p.substr(sz, 4), &sz));
    sz = p.find("^") - 1;
    t->setBase(p.substr(sz, 2)[0]);
}

void Computor::getTerm(string p, string &t, int &last, int &first, int &test)
{
    while (p[last] != '+' && p[last] != '-' && p[last] != '\0')
        last++;
    t = p.substr(first, last - first);
    last++;
    first = last;
    test += 1;
}

void Computor::_sign(int last, int &sign)
{
    if (last > 0)
    {
        if (_lhs[last - 1] == '+')
            sign = 0;
        else if (_lhs[last - 1] == '-')
            sign = 1;
    }
}

void Computor::groupLikeTerms(string p)
{
    Term *t;
    string tmp;
    vector<Term> exp_terms;
    
    int sign = 0;
    int test = 0;
    int last;
    int first;
    
    while (_lhs[last] != '\0')
    {
        _sign(last, sign);
        t = new Term(sign);
        getTerm(_lhs, tmp, last, first, test);
        assign_term(tmp, t);
        exp_terms.push_back(*t);
    }
    exp_terms[1].toString();
}

size_t Computor::count_terms(string exp)
{
    int len;
    size_t terms;
    
    terms = 0;
    for (int i  = 0, j = i; i != string::npos;)
    {
        i = exp.find("+", i + 1);
        j = exp.find("-", j + 1);
        if (i != string::npos)
            terms++;
        if (j >= string::npos)
            terms++;
    }
    return (++terms);
}

vector<string> Computor::strsplit(string del)
{
    int len;
    size_t pos;
    vector<int> delpos;
    vector<string> terms;

    len = 0;
    for (int i = 0; i != string::npos;)
    {
        delpos.push_back((i = _exp.find(del, i + 1)));
        len++;
    }
    terms.push_back(_exp.substr(0, delpos[0]));
    for (int i = 1; i < len; i++)
        terms.push_back(_exp.substr(delpos[i - 1] + 1, (delpos[i] - delpos[i - 1]) - 1));
    return (terms);
}

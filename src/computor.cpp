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

// void Computer::groupLikeTerms()
// {
    
// }

void Computor::assign_term(string p, Term *t)
{
    string::size_type sz;

    t->setCoefficient(stof(p, &sz));
    sz = p.find("^") + 1;
    t->setExponent(stof(p.substr(sz, 4), &sz));
    sz = p.find("^") - 1;
    t->setBase(p.substr(sz, 2)[0]);
}

void Computor::getTerm(string p, string &t)
{
    static int last = 0;
    static int first = 0;

    while (1 && p[last] != '\0')
    {
        last++;
    }
    t = p.substr(first, last - first);
    cout << last << endl;
    first = last;
}

void Computor::groupLikeTerms(string p)
{
    size_t i;
    size_t j;
    string tmp;
    Term t = Term();

    // for (int i = 0; i < _exp.length(); i++)
    // {
        i = _exp.find("+", i + 1);
        j = _exp.find("-", j + 1);
        getTerm(_exp, tmp);
    //     if (_exp[i] == '+')
    //     {
    //         tmp = _exp.substr(0, i - 1);
    //         break;
    //     }
    // }
    // assign_term(_exp, &t);
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
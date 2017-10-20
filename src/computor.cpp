#include "computor.hpp"

Computor::Computor(string exp) : _exp(exp){
    vector<string> ret;

    ret = strsplit("=");
    _reduced = "";
    _lhs = ret[0];
    _rhs = ret[1];
    _h_power = 0;
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
    // if (_h_power > 2)
    transpose();
    addLikeTerms();
    cout << endl;
    cout << "*********** debugging ***************" << endl;
    for (int j = 0; j < 5; j++)
    {
        _exp_terms[j].toString();
        cout << " ";
    }
    cout << "\n*********** debugging ***************" << endl;    
}

void Computor::transpose()
{
    int sign = 0;

    stringToTerm(_exp_terms, _lhs, sign, 0);
    stringToTerm(_exp_terms, _rhs, sign, 1);
}

void Computor::addLikeTerms()
{
    int len = get_termslen();
    float zexp = _exp_terms[0].getExponent();
    
    for (int i = 0; i < len; i++)
    {
        for (int j = i; j < len; j++)
        {
            if (j != 0 && (zexp == _exp_terms[j].getExponent()))
            {
                _exp_terms[j].toString();
                //cout << _exp_terms[0].getExponent() << " = " << _exp_terms[j].getExponent() << endl;
                _exp_terms[0] += _exp_terms[j];
                cout << endl << "i = " << i << " | j = " << j << endl;
            }
        }
    }
}

void Computor::assign_term(string p, Term *t)
{
    string::size_type sz;

    t->setCoefficient(stof(p, &sz));
    sz = p.find("^") + 1;
    t->setExponent(stof(p.substr(sz, 4), &sz));
    sz = p.find("^") - 1;
    if (_h_power < t->getExponent())
        _h_power = t->getExponent();
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

void Computor::_sign(string _e, int last, int &sign)
{
    if (last > 0)
    {
        if (_e[last - 1] == '+')
            sign = 0;
        else if (_e[last - 1] == '-')
            sign = 1;
    }
}

void Computor::stringToTerm(vector<Term> &v, string _e, int &sign, int f)
{
    Term *t;
    int last;
    int first;
    string tmp;
    int test = 0;
    
    last = first = 0;
    while (_e[last] != '\0')
    {
        _sign(_e, last, sign);
        if (f)
            sign = ~sign;
        t = new Term(sign);
        getTerm(_e, tmp, last, first, test);
        assign_term(tmp, t);
        v.push_back(*t);
    }
}

size_t Computor::get_termslen()
{
    return (count_terms(_lhs) + count_terms(_rhs));
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

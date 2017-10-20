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
    int len = count_terms();

    cout << "lhs = " << _lhs << "\nrhs = " << _rhs <<
    "\nreduced form = " << _reduced << endl << endl;
    for (int i = 0; i < len; i++)
    {
        _exp_terms[i].toString();
        cout << " ";
    }
    cout << endl;
}

void Computor::solvepoly()
{
    transpose();    
    if (_h_power > 2)
        cout << "The polynomial is of order > 2";
    else
        addLikeTerms();
}

void Computor::transpose()
{
    int sign = 0;

    stringToTerm(_lhs, sign, 0);
    stringToTerm(_rhs, sign, 1);
}

void Computor::stringToTerm(string _e, int &sign, int f)
{
    Term *t;
    int last;
    int first;
    string tmp;
    
    last = first = 0;
    while (_e[last] != '\0')
    {
        _sign(_e, last, sign);
        if (f)
            sign = ~sign;
        t = new Term(sign);
        getTerm(_e, tmp, last, first);
        assign_term(tmp, t);
        _exp_terms.push_back(*t);
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

void Computor::getTerm(string p, string &t, int &last, int &first)
{
    while (p[last] != '+' && p[last] != '-' && p[last] != '\0')
        last++;
    t = p.substr(first, last - first);
    if (p[last] != '\0')
        last++;
    first = last;
}

void Computor::printTerms()
{
    int len = count_terms();

    for (int j = 0; j < len; j++)
    {
        _exp_terms[j].toString();
        cout << " ";
    }
    cout << endl;
}

void Computor::addLikeTerms()
{
    int len = count_terms();
    vector<Term>::iterator tmp;
    vector<Term>::iterator evi = _exp_terms.end();
    vector<Term>::iterator bvi = _exp_terms.begin();

    // printTerms();
    for (int i = 0; i < len; i++)
    {
        tmp = bvi + 1;
        cout << "start iteration" << endl;
        for (int j = i; j < len; j++)
        {
            tmp->toString();cout << " <-> expo =" << tmp->getExponent() << endl<< endl;
            if (tmp != bvi && (bvi->getExponent() == tmp->getExponent()))
            {
                cout << "hit: "; tmp->toString();cout << endl<< endl;
                len = count_terms();
                *bvi = *bvi + *tmp;
                _exp_terms.erase(tmp);
            }
            tmp++;
        }
        cout << "end iteration" << endl;
        bvi++;
    }
    // printTerms();
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

size_t Computor::count_terms()
{
    size_t terms;
    vector<Term>::iterator evi = _exp_terms.end();
    vector<Term>::iterator bvi = _exp_terms.begin();

    terms = 0;
    while (bvi != evi)
    {
        bvi++;
        terms++;
    }
    return (terms);
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

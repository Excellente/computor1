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

void Computor::toString()
{
    int len = count_terms(_exp_terms);

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
    addLikeTerms();
    find_ABC();
    if (_h_power == 1)
        solvelinear();
    else if (_h_power == 2)
        quadraticForm();
    output();
}

void Computor::transpose()
{
    int sign;

    sign = 0;
    stringToTerm(_lhs, sign, 0);
    sign = 0;
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
        if (f == 1)
        {
            if (sign == 1)
                sign = 0;
            else
                sign = 1;
        }
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

void Computor::printTerms(vector<Term> v)
{
    int len = count_terms(v);

    for (int j = 0; j < len; j++)
    {
        v[j].toString();
        cout << " ";
    }
    cout << endl;
}

bool Computor::ignore(vector<float> del, float _exp)
{
    vector<float>::iterator bvi = del.begin();
    vector<float>::iterator evi = del.end();

    for (; bvi != evi; bvi++)
    {
        if (_exp == *bvi)
            return (true);
    }
    return (false);
}

void Computor::addLikeTerms()
{
    vector<Term> lt;
    vector<float> ig;
    v_iter_t evi = _exp_terms.end();
    v_iter_t bvi = _exp_terms.begin();

    for (; bvi != evi;)
    {
        if (!ignore(ig, bvi->getExponent()))
        {
            reduce(lt, bvi, evi);
            ig.push_back(bvi->getExponent());
        }
        bvi++;
    }
    _exp_terms = lt;
}

void Computor::find_ABC()
{
    v_iter_t evi = _exp_terms.end();
    v_iter_t bvi = _exp_terms.begin();

    for (; bvi != evi; bvi++)
    {
        if (bvi->getSign() == 1)
            _CBA.push_back(bvi->getCoefficient() * -1);
        else
            _CBA.push_back(bvi->getCoefficient());
        if (_h_power < bvi->getExponent() && bvi->getCoefficient() != 0)
            _h_power = bvi->getExponent();
    }
}

void Computor::solvelinear()
{
    float c = _CBA[0] * -1;
    float b = _CBA[1];

    _sol1 = c / b;
}

void Computor::quadraticForm()
{
    float negb;
    float rootd;
    float denom;

    _discrimi = pow(_CBA[1], 2.0f) - 4 * _CBA[2] * _CBA[0];
    negb = -_CBA[1];
    rootd = sqrt(_discrimi);
    denom = 2 * _CBA[2];
    if (_discrimi > 0)
    {
        _sol1 = (negb + rootd) / denom;
        _sol2 = (negb - rootd) / denom;
    }
    else if (_discrimi == 0)
        _sol1 = negb / denom;
    else;
}

void Computor::output()
{
    string tmp;
    v_iter_t evi = _exp_terms.end();
    v_iter_t bvi = _exp_terms.begin();

    cout << "Reduced Form: ";
    for (; bvi != evi; bvi++)
    {
        if (bvi->getSign() == 1)
            cout << " - ";
        else
            if (bvi != _exp_terms.begin())
                cout << " + ";
        bvi->toString();
    }
    cout << " = 0" << endl;
    cout << "Polynomial Degree: " << _h_power << endl;
    if (_h_power == 0 && _exp_terms[0].getCoefficient() == 0)
        cout << "The solution is:\nX ∈ ℝ, ∀ X != 0\n";
    else if (_h_power == 0 && _exp_terms[0].getCoefficient() != 0)
        cout << "No Solution\n";
    else if (_h_power == 1)
        cout << "The Solution is:\n" << _sol1 << endl;
    else if (_h_power == 2)
    {
        if (_discrimi > 0)
        {
            cout << "The Solutions are: " << endl;
            cout << _sol1 << "\n" << _sol2 << endl;
        }
        else if (_discrimi == 0)
            cout << "The Solution is:\n" << _sol1 << endl;
        else
            cout << "No Real Solution" << endl;
    }
    else if (_h_power > 2)
        cout << "Can't solve polynomial of order > 2" << endl;

}

void Computor::reduce(vector<Term> &lt, v_iter_t bvi, v_iter_t evi)
{
    static int i;
    v_iter_t tmp;
    v_iter_t prev;

    lt.push_back(*bvi);
    for (tmp = bvi + 1; tmp != evi;)
    {
        if (bvi->getExponent() == tmp->getExponent())
            lt[i] = lt[i] + *tmp;
        tmp++;
    }
    i++;
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

template <class T>
size_t Computor::count_terms(vector<T> v)
{
    size_t terms;
    typename vector<T>::iterator evi = v.end();
    typename vector<T>::iterator bvi = v.begin();

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

const char *TermFormatException::what() const throw()
{
    return ("WrongTermFormat");
}

void Computor::checkTermFormat(Term &t)
{
    TermFormatException tfe;

    if (t.getExponent() < 0.0f)
        throw tfe;
    // else if ()
        throw tfe;
}
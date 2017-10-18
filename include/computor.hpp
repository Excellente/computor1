#ifndef COMPV1_H
#define COMPV1_H

#include "term.hpp"
#include "common.hpp"

class Computor{

    private:
        string _rhs;
        string _lhs;
        string _exp;
        string _reduced;
        vector<Term> trm;

    public:
        ~Computor();
        void tostring();
        void solvepoly();
        void transpose();
        Computor(string exp);
        void getTerm(string p);
        size_t count_terms(string exp);
        void assign_term(string p, Term t);
        vector<string> strsplit(string del);
        Computor& operator=(const Computor &rhs);
    };

#endif
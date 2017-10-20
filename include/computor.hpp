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
        vector<Term> _exp_term;

    public:
        ~Computor();
        Computor(string exp);

        size_t count_terms(string exp);
        vector<string> strsplit(string del);
        Computor& operator=(const Computor &rhs);
        
        void tostring();
        void solvepoly();
        void transpose();
        void _sign(int last, int &sign);        
        void assign_term(string p, Term *t);
        void groupLikeTerms(string p);        
        void getTerm(string p, string &t, int &l, int &f, int &s);
    };

#endif
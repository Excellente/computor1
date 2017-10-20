#ifndef COMPV1_H
#define COMPV1_H

#include "term.hpp"
#include "common.hpp"

class Computor{

    private:
        string _rhs;
        string _lhs;
        string _exp;
        int _h_power;
        string _reduced;
        vector<Term> _exp_terms;

    public:
        ~Computor();
        Computor(string exp);

        size_t get_termslen();
        size_t count_terms(string exp);
        vector<string> strsplit(string del);
        Computor& operator=(const Computor &rhs);

        void tostring();
        void solvepoly();
        void transpose();
        void _sign(string _e, int last, int &sign);
        void assign_term(string p, Term *t);
        void addLikeTerms();
        void getTerm(string p, string &t, int &l, int &f, int &s);
        void stringToTerm(vector<Term> &v, string _e, int &sign, int f);
    };

#endif
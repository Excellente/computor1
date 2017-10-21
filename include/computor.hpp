#ifndef COMPV1_H
#define COMPV1_H

#include "term.hpp"
#include "common.hpp"

typedef vector<Term>::iterator v_iter_t;

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
        Computor(string e);

        size_t count_terms(vector<Term> v);
        vector<string> strsplit(string d);
        Computor& operator=(const Computor &r);
        
        void simplify();        
        void toString();
        void solvepoly();
        void transpose();
        void deleteN(vector<int> del);
        void printTerms(vector<Term> v);
        void _sign(string e, int l, int &s);
        void assign_term(string p, Term *t);
        void addLikeTerms();
        void getTerm(string p, string &t, int &l, int &f);
        void stringToTerm(string e, int &s, int f);
        void reduce(vector<Term> &lt, v_iter_t bvi, v_iter_t evi);        
    };

#endif
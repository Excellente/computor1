#ifndef COMPV1_H
#define COMPV1_H

#include "term.hpp"
#include "common.hpp"

typedef vector<Term>::iterator v_iter_t;

class TermFormatException : public std::exception{
    public:
        virtual const char * what() const throw();
};

class Computor{

    private:
        int _err;
        float _sol1;
        float _sol2;
        string _rhs;
        string _lhs;
        string _exp;
        int _h_power;
        string _reduced;
        float _discrimi;
        vector<float> _CBA;
        vector<Term> _exp_terms;

    public:
        ~Computor();
        Computor(string e);

        template <class T>
        size_t count_terms(vector<T> v);
        vector<string> strsplit(string d);
        Computor& operator=(const Computor &r);
        bool ignore(vector<float> del, float _exp);

        void lead_sign(string &p, int &_sign, int &last);
        void checkTermFormat(Term &t);        
        void output();
        void simplify();        
        void toString();
        void find_ABC();
        void solvepoly();
        void transpose();
        void solvelinear();
        void addLikeTerms();
        void quadraticForm();
        void debugmode(string d);
        void printTerms(vector<Term> v);
        void _sign(string &e, int &l, int &s);
        void assign_term(string p, Term *t);
        void stringToTerm(string e, int &s, int f);
        void getTerm(string p, string &t, int &l, int &f);
        void reduce(vector<Term> &lt, v_iter_t bvi, v_iter_t evi);
    };

#endif
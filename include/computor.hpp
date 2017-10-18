#ifndef COMPV1_H
#define COMPV1_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Computor{
    
    private:
        string rhs;
        string lhs;

    public:
        Computor();
        ~Computor();
        void tostring();
        void solvepoly(string poly);
        size_t count_terms(string poly);
        vector<string> strsplit(string str, string del);
        Computor& operator=(const Computor &rhs);
    };

#endif
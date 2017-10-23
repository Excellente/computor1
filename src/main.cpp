#include "computor.hpp"

int main(int argc, char *argv[])
{
    vector<string> str;
    Computor pcalc = Computor((string)argv[1]);

    if (argc == 2)
    {
        if (strcmp(argv[1], "") == 0)
            cout << "please enter poylynomial to solve\n";
        pcalc.solvepoly();
    }
    else if (argc == 3)
    {
        pcalc.solvepoly();
        pcalc.debugmode(argv[2]);
    }
    else
        cout << "exception not handled" << endl;
    return (0);
}
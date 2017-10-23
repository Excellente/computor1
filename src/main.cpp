#include "computor.hpp"

int main(int argc, char *argv[])
{
    string pol(argv[1]);
    vector<string> str;
    Computor pcalc = Computor((string)argv[1]);

    if (pol.compare("") == 0)
        cout << "please enter poylynomial to solve\n";
    else
    {
        if (argc == 2)
            pcalc.solvepoly();
        else if (argc == 3)
        {
            pcalc.solvepoly();
            pcalc.debugmode(argv[2]);
        }
        else
            cout << "exception not handled" << endl;
    }
    return (0);
}
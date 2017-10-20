#include "computor.hpp"

int main(int argc, char *argv[])
{
    vector<string> str;
    Computor pcalc = Computor((string)argv[1]);

    if (argc == 2)
    {
        pcalc.solvepoly();
        // pcalc.tostring();
    }
    else
        cout << "exception not handled" << endl;
    return (0);
}
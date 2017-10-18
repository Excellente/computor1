#include "computor.hpp"

int main(int argc, char *argv[])
{
    vector<string> str;    
    if (argc == 2)
    {
        // str = strsplit(argv[1], "=");
        cout << "lhs = " << str[0] << "\nrhs = " << str[1] << endl;
    }
    else
        cout << "exception not handled" << endl;
    return (0);
}
#include <iostream>
#include <regex>

using namespace std;
int main(int ac, char *av[])
{
    char *sub;
    regex rg("(\\+|-)?(\\s)?[[:digit:]]+(\\.([[:digit:]]+))?(\\s+)?(\\*)?(\\s+)?(X(\\^([[:digit:]]+))?)?");

    if (ac == 2)
    {
        sub = av[1];
        if (regex_match(sub, rg))
            cout << "sequqence matched" << endl;
        else
            cout << "match failed\n";
    }
    return (0);
}
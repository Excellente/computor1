#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(int ac,  char *av[])
{
    string input;
    regex rg("((\\s+)?(-|\\+)(\\s+)?)?[[:digit:]]+(\\.[[:digit:]]+)?(\\s\\*\\s)(X|x)(\\^[[:digit:]]+)");

    if (regex_match(av[1], rg))
        cout << "sequence matched\n";
    else
        cout << "unknown sequence\n";
    return (0);
}
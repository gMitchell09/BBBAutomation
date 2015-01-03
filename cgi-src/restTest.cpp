#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <fcntl.h>
#include <unistd.h>

#include "../SockAPI.hpp"

using namespace std;

#define WENDL "<br />"

const string QUERY_STRING = "QUERY_STRING";

int main(int argc, char* argv[])
{
    cout << "Content-type: text/html\r\n\r\n";
    for (int i = 0; i < argc; ++i)
    {
        cout << argv[i] << WENDL << endl;
    }

    string str = string(getenv(ENV[i].c_str()));

    cout << str << WENDL << endl;

    return 0;
}

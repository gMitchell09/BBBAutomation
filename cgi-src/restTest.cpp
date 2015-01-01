#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <fcntl.h>
#include <unistd.h>

using namespace std;

const string ENV[ 24 ] = {                 
        "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
        "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
        "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
        "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
        "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
        "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
        "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
        "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
        "SERVER_SIGNATURE","SERVER_SOFTWARE" };

int main(int argc, char* argv[])
{
    cout << "Content-type: text/html\r\n\r\n";
    for (int i = 0; i < argc; ++i)
    {
        cout << argv[i] << "<br />" << endl;
    }

    for (int i = 0; i < 24; ++i)
    {
        char* val = getenv(ENV[i].c_str());
        if (val != NULL)
            cout << ENV[i] << ": " << val << "<br/>" << endl;
    }

    char *ledPath = "/sys/class/leds/beaglebone::usr1/brightness";
    int fid = open(ledPath, O_WRONLY);
    if (getenv("QUERY_STRING") == 0) write(fid, "0", 1);
    else write(fid, "1", 1);

    return 0;
}

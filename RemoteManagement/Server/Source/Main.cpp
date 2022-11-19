#include "Webserver.h"

int main()
{
    WebServer webServer;
    webServer.Init();

    webServer.Destroy();

    return 0;
}

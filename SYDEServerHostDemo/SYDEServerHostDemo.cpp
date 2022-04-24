#include "BasicWinsockServer.h"

int __cdecl main(void) 
{
    BasicWinsockServer server = BasicWinsockServer();
    server.runInstance(27015);
    return 0;
}

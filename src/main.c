/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "game.h"

int main()
{
    initGame();
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        initState();
        updatePhisycs();
        update();
        VDP_waitVSync();
    }
    return (0);
}

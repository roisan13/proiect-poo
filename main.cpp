#include <iostream>
#include <thread>

#include "Spell.h"
#include "Voievod.h"
#include "Game.h"
#include "Menu.h"

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////

    Menu mainMenu = Menu();
    mainMenu.displayMenu();

    return 0;
}

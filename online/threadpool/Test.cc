#include "SpellCorrectServer.h"
#include <iostream>

int main()
{
    wd::SpellCorrectServer spell("../conf/config");
    spell.start();
    return 0;
}


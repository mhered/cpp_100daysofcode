#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST "\x1B[0m"   // reset
#define KRED "\x1B[31m" // red
#define KGRE "\x1B[32m" // green
#define KYEL "\x1B[33m" // yellow
#define KBLU "\x1B[34m" // blue
#define KMAG "\x1B[35m" // magenta
#define KCYA "\x1B[36m" // cyan
#define KWHI "\x1B[37m" // white

#define FRED(x) KRED x RST
#define FGRE(x) KGRE x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYA(x) KCYA x RST
#define FWHI(x) KWHI x RST

#define BOLD(x) "\x1B[1m" x RST // bold
#define UNDL(x) "\x1B[4m" x RST // underline

#endif /* _COLORS_ */

/* 

// EXAMPLE USAGE

#include <iostream>
#include "colors.h"

int main()
{
    std::cout << FBLU("I'm blue.") << std::endl;
    std::cout << BOLD(FBLU("I'm blue-bold.")) << std::endl;
    return 0;
}

*/
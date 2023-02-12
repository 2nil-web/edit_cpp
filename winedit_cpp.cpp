
#include <iostream>

#ifdef _MSC_VER
#include "editline/readline.h"
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main()
{
    std::cout << "Hello World!\n";
}

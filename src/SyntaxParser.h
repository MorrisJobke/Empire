
/* SyntaxParser.h
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#ifndef SYNTAXPARSER_H
#define SYNTAXPARSER_H

#include "Repository.h"
#include "Template.h"
#include "Filesystem.h"

DEFINE_FAST_EXCEPTION(NotEnoughArgs, "Not enough arguments.")

/* color definitions */
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CLEAR "\033[0m"
#define COLOR_BOLD "\033[1m"

namespace SyntaxParser
{
    void usage();
    void add(int argc, char* argv[]);
    void addi(int argc, char* argv[]);
    void modify(int argc, char* argv[]);
    void show(int argc, char* argv[]);
    void init(int argc, char* argv[]);
    void render(int argc, char* argv[]);
    void remove(int argc, char* argv[]);
}


#endif

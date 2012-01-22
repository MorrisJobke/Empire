
/* SyntaxParser.h
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#ifndef SYNTAXPARSER_H
#define SYNTAXPARSER_H

#include "Repository.h"

namespace SyntaxParser
{
    void add(int argc, char* argv[]);
    void modify(int argc, char* argv[]);
    void show(int argc, char* argv[]);
    void init(int argc, char* argv[]);
    void render(int argc, char* argv[]);

}


#endif

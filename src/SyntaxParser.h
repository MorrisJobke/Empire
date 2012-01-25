
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
#include "Collection.h"

DEFINE_FAST_EXCEPTION(NotEnoughArgs, "Not enough arguments.")

/* color definitions */
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"
#define COLOR_CLEAR "\033[0m"
#define COLOR_BOLD "\033[1m"

enum PrintMode { CREATED, MISSING, ADDED };

namespace SyntaxParser
{
    void usage();
    void create(int argc, char* argv[]);
    void coll_add(int argc, char* argv[]);
    void coll_fill(int argc, char* argv[]);
    void add(int argc, char* argv[]);
    void interactive_add(int argc, char* argv[]);
    void modify(int argc, char* argv[]);
    void show(int argc, char* argv[]);
    void init(int argc, char* argv[]);
    void render(int argc, char* argv[]);
    void remove(int argc, char* argv[]);
}

namespace ConsoleHelper
{
    
    void printColor(PrintMode mode);
    std::string getColor(PrintMode mode);
    void printTripleList(std::list<std::string> const& rList, PrintMode color);
    void printValueList(std::list<std::string> rList, PrintMode mode, bool rValues, bool rTypes, Repository working_repo);
    void printHeader(std::string header, int count);
}


#endif

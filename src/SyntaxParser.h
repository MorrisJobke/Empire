
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
#include "ListHelper.h"
#include "RegexHelper.h"

DEFINE_FAST_EXCEPTION(NotEnoughArgs, "Not enough arguments.")

/* color definitions */
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"
#define COLOR_CLEAR "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_PURPLE "\033[35m"

enum PrintMode { CREATED, MISSING, ADDED, NEEDLESS };
enum WorkingMode { REPO, TEMPLATE };

/** functions for command execution
 */
namespace SyntaxParser
{
    void usage();
    void create(int argc, char* argv[]);
    void coll_add(int argc, char* argv[]);
    void coll_fill(int argc, char* argv[]);
    void coll_show(int argc, char* argv[]);
    void find(int argc, char* argv[]);
    void add(int argc, char* argv[]);
    void interactive_add(int argc, char* argv[]);
    void modify(int argc, char* argv[]);
    void show(int argc, char* argv[]);
    void status(int argc, char* argv[]);
    void init(int argc, char* argv[]);
    void render(int argc, char* argv[]);
    void remove(int argc, char* argv[]);
}

/** some functions for console printing
 */
namespace ConsoleHelper
{

    void printColor(PrintMode mode);
    std::string getColor(PrintMode mode);
    void printCollElem(std::string rElem, int rTabSpace, int rows);
    void printTripleList(std::list<std::string> const& rList, PrintMode color, int rTabSpace);
    void printValueList(std::list<std::string> rList, PrintMode mode, bool rValues,
                        bool rTypes, bool rDirDiff, Repository working_repo, int rTabSpace);
    void printCollectionList(std::list<std::string> rList, PrintMode rMode, Repository working_repo,
                        int rTabSpace, WorkingMode rWorkMode, std::string rTemplPath);
    void printHeaderWithCount(std::string header, int count);
    void printHeader(std::string header);
    void printUnderlinedHeader(std::string header);
    std::string TimeToString(struct tm* time);
}

/** some help functions for SyntaxParser
 */
namespace DryHelpers
{
    void printRenderSynopsis();
}


#endif

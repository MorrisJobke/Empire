
/* SyntaxParser.cc
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#include "SyntaxParser.h"

//////////////////////////////////////////////////////////////////////////////
namespace SyntaxParser
{
    /** Add Command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void add(int argc, char* argv[])
    {
        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** modify command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void modify(int argc, char* argv[])
    {
        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** add command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void show(int argc, char* argv[])
    {
        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** init command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void init(int argc, char* argv[])
    {
        Repository working_repo;
        try
            {
                working_repo.Init();
            }
            catch(RepoExistentError &exc)
            {
                std::cout << "You have already a repo here." << std::endl;
                return;
            }
            catch(CannotCreateRepoError &exc)
            {
                std::cout << "The repository can not be created, maybe you do not have" << std::endl
                     << "permissions." << std::endl;
                return;
            }        
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** render command
     *
     * @param argc count of arguments
     * @param argv arguments
     */
    void render(int argc, char* argv[])
    {
        
    }
}

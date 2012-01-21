
/* RegexHelper.cc
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-20.
 * @Editor:      Sublime Text 2
 */

#include "RegexHelper.h"

//////////////////////////////////////////////////////////////////////////////
namespace RegexHelper
{
     /** 
     * @brief function wich checks if a given string is matching to a given regex-pattern
     * @param rTargetString given String to check against the pattern
     * @param rTargetString given regex pattern to check
     */ 
    bool MatchesRegex(std::string rTargetString, std::string rPattern)
    {
        pcre *re;
        const char *error;
        const char *data = rTargetString.c_str();
        int erroffset;
        int rc;
        int ovector[30];

        re = pcre_compile(
        rPattern.c_str(),   /* the pattern */
        0,                  /* default options */
        &error,             /* for error message */
        &erroffset,         /* for error offset */
        NULL);              /* use default character table */

        if (! re)
        {
            //fprintf(stderr, "PCRE compilation failed at expression offset %d: %s\n", erroffset, error);
            return false;
            //TODO: throw exception
        }

        rc = pcre_exec(
        re,                 /* the compiled pattern */
        NULL,               /* no extra data - we didn't study the pattern */
        data,               /* the subject string */
        strlen(data),       /* the length of the subject */
        0,                  /* start at offset 0 in the subject */
        0,                  /* default options */
        ovector,            /* output vector for substring information */
        30);                /* number of elements in the output vector */

        return rc > 0;
    }

    /** 
     * @brief function wich checks if a given string contains an int value
     * @param rTargetString given string to check
     */
    bool isInt(std::string value) 
    {
        return MatchesRegex(value, INT_PATTERN);
    }
    
    /** 
     * @brief function wich checks if a given string contains a float value
     * @param rTargetString given string to check
     */
    bool isFloat(std::string value) 
    {
        return MatchesRegex(value, FLOAT_PATTERN);
    }
}
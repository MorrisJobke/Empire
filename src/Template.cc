
/* Template.cc
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     11.01.2012.
 * @Editor:      Sublime Text 2
 */

#include "Template.h"

using namespace std;


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

/** add a property for use in the template
 *
 * @param property the property
 */
void SimpleTemplate::AddProperty(GenProperty* property)
{
    mProperties.insert(pair<string, GenProperty*>(property->GetKey(), property));
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add a list of properties for use in the template
 *
 * @param properties the properties
 */
void SimpleTemplate::AddProperties(list<GenProperty*> properties)
{
    list<GenProperty*>::iterator it;
    for (it = properties.begin(); it != properties.end(); it++) {
        AddProperty(*it);
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** parse a string
 *
 * @param input the string to parse
 * @param output the parsed result
 */
void SimpleTemplate::ParseString(string const& input, string& output)
{
    ostringstream result;
    string gathered;
    SimpleTemplate::Behavior behavior = EAT;
    SimpleTemplate::Expectation expectation = ALPHANUM;

    string::const_iterator it;
    it = input.begin();
    while (it < input.end()) {
        switch (behavior) {
            case EAT:
                // Variables in template start with @
                if (*it == '@') {
                    behavior = GATHER;
                    expectation = ALPHANUM;
                } else {
                    result << *it;
                }

                it++;

                break;
            case GATHER:
                if(*it == '@') {
                    result << *it;
                    it++;
                    
                    // reset behavior
                    behavior = EAT;
                    gathered = "";
                } else {
                    switch (expectation) {
                        case ALPHANUM:
                            if (isalnum(*it)) {
                                gathered += *it;
                                it++;
                            } else { // variable found
                                GenProperty* property = mProperties[gathered];
                                if (property && (property->GetType() == "Integer" || property->GetType() == "Float" || property->GetType() == "String")) {
                                    string propertyValue;
                                    property->GetValue(propertyValue);
                                    result << propertyValue;
                                } else { 
                                    // property not provided -> do nothing
                                }

                                // reset behavior
                                behavior = EAT;
                                gathered = "";

                                // btw do not increament it !
                                // because we have to eat this non alpha character
                            }

                    }
                }
                break;
        }
    }

    output = result.str();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** parse a string obtained from a file
 *
 * @param path the path to the file which content should be parsed
 * @param output the parsed result
 */
void SimpleTemplate::ParseFile(string const& path, string& output)
{

}

/*============================= ACCESS     =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

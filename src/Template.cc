
/* Template.cc
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     11.01.2012.
 * @Editor:      Sublime Text 2
 */

#include "Template.h"
#include "Filesystem.h"

using namespace std;


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

/** add a property for use in the template
 *
 * @param property the property
 */
void SimpleTemplate::AddProperty(GenPropertyBase* property)
{
    mProperties.insert(pair<string, GenPropertyBase*>(property->GetKey(), property));
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add a list of properties for use in the template
 *
 * @param properties the properties
 */
void SimpleTemplate::AddProperties(list<GenPropertyBase*> properties)
{
    list<GenPropertyBase*>::iterator it;
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
    std::list< std::list<GenPropertyBase*> > collection;
    SimpleTemplate::Behavior behavior = EAT;
    SimpleTemplate::Expectation expectation = ALPHANUM;

    string::const_iterator it;
    it = input.begin();
    while (it < input.end()) {
        switch (behavior) {
            case EAT:
                // Variables in template start with @
                if (*it == '@') {
                    if (*(it + 1) == '@') {
                        it++;
                        result << '@';
                    } else {
                        behavior = GATHER;
                        expectation = ALPHANUM;
                    }
                } else {
                    result << *it;
                }

                it++;

                break;
            case GATHER:
                switch (expectation) {
                    case ALPHANUM:
                        if (isalnum(*it)) {
                            gathered += *it;
                            it++;
                        } else if (*it == '{' && mProperties[gathered] &&
                                   mProperties[gathered]->GetTypeN() == GetTypeName<Coll>()) { // Collection
                            Coll coll = ((GenProperty<Coll>*)mProperties[gathered])->GetValue();
                            collection = coll.GetList();
                            behavior = GATHER;
                            expectation = NONECOLLECTIONEND;
                            gathered = "";
                            it++;
                        } else { // variable found
                            GenPropertyBase* property = mProperties[gathered];
                            if (property) {
                                string propertyValue = property->ToString();
                                result << propertyValue;
                            }

                            // reset behavior
                            behavior = EAT;
                            gathered = "";

                            // btw do not increament it !
                            // because we have to eat this non alpha character
                        }
                        break;
                    case NONECOLLECTIONEND:
                        if (gathered == "" && *it == '\n') {
                            // swallow first \n
                        } else if (*it != '}') {
                            gathered += *it;
                        } else {
                            // for each list of properties
                            std::list< std::list<GenPropertyBase*> > list = collection;
                            std::list< std::list<GenPropertyBase*> >::iterator properties;
                            for (properties = list.begin(); properties != list.end(); properties++) {
                                // create new SimpleTemplate instance,
                                SimpleTemplate* tmpl = new SimpleTemplate();
                                
                                // assign properties to it
                                std::list<GenPropertyBase*>::iterator property;
                                for (property = properties->begin(); property != properties->end(); property++) {
                                    tmpl->AddProperty(*property);
                                }
                                
                                // and render it ...
                                string output;
                                tmpl->ParseString(gathered, output);
                                result << output;
                            }

                            // reset behavior
                            behavior = EAT;
                            gathered = "";
                        }

                        it++;
                        break;
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
    string result;
    ParseString(Filesystem::FileReadString(path), result);
    output = result;
}

/*============================= ACCESS     =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

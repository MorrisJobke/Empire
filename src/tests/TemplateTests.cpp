
/* TemplateTests.cpp
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     2012-01-11.
 * @Editor:      Sublime Text 2
 */

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Template
#endif

#include <iostream>
#include <string>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../Template.h"
#include "../Filesystem.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(TemplateTestSuite)

/*============================= BASIC TESTS ================================*/

BOOST_AUTO_TEST_CASE(NothingToReplaceShouldReturnOriginalInput)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string input = "Realität ist da,\nwo der Pizzamann herkommt.";
    string output;
    tmpl->ParseString(input, output);

    BOOST_CHECK(input == output);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(ReplaceVariablePlaceholder)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string individual = "Pizzamann";
    string key = "individual";
    GenProperty<string> property(individual, key);
    tmpl->AddProperty(&property);

    string input = "Realität ist da,\nwo der @individual herkommt.@shouldDisappear";
    string output;
    tmpl->ParseString(input, output);

    BOOST_CHECK(output == "Realität ist da,\nwo der Pizzamann herkommt.");

    input = "email@@example.tld";
    tmpl->ParseString(input, output);

    //std::cout << "output: " << output << endl;

    BOOST_CHECK(output == "email@example.tld");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(TemplateReadFileTest)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string individual = "Bill Gates";
    string key = "unimportantPerson";    
    GenProperty<string> property(individual, key);
    tmpl->AddProperty(&property);
    string path = "testtemplate";

    string input = "\"640 Kilobyte ought to be enough for anybody.\"\n@unimportantPerson, 1981@nothingToSeeHere";
    
    Filesystem::FileWriteString(path, input);

    string output;
    tmpl->ParseFile(path, output);

    BOOST_CHECK(output == "\"640 Kilobyte ought to be enough for anybody.\"\nBill Gates, 1981");
    
    remove(path.c_str());
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(TemplateCollectionTest)
{
    GenProperty<string> ingredient1_ingredient("Midori Melon Liqueur", "ingredient");
    GenProperty<double> ingredient1_oz(1, "oz");
    GenProperty<string> ingredient2_ingredient("Blue Curacao", "ingredient");
    GenProperty<double> ingredient2_oz(1, "oz");
    GenProperty<string> ingredient3_ingredient("Lemonade", "ingredient");
    GenProperty<double> ingredient3_oz(0.5, "oz");

    std::list<GenPropertyBase*> ingredient1;
    ingredient1.push_back(&ingredient1_ingredient);
    ingredient1.push_back(&ingredient1_oz);

    std::list<GenPropertyBase*> ingredient2;
    ingredient2.push_back(&ingredient2_ingredient);
    ingredient2.push_back(&ingredient2_oz);

    std::list<GenPropertyBase*> ingredient3;
    ingredient3.push_back(&ingredient3_ingredient);
    ingredient3.push_back(&ingredient3_oz);

    Coll ingredients_coll("ingredients");
    ingredients_coll.Declare(ingredient1);
    ingredients_coll.AddRow(ingredient2);
    ingredients_coll.AddRow(ingredient3);

    GenProperty<Coll> ingredients(ingredients_coll, "ingredients");

    SimpleTemplate* tmpl = new SimpleTemplate();
    tmpl->AddProperty(&ingredients);

    string input = "Nerds Recipe\n\n@ingredients{\n@oz oz @ingredient\n}";
    string output;
    tmpl->ParseString(input, output);

    // std::cout << "output: " << output << endl;

    BOOST_CHECK(output == "Nerds Recipe\n\n1 oz Midori Melon Liqueur\n1 oz Blue Curacao\n0.5 oz Lemonade\n");

    remove("ingredients/0");
    remove("ingredients/0/ingredient");
    remove("ingredients/0/oz");
    remove("ingredients/1");
    remove("ingredients/1/ingredient");
    remove("ingredients/1/oz");
    remove("ingredients/2");
    remove("ingredients/2/ingredient");
    remove("ingredients/2/oz");
    remove("ingredients");
}

BOOST_AUTO_TEST_SUITE_END()

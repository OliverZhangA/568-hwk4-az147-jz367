//headers for dp operations
#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;
//header for Xml operations
#include "tinyxml2.h"
using namespace tinyxml2;
//Xml functions
void xml_handler(string xmltext, connection * C);


//db operations below
connection* create_table();
void create_account(XMLElement* cur, connection * C);
void create_symbol(XMLElement* cur, connection * C);
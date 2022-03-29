//headers for dp operations
#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using namespace pqxx;
//header for Xml operations
#include "tinyxml2.h"
using namespace tinyxml2;
//Xml functions
string xml_handler(string xmltext, connection * C);


//db operations below
connection* create_table();
void create_account(XMLElement* cur, connection * C, string & resp);
void create_symbol(XMLElement* root, connection * C, string & resp);
void create_symbol(string symname, string account_id, int amount, connection *C);
void transactions_handler(XMLElement* root, connection* C, string &resp);
void create_order(XMLElement* cur, connection * C, string & resp, string account_id);
void create_query(XMLElement* cur, connection * C, string & resp, string account_id);
void create_cancel(XMLElement* cur, connection * C, string & resp, string account_id);
void buy_match(XMLElement* cur, connection * C, string & resp, string account_id);
void sell_match(XMLElement* cur, connection * C, string & resp, string account_id);
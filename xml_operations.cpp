#include "operations.hpp"
void xml_handler(string xmltext, connection* C){
    XMLDocument doc;
    // doc.LoadXml("<book xmlns:bk='urn:samples'>" +
    //             "<bk:ISBN>1-861001-57-5</bk:ISBN>" +
    //             "<title>Pride And Prejudice</title>" +
    //             "</book>");
    doc.Parse(xmltext.c_str());
    XMLElement* elmtRoot = doc.RootElement();
    //initalize a response variable x
    if(strcmp(elmtRoot->Name(), "create") == 0) {
        cout<<"this xml is create"<<endl;
        XMLElement* cur = elmtRoot->FirstChildElement();
        /*
        for (elmtAttData = elmtAttParam->FirstChildElement(); elmtAttData != NULL; elmtAttData = elmtAttData->NextSiblingElement())
		{
        node = node->next
        while(node) {
            if(account) {
                create account(x&)
            }
            else if(symbol, node*) {
                createsymbol(x&)
            }
        */
        while(cur) {
            if(strcmp(cur->Name(), "account") == 0) {
                //parameters and return value???
                create_account(cur, C);
            } else if(strcmp(cur->Name(), "symbol")) {
                create_symbol(cur, C);
            } else {
                cerr<<"wrong format"<<endl;
                exit(EXIT_FAILURE);
            }
            cur = cur->NextSiblingElement();
        }
    } else if(strcmp(elmtRoot->Name(), "transactions") == 0) {

    } else {
        //report error
    }
    //return response
}
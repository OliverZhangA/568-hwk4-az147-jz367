#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>

using namespace std;
using namespace pqxx;

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=EXCHANGE user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  work W(*C);

  string sql_drop;

  sql_drop = "DROP TABLE IF EXISTS \"SYMBOL\" CASCADE; " \
  "DROP TABLE IF EXISTS \"ORDER\" CASCADE; " \
  "DROP TABLE IF EXISTS \"TRANSACTION\" CASCADE; " \
  "DROP TABLE IF EXISTS \"ACCOUNT\" CASCADE;";

  W.exec(sql_drop);

  string sql_account;
  sql_account = "CREATE TABLE \"ACCOUNT\" (" \
  "\"ACCOUNT_ID\" VARCHAR(20) NOT NULL," \
  "\"BALANCE\" INT NOT NULL," \
  "PRIMARY KEY (\"ACCOUNT_ID\"));";

  W.exec(sql_account);

  string sql_trans;
  sql_state = "CREATE TABLE \"TRANSACTION\" (" \
  "\"TRANS_ID\" SERIAL PRIMARY KEY," \
  "\"BUY_ID\" VARCHAR(20) NOT NULL," \
  "\"SELL_ID\" VARCHAR(20) NOT NULL," \
  "\"SYM\" VARCHAR(20) NOT NULL,"
  "\"NUM\" INT NOT NULL," \
  "\"PRICE\" INT NOT NULL," \
  "FOREIGN KEY (\"BUY_ID\") REFERENCES \"ACCOUNT\"(\"ACCOUNT_ID\") ON DELETE CASCADE," \
  "FOREIGN KEY (\"SELL_ID\") REFERENCES \"ACCOUNT\"(\"ACCOUNT_ID\") ON DELETE CASCADE);";

  W.exec(sql_trans);

  string sql_order;
  sql_team = "CREATE TABLE \"ORDER\" (" \
  "\"ID\" SERIAL PRIMARY KEY," \
  "\"CALLER_ID\" VARCHAR(20) NOT NULL," \
  // Is symbol a foreign key?
  "\"SYM\" VARCHAR(20) NOT NULL," \
  "\"AMOUNT\" INT NOT NULL," \
  "\"LIMIT\" INT NOT NULL," \
  "FOREIGN KEY (\"CALLER_ID\") REFERENCES \"ACCOUNT\"(\"ACCOUNT_ID\") ON DELETE CASCADE);";
  W.exec(sql_order);

  string sql_symbol;
  // How to know the number of symbols?
  sql_player = "CREATE TABLE \"SYMBOL\" (" \
  "\"USER_ID\" VARCHAR(20) NOT NULL," \
  "\"SYM\" VARCHAR(20) NOT NULL," \
  "\"SHARE\" INT NOT NULL," \
  /*
  "\"TEAM_ID\" INT NOT NULL," \
  "\"UNIFORM_NUM\" INT NOT NULL," \
  "\"FIRST_NAME\" VARCHAR(30) NOT NULL," \
  "\"LAST_NAME\" VARCHAR(30) NOT NULL," \
  "\"MPG\" INT NOT NULL," \
  "\"PPG\" INT NOT NULL," \
  "\"RPG\" INT NOT NULL," \
  "\"APG\" INT NOT NULL," \
  "\"SPG\" DECIMAL(2,1) NOT NULL," \
  "\"BPG\" DECIMAL(2,1) NOT NULL," \
  */
  "PRIMARY KEY (\"USER_ID\", \"SYM\"), " \
  "FOREIGN KEY (\"USER_ID\") REFERENCES \"ACCOUNT\"(\"ACCOUNT_ID\") ON DELETE CASCADE);";

  W.exec(sql_symbol);

  W.commit();

  /*
  string colorStr("color.txt");
  vector<string> colorLines = readFile(colorStr.c_str());
  insertColors(C, colorLines);
  string stateStr("state.txt");
  vector<string> stateLines = readFile(stateStr.c_str());
  insertStates(C, stateLines);
  string teamStr("team.txt");
  vector<string> teamLines = readFile(teamStr.c_str());
  insertTeams(C, teamLines);
  string playerStr("player.txt");
  vector<string> playerLines = readFile(playerStr.c_str());
  insertPlayers(C, playerLines);


  exercise(C);
  */


  //Close database connection
  C->disconnect();

  return 0;
}

#include <iostream>
#include <sqlite3.h>
// #include "sqlite3.c"
using namespace std;

// This is the callback function to display the select data in the table
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
  for(int i = 0; i < argc; i++)
  {
    std::cout << szColName[i] << " = " << argv[i] << std::endl;
  }

  std::cout << "\n";

  return 0;
}

int main()
{
  sqlite3 *db;
  char *szErrMsg = 0;

  // open database
  // int rc = sqlite3_open("Sqlite_Test.db", &db);
  int rc = sqlite3_open("sample.sqlite", &db);

  if(rc)
  {
    std::cout << "Can't open database\n";
  } else {
    std::cout << "Open database successfully\n";
  }

  // prepare our sql statements
  const char *pSQL[6];
  pSQL[0] = "CREATE TABLE Employee(Firstname varchar(30), Lastname varchar(30), Age smallint)";
  pSQL[1] = "INSERT INTO Employee(Firstname, Lastname, Age) VALUES ('Woody', 'Alan', 45)";
  pSQL[2] = "INSERT INTO Employee(Firstname, Lastname, Age) VALUES ('Micheal', 'Bay', 38)";
  pSQL[3] = "SELECT * FROM center";

  // execute sql
  for(int i = 3; i < 4; i++)
  {
    rc = sqlite3_exec(db, pSQL[i], callback, 0, &szErrMsg);
    if(rc != SQLITE_OK)
    {
      std::cout << "SQL Error: " << szErrMsg << std::endl;
      sqlite3_free(szErrMsg);
      break;
    }
  }

  // close database
  if(db)
  {
    sqlite3_close(db);
  }

  return 0;
}

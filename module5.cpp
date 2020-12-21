#include <iostream>
#include <sqlite3.h>
#include <unordered_map>
#include <list>
#include <iterator>
#include <fstream>

using namespace std;
// string cid="c6";
string value;

// This is the callback function to display the select data in the table
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
  // cout<<endl<<value<<endl;
  string a(argv[0]);
  if(a!=value)
  {
    return 0;
  }
  else
  {
    cout<<"\x1b[36;40mNearest covid center is:\x1b[0m"<<" "<<argv[1]<<endl;
    cout<<"\x1b[36;40mAddress:\x1b[0m"<<" "<<argv[2]<<endl;
    cout<<"\x1b[36;40mContact Details:\x1b[0m"<<" "<<argv[3]<<endl;
    cout<<argv[4]<<endl;
    cout<<"\x1b[36;40mPincode:\x1b[0m"<<" "<<argv[5]<<endl;
  }
  // cout<<"a"<<argc<<endl;
  // for(int i = 0; i < argc; i++)
  // {
  //   // if(argv[1]!=cid)
  //   // continue;
  //   // string x=argv[0];
  //   // string y=argv[1];
  //   std::cout << szColName[i] << " = " << argv[i] << std::endl;
  // }

  // std::cout << "\n";

  return 0;
}

int main()
{
  sqlite3 *db;
  char *szErrMsg = 0;

  // string value;
  ifstream myfile ("mycenter.txt");
  if (myfile.is_open())
  {

		getline (myfile,value);
		// cout<<value;
    myfile.close();
  }

  // open database
  // int rc = sqlite3_open("Sqlite_Test.db", &db);
  int rc = sqlite3_open("center.sqlite", &db);

  // if(rc)
  // {
  //   std::cout << "Can't open database\n";
  // } else {
  //   std::cout << "Open database successfully\n";
  // }

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
  cout<<endl;
  return 0;
}

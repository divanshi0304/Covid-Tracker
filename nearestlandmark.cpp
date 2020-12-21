// C++ program to calculate distance between two coordinates on Earth
#include <bits/stdc++.h>
#include <iomanip>
#include <jsoncpp/json/json.h>
// #include <json/value.h>
#include <fstream>
#include <sqlite3.h>
#include <cmath>

using namespace std;

//To link database and store location of landmark in array
long double landmark_lat[19];
long double landmark_long[19];
string loc_id[19];
int p=0;

// This is the callback function to display the select data in the table
static int callback(void *NotUsed, int argc, char ** argv, char **szColName)
{
	// cout<<argv[3]<<" "<<argv[4]<<endl;
	// cout<<typeid(argv[3]).name()<<" "<<(long double)argv[4]<<endl;
	std::size_t temp = 20;
	string c(argv[0]);
	string a(argv[3]);
	string b(argv[4]);
	// cout<<a<<" "<<b<<endl;
	landmark_lat[p]= stold(a, &temp);//stod(argv[3], &temp);
	// landmark_long[p]=(atof)argv[4];
	landmark_long[p]=stold(b,&temp);//stod(argv[4], &temp);
	loc_id[p] = c;
	++p;
  // cout<<"a"<<argc<<endl;
  // for(int i = 3; i <5; i++)
  // {
  //   // if(argv[1]!=cid)
  //   // continue;
  //   string x=argv[0];
  //   string y=argv[1];
  //   std::cout << szColName[i] << " = " << argv[i] << std::endl;
  // }

  // std::cout << "\n";

  return 0;
}

// converting degrees to radians
long double toRadians(const long double degree)
{
	// cmath library in C++ defines the constant  M_PI as the value of pi accurate to 1e-30
	long double one_deg = (M_PI) / 180;
	return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
					long double lat2, long double long2)
{
	// landmark_lat
	// Convert the latitudes and longitudes from degree to radians.
	lat1 = toRadians(lat1);
	long1 = toRadians(long1);
	lat2 = toRadians(lat2);
	long2 = toRadians(long2);

	// Haversine Formula
	long double dlong = long2 - long1;
	long double dlat = lat2 - lat1;

	long double ans = pow(sin(dlat / 2), 2) +
						cos(lat1) * cos(lat2) *
						pow(sin(dlong / 2), 2);

	ans = 2 * asin(sqrt(ans));

	// Radius of Earth in Kilometers, R = 6371
	long double R = 6371;

	// Calculate the result
	ans = ans * R;

	return ans;
}

// Driver Code
int main()
{
	Json::Value data;
	std::ifstream sample_file("sample.json", std::ifstream::binary);
sample_file >> data;
// cout<<data["data"][0]["latitude"]<<endl;
// cout<<data; //This will print the entire json object.

//The following lines will let you access the indexed objects.
// cout<<sample["Anna"]; //Prints the value for "Anna"
// cout<<sample["ben"]; //Prints the value for "Ben"
// cout<<sample["data"]["longitude"]; //Prints the value corresponding to "profession" in the json for "Anna"
//
// cout<<sample["profession"];
	long double lat1=data["data"][0]["latitude"].asDouble();
	long double long1=data["data"][0]["longitude"].asDouble();
    long double lat2;
	long double long2;
		//
    // // API Call
    // cout << "User latitute: ";
    // cin >> lat1;
    // cout << "User longitude: ";
    // cin >> long1;

		sqlite3 *db;
		char *szErrMsg = 0;

		// open database
		// int rc = sqlite3_open("Sqlite_Test.db", &db);
		int rc = sqlite3_open("landmark.sqlite", &db);

		// if(rc)
		// {
		// 	std::cout << "Can't open database\n";
		// } else {
		// 	std::cout << "Open database successfully\n";
		// }

		// prepare our sql statemcharents
		const char *pSQL[6];
		pSQL[3] = "SELECT * FROM landmark";

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

    //array storing distance
    long double dist[19];
    setprecision(15);
    for(int i=0; i<19; i++){
        lat2 = landmark_lat[i];
        long2 = landmark_long[i];
        dist[i] = distance(lat1, long1, lat2, long2);
    }

// Printing min element i.e. nearest landmark
    // cout << "\nNearest Landmark = "
         // << *min_element(dist, dist + 19)<<endl;
				 int min_elem = 0;
				 long double min_dist = dist[0];
		for(int i=0; i<19; i++){
			if(dist[i] < min_dist){
				min_dist = dist[i];
				min_elem = i;
			}
		}
		// cout << min_dist<<" "<<loc_id[min_elem]<<" "<<endl;

		string final=loc_id[min_elem];
		ofstream myfile ("value.txt");
  if (myfile.is_open())
  {
    myfile << final;
    // myfile << "This is another line.\n";
    myfile.close();
  }
  else cout << "Unable to open file";
  return 0;

    return 0;
}

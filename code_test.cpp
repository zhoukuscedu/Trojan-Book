#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string codeName(string str1, string str2) {

   str1 = str1.substr(0, str1.find(" ")) + str1.substr(str1.find(" ") + 1);
   if(str2.find(" ") != str2.length() - 1) {
      str2 = str2.substr(0, str2.find(" ")) + str2.substr(str2.find(" ") + 1);
   }
      
   string str = str1 + str2;  
   
   transform(str.begin(), str.end(), str.begin(), ::tolower);
   
   return str;

}

int main(){

string fname = "Kevin Zhou";
string lname = "LastName";

string code = codeName(fname, lname);

cout << code;


}

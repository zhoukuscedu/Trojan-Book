
#include "connection.h"

Connection::Connection(){
    // I'm already done! 
    set_connection();
}


Connection::~Connection(){
    // TODO: Complete me!
    delete birthdate;
    delete email;
    delete phone;
}


Connection::Connection(string fname, string lname, string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    
    string etype, ptype, mail, num;
    
    etype = email.substr(1, email.find(')') - 1);
    mail = email.substr(email.find(')')+2);
    
    ptype = phone.substr(1, phone.find(')') - 1);
    num = phone.substr(phone.find(')')+2);
    
    this->f_name = fname;
    this->l_name = lname;
    this->email = new Email(etype, mail);
    this->phone = new Phone(ptype, num);
    this->birthdate = new Date(bdate);
}


Connection::Connection(string filename){
    // TODO: Complete this method!
    set_connection(filename); 
}


void Connection::set_connection(){
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    string bdate;
    
    string type1;
    string mail;
    
    string type2;
    string num;

    cout << "First Name: ";
    getline(cin, f_name);
	 cout << "Last Name: ";
    getline(cin, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin, bdate);
    birthdate = new Date(bdate);
    
    cout << "Type of email address: ";
    getline(cin, type1);
    cout << "Email address: ";
    getline(cin, mail);
    email = new Email(type1, mail);

    cout << "Type of phone number: ";
    getline(cin, type2);
    cout << "Phone number: ";
    getline(cin, num);
    phone = new Phone(type2, num);
}


void Connection::set_connection(string filename){
    // TODO: Complete this method!
    // Look at connection_template files as examples.     
    // Phone number in files can have '-' or not.
    string buff1, buff2, buff3;
    string date, mail, num;
    string type;
    
    int n = filename.length();
    char char_array[n+1];
    strcpy(char_array, filename.c_str());
    
    ifstream infile;
    
    infile.open(char_array);
    
    getline(infile, buff1);
    l_name = buff1.substr(0, buff1.find(','));
    f_name = buff1.substr(buff1.find(',')+2);
    
    getline(infile, date);
    birthdate = new Date(date);
    
    getline(infile, buff2);
    type = buff2.substr(1, buff2.find(')') - 1);
    mail = buff2.substr(buff2.find(')')+2);
    email = new Email(type, mail);
        
    getline(infile, buff3);
    type = buff3.substr(1, buff3.find(')') - 1);
    num = buff3.substr(buff3.find(')')+2);
    phone = new Phone(type, num);
    
    
    infile.close();
}


bool Connection::operator==(const Connection& rhs){
    // TODO: Complete this method!
    // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
    if ( (f_name == rhs.f_name) && (l_name == rhs.l_name))
        return true;
    else
        return false;
}


bool Connection::operator!=(const Connection& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Connection::print_connection(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
   email->print();
   phone->print();
   for(int i = 0; i < myfriends.size(); i++) {
      string str1 = myfriends[i]->f_name;
      string str2 = myfriends[i]->l_name;
      cout << codeName(str1, str2) << endl;
   }
}

void Connection::makeFriend(Connection* newFriend){
   myfriends.push_back(newFriend);
   string temp = codeName(newFriend->f_name, newFriend->l_name);
   codes.push_back(temp);

}

void Connection::write_connection(ofstream& file) {
   file << l_name << ", " << f_name << endl;
   file << birthdate->get_date() << endl;
   file << email->get_contact() << endl;
   file << phone->get_contact() << endl;
   for(int i = 0; i < myfriends.size(); i++){
      string str1 = myfriends[i]->f_name;
      string str2 = myfriends[i]->l_name;
      file << codeName(str1, str2) << endl;
   }
   file << "--------------------" << endl;
}
   


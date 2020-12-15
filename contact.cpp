
#include "contact.h"
using namespace std;

// TODO: Add needed libraries! 

Email:: Email(){
   set_contact();
}


Email::Email(string type, string email_addr){
    // TODO: Complete me!
    set_contact(type, email_addr);
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
    cout << "Enter the type of email address: ";
    cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}

void Email::set_contact(string type, string email_addr){
    // TODO: Do not change the prompts!
    this->type = type;
    this->email_addr = email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << "Email: " << get_contact("full") << endl;
}


Phone::Phone(){
   set_contact();
}

Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    // The code has been covered in the discussion session
    
    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */
    
    num.erase(remove(num.begin(), num.end(), '-'), num.end());
    num = num.substr(0,3) + "-" + num.substr(3, 3) + "-" + num.substr(6);
    set_contact(type, num);
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	
   stringstream ss;
	
	cout <<"Enter the type of phone number: ";
	cin >> type;
	cout << "Enter the phone number: ";
	cin >> phone_num;
	phone_num.erase(remove(phone_num.begin(), phone_num.end(), '-'), phone_num.end());
	phone_num = phone_num.substr(0,3) + "-" + phone_num.substr(3, 3) + "-" + phone_num.substr(6);
 
}

void Phone::set_contact(string type, string phone_num){

   this->type = type;
   this->phone_num = phone_num;

}
string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // The code has been covered in discussion session 
    if (style=="full")
	    return "(" + type + ") " + phone_num;
    else 
        return phone_num;
        
    /* Note: Understand your own TA's bug!
     * This code has a bug, can you understand it!
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
    */ 
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << "Phone: " << get_contact("full") << endl;
}



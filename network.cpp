
#include "network.h"
#include "connection.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <cstring>
#include <dirent.h>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    head = NULL;
    tail = NULL;
    count = 0;
    loadDB(fileName);
}

Network::~Network(){
    Connection* ptr = head;
    while(head != NULL){
       ptr = head->next;
       delete head;
       head = ptr;
       count--;
    }
    head = NULL;
    tail = NULL;
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
   
   newEntry->next = NULL;
   
    if(head == NULL) {
      head = newEntry;
      
    }
    
    else {   
      tail->next = newEntry;
      newEntry->prev = tail;
      
    }
    count++;
    tail = newEntry;
}


Connection* Network::search(Connection* searchEntry){
    Connection* ptr = head;
    
    while(ptr != NULL) {
      if(*ptr == *searchEntry) {
         break;
      }
      
      ptr=ptr->next;
      
    }
    
    return ptr;
}


Connection* Network::search(string fname, string lname){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 
    Connection* searchEntry = new Connection(fname, lname, "10/09/1998", "email", "123456789");
    Connection* ptr = head;
    
    while(ptr != NULL) {
      if(*ptr == *searchEntry) {
         break;
      }
      
      ptr=ptr->next;
      
    }
    delete searchEntry;
    return ptr;
    
}

Connection* Network::search(string code){
   //cout << "code in: " << code << endl;
   Connection* ptr = head;
   
   while(ptr != NULL) {
      string temp = codeName(ptr->f_name, ptr->l_name);
      //cout << "code created: " << temp << endl;
      if(temp == code) {
         break;
      }
      
      ptr = ptr->next;
      }
      return ptr;
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
    cout << "Number of connections: " << count << endl;
    
    int n = filename.length();
    char char_array[n+1];
    strcpy(char_array, filename.c_str());
    
    ofstream *outfile = new ofstream(filename.c_str());
    //outfile.open(char_array);
    Connection* ptr = head;
    while(ptr != NULL) {
      /*outfile << ptr->l_name <<", " << ptr->f_name << endl;
      outfile << ptr->birthdate->get_date() << endl;
      outfile << ptr->email->get_contact() << endl;
      outfile << ptr->phone->get_contact() << endl;
      outfile << "--------------------" << endl;
      ptr = ptr->next;*/
      ptr->write_connection(*outfile);
      ptr = ptr->next;
    }
    
    //outfile.close();
    outfile->close();
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 
    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, mail, num;
    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        getline(infile, mail);
        getline(infile, num);
        Connection* newEntry = new Connection(fname, lname, bdate, mail, num);
        
        while(getline(infile, buff)) {
            if(buff.substr(0,1) != "-") {
               newEntry->codes.push_back(buff);
            }
               
            else{
               break;
            }
        }
        this->push_back(newEntry);
    }
    
    ptr = head;
    Connection* ref;
    while(ptr != NULL) {
         int size = ptr->codes.size();
         
            for(int i = 0; i < size; i++) {
               //cout << ptr->codes[i] << endl;
               ref = search(ptr->codes[i]);
               
               if(ref != NULL) {
               //cout << i << endl;
               //cout << ref->f_name << endl;
                  ptr->myfriends.push_back(ref);
               }
            }
         ptr = ptr->next;       
         
    }
    
}


bool Network::remove(string fname, string lname){
    
    Connection* ref = search(fname, lname);
    if(ref != NULL) {
      
      if(count == 1) {
         delete ref;
         head = NULL;
         tail = NULL;
         count = 1;
      }
      
      else if(ref == head) {
         head = ref->next;
         delete ref;
         head->prev = NULL;
      }
      
      else if(ref == tail) {
            tail = tail->prev;
            delete ref;
            tail->next = NULL;
      }
      
      else {
         Connection* temp1 = ref->prev;
         Connection* temp2 = ref->next;
         temp1->next = ref->next;
         temp2->prev = ref->prev;
         delete ref;
      }
      
      count--;
      
      Connection* ptr = head;
      string codename = codeName(fname, lname);
      while(ptr != NULL) {
         int size = ptr->myfriends.size();
         for(int i = 0; i < size; i++) {
           if(ptr->codes[i] == codename){
           //remove element
           ptr->codes.erase(ptr->codes.begin() + i);
           ptr->myfriends.erase(ptr->myfriends.begin() + i);
           }
         }
         ptr = ptr->next;       
         
      }
    
      
      return true;
    }
    
    else {
      return false;
    }
}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    addr = "\"" + addr + "\"";
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    string cmd;
    
    if(attachment == "") {
       cmd = "echo " + content + " | mailx -s " + subject + " " + addr;
    }
    
    else {
      cmd = "echo " + content + " | mailx -s " + subject + " -a " + attachment + " " + addr;
    }
    //cout << cmd << endl;
    system(cmd.c_str());
   
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!
    
    Network network;
    
    int opt;
    while(1){
        cout << "\033[2J\033[1;1H"; 
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate, etype, ptype, mail, num;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            network.saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            string name;
            int i = 0;
            string files[100]; //statically allocated with 100 elements
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            if ((dir = opendir ("./")) != NULL) {
               while ((ent = readdir (dir)) != NULL) {
                  name = ent->d_name;
                  if((name.length() > 3) && (name.substr(name.length() - 2) == "db")) {             
                     cout << ent->d_name << endl;
                     files[i] = name;
                     i++;
                  }
               }
            closedir (dir);
            } 
            else {
               /* could not open directory */
               perror ("No directory!");
            }
            
            // Take a look into sample_files.cpp 
            cout << "Enter the name of the load file: ";
            cin >> fileName; 
            // If file with name FILENAME does not exist: 
            int flag = 0;
            
            for(int j = 0; j < i; j++) {
               if(fileName == files[j]) {
                  flag = 1;
               }
            }
            
            if(flag == 0) {
               cout << "File " << fileName << " does not exist! " << endl;
            }
            // If file is loaded successfully, also print the count of connections in it: 
            else {
               network.loadDB(fileName);
               cout << "Network loaded from " << fileName << " with " << network.count << " connections \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
            cout << "Enter first name \n";
            getline (cin, fname);
            cout << "Enter last name \n";
            getline (cin, lname);
            cout << "Enter birthdate \n";
            getline(cin, bdate);
            cout << "Enter email type: \n";
            getline(cin, etype);
            cout << "Enter email: \n";
            getline(cin, mail);
            cout << "Enter phone type: \n";
            getline(cin, ptype);
            cout << "Enter phone number: \n";
            getline(cin, num);
            
            Connection* node = network.search(fname, lname);
            
            if(node == NULL) {
               Connection* new_connection = new Connection(fname, lname, bdate, "(" + etype + ") " + mail, "(" + ptype + ") " + num);
               network.push_front(new_connection);
               cout << "Connection added" << endl;
               } 
               
            else {
               cout << "Connection already exists" << endl;
            }   
            
        }
        
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Removing a connection \n";
            cout << "First name: ";
            getline (cin, fname);
            cout << "Last name: ";
            getline (cin, lname);
            
            if(network.remove(fname, lname) == true) {
               cout << "Remove Successful! \n";
               //network.printDB();
            }
            
            else {
               cout << "Connection not found! \n";
            }
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Connection not found! \n";
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            getline (cin, fname);
            cout << "Last Name: ";
            getline (cin, lname);
            
            Connection* node = network.search(fname, lname);
            
            if(node == NULL) {
               cout << "Not found! \n";
            }
            
            else {
               node->print_connection();
            }
            
            // if found: print connection
            // if not, cout << "Not found! \n";
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = network.search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            network.printDB();
            
        }
        
        else if (opt==9){
            cout << "Make friends: \n";
            cout << "Connection 1: " << endl;
            cout << "First Name: ";
            getline (cin, fname);
            cout << "Last Name: ";
            getline (cin, lname);
            
            Connection* node1 = network.search(fname, lname);
            
            if(node1 == NULL) {
               cout << "Not found! \n";
            }
            
            else {
               cout << "Connection 2: " << endl;
               cout << "First Name: ";
               getline (cin, fname);
               cout << "Last Name: ";
               getline (cin, lname);
            
               Connection* node2 = network.search(fname, lname);
            
               if(node2 == NULL) {
                  cout << endl;
                  cout << "Not found! \n";
               }
            
               else {
                  node1->makeFriend(node2);
                  node2->makeFriend(node1);
                  
                  cout << "Connection Made!";
               }
               
            }
        }
        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}



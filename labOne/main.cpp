//
//  main.cpp
//  labOne
//
//  Created by Gleb Zhutowskiy on 2/26/20.
//  Copyright © 2020 Gleb Zhutowskiy. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <chrono>


using namespace std;

    struct date{
        int year=1111;
        int month=11;
        int day=11;
        
        void print(){
            cout<<day<<"."<<month<<"."<<year<<endl;
        }
    };
    struct MassegeLog{
//        static int maxId;
        MassegeLog()
               {
                   text ="demo";
                   type = "demo";
                   priority =23;
                   busyness=0.5;
                   id=5;

               }
        MassegeLog(string text,string type,int priority,double busyness,int id){
            this->text = text;
            this->type = type;
            this->priority = priority;
            this->busyness = busyness;
            this->id = id;

        }
        string text;
        date defdate;
        string type;
        int priority;
        int id;
        double busyness;
        void print(){
            cout<<endl;
            cout<<"ID:"<<id<<endl;
            cout<<"Text: "<<text<<endl;
            cout<<"Date: "<<defdate.day<<"."<<defdate.month<<"."<<defdate.year<<endl;
            cout<<"Type: "<<type<<endl;
            cout<<"Priority: "<<priority<<endl;
            cout<<"Busyness: "<<busyness<<endl;
        }
    };

void reader_text(string textPath);
int get_main_variant();
void print_main_menu();
void print_hand_menu();
float randomLowerOne();
string get_type_variant();
int get_priority_variant();
int generateID();
int get_fromShow_variant();
void print_fromShow_menu();
void print_search_menu();
int findMaxId (string textPath);
void demo_mode(string path_binary,string textPath, vector<MassegeLog> myVec);
void reader_bin(string path_binary);
void add_to_binary(string path_binary,MassegeLog msg);
void add_to_txt(string textPath, MassegeLog msg);
string random_msgText(int a,int b);
string random_msgType();
void serach_fragment(vector<MassegeLog> myVec);
bool compare(date vectorDate,date usersDate);
void random_serach_fragment(vector<MassegeLog> myVec);
void search_afterDate(vector<MassegeLog> myVec);
void search_type(vector<MassegeLog> myVec);
auto filler_random_date(){
    date res;
    res.day = rand() % 30+1;
    res.month = rand() % 11+1;
    res.year = rand() % 70+1950;
    return res;
}
void random_search_afterDate(vector<MassegeLog> myVec);
void random_search_type(vector<MassegeLog> myVec);
auto get_date(){
    cout<<"Enter Date with a space (dd mm yyyy)"<<endl;
    int day,month,year;
    cout << ">";
    cin>> day >> month >> year;
    
    
    while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2020  ) {
              cout << "Enter correct date please: "<<endl;
              cout << ">";
                 cin>> day >> month >> year;
    }
    date reciveDate;
    reciveDate.day = day;
    reciveDate.month = month;
    reciveDate.year = year;
    
    return reciveDate;
}
void demo_mode_for_benchmark(string path_binary,string textPath, vector<MassegeLog> myVec,int num);
void random_search_type_benchmark(vector<MassegeLog> myVec);
void random_search_afterDate_benchmark(vector<MassegeLog> myVec);
void random_serach_fragment_benchmark(vector<MassegeLog> myVec);
void benchmark(string path_binary,string textPath, vector<MassegeLog> myVec);



int main() {
    setlocale(LC_ALL,"ru");
    srand( time( 0 ) );
    
    string path_binary = "myFile.txt";
    string textPath = "textfile.txt";
    int choice,hand_choice,search_choice;
    vector<MassegeLog> myVec;

    
    

   
    
    do{
        print_main_menu();
        choice = get_main_variant();
        switch (choice) {
        case 1://HAND MODE
             do{
                 print_hand_menu();
                 hand_choice = get_main_variant();
                 switch (hand_choice) {
                 case 1://ADD MASSEGE
                     {
                       struct MassegeLog msg;
                             cout<< "----- Adding new messege -----"<<endl;
                             cout<< "Enter message text:"<<endl;
                             cout<< ">"<<endl;
                             string text;
                             getline(cin, text);
                             cout<< "Enter message type:"<<endl;
                             cout<< ">"<<endl;
                             string type;
                             type =get_type_variant();
                             cout<< "Enter priority from 1 to 200:"<<endl;
                             cout<< ">"<<endl;
                             int priority;
                             priority = get_priority_variant();

                         msg.defdate = get_date();

                             msg.text=text;
                             msg.type=type;
                             msg.priority=priority;
                             msg.busyness=randomLowerOne();
                             msg.id=generateID();

                         add_to_binary(path_binary,msg);// Add to binary

                         add_to_txt(textPath,msg);//Add to txt

                         myVec.push_back(msg);//Add to vector

                         cout<<endl;
                         cout<<"---Message saved successfully---"<<endl;
                         cout<<endl;

                     }
                     break;

                 case 2://VIEW MASSEGE
                     {
                         print_fromShow_menu();
                         int num =get_fromShow_variant();
                         switch (num) {
                             case 1:{
                                 reader_bin(path_binary);
                         }
                                 break;
                             case 2:
                                 reader_text(textPath);
                             break;
                             case 3:
                                 for (int i = 0; i < myVec.size(); i++) {

                                         myVec[i].print();

                                 }

                             break;
                             default:
                                 break;
                         }

                 }
                     break;

                 case 3://SEARCH
                         print_search_menu();
                         search_choice = get_fromShow_variant();
                         switch (search_choice) {
                             case 1:
                                 search_afterDate(myVec);
                                 break;
                             case 2:

                                 serach_fragment(myVec);

                                 break;
                             case 3:
                                 search_type(myVec);
                                 break;
                         }
                     break;
             }


             }while (hand_choice != 4);
            break;

        case 2://DEMO MODE

demo_mode(path_binary,textPath,myVec);
            break;

        case 3://BENCHMARK
                benchmark(path_binary, textPath, myVec);
            break;
    }


    }while (choice != 4);

    
    
    return 0;
}

// function declaration
void print_main_menu() { //Выводим опции
    cout<<endl;
    cout << "Select the option:" << endl;
    cout << "1. Manual mode" << endl;
    cout << "2. Demo mode" << endl;
    cout << "3. Benchmark mode" << endl;
    cout << "4. Exit" << endl;
    cout << ">";
}
void print_hand_menu() { //Выводим опции
    cout<<endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Add new massage" << endl;
    cout << "2. View messages" << endl;
    cout << "3. Search" << endl;
    cout << "4. Exit to main menu" << endl;
    cout << ">";
}
void print_whereToAdd_menu() { //Выводим опции
    cout<<endl;
    cout << "Where would you like to add this messege?" << endl;
    cout << "1. To b" << endl;
    cout << "2. Demo mode" << endl;
    cout << "3. Benchmark mode" << endl;
    cout << "4. Exit" << endl;
    cout << ">";
}
void print_fromShow_menu() { //Выводим опции
    cout<<endl;
    cout << "Where to get messages?" << endl;
    cout << "1. From Binary file" << endl;
    cout << "2. From Text file" << endl;
    cout << "3. From Vektor" << endl;
    cout << ">";
}
void print_search_menu() { //Выводим опции
    cout<<endl;
    cout << "Choose your method to search" << endl;
    cout << "1. Later then your date" << endl;
    cout << "2. By text fragment" << endl;
    cout << "3. Search by type..." << endl;
    cout << ">";
}
int get_fromShow_variant() {// Чекаем ввод
string s;
    int variant;
  
    getline(cin, s);
    sscanf(s.c_str(), "%d", &variant);

    while (variant != 1 && variant != 2 && variant != 3 ) {
              cout << "Don't play with me!. Try again: "<<endl;
                  cout << ">";
                  getline(cin, s);
                    sscanf(s.c_str(), "%d", &variant);
    }
    return variant;
}
int get_main_variant() {// Чекаем ввод

    string s;
    int variant;
    getline(cin, s);

    sscanf(s.c_str(), "%d", &variant);
    
    while (variant != 1 && variant != 2 && variant != 3 && variant != 4 ) {
        cout << "Don't play with me!. Try again: " << endl;
        cout << ">";
        getline(cin, s);
        sscanf(s.c_str(), "%d", &variant);
        
    }
 
    return variant;
}
string get_type_variant(){
    string s;
    getline(cin, s);
    while (s != "debug" && s != "info" && s != "warning" && s != "error" && s != "fatal" ) {
        cout << "Don't play with me!. Try again: " << endl;
        cout << ">";
        getline(cin, s);
    }
    return s;
}
int get_priority_variant() {// Чекаем ввод
string s;
    int variant;
    getline(cin, s);
    sscanf(s.c_str(), "%d", &variant);
    while (variant < 1 || variant > 200 ) {
              cout << "Don't play with me!. Try again: "<<endl;
                  cout << ">";
                  getline(cin, s);
                    sscanf(s.c_str(), "%d", &variant);
    }
    return variant;
}
float randomLowerOne(){
    float num = rand() % 10+1;
    return num/10;
};
int generateID(){
    int maxId = 0;
    ifstream file;

                  file.open("myFile.txt");

               if (!file.is_open()) {
                   cout<<"Error of opening file"<<endl;
               }
               else{
                   MassegeLog msg_get;
                   while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                       if (msg_get.id > maxId) {
                           maxId=msg_get.id;
                       }
                   }
                  
               }
                  file.close() ;
    static int s_itemID = maxId;
    return s_itemID++;
}

void reader_text(string textPath){
        fstream textFile;
    
    textFile.open(textPath,fstream::in);
    
    if (!textFile.is_open()) {
    cout<<"Error of opening file"<<endl;
       }
     else{
         string line;
         while (!textFile.eof()) {
             line = "";
             getline(textFile, line);
             cout<<line<<endl;
         }
      
          }
    textFile.close();
}
void reader_bin(string path_binary){
    ifstream file;

                    file.open(path_binary);

                 if (!file.is_open()) {
                     cout<<"Error of opening file"<<endl;
                 }
                 else{
                     MassegeLog msg_get;
                     while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                         msg_get.print();
                     }
                 }
                
                    file.close() ;
}

void add_to_binary(string path_binary,MassegeLog msg){
    ofstream file;// bin file

           file.open(path_binary, ofstream::app);

        if (!file.is_open()) {
            cout<<"Error of opening file"<<endl;
        }
        else{
            file.write((char*)&msg, sizeof(MassegeLog));
        }

           file.close() ;
}
void add_to_txt(string textPath, MassegeLog msg){
                             fstream textFile;// txt file

                             textFile.open(textPath,fstream::in | fstream::app);

                             if (!textFile.is_open()) {
                             cout<<"Error of opening file"<<endl;
                                }
                              else{
                                              textFile<<"-------------"<<endl;
                                              textFile<<"ID:"<<msg.id<<endl;
                                              textFile<<"Text: "<<msg.text<<endl;
                                              textFile<<"Date: "<<msg.defdate.day<<"."<<msg.defdate.month<<"."<<msg.defdate.year<<endl;
                                              textFile<<"Type: "<<msg.type<<endl;
                                              textFile<<"Priority: "<<msg.priority<<endl;
                                              textFile<<"Busyness: "<<msg.busyness<<endl;

                                   }
                             textFile.close();
}

void demo_mode(string path_binary,string textPath, vector<MassegeLog> myVec){
    cout<< "-----DEMO MODE-----"<<endl;
    sleep(1);
//    float num = rand() % 30+10;
    float num = rand() % 5+1;
    cout<< "Creating "<<num<<" messages..."<<endl;
    
    for (int i=0; i < num; i++) {
        int pr = rand() %200 +1;
                                struct MassegeLog msg;
                                      string text=random_msgText(15,5);
                                      string type =random_msgType();
                                      msg.text = text;
                                      msg.type = type;
                                     msg.priority=pr;
                                      msg.busyness=randomLowerOne();
                                      msg.id=generateID();
        
        msg.print();
        cout<<endl;
        add_to_binary(path_binary,msg);// Add to binary

        add_to_txt(textPath,msg);//Add to txt

        
    }
    cout<<endl;
    cout<<"-----Messages succesfully created-----"<<endl;
    cout<<endl;
    
    random_serach_fragment( myVec );
    
    random_search_afterDate(myVec);
    
    random_search_type(myVec);
    

    cout<<endl;
    cout<<"----Demo mode ended----"<<endl;
}
string random_msgText(int a,int b){
    int num = rand() % a+b;
    string messege;
    for (int i = 0; i<num; i++) {
        int a = rand() % 25+97;
        char ch = a;
        messege.push_back(ch);
    }
    return messege;
}

string random_msgType(){
    string type;
    int num = rand() %5+1;
    switch (num) {
        case 1:
            type = "debug";
            break;
        case 2:
        type = "info";
        break;
        case 3:
        type = "warning";
        break;
        case 4:
        type = "error";
        break;
        case 5:
        type = "fatal";
        break;
            
        default:
            break;
    }
    
    return type;
}
void serach_fragment(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;
    cout<<"Enter fragment you need to find:"<<endl;
    string s;
    getline(cin, s);
    int j=0;
    for (int i = 0; i < myVec.size(); i++) {

        auto res = myVec[i].text.find(s);

        if (res <= myVec[i].text.size()) {
            myVec[i].print();
            j++;
        }

    }
    if (j==0) {
            cout<< "---Nothing was found---"<<endl;
                   sleep(1);
    }
}

void random_serach_fragment(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;

    string s = random_msgText(3,0);
    
    cout<< "Searching for "<<"'"<<s<<"'"<<"..."<<endl;
    cout<<endl;
    sleep(3);
    int j=0;
    for (int i = 0; i < myVec.size(); i++) {

        auto res = myVec[i].text.find(s);

        if (res <= myVec[i].text.size()) {
            myVec[i].print();
            cout<<endl;
            j++;
        }
    }
    if (j==0) {
        cout<<endl;
            cout<< "---Nothing was found---"<<endl;
        cout<<endl;
                   sleep(2);
    }

}
void random_serach_fragment_benchmark(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;

    string s = random_msgText(3,0);
    
    int j=0;
    for (int i = 0; i < myVec.size(); i++) {

        auto res = myVec[i].text.find(s);

        if (res <= myVec[i].text.size()) {
            j++;
        }
    }

}
bool compare(date vectorDate,date usersDate){
    bool isVectorMore;
    if (vectorDate.year > usersDate.year) {
        isVectorMore = true;
    }
    else if (vectorDate.year == usersDate.year){
        if (vectorDate.month > usersDate.month) {
            isVectorMore = true;
        }
        else if (vectorDate.month == usersDate.month){
            if (vectorDate.day > usersDate.day) {
                isVectorMore = true;
            }
            else if (vectorDate.day == usersDate.day){
                isVectorMore = true;
            }
            else{
                isVectorMore = false;
            }
        }
        else{
            isVectorMore = false;
        }
    }
    else{
        isVectorMore = false;
    }
    return isVectorMore;
}

void search_afterDate(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;
    cout<<"Enter min date:"<<endl;
    date usersDate;
    
    cin>>usersDate.day>>usersDate.month>>usersDate.year;
    
    int j=0;
    for (int i = 0; i < myVec.size(); i++) {


       
        if (compare(myVec[i].defdate, usersDate)) {
            myVec[i].print();
            j++;
        }

    }
    if (j==0) {
            cout<< "---Nothing was found---"<<endl;
                   sleep(1);
    }
}
void random_search_afterDate(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;
    date usersDate;
    usersDate = filler_random_date();
    cout<< "Searching for messages newer then "<< usersDate.day<<"."<< usersDate.month<<"."<< usersDate.year<<"..."<<endl;
    cout<<endl;
    sleep(3);

    int j=0;
    for (int i = 0; i < myVec.size(); i++) {


       
        if (compare(myVec[i].defdate, usersDate)) {
            myVec[i].print();
            j++;
        }

    }
    if (j==0) {
            cout<< "---Nothing was found---"<<endl;
                   sleep(1);
    }
    
}
void random_search_afterDate_benchmark(vector<MassegeLog> myVec){
    myVec.clear();
    myVec.shrink_to_fit();
    
    ifstream file;
                      file.open("myFile.txt");
                   if (!file.is_open()) {
                       cout<<"Error of opening file"<<endl;
                   }
                   else{
                       MassegeLog msg_get;
                       while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                           myVec.push_back(msg_get);

                       }
                      
                   }
                      file.close() ;
    date usersDate;
    usersDate = filler_random_date();
    int j=0;
    for (int i = 0; i < myVec.size(); i++) {


       
        if (compare(myVec[i].defdate, usersDate)) {
            j++;
        }

    }
    
}


void search_type(vector<MassegeLog> myVec){

    ifstream file;
                         file.open("myFile.txt");
                      if (!file.is_open()) {
                          cout<<"Error of opening file"<<endl;
                      }
                      else{
                          MassegeLog msg_get;
                          while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                              myVec.push_back(msg_get);

                          }
                         
                      }
                         file.close() ;
    cout<<endl;
    cout<<"Enter message type:"<<endl;
    string usersType = get_type_variant();
    cout<<endl;
    cout<<"Enter minimal date:"<<endl;
    date usersMin = get_date();
    cout<<endl;
    cout<<"Enter maximum date:"<<endl;
    date usersMax = get_date();
    MassegeLog maxRate;
    maxRate.priority=0;
    int j=0;
        for (int i = 0; i < myVec.size(); i++) {


           
            if ((myVec[i].type == usersType) && (compare(myVec[i].defdate, usersMin)) && (compare(usersMax, myVec[i].defdate))) {
                if (myVec[i].priority > maxRate.priority) {
                    maxRate = myVec[i];
                    j++;
                }
            }
        }
    
        if (j==0) {
                cout<< "---Nothing was found---"<<endl;
                       sleep(1);
        }
        else{
            maxRate.print();
        }
    }
void random_search_type(vector<MassegeLog> myVec){
    ifstream file;
                            file.open("myFile.txt");
                         if (!file.is_open()) {
                             cout<<"Error of opening file"<<endl;
                         }
                         else{
                             MassegeLog msg_get;
                             while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                                 myVec.push_back(msg_get);

                             }
                            
                         }
                            file.close() ;
    
    string usersType = random_msgType();
    date usersMin = filler_random_date();
    date usersMax = filler_random_date();
    usersType = "error";
    cout<<endl;
    cout<<"Seraching for a message with type "<<"'"<<usersType<<"'"<<" newer then "<< usersMin.day<<"."<< usersMin.month<<"."<< usersMin.year<<" and older then "<<usersMax.day<<"."<< usersMax.month<<"."<< usersMax.year<<" with a max rate..."<<endl;
     sleep(3);
    MassegeLog maxRate;
    maxRate.priority=0;
    int j=0;
        for (int i = 0; i < myVec.size(); i++) {
            if ((myVec[i].type == usersType) && (compare(myVec[i].defdate, usersMin)) && (compare(usersMax, myVec[i].defdate))) {
                if (myVec[i].priority > maxRate.priority) {
                    maxRate = myVec[i];
                    j++;
                }
            }
        }
    
        if (j==0) {
            cout<<endl;
                cout<< "---Nothing was found---"<<endl;
                       sleep(1);
        }
        else{
            maxRate.print();
        }
    
}
void random_search_type_benchmark(vector<MassegeLog> myVec){
    ifstream file;
                            file.open("myFile.txt");
                         if (!file.is_open()) {
                             cout<<"Error of opening file"<<endl;
                         }
                         else{
                             MassegeLog msg_get;
                             while(file.read((char*)&msg_get, sizeof(MassegeLog))){
                                 myVec.push_back(msg_get);

                             }
                            
                         }
                            file.close() ;
    
    string usersType = random_msgType();
    date usersMin = filler_random_date();
    date usersMax = filler_random_date();
    usersType = "error";

    MassegeLog maxRate;
    maxRate.priority=0;
    int j=0;
        for (int i = 0; i < myVec.size(); i++) {
            if ((myVec[i].type == usersType) && (compare(myVec[i].defdate, usersMin)) && (compare(usersMax, myVec[i].defdate))) {
                if (myVec[i].priority > maxRate.priority) {
                    maxRate = myVec[i];
                    j++;
                }
            }
        }
    
}
    
void benchmark(string path_binary,string textPath, vector<MassegeLog> myVec){
    
    chrono::duration<float> new_duration;
    int num;
    for (num = 450; ; num = num * 2) {
    
    auto start = chrono::high_resolution_clock::now();
    demo_mode_for_benchmark(path_binary,textPath,myVec,num);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<float> duration = end - start;
        
        new_duration = duration;
    
    cout<<"Number of created message: "<<num<<endl;
    cout<<"Time:"<<duration.count()<<endl;
    cout<<"Byte: "<<num * 80 <<endl;
        
        if (new_duration.count() >= 2) {
            break;
        }
    cout<<endl;
    }
    cout<<"end 1"<<endl;
    cout<<num<<endl;
    num = num * 1.5;
    for (num; ; num = num * 1.3) {

       auto start = chrono::high_resolution_clock::now();
       demo_mode_for_benchmark(path_binary,textPath,myVec,num);
       auto end = chrono::high_resolution_clock::now();

       chrono::duration<float> duration = end - start;

           new_duration = duration;

       cout<<"Number of created message: "<<num<<endl;
       cout<<"Time:"<<duration.count()<<endl;
       cout<<"Byte: "<<num * 80 <<endl;

           if (new_duration.count() >= 8) {
               break;
           }
       cout<<endl;
       }
    cout<<"end 2"<<endl;
    cout<<num<<endl;
    num = num * 1.2;
    for (num; ; num = num * 1.1) {
        if (new_duration.count() >= 10) {
            break;
        }
       auto start = chrono::high_resolution_clock::now();
       demo_mode_for_benchmark(path_binary,textPath,myVec,num);
       auto end = chrono::high_resolution_clock::now();

       chrono::duration<float> duration = end - start;

           new_duration = duration;

       cout<<"Number of created message: "<<num<<endl;
       cout<<"Time:"<<duration.count()<<endl;
       cout<<"Byte: "<<num * 80 <<endl;

           if (new_duration.count() >= 10) {
               break;
           }
       cout<<endl;
       }

}

void demo_mode_for_benchmark(string path_binary,string textPath, vector<MassegeLog> myVec,int num){

        
        for (int i=0; i < num; i++) {
            int pr = rand() %200 +1;
                                    struct MassegeLog msg;
                                          string text=random_msgText(15,5);
                                          string type =random_msgType();
                                          msg.text = text;
                                          msg.type = type;
                                         msg.priority=pr;
                                          msg.busyness=randomLowerOne();
                                          msg.id=generateID();
            
            add_to_binary(path_binary,msg);// Add to binary

            add_to_txt(textPath,msg);//Add to txt
            

            
        }

        random_serach_fragment_benchmark( myVec );
        
        random_search_afterDate_benchmark(myVec);
        
        random_search_type_benchmark(myVec);
    
        

        cout<<endl;

}

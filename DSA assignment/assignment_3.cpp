#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

long long m = 1000000007;

long long modulo(long long i) {
    long long x = 263;

    if (i == 0) {
        return 1;
    }

    long long result = 1;
    x = x % m;

    while (i > 0) {
        // If i is odd, multiply x with the result
        if (i % 2 == 1) {
            result = (result * x) % m;
        }

        // Square x and reduce i by half
        x = (x * x) % m;
        i = i / 2;
    }

    return result;
}

int countcomma(string line){
    int count = 0;
    for(int i=0 ; i<line.size() ; i++){
        if(line[i] == ','){
            count++;
        }
    }
    return count;
}

// bool cmp(pair<PhoneRecord*, int>& a,pair<PhoneRecord*, int>& b)
// {
//     return a.second > b.second;
// }

vector<string> addname(string name){
    vector<string> result;
    string str = name;
    str = str + ' ';
    string word;
    word = "";
    for(int i=0 ; i<str.size() ; i++){
        if(str[i] == ' '){
            result.push_back(word);
            word = "";
        }
        else{
            word = word + str[i];
        }
    }
    return result;
}

bool compare1(string q,vector<string> name){
    for(int i=0 ; i<name.size() ; i++){
        if(!q.compare(name[i])){
            return true;
        }
    }
    return false;
}

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str){
        long long h = 0;
        
        for(int i=0 ; i < str.size() ; i++){
            h = h + (((int)str[i]) * (modulo(i)));
        }

        return h % 263;
    }
    

    // Add your own implementation for adding a contact
    void addContact( PhoneRecord* record){
        string str ;
        str = record-> getName();
        str = str + " ";
        string word = "";
        for(int i  = 0; i<str.size() ; i++){
            if(str[i] == ' '){
                int key;
                key = computeHash( str );
                HashTableRecord* temp = new HashTableRecord(key,record);
                if(hashTable[key] == nullptr){
                    hashTable[key] = temp;
                }
                else{
                    HashTableRecord* trav = hashTable[key];
                    while( trav-> getNext()){
                        trav = trav-> getNext();
                    }
                    trav-> setNext( temp );
                }
                word = "";
            }
            else{
                word = word + str[i];
            }
        }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName){
        vector<PhoneRecord*> fetched_vector=fetchContacts(searchName);
        PhoneRecord* temp=fetched_vector[0];
        if(fetched_vector.empty())
        {
            return false;
        }
        
       
        else
        {   bool flag=true;
            string buff =temp->getName();
            stringstream s;
            HashTableRecord* prev;
            while(getline(s,buff,' '))
            {
                HashTableRecord* ptr=hashTable[computeHash(buff)];
                
                while(ptr!=nullptr)
                {   prev=ptr;
                    if(ptr->getRecord()==temp)
                    {
                      if(ptr->getRecord()->getName()!=*searchName && flag)
                       {
                        return false;
                       }
                       if(ptr==hashTable[computeHash(buff)])
                       {
                         hashTable[computeHash(buff)]=ptr->getNext();
                         ptr->setNext(nullptr);
                         delete ptr;
                       }

                       else
                       {
                          prev->setNext(ptr->getNext());
                          ptr->setNext(nullptr);
                          delete  ptr;
                       }
                    }  
                    prev=ptr;
                    ptr=ptr->getNext();
                }

            } 
        return true;
        }
        
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){

        map<PhoneRecord* , int> freq;
        
        string str ;

        str = *query;

        string tquery = str;

        str = str + " ";
        string word = "";
        vector<string> names;
        for(int i=0 ; i<str.size() ; i++){
            if(str[i] == ' '){
                names.push_back(word);
                word = "";
            }
            else{
                word = word + str[i];
            }
        }

        for(int i=0 ; i<names.size() ; i++){
            int k;
            k = computeHash(names[i]);
            HashTableRecord* trav = hashTable[k];
            HashTableRecord* trav2 = hashTable[k];
            if(hashTable[k] != nullptr){
                while(trav-> getNext()){
                    freq[trav-> getRecord()]++;
                    trav = trav-> getNext();
                }
                while(trav2-> getNext()){
                    vector<string> RecordName = addname(trav2->getRecord()->getName());
                    for(int i=0 ; i<names.size() ; i++){
                        if(compare1(names[i],RecordName)){
                            freq[trav2-> getRecord()]++;
                        }
                        if(trav2-> getRecord()-> getName() == tquery){
                            freq[trav2-> getRecord()]++;
                        }
                    }
                    trav2 = trav2-> getNext();
                }
            } 
        }





        // for(int i  = 0; i<str.size() ; i++){
        //     if(str[i] == ' '){
        //         int k;
        //         k = computeHash( query );
        //         HashTableRecord* trav = hashTable[k];
        //         if(hashTable[k] != nullptr){
        //             while(trav-> getNext()){
        //                 //string address;
        //                 //address = trav-> getRecord();
        //                 freq[trav-> getRecord()]++;
        //                 trav = trav-> getNext();
        //             }
        //         }       
        //         word = "";
        //     }
        //     else{
        //         word = word + str[i];
        //     }
        // }

        // int spacecount = 0;
        // string name;
        // name = query;
        // for(int i=0 ; i<name.size() ; i++){
        //     if (name[i] == ' '){
        //         spacecount++;
        //     }
        // }

        // HashTableRecord* trav = 

        // if(spacecount > 0){
        //     for(auto &i : freq){ 
                
        //     }
        // }


        vector<pair<PhoneRecord*,int>> vec1;
        for(auto &i:freq){
            vec1.push_back(make_pair(i.first,i.second));
        }
        
        multimap<int,PhoneRecord*> mpp;
        vector<PhoneRecord*> result;
            for(auto it=freq.begin();it!=freq.end();it++)
            {
                mpp.insert({it->second,it->first});
            }
            for(auto it=mpp.begin();it!=mpp.end();it++)
            {
                result.insert(result.begin(),it->second);
            }

        // sort(vec1.begin(),vec1.end(),cmp);
        // vector<PhoneRecord*> result;
        // for(auto &i:vec1){
        //     result.push_back(i.first);
        // }

        return result;

        
    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const;

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename){
        ifstream details(filename);
        string line;
        // if( details.open() ){

            while( getline(details,line) ){
                int comma = countcomma(line);
                stringstream stg (line);
                string str,org,num;
                vector<string> numbers;
                getline(stg,str,',');

                while( comma!=1 ){
                    getline(stg,num,',');
                    numbers.push_back(num);
                    comma--;
                }

                getline(stg,org);
                PhoneRecord* rec = new PhoneRecord(str , org , numbers);
                addContact(rec);
            }
        //}
        // else{
        //     cout << "Error : File not opened" << endl;
        // }
    }

    // // Destructor
    // ~PhoneBook();

};

// void readfromfile(string file_path){

    // ifstream file(file_path);
    // string line;
    // int count = 0;
    // if( file.open() ){
    //     while(getline(file,line)){
    //         count++;
    //     }
    // }
    // else{
    //     "File not opened";
    // }
    // file.close();

    // ifstream details(file_path);
    // string line;
    // if( file.open() ){
        
    //     while( getline(details,line) ){
    //         int comma = countcomma(line);
    //         stringstream stg (line);
    //         string str,org,num;
    //         vector<string> numbers;
    //         getline(stg,str,',');

    //         while( comma!=1 ){
    //             getline(stg,num,',');
    //             numbers.push_back(num);
    //             comma--;
    //         }

    //         getline(stg,org);

    //     }
    // }

// }

// int main() {
//     // Your test cases and program logic can go here.
//     return 0;
// }

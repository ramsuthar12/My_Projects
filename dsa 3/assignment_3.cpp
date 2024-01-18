#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

long long int mod(int i,long long int p){
    int long long ans=1;

    while(i--){
        ans=((ans%p)*(263))%p;
    }
    
    return ans;
    
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

vector<string> addname(const string &name){
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
        long long int p=1000000007;
        long long int hashindex=0;
        for(int i=0;i<str.length();i++){
            hashindex =hashindex +((int)(str[i]))*(mod(i,p));
        }
        hashindex=hashindex % HASH_TABLE_SIZE;
        return hashindex;
    }

    // Add your own implementation for adding a contact
    void addContact( PhoneRecord* record){
        string str ;
        str = record-> getName();
        str = str + ' ';
        string word = "";
        for(int i  = 0; i<str.size() ; i++){
            if(str[i] == ' '){
                int key;
                key = computeHash( word );
                HashTableRecord* temp = new HashTableRecord(key,record);
                if(hashTable[key] == nullptr){
                    hashTable[key] = temp;
                }
                else{
                    HashTableRecord* trav = hashTable[key];
                    while( trav-> getNext() != nullptr){
                        trav = trav -> getNext();
                    }
                    trav -> setNext( temp );
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
        string name = *searchName;
        vector<PhoneRecord*> contacts = fetchContacts(&name);
        name = *searchName;
        if(!contacts.empty()){
            PhoneRecord* trav=contacts[0];
            vector<string> separated = addname(contacts[0]->getName());
            vector<string> nametodelete=addname(name); 
            
            for(int i=0;i<separated.size();i++){
                
                int key=computeHash(separated[i]);
                HashTableRecord* trav2=hashTable[key];
                HashTableRecord*trav3=trav2;
                while(trav2!=nullptr || (trav2==hashTable[key] && trav2->getRecord()==trav)){
                    HashTableRecord* temp= trav2;   
                    if(trav2->getRecord()==trav){
                        if(trav2->getRecord()->getName()!=name&& nametodelete.size()>1){
                            return false;
                        }
                        if(trav2==hashTable[key])
                        {
                            hashTable[key]=temp->getNext();
                            temp->setNext(nullptr);
                            delete temp;
                            break;
                        }
                        else{
                            trav3->setNext(temp->getNext());
                            temp->setNext(nullptr);
                            delete temp;
                            break;
                        }
                    }
                    trav3=trav2;
                    trav2=trav2->getNext();
                }   
            }
            return true;   
        }
        else{
            return false;
        }
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){

        map<PhoneRecord* , int> freq;
        multimap<int,PhoneRecord*> mpp;
        vector<PhoneRecord*> result;
        
        string str ;

        str = *query;

        string tquery = str;

        str = str + ' ';
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
            HashTableRecord* trav2 = hashTable[k];
            while(trav2 != nullptr){
                vector<string> RecordName = addname(trav2->getRecord()->getName());
                if(count(RecordName.begin(),RecordName.end(),names[i]) > 0)
                    {
                        freq[trav2->getRecord()]++;
                        if(trav2->getRecord()->getName()==tquery)
                        freq[trav2->getRecord()]++;
                    
                    }
                    trav2 = trav2->getNext();
            }
        } 
        for(auto it=freq.begin();it!=freq.end();it++){
            mpp.insert({it->second,it->first});
        }
        for(auto it=mpp.begin();it!=mpp.end();it++){
            result.insert(result.begin(),it->second);
        }
        return result;
    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo( PhoneRecord* record) {
        stringstream name;
        name << record-> getName();
        int count;
        count = 0;
        string word = "";
        while(getline(name,word,' ')){
            long long k = computeHash(word);
            HashTableRecord* rec = hashTable[k];
            while(rec){
                if(rec-> getRecord() == record)
                count++;
                rec = rec-> getNext();
            }
        }
        return count;
    }

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
    }
    // // Destructor
    // ~PhoneBook();
};
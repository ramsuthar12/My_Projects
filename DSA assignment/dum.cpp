#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include<bits/stdc++.h>

using namespace std;


//bool cmp(pair<PhoneRecord*, int>& a,pair<PhoneRecord*, int>& b)
//{
  //  return a.second > b.second;
//}

int countcomma(string line){
    int count = 0;
    for(int i=0 ; i<line.size() ; i++){
        if(line[i] == ','){
            count++;
        }
    }
    return count;
}

long long modulo(long long i) {
    long long x = 263;
    long long m=1000000007;

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

    void addContact(PhoneRecord* record){
        
        stringstream name;
        name << (record)->getName();
        string buff;
        
        while(getline(name,buff,' '))
        {
            getline(name,buff,' ');
            int key=computeHash(buff);
            HashTableRecord* temp = new HashTableRecord(key,record);
            if(hashTable[key]==nullptr)
            {
                hashTable[key]==temp;
            }

            else
            {   
                HashTableRecord* pointer=hashTable[key];
                while(pointer->getNext())
                {
                   pointer=pointer->getNext();
                }
                pointer->setNext(temp);
             
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

        }
        
    };

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query)
    {
        stringstream s;
      //  stringstream name_in_phonerecord;
        s << *query;
        string buff = "";
     //   string(words_in_query[i]) = *query;
        //stringstream s2;
        //s2 <<(words_in_query[i]);
        vector<string> words_in_query;
        string buffer3="";
        while(getline(s,buffer3,' '))
        {
            words_in_query.push_back(buffer3);
        }

       map<PhoneRecord*,int> m1;

       for(int i=0;i<words_in_query.size();i++)
       {
       HashTableRecord* temp = hashTable[computeHash(words_in_query[i])];
       if(temp!=nullptr){
       while(temp->getNext()!=nullptr)
       {
          buff = temp->getRecord()->getName();
          string word_of_phonerecord_name = "";
          stringstream name_in_phonerecord;
           if(buff==(words_in_query[i]))
            {
                m1[temp->getRecord()]++;
            }
         // m1[temp->getRecord()]++;
          name_in_phonerecord << buff;
          while(getline(name_in_phonerecord,word_of_phonerecord_name,' '))
          { 
            if(words_in_query[i]==word_of_phonerecord_name)
            {
                m1[temp->getRecord()]++;
            }
          }
          temp=temp->getNext();
        }
       }
    
       }

        vector<pair<PhoneRecord*,int>> vec1;
        for(auto &i:m1)
        {
            vec1.push_back(make_pair(i.first,i.second));
        }
       // map<PhoneRecord*,int> m1;
        multimap<int,PhoneRecord*> mpp;
        vector<PhoneRecord*> result;
            for(auto it=m1.begin();it!=m1.end();it++)
            {
               mpp.insert({it->second,it->first});
            }
            for(auto it=mpp.begin();it!=mpp.end();it++)
            {
                result.insert(result.begin(),it->second);
            }
            
        
        // sort(vec1.begin(),vec1.end(),cmp());
        // 
        // for(auto &i:vec1)
        // {
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
      //  if( details.open() ){

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
      //  }
       // else{
         //   cout << "Error : File not opened" << endl;
        //}
    }

    // Destructor
    //~PhoneBook();
};
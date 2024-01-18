#include <bits/stdc++.h>
#include <sstream>

using namespace std;

bool cmp(pair<string, int>& a,pair<string, int>& b)
{
    return a.second > b.second;
}

// class record{

//     public:
//     string name;
//     int number;

//     public:
//     record(string n,int num){
//         this-> name = n;
//         this-> number = num;
//     }

// };

int countcomma(string line){
    int count = 0;
    for(int i=0 ; i<line.size() ; i++){
        if(line[i] == ','){
            count++;
        }
    }
    return count;
}

int main(){

    // record* r1("hello", 24);
    // cout << r1->name << endl;
    // return 0;
    // string line; 
    // line = "Rahul Kumar Mishra,6934782150,2201234567,Tech Innovators Inc.";
    // ifstream f1("dummy.txt");
    // getline(f1,line);
    // int c = countcomma(line);
    // cout << c << endl;

    // ifstream details("dummy.txt");

    //if( details.open() ){
        
    //     getline(details,line);
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

        
    // //}

    // cout << str << endl;
    // cout << org << endl;
    // for(int i=0 ; i<numbers.size() ; i++){
    //     cout << numbers[i] << endl;
    // }

    map<string, int> m1;

    m1["hi"] = 1;
    m1["we"] = 2;
    m1["are"] = 4;
    m1["friends"] = 0;
    m1["here"] = 8;

    // map<string, int> map :: iterator i = map.begin();
    for(auto &i : m1){ 
        cout << i.first << " " << i.second << endl;
    }

    for(int i=0 ; i<m1.size() ; i++){
        cout <<  << endl;
    }

    vector<pair<string,int>> vec1;
        for(auto &i:m1){
            vec1.push_back(make_pair(i.first,i.second));
        }
        
        sort(vec1.begin(),vec1.end(),cmp);
        vector<string> result;
        for(auto &i:vec1){
            result.push_back(i.first);
        }

        //return result;
        
    for(int i=0 ; i<result.size() ; i++){
        cout << result[i] << endl;
    }


    return 0;
}
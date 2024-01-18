#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    string chapter_name = "Chapter3.txt";
    ifstream chap(chapter_name);
        string ss;
        string word = "";
        getline(chap,ss);
        for(int i = 0 ; i<ss.size() ; i++){
            if (ss[i] > 90 && ss[i] < 97 || ss[i] < 64 || ss[i] > 122 ){
                if(ss[i] != 39)
                ss[i] = ' ';
            }
        }
        for(int i = 0 ; i<ss.size() ; i++){
            if(ss[i] != ' '){
                word = word + ss[i];
            }
            else{
                cout << word << endl;
                word = "" ;
            }
        }
    return 0;

}


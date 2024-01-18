#include<bits/stdc++.h>
#include<fstream>
#include<vector>
using namespace std;

vector<string> details;

vector<string> breakline(string line){
    string subline = "";
    vector<string> ans;
    for(int i = 0 ; i<line.size() ; i++){
        if(line[i] == ' ' || line[i] == ','){
            ans.push_back(subline);
            subline = "";
        }
        else{
            subline = subline + line[i];
        }
    }
    return ans;
}

class node{
    public:
    int data;
    node* left;
    node* right;

    
};

node* insert(node* n, int d){
    //cout << "hello" <<endl;
    if(n == nullptr){

    node* temp = new node();
    temp->data = d;
    temp->left = nullptr;
    temp->right = nullptr;

    return temp;
    }

    if(d < n->data){
        n->left = insert(n->left,d);
    }
    else{
        n->right = insert(n->right,d);
    }
    return n;
}


// class normal{
//     public:
//     void getaddress(){
//         cout << "Address is " << this << endl;
//     }
// };

bool change(int &v){
    v = 10;
    return true;
}

int main(){
    
    // node* root = nullptr;
    // cout << "hi" << endl;
    // root = insert(root , 10);
    // cout << root->data << endl;
    // root = insert(root , 7);
    // cout << root->data << endl;
    // root = insert(root , 9);
    // cout << root->data << endl;
    // root = insert(root , 11);
    // cout << root->data << endl;
    // cout << root->left->data << endl;
    // cout << root->left->right->data << endl;
    // cout << root->right->data << endl;

    int x = 4;
    change(x);
    cout  << x << endl;
    
    // ifstream file("blue.txt");
    // string s1 ; 
    // getline(file,s1);
    // cout << s1 << endl;
    // details = breakline(s1);
    // cout << details.size() << endl;
    // for(int i = 0 ; i<details.size() ; i++){
    //     cout << details[i] << endl;
    // }
    // string s1 = "224";
    // int ans = stoi(s1);
    // cout << typeid(ans).name();
    // normal n1;
    // cout << "Address of n1 " << &n1 << endl;
    // n1.getaddress();
    return 0 ;
}

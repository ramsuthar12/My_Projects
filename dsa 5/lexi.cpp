#include<bits/stdc++.h>
using namespace std;

int main(){
    string s1 = "Apple Us";
    string s2 = "apple Me";

    int ans = s1.compare(s2);
    cout << s1.compare(s2);
    if(ans == 0){
        cout << "Both s1 and s2 are same" << endl;
    }
    else if(ans < 0){
        cout << "s1 is smaller in lexi order" << endl;
    }
    else if(ans > 0){
        cout << "s1 is larger in lexi order" << endl;
    }
    return 0;
}
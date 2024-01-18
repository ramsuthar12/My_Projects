#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
using namespace std;

class StudentRecord{
    private:
    
    string studentName;
    string rollNumber;

    public:
    
    string get_studentName() {
        return this-> studentName;
    }      
    
    void set_studentName(string Name){
        this-> studentName = Name;
    }

    string get_rollNumber(){
        return this-> rollNumber;
    }
    
    void set_rollNumber(string rollnum){
        this-> rollNumber = rollnum;
    }
};

class Node{
    
    private:
	
    Node* next;
	StudentRecord* element;
    
    public:
    
    Node* get_next(){
        return this-> next;
    }
    
    StudentRecord* get_element(){
        return this-> element;
    }

    void set_next(Node* value){
        this-> next = value;
    }
    
    void set_element(StudentRecord* student){
        this-> element = student;
    }

};

class Entity {
    
    private:
    
    string name;
    Node* iterator;

    public:
    
    string get_name(){
        return this-> name;
    }
    
    void set_name(string Name){
        this-> name = Name;
    }
    
    Node* get_iterator(){
        return this-> iterator;
    }
    
    void set_iterator(Node* iter){
        this-> iterator = iter;
    }
};


class LinkedList : public Entity {

    public:
    void add_student(StudentRecord student){
        StudentRecord* stdrec = new StudentRecord;
        stdrec-> set_studentName( student.get_studentName() );
        stdrec-> set_rollNumber( student.get_rollNumber() );

        Node* node = new Node();
        node-> set_element( stdrec );
        node-> set_next( nullptr );

        Node* temp = get_iterator();
        while( temp->get_next() != nullptr){
            temp = temp-> get_next();
        }
        temp-> set_next( node );
    }
    void delete_student(string studentName){

        Node* trav1 = get_iterator();
        Node* trav2 = nullptr;
        
        while( trav1-> get_element()-> get_studentName() != studentName){
            trav2 = trav1;
            trav1 = trav1-> get_next();
        }

        if( trav1 == get_iterator() ){
            set_iterator( trav1-> get_next() );
            trav1-> set_next( nullptr );
        }
        else{
            trav2 -> set_next(trav1->get_next());
            trav1 -> set_next(nullptr);
        }
    }
};

vector<StudentRecord> students;
vector<LinkedList> EntityArray;

int Checkstudent(vector<StudentRecord> vec,string name,string rollno){
    int i;
    for( i = 0 ; i<vec.size() ; i++){
        if( name == vec[i].get_studentName() && rollno == vec[i].get_rollNumber()){
            return 1;   
        }
    }
    return 0;
}

int Checkentity(vector<LinkedList> vec,string entity){
    int i;
    for( i = 0; i<vec.size() ; i++){
        if( entity == vec[i].get_name()){
            return 1;
        }
    }
    return 0;
}

void create(vector<LinkedList> vec,string word,StudentRecord *stdrec){

    if(!Checkentity( EntityArray,word )){
            LinkedList ll;
            Node* node = new Node();
            node->set_element(stdrec);
            node->set_next(NULL);
            ll.set_name(word);
            ll.set_iterator(node);
            EntityArray.push_back(ll);
        }

        else{
            for(auto it:EntityArray){
                if(word==it.get_name()){
                it.add_student(*stdrec);
                }
            }
        }
}

void read_input_file(string file_path){
    
    ifstream file(file_path);
    string line,word;
    int count = 0;
    if(file.is_open()){
    while(getline(file,line)){
        count ++;
        }
    }
    else{
        cout<<"Error: File not openened"<<endl;
    }
    file.close();
    students.reserve( count );
    
    ifstream file1(file_path);
    if(file1.is_open()){
        while(getline(file1,line)){
        
            stringstream stg (line);
            getline(stg,word,',');
            string name = word;
            getline(stg,word,',');
        
            if(!Checkstudent(students,name,word)){
            
                StudentRecord *stdrec = new StudentRecord();
                stdrec-> set_studentName(name);
                stdrec-> set_rollNumber(word);
                students.push_back(*stdrec);
                getline(stg,word,',');
                create(EntityArray,word,stdrec);
                string word1;
                getline(stg,word1,'[');
                getline(stg,word1,']');
                stringstream stg1(word1);
            
                while(getline( stg1,word,',')){
                    create(EntityArray,word,stdrec);
                }
            
                getline(stg,word1,',');
                getline(stg,word,',');
                create(EntityArray,word,stdrec);
        
                getline( stg,word1,'[');
                getline( stg,word1,']');
                
                stringstream stg2(word1);
                while(getline(stg2,word,',')){
                create( EntityArray,word,stdrec );
                }
            }
        }
    }
}

int failed_tests = 0;

void test1() {
    std::string entity_name = "CSE";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "JohnDoe") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "JohnDoe" && "Student JohnDoe is not present in the CSE Entity");
}

void test2() {
    std::string entity_name = "EE";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "SanyaSharma") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "SanyaSharma"&& "Student SanyaSharma is not present in the EE Entity");
}

void test3() {
    std::string entity_name = "DSA";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 20 && "Incorrect count of records in DSA course");
}

void test4() {
    std::string entity_name = "Programming";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 20 && "Incorrect count of records in Programming Club");
}

void test5() {
    std::string entity_name = "Toastmasters";
    LinkedList entity;
    std::string studentname = "RaviKumar";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test6() {
    std::string entity_name = "Maths";
    LinkedList entity;
    std::string studentname = "UzumakiNaruto";
    std::string studentroll = "B20CS011";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

void test7() {
    std::string entity_name = "PRML";
    LinkedList entity;
    std::string studentname = "HimashuGupta";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test8() {
    std::string entity_name = "G5";
    LinkedList entity;
    std::string studentname = "UchihaSasuke";
    std::string studentroll = "B20ES011";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

int main() {
    int failed_tests = 0;

    std::vector<void (*)()> unit_tests_list = {
        test1, test2, test3, test4, test5, test6, test7, test8
    };
    int total = unit_tests_list.size();

    try {
        read_input_file("Details.txt");
    } catch (const std::exception& e) {
        std::cout << "Could not read Sample Input File! Ensure that the file 'Details.txt' is in the folder and try again!" << std::endl;
        return 1;
    }

    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i]();
        } catch (const std::exception& e) {
            failed_tests++;
            std::cout << "Unit test #" << i+1 << " failure: " << e.what() << std::endl;
        }
    }

    if (failed_tests == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << failed_tests << " tests failed!" << std::endl;
    }

    cout << "Number of failed test cases are: " << failed_tests<< endl;
    return 0;
}

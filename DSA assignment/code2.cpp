#include<bits/stdc++.h>


#include<fstream>

#include<sstream>
using namespace std;

class StudentRecord{
    private:
    
    string studentName;
    string rollNumber;

    public:
    
    string get_studentName() {
        return studentName;
    }      
    
    void set_studentName(string Name){
        studentName = Name;
    }

    string get_rollNumber(){
        return rollNumber;
    }
    
    void set_rollNumber(string rollnum){
        rollNumber = rollnum;
    }
};

class Node{
    
    private:
	
    Node* next;
	StudentRecord* element;
    
    public:
    
    Node* get_next(){
        return next;
    }
    
    StudentRecord* get_element(){
        return element;
    }

    void set_next(Node* value){
        next = value;
    }
    
    void set_element(StudentRecord* student){
        element = student;
    }

};

class Entity {
    
    private:
    
    string name;
    Node* iterator;

    public:
    
    string get_name(){
        return name;
    }
    
    void set_name(string Name){
        name = Name;
    }
    
    Node* get_iterator(){
        return iterator;
    }
    
    void set_iterator(Node* iter){
        iterator = iter;
    }
};

vector<StudentRecord> students;

class LinkedList : public Entity {

    public:
    void add_student(StudentRecord student){
        Node* node = new Node();
        StudentRecord* sr = new StudentRecord;
        Node* temp = get_iterator();
        
        sr-> set_studentName( student.get_studentName() );
        sr-> set_rollNumber( student.get_rollNumber() );
        node-> set_element( sr );
        node-> set_next( nullptr );
        while( temp->get_next() != nullptr){
            temp = temp-> get_next();
        }
        temp-> set_next( node );
    }
    void delete_student(string studentName){

        Node* p = nullptr;
        Node* c = get_iterator();
        
        while( c-> get_element()-> get_studentName() != studentName){
            p = c;
            c = p-> get_next();
        }

        if( c != get_iterator() ){
            p -> set_next(c->get_next());

            c -> set_next(nullptr);
            
        }
        else{
            set_iterator( c-> get_next() );
            
            c-> set_next( nullptr );
        }
    }
};

vector<LinkedList> EntityArray;


bool checkent(vector<LinkedList> vect,string entity){
    for( int i = 0; i<vect.size() ; i++){
    if( entity == vect[i].get_name()){
        return true;
    }
    }
    return false;
}

void create(vector<LinkedList> vect,string word,StudentRecord *objt){

    bool value = checkent( EntityArray,word );

    if(value ){
        for(auto it:EntityArray){
            if(word==it.get_name()){
            it.add_student(*objt);
            }
        }
    }

    else{
        LinkedList llist;
        Node* node = new Node();
        node->set_element(objt);
        node->set_next(NULL);
        llist.set_name(word);
        llist.set_iterator(node);
        EntityArray.push_back(llist);
    }
}

bool checkstud(vector<StudentRecord> vect,string roll,string name){
    int i;
    for( i = 0 ; i<vect.size() ; i++){
    if( name == vect[i].get_studentName() && roll == vect[i].get_rollNumber()){
        return true;   
    }
    }
    return false;
}

void read_input_file(string file_path){
    
    ifstream fl (file_path);
    string line,word;
    int counting ;
    counting = 0;
    if(fl.is_open()){
    while(getline(fl,line)){
        counting ++;
        }
    }
    else{
        cout<<"File not openened"<<endl;
    }
    students.reserve( counting );
    fl.close();
    
    ifstream fl0(file_path);
    if(fl0.is_open()){
    
    while(getline(fl0,line)){
        
        stringstream stgt (line);
        //Reading name.
        getline(stgt,word,',');
        string name = word;
        //Reading rollno.
        getline(stgt,word,',');
        
        //duplicates.checking
        bool value = checkstud(students,name,word);


        if(!value ){
            StudentRecord *sr = new StudentRecord();
            sr-> set_studentName(name);
            sr-> set_rollNumber(word);
            students.push_back(*sr);

            //Reading department and then adding  
            getline(stgt,word,',');
            create(EntityArray,word,sr);
            //Reading courses and then adding 
            string word1;
            getline(stgt,word1,'[');
            getline(stgt,word1,']');
            stringstream stg1(word1);
        
            while(getline( stg1,word,',')){
            create(EntityArray,word,sr);

            }
            
            //Removing the leftover comma , reading hostel and adding 
            getline(stgt,word1,',');
            getline(stgt,word,',');
            create(EntityArray,word,sr);
        
            //Removing the "[]" and reading the club and adding
            getline( stgt,word1,'[');
            getline( stgt,word1,']');
            stringstream stg4(word1);
            while(getline(stg4,word,',')){
            create( EntityArray,word,sr );
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
    //cout << "test5" << endl;
    entity.delete_student(studentname);
    //cout << "test5" << endl;
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
        test1, test2,test3, test4, test5, test6, test7, test8
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


#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare){
        stopName = name;
        line = metroLine;
        this-> fare = fare;
        nextStop = nullptr;
        prevStop = nullptr;
    }

    // Getter methods
    std::string getStopName() const{
        return stopName;
    }
    MetroStop* getNextStop() const{
        return nextStop;
    }
    MetroStop* getPrevStop() const{
        return prevStop;
    }
    MetroLine* getLine() const{
        return line;
    }
    int getFare() const{
        return fare;
    }

    // Setter methods
    void setNextStop(MetroStop* next){
        this-> nextStop = next;
    }
    void setPrevStop(MetroStop* prev){
        this-> prevStop = prev;
    }
};

// MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
//     stopName = name;
//     nextStop = nullptr;
//     prevStop = nullptr;
//     line = metroLine;
//     this->fare = fare;
// }

// std::string MetroStop::getStopName() const {
//     return stopName;
// }

// MetroStop* MetroStop::getNextStop() const {
//     return nextStop;
// }

// MetroStop* MetroStop::getPrevStop() const {
//     return prevStop;
// }

// MetroLine* MetroStop::getLine() const {
//     return line;
// }

// int MetroStop::getFare() const {
//     return fare;
// }

// void MetroStop::setNextStop(MetroStop* next) {
//     nextStop = next;
// }

// void MetroStop::setPrevStop(MetroStop* prev) {
//     prevStop = prev;
// }

vector<string> details;

vector<string> breakline(string line){
    string subline = "";
    string subline2 = "";
    vector<string> ans;
    for(int i = 0 ; i<line.size() ; i++){
        if(line[i] == ' ' ){
            // if(i != line.size()-2 ){
                subline = subline + ' ';
            // }
            ans.push_back(subline);
            subline = "";
        }
        else{
            subline = subline + line[i];
        }
    }
    for(int i = 0 ; i<subline.size() ; i++){
        if(subline[i] == ','){
            break;
        }
        subline2 = subline2 + subline[i];
    }
    ans.push_back(subline2);
    // cout << '(' <<subline2 << ')' << endl;
    return ans;
}

vector<MetroStop* > make_stops_list(vector<string> details, vector<MetroStop* > stopslist, int ffare, MetroLine* lineaddress){
    //int finalfare = 0;
    string stpname = "";
    string stpname2 = "";
    for(int i = 0 ; i<details.size()-1 ; i++){
        stpname = stpname + details[i];
        // if(i != deatails.size()-2){
        //     stpname = stpname + ' ';
        // }
    }
    // cout << stpname << "||" << endl;
    for(int i = 0 ; i<stpname.size()-1 ; i++){
        stpname2 = stpname2 + stpname[i];
    }
    // cout << stpname2 << "||" << endl;
    MetroStop* temp = new MetroStop(stpname2, lineaddress , ffare);
    // cout << "I am in function make stop list" << endl;
    stopslist.push_back(temp);
    return stopslist;
}

vector<MetroStop*> connectlist(vector<MetroStop*> stopslist){
    for(int i = 0 ; i<stopslist.size()-1 ; i++){
        stopslist[i]-> setNextStop(stopslist[i+1]) ;
        stopslist[i+1]-> setPrevStop(stopslist[i]) ;
    }
    return stopslist;
}
// MetroLine class

class MetroLine {
private:
    std::string lineName;
    MetroStop* node;
    vector<MetroStop*> stopslist;

public:
    MetroLine(std::string name){
        lineName = name;
    }

    // Getter methods
    std::string getLineName() {
        return lineName;
    }
    MetroStop* getNode() {
        return this-> node;
    }

    // Setter methods
    void setNode(MetroStop* node){
        this-> node = node;
    }

    void populateLine(std::string filename){
        ifstream file(filename);
        string s1 ; 
            int num = 1;
        int prevfare ;
        int currfare = 0;
        int finalfare;
        while(getline(file,s1)){
                // cout << s1 << endl;
            details = breakline(s1);
                // for(int i = 0 ; i<details.size() ; i++){
                //     cout << details[i] ;
                // }
                // cout << endl;
            prevfare = currfare;
            currfare = stoi(details[details.size()-1]);
            finalfare = currfare - prevfare;
                // cout << finalfare << endl << endl;
                // cout << "hi" << endl;
            stopslist = make_stops_list(details, stopslist, finalfare, this);
                // cout << "Hello " << num++ << endl;
        }
        // cout << stopslist.size() << endl;
        // for(int i = 0 ; i<stopslist.size() ; i++){
        //     cout << stopslist[i]-> getStopName() << "--" << stopslist[i]-> getFare()<< endl;
        // }
        stopslist = connectlist(stopslist);
        setNode(stopslist[0]);
        // cout << getNode()->getNextStop()->getLine()-> getLineName() << endl;
    }

    // helper function
    void printLine() {
        for(int i = 0 ; i<stopslist.size() ; i++){
            cout << stopslist[i]-> getStopName() << endl;
        }
    }
    int getTotalStops() {
        // cout << "hi" << endl;
        return stopslist.size();
    }
};

// MetroLine::MetroLine(std::string name) {
//     lineName = name;
//     node = nullptr;
// }

// std::string MetroLine::getLineName() const {
//     return lineName;
// }

// MetroStop* MetroLine::getNode() const {
//     return node;
// }

// void MetroLine::setNode(MetroStop* node) {
//     this->node = node;
// }

// void MetroLine::printLine() const {
//     MetroStop* stop = node;
//     while (stop != nullptr) {
//         cout << stop->getStopName() << endl;
//         stop = stop->getNextStop();
//     }
// }

// int MetroLine::getTotalStops() const {

// }

// void MetroLine::populateLine(std::string filename) {
//     // Read the file and populate the line
// }

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    AVLNode* insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

int max(int a, int b){
	if(a > b){
        return a;
    }
    else{
        return b;
    }
}

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node == nullptr){
        return 0 ;
    }
    int h = max(height(node->getLeft()), height(node->getRight())) + 1;
    return h;
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    // cout << "hello4" << endl;
    int value;
    value  = height(node->getLeft()) - height(node->getRight()) ;
    return value;
}

AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    AVLNode*y = node->getRight();
	AVLNode*x = y->getLeft();

	// Perform rotation
	y->setLeft(node) ;
	node->setRight(x) ;

	// Update heights
	// node->height = max(height(node->left),
	// 				height(node->right)) + 1;
	// y->height = max(height(y->left),
	// 				height(y->right)) + 1;
    return y;

}

AVLNode* AVLTree::rotateRight(AVLNode* node) {
    AVLNode* x = node->getLeft();
	AVLNode* y = x->getRight();

	// Perform rotation
	x->setRight(node) ;
	node->setLeft(y) ;

	// Update heights
	// node->height = max(height(node->left),
	// 				height(node->right)) + 1;
	// x->height = max(height(x->left),
	// 				height(x->right)) + 1;
    return x;
}

int computeLexiOrder(string s1, string s2){
    return s1.compare(s2);
}

void AVLTree::balance(AVLNode* node) {
}

AVLNode* AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    if (node == nullptr){
        // cout << "node is nullptr" << endl;
		AVLNode* temp = new AVLNode(metroStop->getStopName());
        temp->addMetroStop(metroStop);
        return temp;
    }
    // cout << node->getStopName() << endl;
    // cout << "hello1" << endl;
	if (computeLexiOrder(metroStop->getStopName(), node->getStopName()) < 0){
		node->setLeft(insert(node->getLeft(), metroStop)) ;
    }
	else if (computeLexiOrder(metroStop->getStopName(), node->getStopName()) > 0){
    // cout << "hello2" << endl;
		node->setRight(insert(node->getRight(), metroStop)) ;
        // cout << node->getRight()->getStopName();
    }
	else {
        node->addMetroStop(metroStop);
		return node;
    }
    // cout << "hello3" << endl;
    int factor  = balanceFactor(node);
    // cout << factor << endl;
    if (factor > 1 && computeLexiOrder(metroStop->getStopName(), node->getLeft()->getStopName()) < 0)
		return rotateRight(node);

	// Right Right Case
	if (factor < -1 && computeLexiOrder(metroStop->getStopName(), node->getRight()->getStopName()) > 0)
		return rotateLeft(node);

	// Left Right Case
	if (factor > 1 && computeLexiOrder(metroStop->getStopName(), node->getLeft()->getStopName()) > 0)
	{
		node->setLeft(rotateLeft(node->getLeft())) ;
		return rotateRight(node);
	}

	// Right Left Case
	if (factor < -1 && computeLexiOrder(metroStop->getStopName(), node->getRight()->getStopName()) < 0)
	{
		node->setRight(rotateRight(node->getRight())) ;
		return rotateLeft(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}
void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

void AVLTree::populateTree(MetroLine* metroLine) {
    // AVLNode* root = nullptr;
    MetroStop* trav = nullptr;
    trav = metroLine->getNode();
    // cout << "hi" <<endl;
    while(trav != nullptr){
        //cout << "hello" <<endl;
        root = (insert(root, trav));
        // cout << root->getStopName() << "root" << endl;
        trav = trav->getNextStop();
        // cout << trav->getStopName() << "trav" <<endl;
    }
    // inOrderTraversal(root);
    // cout << getTotalNodes(root) << endl;
    setRoot(root);
}



AVLNode* AVLTree::searchStop(string stopName) {
    // if (stopName == root->getStopName()){
    //     // cout << "node is nullptr" << endl;
	// 	// AVLNode* temp = new AVLNode(metroStop->getStopName());
    //     // temp->addMetroStop(metroStop);
    //     return root;
    // }
    // cout << node->getStopName() << endl;
    // cout << "hello1" << endl;
    AVLNode* node = this -> getRoot();
    while(node != nullptr){
	if(stringCompare(stopName, node -> getStopName()) > 0){
        node = node -> getRight();
    }
    else if(stringCompare(stopName, node -> getStopName()) < 0){
        node = node -> getLeft();
    }
    else{
        return node;
    }
    }
    return nullptr;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    int x;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
    int getx() const;
    
    void setx(int value){
        x = value;
    }

    // int getx(){
    //     return x;
    // }
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}



MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

int Trip::getx() const {
    return x;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    // cout << "here in dequeque" << endl;
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    // cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    // cout << "here in dequeque" << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// Exploration* createtrip(string og,AVLNode* root){
//     cout << "Hi Hello--" << root->getStopName() << endl;
//     Exploration* tempexp = new Exploration();
//     if (root->getStopName() == og){
//         if(root->getStops().size() == 1 ){
//             Trip* tback = new Trip(root->getStops()[0]->getPrevStop(),nullptr);
//             tback->setx(1);
//             Trip* tforwd = new Trip(root->getStops()[0]->getNextStop(),nullptr);
//             tforwd->setx(2);
//             tempexp->enqueue(tback);
//             tempexp->enqueue(tforwd);
//             cout << "GG" << endl;
//             cout << tempexp->getTrips().front()->getNode()->getStopName() << endl;
//             return tempexp;
//         }
//         else{
//             for(int i = 0 ; i<root->getStops().size() ; i++){
//                 Trip* tback = new Trip(root->getStops()[i]->getPrevStop(),nullptr);
//                 tback->setx(1);
//                 Trip* tforwd = new Trip(root->getStops()[i]->getNextStop(),nullptr);
//                 tback->setx(2);
//                 tempexp->enqueue(tback);
//                 tempexp->enqueue(tforwd);
//             }
//             return tempexp;
//         }
//     }

//     if (computeLexiOrder(root->getStopName(), og) < 0)
//         createtrip(og,root->getRight() );

//     else if(computeLexiOrder(root->getStopName(), og) > 0){
//         createtrip(og,root->getLeft());
//     }
// }



Exploration* checkjunction(string stop,Exploration* exp, Trip* prevtrip,AVLNode* root){
    // Exploration* tempexp = new Exploration();
    // if (root->getStopName() == stop){
        // cout << "hi GG" << endl;
        // cout << "size --" << root->getStops().size() << endl;
        // cout << root->getStopName() << endl;
        if(root->getStops().size() > 1){
            
            for(int i = 1 ; i<root->getStops().size() ; i++){
                Trip* tback = new Trip(root->getStops()[i]->getPrevStop(),prevtrip);
                tback->setx(1);
                Trip* tforwd = new Trip(root->getStops()[i]->getNextStop(),prevtrip);
                tforwd->setx(2);
                exp->enqueue(tback);
                exp->enqueue(tforwd);
            }
            return exp;
        }
        else{
            // cout << "size --" << exp->getTrips().size() << endl;
            // cout << "here" << endl;
            return exp;
        }
    }



Path* getPath(MetroStop* stop, Trip* tt){
    int fare = 0;
    int i = 1;
    // cout << tt->getNode()->getStopName() << "--trip" << endl;
    
    // cout << tt->getx() << "--tripx" << endl;
    Path* finalpath = new Path();
    MetroStop* backtrav = stop;
    // cout << backtrav->getFare() << "--fare" << endl;
    while (tt != nullptr){
        finalpath->addStop(backtrav);
        fare = fare + backtrav->getFare();
        // cout << "gg" << endl;
        while (backtrav != tt->getNode() ){
            if (tt->getx() == 1){
                backtrav = backtrav->getNextStop();
                finalpath->addStop(backtrav);
                fare = fare + backtrav->getFare();
            }
            else if(tt->getx() == 2){
                backtrav = backtrav->getPrevStop();
                finalpath->addStop(backtrav);
                fare = fare + backtrav->getFare();
            }
        }
        // cout << "fare is -- " << fare << endl;
        if(tt->getPrev() == nullptr){
            finalpath->setTotalFare(fare);
            break;
        }
        else{
            tt = tt->getPrev();
        }
        
        // cout << "gggg" << endl;
        // cout << backtrav->getStopName() << "--finalstop" << endl;
    }
    // cout << "fare is -- " << fare << endl;
    // finalpath->setTotalFare(fare);
    return finalpath;
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    for(int i = 0 ; i<lines.size() ; i++){
        tree->populateTree(lines[i]);
    }
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    int fare = 0;
    Exploration* explr = new Exploration();
    Exploration* tempexplr = nullptr;
    // cout << "Hello" << endl
    AVLNode* node = tree -> getRoot();
    AVLNode* stop1 = tree -> searchStop(origin);
    // cout << "kabadi" << endl;
    vector<MetroStop*> stops = stop1 -> getStops();
    // cout << stops.size() << endl;
    int i = 0;
    while(i < stops.size()){
        MetroStop* currStop = stops[i];
        Trip* t1 = new Trip(currStop->getPrevStop(),nullptr);
        t1 -> setx(1);
        Trip* t2 = new Trip(currStop->getNextStop(),nullptr);
        t2 -> setx(2);
        explr -> enqueue(t1);
        explr -> enqueue(t2);
        i++;

    }
   //explr = createtrip(origin,tree->getRoot());
    while( !explr -> isEmpty() ){
    // cout << explr->getTrips().size() << "--size" <<  endl;
        Trip* travtrip = explr -> dequeue();
        MetroStop* stop = travtrip -> getNode();
        // cout << stop->getStopName() << " -- stop is" << endl;
        while(stop != nullptr ){
            if(travtrip->getx() == 1){
                // cout << "aple" << endl;
                AVLNode* temp = tree -> searchStop(stop->getStopName());
                // cout << temp->getStopName() << " -- temp name prev" <<  endl;
                // cout << "Hi" << endl;
                explr = checkjunction(stop->getStopName(),explr,travtrip,temp);
                // cout << "good" << endl;
                if (stop->getStopName() == destination){
                    Path* finalpath = getPath(stop,travtrip);
                    finalpath->addStop(stop1->getStops()[0]);
                    return finalpath;
                }
                stop = stop->getPrevStop();
                // if(stop->getPrevStop() == nullptr)
                // break;
            }
            else if(travtrip->getx() == 2){
                AVLNode* temp = tree -> searchStop(stop->getStopName());
                // cout << temp->getStopName() << " -- temp name" <<  endl;
                // cout << temp->getStopName() << " -- temp name fwd" <<  endl;
                // cout << temp->getStopName() << " -- temp name" <<  endl;
                explr = checkjunction(stop->getStopName(),explr,travtrip,temp);
                // stop = travtrip->getNode()->getNextStop();
                if (stop->getStopName() == destination){
                    // cout << "here" << endl;
                    // cout << travtrip->getNode()->getStopName() << "--trip" << endl;
                    Path* finalpath = getPath(stop,travtrip);
                    finalpath->addStop(stop1->getStops()[0]);
                    // cout << "here" << endl;
                    return finalpath;
                }
                stop = stop->getNextStop();
                // if(stop->getNextStop() == nullptr)
                // break;
            }

            // cout << explr->getTrips().size() << endl;
        }
        // explr->getTrips() = explr->dequeue();
        // cout << "hi" << endl;
        //     cout << explr->getTrips().size() << endl;
    }
    return nullptr;
    //Trip* trip;
}

// vector<string> getFileNames() {
//     vector<string> filenames;
//     filenames.push_back("blue.txt");
//     filenames.push_back("green.txt");
//     filenames.push_back("magenta.txt");
//     filenames.push_back("orange.txt");
//     filenames.push_back("red.txt");
//     filenames.push_back("violet.txt");
//     filenames.push_back("yellow.txt");
//     return filenames;
// }

vector<MetroLine*> lines;

// void testPopulateLine() {
//     cout<<"Testing populateLine()"<<endl;
//     vector<string> filenames = getFileNames();
//     int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
//     for (int i = 0; i < filenames.size(); i++) {
//         string lineName = filenames[i].substr(0, filenames[i].length() - 4);
//         MetroLine* metroLine = new MetroLine(lineName);
//         metroLine->populateLine(filenames[i]);
//         lines.push_back(metroLine);
//         cout << "Line name: " << metroLine->getLineName() << endl;
//         cout << "Total stops: " << metroLine->getTotalStops() << endl;
//         cout << endl;
//         assert(metroLine->getTotalStops() == expectedTotalStops[i]);
//         metroLine->printLine();
//     }
// }

// void testPopulateTree() {
//     cout<<"Testing populateTree()"<<endl;
//     vector<string> filenames = getFileNames();
//     AVLTree* tree = new AVLTree();
//     tree->setRoot(nullptr);
//     for (auto line : lines) {
//         if (tree->getRoot() == nullptr) {
//             tree->setRoot(new AVLNode(line->getNode()->getStopName()));
//         }
//         tree->populateTree(line);
//     }
//     cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
//     cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
// }

// int main(){
    // MetroLine* mline = new MetroLine("yellow");
    // mline-> populateLine("yellow.txt");
    // // mline->printLine();
    // // mline->getTotalStops();
    // // AVLTree* temptree = new AVLTree();
    // // temptree->populateTree(mline);
    // // cout << temptree->height(temptree->getRoot()) << "--height" << endl;;
    // // temptree->inOrderTraversal(temptree->getRoot());
    // cout<<"Testing populateTree()"<<endl;
    // // vector<string> filenames = getFileNames();
    // AVLTree* tree = new AVLTree();
    // tree->setRoot(nullptr);
    // // // for (auto line : mline) {
    // //     if (tree->getRoot() == nullptr) {
    // //         tree->setRoot(new AVLNode(mline->getNode()->getStopName()));
    // //     }
    //     tree->populateTree(mline);
    // // // }
    // cout << tree->getRoot()->getStops().size() << "--Size of Vector" << endl;
    // cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    // cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    
    // assert(tree->height(tree->getRoot()) == 9);
    // assert(tree->getTotalNodes(tree->getRoot()) == 211);
    // testPopulateLine();
    // testPopulateTree();
// }
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel> heap;

    int parent(int i) {
        // fill in this function
        return i%2;
    }

    int left(int i) {
        // fill in this function
        return 2*i;
    }

    int right(int i) {
        // fill in this function
        return (2*i) + 1;
    }

    Parcel get_max() {
        // fill in this function
        return heap[1];
    }

    Parcel extract_max() {
        // function that returns the max element and removes it from the heap
        Parcel temp = heap[1];
        heap[1] = heap[heap.size() - 1];
        heap.pop_back();
        int t1 = 1;
        int t2 = (2*t1);
        while(t2 < heap.size()){
            if(heap[2*t1].priority > heap[(2*t1) + 1].priority){
                swap(heap[t1], heap[2*t1]);
                t1 = 2*t1;
            }
            else{
                swap(heap[t1], heap[(2*t1) + 1]);
                t1 = (2*t1) + 1;
            }
            t2 = 2*t1;
        }

        return temp;
    }

    void max_heapify(int i) {
        // function that maintains the max heap property
        int t1 = 1;
        int t2 = (2*t1);
        while(t2 < heap.size()){
            if(heap[2*t1].priority > heap[(2*t1) + 1].priority){
                swap(heap[t1], heap[2*t1]);
                t1 = 2*t1;
            }
            else{
                swap(heap[t1], heap[(2*t1) + 1]);
                t1 = (2*t1) + 1;
            }
            t2 = 2*t1;
        }
    }

    void insert(Parcel item) {
        // function that inserts item into the heap
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;
    

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel parcel) {
        // load parcel
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
    }
};


class Vertex {
public:
    std::string name;
    std::vector<FreightCar> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    std::vector<FreightCar> sealed_freight_cars;
    std::vector<Parcel> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
        neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
    }

    std::vector<Parcel> get_all_current_parcels() {
        // get all parcels from all destination heaps
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
    }

    void loadParcel(Parcel parcel) {
        // load parcel into heap
    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
    }

    // void print_parcels_in_freight_cars() {
    //     for (auto& [destination, heap] : this->parcel_destination_heaps) {
    //         for (auto& parcel : heap.heap) {
    //             std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
    //         }
    //     }
    // }
};

vector<string> shortestPath(list<Vertex* > adjacencyList,const string& start, const string& end) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    queue<string> q;
    vector<Vertex* > ngbrvertex;
    vector<string> ngbr;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for(auto it: adjacencyList){
            if(it->name == current){
                ngbrvertex = it->neighbors;
            }
        }

        for(int i = 0 ; i<ngbrvertex.size() ; i++){
            ngbr.push_back(ngbrvertex[i]->name);
        }

        for (const string& neighbor : ngbr) {
            if (!visited[neighbor]) {

                visited[neighbor] = true;
                q.push(neighbor);
                parent[neighbor] = current;
            }
        }
    }

    // Reconstruct the path
    vector<string> path;
    string current = end;

    while (parent.find(current) != parent.end()) {
        path.push_back(current);
        current = parent[current];
    }

    // Add the starting node
    path.push_back(start);

    // Reverse the path to get it in the correct order
    reverse(path.begin(), path.end());

    return path;
}

int f = 1;

void doing_dfs(list<Vertex*> adjacencyList,string current, string end, unordered_map<string, bool>& visited, vector<string>& path, vector<vector<string>>& paths) {
    visited[current] = true;
    path.push_back(current);
    vector<Vertex* > ngbrvertex;
    vector<string> ngbr;

    if (current == end) {
        paths.push_back(path);
        // for(auto i:path){
        //     cout << i << " " ;
        // }
        // cout << endl;
        // cout << f++ << endl;
    }
    else {

        for(auto it: adjacencyList){
            if(it->name == current){
                ngbrvertex = it->neighbors;
            }
        }

        for(int i = 0 ; i<ngbrvertex.size() ; i++){
            ngbr.push_back(ngbrvertex[i]->name);
        }

        for (const string& neighbor : ngbr) {
            if (!visited[neighbor]) {
                doing_dfs(adjacencyList,neighbor, end, visited, path, paths);
            }
        }
    }

    // visited.erase(current);
    path.pop_back();
}

vector<vector<string>> findAllPaths(list<Vertex*> adj, string start, string end) {
    unordered_map<string, bool> visited;
    vector<string> path;
    vector<vector<string>> paths;

    doing_dfs(adj, start, end, visited, path, paths);


    return paths;
}

class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        // int flag = 0;

        Vertex* tempstart = nullptr;
        Vertex* tempfinish = nullptr;
        for(auto i:vertices){
            if(i->name == source){
                // flag = 1;
                // break;
                tempstart = i;
            }
            if(i->name == destination){
                // flag = 2;
                // break;
                tempfinish = i;
            }
        }

        if(tempstart == nullptr){
            tempstart = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(tempstart);
        }
        if(tempfinish == nullptr){
            tempfinish = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(tempfinish);
        }

        tempstart->add_neighbor(tempfinish);
        tempfinish->add_neighbor(tempstart);
        edges.push_back({tempstart, tempfinish});

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto& vertex : this->vertices) {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto& neighbor : vertex->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        // function to return path from source to destination using bfs
        vector<string> ans = shortestPath(vertices, source, destination);
        return ans;
    }

    std::vector<std::vector<std::string>> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
        vector<vector<string>> ans = findAllPaths(vertices, source, destination);
        return ans;
    }

    void groupFreightCars() {
        // for every vertex, group freight cars by links
    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
    }



};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar> freight_cars;
    std::map<std::string, Parcel> parcels;
    std::map<int, std::vector<Parcel>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {

        // read graph.txt file and create graph
        ifstream file(graph_file_name);
        string str;
        string source = "";
        string destination = "";

        while (getline(file, str)){
            int flag = 0;
            for(int i = 0 ; i<str.size() ; i++){
                if(flag == 0 && str[i] != ' '){
                    source = source + str[i];
                }
                else if(flag == 1){
                    destination = destination + str[i];
                }
                if(str[i] == ' '){
                    flag = 1;
                }
            }
            // cout << "source is -- " << source << " , destination is -- " << destination << endl;
            graph.add_edge(source, destination, min_freight_cars_to_move, max_parcel_capacity);

            source = "";
            destination = "";
            // cout << str << ++flag <<  endl;
        }

        graph.print_graph();
        

    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel> get_bookings(int time_tick, std::string vertex) {
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        for (auto& parcel_pair : this->parcels) {
            Parcel& parcel = parcel_pair.second;
            state[parcel.parcel_id] = parcel.current_location;
        }
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {
        
        // function to run simulation
    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered() {
        for (auto& parcel_pair : this->parcels) {
            Parcel& parcel = parcel_pair.second;
            if (!parcel.delivered) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
    }

};


int main() {

    PRC prc = PRC(2, 2);
    prc.create_graph("graph.txt");
    // vector<string> path = prc.graph.bfs("A", "F");
    cout << endl;
    vector<vector<string>> paths = prc.graph.dfs("Mumbai", "Ahmedabad");
    cout << "path size is -- " << paths.size() << endl;
    for(auto it:paths){
        for(auto jt:it){
            cout << jt << " ";
        }
        cout << endl;
    }
    // prc.process_parcels();
    // prc.run_simulation(3);

    return 0;
}
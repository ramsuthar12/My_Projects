#include <iostream>
#include <vector>
#include <iostream>
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
    std::vector<Parcel*> heap;

    MaxHeap(){
        heap.push_back(nullptr);
    }

    int parent(int i) {
        // fill in this function
        return i/2;
    }

    int left(int i) {
        // fill in this function
        return 2*i;
    }

    int right(int i) {
        // fill in this function
        return 2*i + 1;
    }

    Parcel* get_max() {
        // fill in this function
        return heap[1];
    }

    Parcel* extract_max() {
        // function that returns the max element and removes it from the heap
        Parcel* result=heap[1];
        swap(heap[1],heap[heap.size()-1]);
        heap.erase(heap.end()-1);
        max_heapify(1);
        return result;
        

    }

    void max_heapify(int i) {
        // function that maintains the max heap property
        int flag=i;

        if(left(i)<heap.size() && heap[left(i)]->priority>heap[flag]->priority){
            flag=left(i);
            
        }
        if(right(i)<heap.size() && heap[right(i)]->priority>heap[flag]->priority){
            flag=right(i);
            
        }
        if(flag!=i){
            swap(heap[i],heap[flag]);
            max_heapify(flag);
        }
        
    }

    void insert(Parcel* item) {
        // function that inserts item into the heap
       
        heap.push_back(item);
        
        int index=heap.size()-1;
        // for(int i=0;i<heap.size();i++){
        //     if(heap[i].parcel_id==item.parcel_id){
        //         index=i;
        //         break;
        //     }
        // }
        while(index>1){
            int parent=index/2;
            if(heap[parent]->priority<heap[index]->priority){
                swap(heap[parent],heap[index]);
            }
            index=parent;
        }
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel*> parcels;
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

    void load_parcel(Parcel* parcel) {
        // load parcel
        parcels.push_back(parcel);
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
        if(parcels.size()==max_parcel_capacity){
            return true;
        }
        return false;

    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
        current_location=destination;


    }
};

class Vertex {
public:
    std::string name;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap*> parcel_destination_heaps;
    std::vector<FreightCar*> sealed_freight_cars;
    std::vector<Parcel*> all_parcels;
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

    std::vector<Parcel*> get_all_current_parcels() {
        // get all parcels from all destination heaps
        return all_parcels;
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
        // cout<<"fc size "<<freight_cars.size()<<endl;
        vector<FreightCar*> result;
        vector<Parcel*> unmoved_parcels;
        for(int i=0;i<freight_cars.size();i++){
            if(freight_cars[i]->parcels.size() < freight_cars[i]->max_parcel_capacity){
                // cout<<"rrrrrrrrr"<<endl;
                // cout<<max_parcel_capacity<<endl;
                // cout<<freight_cars[i]->parcels.size()<<endl;
                // cout<<freight_cars[i]->destination_city<<endl;
                    for(int j=0;j<freight_cars[i]->parcels.size();j++){
                        //cout<<it->parcel_id<<endl;
                        //cout<<"tttt"<<endl;
                        unmoved_parcels.push_back(freight_cars[i]->parcels[j]);
                         if(freight_cars[i]->parcels[j]==nullptr){
                            cout<<"null"<<endl;
                         }
                         //cout << "apple" << endl;
                        cout<<freight_cars[i]->parcels[j]->destination<<endl;
                        //cout << "kanjar" << endl;
                          if(parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]==nullptr){
                            //cout<<"iiiiii"<<endl;
                                    parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]=new MaxHeap();

                            }
                            //cout<<"uuuuuuu"<<endl;
                        parcel_destination_heaps[freight_cars[i]->parcels[j]->destination]->insert(freight_cars[i]->parcels[j]);
                        //cout<<"yyyyyyyy"<<endl;
                    }
                  // freight_cars.erase(freight_cars.begin()+i);
                 
            }
            else{
                result.push_back(freight_cars[i]);
            }

        }
        // cout << unmoved_parcels.size() << endl;
        this->freight_cars = result;
    }

    void loadParcel(Parcel *parcel) {
        // load parcel into heap
        string dest=parcel->destination;
       // cout<<"rr"<<endl;
        if(parcel_destination_heaps[dest]==nullptr){
            parcel_destination_heaps[dest]=new MaxHeap();

        }
        parcel_destination_heaps[dest]->insert(parcel);
       // cout<<"kkk"<<endl;
        all_parcels.push_back(parcel);

    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        for(auto it : parcel_destination_heaps){
          // cout<<it.second->heap.size()<<endl;
          // cout << "----------------------------------------------------------" << endl;
          

            while(it.second->heap.size()>1){
                
              int val=it.second->heap.size()-1;
              int max;
              if(val % max_parcel_capacity==0){
                max=val/max_parcel_capacity;
              }
              else{
                max=(val/max_parcel_capacity)+1;
              }
                 for(int i=0;i<max;i++){
                   FreightCar* obj= new FreightCar(max_parcel_capacity);
                   obj->current_location=this->name;
                   obj->destination_city=it.first;
                   
                   
                   while(obj->parcels.size()<obj->max_parcel_capacity && it.second->heap.size()>1){
                      // cout<<it.second->heap.size()<<"hhhe"<<endl;
                      // cout << "********************" << endl;
                       obj->load_parcel(it.second->extract_max());
                       //cout<<"eeeeeee"<<endl;
                    //    for(auto par:obj->parcels){
                    //     cout<<par->parcel_id<<endl;
                    //    }
                        
                   }
                   
                   //cout<<obj->parcels.size()<<"iiiiiiiiiiiii"<<endl;
                   if(obj->parcels.size() == obj->max_parcel_capacity){
                      // cout<<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"<<endl;
                       obj->sealed=true;
                       sealed_freight_cars.push_back(obj);
                   }
                   //cout << "#####################################################" << endl;
                   freight_cars.push_back(obj);
   
                 }


            }

        }


    }

//     void print_parcels_in_freight_cars() {
// //for (auto& [destination, heap] : this->parcel_destination_heaps) {
//             for (auto& parcel : heap.heap) {
//                 std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
//             }
//         }
    
};

class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        Vertex* origin=nullptr;
        Vertex* dest=nullptr;
        for(auto it:vertices){
            if(it->name==source){
                origin=it;
            }
            if(it->name==destination){
                dest=it;
            }
        }
        if(!origin){
            origin=new Vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            vertices.push_back(origin);
        }
        if(!dest){
            dest=new Vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            vertices.push_back(dest);
        }
        pair<Vertex*,Vertex*> p={origin,dest};
        origin->add_neighbor(dest);
        dest->add_neighbor(origin);
        edges.push_back(p);

        

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
        vector<string> visited;
        vector<string> result;
        Vertex* origin=nullptr;
        for(auto it:vertices){
            if(it->name==source){
                origin=it;
                
            }
        }
       // cout<<origin->name<<endl;
        if(!origin){
            return {};
        }
        visited.push_back(source);
        queue<Vertex*> q;
        q.push(origin);
        vector<pair<Vertex*,string>> path;
        path.push_back({nullptr,source});
        while(!q.empty()){
            Vertex* temp=q.front();
           // cout<<temp->name<<endl;
            vector<Vertex*> neigh=temp->get_neighbors();
            
            q.pop();
            for(auto it:neigh){
                int c=0;
               // cout<<it->name<<" ";
                for(auto a:visited){
                    if(a==it->name){
                        c=1;
                    }
                }
               // cout<<endl;
                if(c==0){
                    visited.push_back(it->name);
                    q.push(it);
                    path.push_back({temp,it->name});
                    if(it->name==destination){
                      result.push_back(it->name);
                     // cout<<it->name<<" "<<"done"<<endl;
                      pair<Vertex*,string> flag;
                      for(auto p:path){
                        if(p.second==it->name){
                            flag=p;
                        }
                      }
                     // cout<<flag.second<<" jj"<<endl;
                      Vertex* abc=flag.first;
                     // cout<<abc->name<<endl;
                      while(abc){
                        result.insert(result.begin(),abc->name);
                       // cout<<"yyyyy"<<endl;
                        for(auto b:path){
                            if(b.second==abc->name){
                               // cout<<"oooo"<<endl;
                                abc=b.first;
                                break;
                            }
                        }
                       // cout<<"uuuu"<<endl;
                      }
                      return result;
                    }
                }


            }
            


        }
       // cout<<"ended"<<endl;
        return {};
        


        }
    void dfs_help(Vertex* origin,Vertex* destination,vector<string>&result,vector<Vertex*>&visited,vector<string>&temp){
        temp.push_back(origin->name);
        if(origin==destination){
            result=temp;
            return;

        }
        vector<Vertex*> neighbour=origin->get_neighbors();

        for(auto it:neighbour){
            if(find(visited.begin(),visited.end(),it)==visited.end()){
                visited.push_back(it);
                dfs_help(it,destination,result,visited,temp);
                temp.erase(temp.end()-1);
                //visited.erase(visited.end()-1);
            }

        }
        



    }

    std::vector<std::string> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
       vector<string> result;
       vector<Vertex*> visited;
       vector<string> temp;
       Vertex* origin=nullptr;
       Vertex* dest=nullptr;
       for(auto it:vertices){
        if(it->name==source){
            origin=it;
        }
        if(it->name==destination){
            dest=it;
        }
       }
       if(!origin || !dest){
        return{};
       }
       visited.push_back(origin);
       dfs_help(origin,dest,result,visited,temp);
       //cout<<origin->name<<endl;
       return result;
       
    
       }

    void groupFreightCars() {
        // for every vertex, group freight cars by links
       for(auto it:vertices){
        cout<<it->name<<":"<<it->sealed_freight_cars.size()<<endl;
       for(auto fc:it->sealed_freight_cars){
            vector<string> bfs=this->bfs(fc->current_location,fc->destination_city);
            fc->next_link=bfs[1];
            it->trains_to_move[fc->next_link].push_back(fc);
        }
      //  cout<<"qqqq"<<endl;
        }
        vector<FreightCar*> temp;
        for(auto it:vertices){
            for(auto mpp:it->trains_to_move){
                if(mpp.second.size()<it->min_freight_cars_to_move){
                    it->trains_to_move.erase(mpp.first);
                    for(auto fc:mpp.second){
                        temp.push_back(fc);
                    }

                }
            }
        }
       // cout<<"vvvv"<<endl;
        for(auto it:temp){
            for(auto v:vertices){
                if(v->name==it->current_location){
                   vector<string> dfs=this->dfs(it->current_location,it->destination_city);
                    it->next_link=dfs[1];
                    v->trains_to_move[it->next_link].push_back(it);

                }
            }
        }
        temp.clear();
          for(auto it:vertices){
            for(auto mpp:it->trains_to_move){
                if(mpp.second.size()<5){
                    it->trains_to_move.erase(mpp.first);
                    for(auto fc:mpp.second){
                        temp.push_back(fc);
                    }

                }
            }
        }
        for(auto it:vertices){
            cout<<it->name<<":"<<endl;
            for(auto m:it->trains_to_move){
                cout<<m.first<<" next link"<<endl;
                for(auto p:m.second){
                    cout<<p->destination_city<<" ";
                }
                cout<<endl;

            }

        }
        


    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
        vector<pair<FreightCar* ,string>> abc;
        for(auto it:vertices){
            //cout<<it->name<<endl;
            cout<<it->freight_cars.size()<<"rrrr"<<endl;
            for(auto mpp:it->trains_to_move){
               // cout<<"yes"<<endl;
               // cout<<it->freight_cars.size()<<endl;
                for( auto fc:mpp.second){
                    //cout<<fc->next_link<<endl;
                    
                    fc->move(fc->next_link);
                    fc->next_link="";
                    // vector<FreightCar*> temp;
                    // for(int i=0;i<it->freight_cars.size();i++){
                    //     if(it->freight_cars[i]!=fc){
                    //         //it->freight_cars.erase(it->freight_cars.begin()+i);
                    //         cout<<"aaa"<<endl;
                    //         temp.push_back(fc);
                    //     }
                    // }
                    if(find(it->freight_cars.begin(),it->freight_cars.end(),fc)!=it->freight_cars.end()){
                        it->freight_cars.erase(find(it->freight_cars.begin(),it->freight_cars.end(),fc));
                    }
                   
                    // it->freight_cars=temp;
                    //  cout<<it->freight_cars.size()<<"oooo"<<endl;
                    // vector<FreightCar*> temp1;
                    // for(int i=0;i<it->sealed_freight_cars.size();i++){
                    //     if(it->sealed_freight_cars[i]!=fc){
                    //         //it->sealed_freight_cars.erase(it->freight_cars.begin()+i);
                    //          temp1.push_back(fc);
                    //     }

                    // }
                    // it->sealed_freight_cars=temp1;
                      if(find(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),fc)!=it->sealed_freight_cars.end()){
                        it->sealed_freight_cars.erase(find(it->sealed_freight_cars.begin(),it->sealed_freight_cars.end(),fc));
                    }
                    //cout<<"done"<<endl;
                   // cout<<fc->current_location<<endl;
                    if(fc->current_location!=fc->destination_city){
                       // cout<<"uu"<<endl;
                    for(auto ver:vertices){
                        if(ver->name==mpp.first){
                            //cout<<ver->name<<endl;
                        ver->freight_cars.push_back(fc);
                        ver->sealed_freight_cars.push_back(fc);
                        }
                    }
                    }
                    //cout<<"ppppppp"<<endl;
                    cout<<fc->parcels.size()<<endl;
                    //abc.push_back({fc,fc->current_location});

                    for(auto par:fc->parcels){
                    //     vector<Parcel*> abc;
                    //    // cout<<"lllllll"<<endl;
                    //     for(int i=0;i<it->all_parcels.size();i++){
                    //         if(it->all_parcels[i]!=par){
                    //            // it->all_parcels.erase(it->all_parcels.begin()+i);
                    //            abc.push_back(par);
                    //         }
                    //     }
                    //     it->all_parcels=abc;
                    if(find(it->all_parcels.begin(),it->all_parcels.end(),par)!=it->all_parcels.end()){
                        it->all_parcels.erase(find(it->all_parcels.begin(),it->all_parcels.end(),par));
                    }
                        par->current_location=mpp.first;
                       // cout<<par->current_location<<endl;
                        if(par->current_location==par->destination){
                            par->delivered=true;
                        }
                       
                        for(auto ver:vertices){
                        if(ver->name==mpp.first){
                        ver->all_parcels.push_back(par);
                        
                        }
                    }
                        }
                       // cout<<"kkk"<<endl;


                    


                }
            }
            it->trains_to_move.clear();
        }
        // for(auto it:abc){
        //     for(auto par:it.first->parcels){
        //         cout<<"aa"<<endl;
        //         cout<<par->parcel_id<<endl;

        //     }
        // }
        


    }



};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    std::map<std::string, Parcel*> parcels;
    std::map<int, std::vector<Parcel*>> parcels_with_time_tick;
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
        ifstream in(graph_file_name);
        if(!in.is_open()){
            return;
        }
        string line;
        while(getline(in,line)){
            stringstream ss(line);
            string place1;
            string place2;
            getline(ss,place1,' ');
            getline(ss,place2,' ');
            graph.add_edge(place1,place2,min_freight_cars_to_move,max_parcel_capacity);


        }




    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
        ifstream in(parcels_file_name);
        if(!in.is_open()){
            return;
        }
        string line;
        string word;
        int time;
        string id;
        string origin;
        string destination;
        int priority;
        while(getline(in,line)){
        stringstream ss(line);
        getline(ss,word,' ');
        time=stoi(word);

        getline(ss,id,' ');
        getline(ss,origin,' ');
        getline(ss,destination,' ');

        getline(ss,word,' ');
        priority=stoi(word);
        Parcel* obj=new Parcel(time,id,origin,destination,priority);
        obj->current_location=origin;
        parcels.insert({id,obj});
        parcels_with_time_tick[time].push_back(obj);

        

        }
       

        
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel*> get_bookings(int time_tick, std::string vertex) {
        Vertex* obj=nullptr;
        list<Vertex*> vertices=graph.vertices;
        for(auto it:vertices){
            if(it->name==vertex){
                obj=it;
            }
        }
        vector<Parcel*> abc=obj->all_parcels;
        vector<Parcel*> result;
        for(int i=0;i<abc.size();i++){
            if(abc[i]->time_tick==time_tick){
                result.push_back(abc[i]);
            }
        }
        return result;

    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {

        // function to run simulation 
        if(run_till_time_tick==-1 || run_till_time_tick>max_time_tick){
            run_till_time_tick=max_time_tick;
        }
        int tt=1;
        while(tt<run_till_time_tick){
           cout<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<tt<<endl;
            for(auto it:parcels_with_time_tick){
                //cout<<it.first<<endl;
                if(it.first==tt){
                  //  cout<<"here"<<endl;
                    for(auto parcel:it.second){
                       // cout<<parcel->parcel_id<<endl;
                        if(parcel->origin==parcel->current_location){
                           // cout<<"kkkkkkkkkkkkkkkkk"<<endl;
                            for(auto v:graph.vertices){
                               
                                if(v->name==parcel->origin){
                                  //  cout<<v->name<<endl;
                                    v->loadParcel(parcel);
                                   // cout<<"yyyyyyyyy"<<endl;
                                }
                            }
                        }
                    }
                   // cout<<"lll"<<endl;
                    break;

                }
            }
            for(auto it:graph.vertices){
              //  cout<<it->name<<endl;
              //cout<<it->name<<endl;
                it->loadFreightCars();
               // cout<<it->name<<" done"<<endl;
            }
            cout<<"yyyyyyy"<<endl;
            for(auto it:graph.vertices){
                                
               // cout<<it->name<<endl;
                it->clean_unmoved_freight_cars();
               // cout<<it->name<<" done"<<endl;

            }
            cout<<"ppp"<<endl;
            graph.groupFreightCars();
            cout<<"kkkkkkkkkkkkkkkkkkkk"<<endl;
            graph.moveTrains();
            tt++;

        }
        

    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

     bool all_parcels_delivered() {
        // function to check if all parcels are delivered
        // return true if all parcels are delivered else return false
        for(auto it:parcels){
            if(it.second->delivered==false){
                return false;
            }

        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
        vector<string> result;
        for(auto it:parcels){
            if(it.second->delivered==false){
                result.push_back(it.second->parcel_id);
            }
        }
        return result;
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
          vector<string> result;
        for(auto it:parcels){
            if(it.second->delivered==true){
                result.push_back(it.second->parcel_id);
            }
        }
        return result;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
        vector<string> result;
        for(auto mpp:parcels_with_time_tick){
            if(mpp.first<=t){
                for(auto parcel:mpp.second){
                    result.push_back(parcel->parcel_id+" "+parcel->current_location+" "+to_string(parcel->delivered));
                }
            }
        }
        return result;
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
          for(auto mpp:parcels_with_time_tick){
            if(mpp.first<=t){
                for(auto parcel:mpp.second){
                    if(parcel->parcel_id==parcel_id){
                    return parcel->parcel_id+" "+parcel->current_location+" "+to_string(parcel->delivered);
                    }
                }
            }
        }

    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
        vector<string> result;
         for(auto mpp:parcels_with_time_tick){
            if(mpp.first<=t){
                for(auto parcel:mpp.second){
                    if(parcel->delivered==true){
                      result.push_back(parcel->parcel_id);
                    }
                }
            }
        }
        return result;

    }

};


// int main() {

//     PRC prc = PRC(5, 5);
//     prc.create_graph("graph5.txt");
//     //prc.graph.print_graph();
//     cout<<"here"<<endl;
//     vector<string> abc=prc.graph.dfs("Mumbai","Ahmedabad");
//     vector<string> pqr=prc.graph.bfs("Mumbai","Ahmedabad");
//     cout<<"ee"<<endl;
//     cout<<abc.size()<<endl;
//     for(auto it: abc){
      
//         cout<<it<<" ";
       
      
//     }
//     cout<<endl;
//     for(auto it:pqr){
//         cout<<it<<" "<<endl;
//     }
//     cout<<endl;
//     cout<<"ended"<<endl;
//     cout<<prc.graph.edges.size()<<endl;
//     // prc.process_parcels();
//     // prc.run_simulation(3);
//     prc.process_parcels("booking5.txt");
//     cout<<"process_parcels done"<<endl;
//     prc.run_simulation(60);
//     cout<<"running:"<<endl;
//    //vector<string> sp=prc.get_stranded_parcels();
//     cout<<"here"<<endl;
//     int c=0;
    
//     for(auto it:prc.graph.vertices){
//         //cout<<"lll"<<endl;
//         cout<<it->name<<":"<<it->freight_cars.size()<<endl;
//         if(it->name=="AHMEDABAD"){
//             cout<<"aaa"<<endl;
//             if(it->all_parcels.size()==0){
//                 cout<<"wrong"<<endl;
//             }
//             for(auto par:it->all_parcels){
//                 cout<<par->parcel_id<<endl;

//             }
//         }
//     }
//     // for(auto it:sp){
//     //     c++;
//     //     cout<<it<<" ";
//     // }
//     // cout<<c<<endl;

//     return 0;
// }
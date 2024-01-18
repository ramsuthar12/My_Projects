#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Graph {
public:
    void addEdge(const string& u, const string& v);
    vector<vector<string>> findAllPaths(const string& start, const string& end);

private:
    unordered_map<string, vector<string>> adjacencyList;
    void dfs(const string& current, const string& end, unordered_set<string>& visited, vector<string>& path, vector<vector<string>>& paths);
};

void Graph::addEdge(const string& u, const string& v) {
    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);  // Assuming an undirected graph
}

void Graph::dfs(const string& current, const string& end, unordered_set<string>& visited, vector<string>& path, vector<vector<string>>& paths) {
    visited.insert(current);
    path.push_back(current);

    if (current == end) {
        paths.push_back(path);
    } else {
        for (const string& neighbor : adjacencyList[current]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, end, visited, path, paths);
            }
        }
    }

    visited.erase(current);
    path.pop_back();
}

vector<vector<string>> Graph::findAllPaths(const string& start, const string& end) {
    unordered_set<string> visited;
    vector<string> path;
    vector<vector<string>> paths;

    dfs(start, end, visited, path, paths);

    return paths;
}

int main() {
    // Graph graph;

    // // Add edges to the graph
    // graph.addEdge("A", "B");
    // graph.addEdge("B", "C");
    // graph.addEdge("C", "D");
    // graph.addEdge("D", "A");
    // graph.addEdge("A", "C");
    // graph.addEdge("B", "E");
    // graph.addEdge("E", "F");
    // graph.addEdge("C", "F");

    // // Find all paths from "A" to "E"
    // vector<vector<string>> paths = graph.findAllPaths("A", "F");

    // // Print the paths
    // cout << "All Paths from A to E:\n";
    // for (const auto& path : paths) {
    //     for (const string& node : path) {
    //         cout << node << " ";
    //     }
    //     cout << endl;
    // }
    
    vector<int> maxheap;


    maxheap.push_back(-1);
    maxheap.push_back(22);
    maxheap.push_back(15);
    maxheap.push_back(17);
    maxheap.push_back(10);
    maxheap.push_back(9);
    maxheap.push_back(7);
    maxheap.push_back(8);
    maxheap.push_back(6);

    for(auto it : maxheap){
        cout << it << " ";
    }
    cout << endl;

    maxheap[1] = maxheap[maxheap.size() - 1];
    maxheap.pop_back();

    for(auto it : maxheap){
        cout << it << " ";
    }
    cout << endl;

    int t1 = 1;
    int t2 = (2*t1);
    while(t2 < maxheap.size()){
        if(maxheap[2*t1] > maxheap[(2*t1) + 1]){
            swap(maxheap[t1], maxheap[2*t1]);
            t1 = 2*t1;
        }
        else{
            swap(maxheap[t1], maxheap[(2*t1) + 1]);
            t1 = (2*t1) + 1;
        }
        t2 = 2*t1;
    }

    for(auto it : maxheap){
        cout << it << " ";
    }
    cout << endl;

    return 0;
}

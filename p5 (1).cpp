#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct node {
    int  vertex;
    node* next;
};

struct p5 {
    int nv;
    int edges[10][2];
    int ne;
};

p5 data_c[] = {
    { 6, {{0,1},{1,4},{4,5},{0,3},{3,2},{2,1}}, 6 },
    { 7, {{0,1},{1,2},{2,3},{3,1},{4,5},{5,6},{6,4}}, 7 },
    { 7, {{0,1},{2,3},{4,5},{5,6},{6,4}}, 5 }
};

class Graph {
private:
    int  n;
    int  e;
    node* headnodes;
    bool cycle;
    vector<int>  parent;
    vector<pair<int,int>> cycleEdges;
    void addEdge(int u,int v);
    bool DFS_cycle(int father,int v, bool* Visited, int* parent);

public:
    Graph(int nodes): n(nodes), e(0), cycle(false){
        headnodes = new node[n];
        for(int i=0; i<n; i++){
            headnodes[i].vertex = i;
            headnodes[i].next = nullptr;
        }
    }
    void create(int edges[][2], int numEdges);
    void DFS(int v, bool* Visited);
    void primerocycle();
    void printCycle();
    bool hasCycle() const { return cycle; }
};

int main() {
    int numTests = sizeof(data_c) / sizeof(data_c[0]);

    for (int t = 0; t < numTests; t++) {
        int n = data_c[t].nv;
        int ne = data_c[t].ne;
        int (*edges)[2] = data_c[t].edges;
        
        cout << "\nGraph: " << t + 1 << " " << endl;
        Graph G(n);
        G.create(edges, ne);
        bool* Visited = new bool[n];
        for (int i = 0; i < n; i++) Visited[i] = false;
        int numComponents = 0;
        for (int i = 0; i < n; i++) {
            if (!Visited[i]) {
                G.DFS(i, Visited);
                numComponents++;
            }
        }

        cout << "Number of connected components: " << numComponents << endl;
        G.primerocycle();
        cout << "Graph has cycles: " << (G.hasCycle() ? "Yes" : "No") << endl;
        G.printCycle();

        delete[] Visited;
    }
    return 0;
}
void Graph::primerocycle() {
        bool* Visited = new bool[n];
        int* parent = new int[n];
        for (int i = 0; i < n; i++) {
            Visited[i] = false;
            parent[i] = -1;
        }
        cycleEdges.clear();
        cycle = false;
        for (int i = 0; i < n && !cycle; i++) {
            if (!Visited[i]) DFS_cycle(-1, i, Visited, parent);
        }
        delete[] Visited;
        delete[] parent;
    }
bool Graph::DFS_cycle(int father, int v, bool* Visited, int* parent) {
    Visited[v] = true;
    node* adj = headnodes[v].next;
    while (adj) {
        int u = adj->vertex;
        if (!Visited[u]) {
            parent[u] = v;
            if (DFS_cycle(v, u, Visited, parent)) return true;
        }
        else if (u != father) {
            cycle = true;
            cycleEdges.clear();
            int x = v;
            vector<int> path;
            path.push_back(u);

            while (x != u) {
                path.push_back(x);
                x = parent[x];
            }
            path.push_back(u);

            for (size_t i = 0; i < path.size() - 1; i++) {
                cycleEdges.push_back({path[i], path[i + 1]});
            }

            return true;
        }
        adj = adj->next;
    }
    return false;
}
void Graph::addEdge(int u,int v){
        node* p = new node{v, headnodes[u].next};
        headnodes[u].next = p;
        node* q = new node{u, headnodes[v].next};
        headnodes[v].next = q;
        e++;
    }
void Graph::printCycle() {
        if (!cycle) {
            cout << "No cycles\n";
            return;
        }
        cout << "Cycle: ";
        for (size_t i = 0; i < cycleEdges.size(); i++) {
            cout << '(' << cycleEdges[i].first << ',' << cycleEdges[i].second << ')';
            if (i + 1 < cycleEdges.size()) cout << ", ";
        }
        cout << endl;
    }
void Graph::DFS(int v, bool* Visited) {
        Visited[v] = true;
        node* adj = headnodes[v].next;
        while (adj) {
            if (!Visited[adj->vertex]) DFS(adj->vertex, Visited);
            adj = adj->next;
        }
    }
void Graph::create(int edges[][2], int ne) {
        for (int i = 0; i < ne; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if (u >= 0 && u < n && v >= 0 && v < n) addEdge(u, v);
        }
    }
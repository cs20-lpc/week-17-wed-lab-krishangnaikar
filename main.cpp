#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int weight;
    Edge* next;

    Edge(int t, int w) : to(t), weight(w), next(nullptr) {}
};

struct Graph {
    int numVertices;
    Edge** adjList;

    Graph(int n) : numVertices(n) {
        adjList = new Edge*[n];
        for (int i = 0; i < n; i++)
            adjList[i] = nullptr;
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Edge* curr = adjList[i];
            while (curr) {
                Edge* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
        delete[] adjList;
    }

    void addEdge(int from, int to, int weight) {
        Edge* newEdge = new Edge(to, weight);
        newEdge->next = adjList[from];
        adjList[from] = newEdge;
    }

    void print() const {
        for (int i = 0; i < numVertices; i++) {
            cout << "node " << i << ": ";
            Edge* curr = adjList[i];
            while (curr) {
                cout << "(" << curr->to << ", " << curr->weight << ")";
                if (curr->next) cout << " -> ";
                curr = curr->next;
            }
            if (!adjList[i]) cout << "NULL";
            cout << "\n";
        }
    }
};

vector<int> dijkstra(const Graph& g, int src) {
    int n = g.numVertices;
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;

        for (Edge* e = g.adjList[u]; e; e = e->next) {
            if (dist[u] + e->weight < dist[e->to]) {
                dist[e->to] = dist[u] + e->weight;
                pq.push({dist[e->to], e->to});
            }
        }
    }
    return dist;
}

void printDistances(const vector<int>& dist, int src) {
    cout << "Shortest distances from node " << src << ":\n";
    for (int i = 0; i < (int)dist.size(); i++) {
        cout << "  " << src << " -> " << i << ": ";
        if (dist[i] == INT_MAX) cout << "unreachable\n";
        else cout << dist[i] << "\n";
    }
}

int main() {
    Graph g(6);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 9);
    g.addEdge(0, 4, 2);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 2, 3);
    g.addEdge(4, 5, 8);

    cout << "Adjacency List:\n";
    g.print();
    cout << "\n";

    auto dist0 = dijkstra(g, 0);
    printDistances(dist0, 0);
    cout << "\n";

    auto dist1 = dijkstra(g, 1);
    printDistances(dist1, 1);

    return 0;
}

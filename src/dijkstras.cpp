#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distance(G.numVertices, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distance[source] = 0;
    pq.push({0, source});
    previous.assign(G.numVertices, -1);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst, weight = edge.weight;
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (previous[destination] == -1 && destination != 0) {
        return path;
    }
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());    
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

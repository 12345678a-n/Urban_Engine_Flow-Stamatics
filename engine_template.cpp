#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
// `rev` is the index, within the OTHER node's adjacency list, of
// this edge's paired reverse edge. This is what lets the flow
// algorithms "undo" flow they've pushed — a core idea in residual
// graphs. It is set up for you in buildGraph() below; you don't
// need to build this wiring yourself, just understand that it
// exists and how to use it (you'll need g.adj[u.to][u.rev] inside
// your flow algorithms).
struct Edge {
    int to;
    double weight;
    long long cap;
    long long flow = 0;
    int rev = -1;
};
struct Graph {
    int n;
    vector<vector<Edge>> adj;
    Graph(int vertices) : n(vertices), adj(vertices) {}
    void addEdge(int from, int to, double w, long long cap) {
        Edge a = {to, w, cap, 0, (int)adj[to].size()};
    Edge b = {from, 0, 0,   0, (int)adj[from].size()};

    adj[from].push_back(a);
    adj[to].push_back(b);
    }
};
Graph buildGraphForDijkstra(const json& input) {
    
}
Graph buildGraph(const json& input) {
    int n = input.at("num_nodes").get<int>();
    Graph g(n);
    for (auto& e : input.at("edges")) {
        int u = e.at("from").get<int>();
        int v = e.at("to").get<int>();
        double w = e.value("weight", 1.0);
        long long cap = e.value("capacity", 0LL);
        g.addEdge(u, v, w, cap);
        if (e.value("undirected", false)) {
            g.addEdge(v, u, w, cap);
        }
    }
    return g;
}
json runDijkstra(const Graph& g, int source, int target) {
    json result;
    //algo here
    result["found"] = true;
    return result;
}
json runDinic(Graph& g, int source, int target) {
    json result;
    long long flow = 0;
    //algo here
    result["found"] = true;
    result["max_flow"] = flow;
    return result;
}
json runMinCut(Graph& g, int source, int target) {
    json result;
    result["found"] = true;
    
    return result;
}

// ==================================================================
// DISPATCH — given, you shouldn't need to modify this
// ==================================================================
int main() {
    ostringstream ss;
    ss << cin.rdbuf();
    string input_str = ss.str();

    json input;
    try {
        input = json::parse(input_str);
    } catch (const exception& ex) {
        json err;
        err["error"] = string("invalid JSON input: ") + ex.what();
        std::cout << err.dump() << std::endl;
        return 1;
    }

    string algorithm = input.value("algorithm", "");
    int source = input.value("source", 0);
    int target = input.value("target", 0);

    json result;
    try {
        if (algorithm == "dijkstra") {
            Graph g = buildGraphForDijkstra(input);
            result = runDijkstra(g, source, target);
        } else if (algorithm == "dinic") {
            Graph g = buildGraph(input);
            result = runDinic(g, source, target);
        } else if (algorithm == "min_cut") {
            Graph g = buildGraph(input);
            result = runMinCut(g, source, target);
        } else {
            result["error"] = "unknown algorithm: " + algorithm;
            result["algorithm"] = algorithm;
            std::cout << result.dump() << std::endl;
            return 1;
        }
    } catch (const exception& ex) {
        result = json{};
        result["error"] = string("runtime error: ") + ex.what();
        std::cout << result.dump() << std::endl;
        return 1;
    }

    result["algorithm"] = algorithm;
    std::cout << result.dump() << std::endl;
    return 0;
}

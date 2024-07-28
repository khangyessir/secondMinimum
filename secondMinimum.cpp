class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> graph(n + 1);
        for(const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<vector<int>> dist(n + 1, vector<int>(2, INT_MAX));
        dist[1][0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        while(!pq.empty()) {
            auto[current_time, u] = pq.top();
            pq.pop();
            for(int v : graph[u]) {
                int next_time;
                if((current_time / change) % 2 == 0) {
                    next_time = current_time + time;
                } else {
                    next_time = ((current_time / change) + 1) * change + time;
                }
                if(next_time < dist[v][0]) {
                    dist[v][1] = dist[v][0];
                    dist[v][0] = next_time;
                    pq.push({next_time, v});
                } else if(dist[v][0] < next_time && next_time < dist[v][1]) {
                    dist[v][1] = next_time;
                    pq.push({next_time, v});
                }
            }
        }
        return dist[n][1];
    }
};
#include <bits/stdc++.h>
using namespace std;

// Base Class
class GraphAlgorithm
{

public:
    vector<vector<int>> adj;
    vector<int> h;
    GraphAlgorithm(const vector<vector<int>> adjList, const vector<int> &hype) // Parameterized Constructor
    {
        adj = adjList;
        h = hype;
    }
    virtual void Query() = 0; // Pure virtual function
};
class isCycle : public GraphAlgorithm // Derived from Base class
{
public:
    isCycle(const vector<vector<int>> adjList, const vector<int> &hype) : GraphAlgorithm(adjList, hype) {}
    void Query() override // overriding pure virtual function
    {
        int n = h.size() - 1;
        vector<int> indegree(n + 1, 0); // Initialize indegree vector
        for (int i = 1; i <= n; i++)
        {
            for (auto &adjNode : adj[i])
            {
                indegree[adjNode]++;
            }
        }
        queue<int> q;
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0) // Independent vertices ,push into queue
            {
                q.push(i);
            }
        }
        vector<int> topo; // topological order
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for (auto adjNode : adj[node])
            {
                if (--indegree[adjNode] == 0) // remove dependancy
                {
                    q.push(adjNode);
                }
            }
        }
        if ((int)topo.size() != n) // If size of topo sort is not equal to n,there is a dependancy cycle
        {
            cout << "YES" << '\n';
        }
        else
        {
            cout << "NO" << '\n';
        }
        return;
    }
};
class indepComponent : public GraphAlgorithm // Derived from Base class
{
public:
    indepComponent(const vector<vector<int>> adjList, const vector<int> &hype) : GraphAlgorithm(adjList, hype) {}
    void dfs1(int u, vector<int> &visited, stack<int> &order) // get the order of nodes for second dfs
    {
        visited[u] = 1;
        for (auto &adjNode : adj[u])
        {
            if (!visited[adjNode])
            {
                dfs1(adjNode, visited, order);
            }
        }
        order.push(u);
    }
    void dfs2(int u, const vector<vector<int>> &revAdj, vector<int> &visited, vector<int> &component)
    {
        // perform dfs for each strongly connected component and compute the size
        visited[u] = 1;
        component.push_back(u);
        for (auto &adjNode : revAdj[u])
        {
            if (!visited[adjNode])
            {
                dfs2(adjNode, revAdj, visited, component);
            }
        }
    }
    void Query() override // overriding pure virtual function
    {
        stack<int> order;
        int n = (int)adj.size() - 1;
        vector<int> visited(n + 1, 0); // visited array
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                dfs1(i, visited, order);
            }
        }
        vector<vector<int>> revAdj(n + 1); // transpose the graph to find strongly connected components
        for (int i = 1; i <= n; i++)
        {
            for (auto &adjNode : adj[i])
            {
                revAdj[adjNode].push_back(i);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            visited[i] = 0; // reset visited array
        }
        int scc = 0, maxSize = 0;
        while (!order.empty()) // perform dfs2 in order of stack
        {
            int node = order.top();
            order.pop();
            if (!visited[node])
            {
                scc++;
                vector<int> component;
                dfs2(node, revAdj, visited, component);
                maxSize = max(maxSize, (int)component.size());
            }
        }
        cout << scc << ' ' << maxSize << '\n';
        return;
    }
};
class validOrder : public GraphAlgorithm // Derived from Base class
{
public:
    validOrder(const vector<vector<int>> adjList, const vector<int> &hype) : GraphAlgorithm(adjList, hype) {}
    void Query() override // overriding pure virtual function
    {
        int n = (int)adj.size() - 1;
        vector<int> indegree(n + 1, 0); // Initialize indegree vector
        for (int i = 1; i <= n; i++)
        {
            for (auto &adjNode : adj[i])
            {
                indegree[adjNode]++;
            }
        }
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i); // Independent vertices ,push into queue
            }
        }
        vector<int> topo; // topological order
        while (!q.empty())
        {
            int node = q.top();
            q.pop();
            topo.push_back(node);
            for (auto adjNode : adj[node])
            {
                if (--indegree[adjNode] == 0) // remove dependancy
                {
                    q.push(adjNode);
                }
            }
        }
        if ((int)topo.size() == n) // print the topological order
        {
            for (auto &node : topo)
            {
                cout << node << ' ';
            }
            cout << '\n';
        }
        else
        {
            cout << "NO" << '\n';
        }
        return;
    }
};
class maxHype : public GraphAlgorithm // Derived from Base class
{
public:
    maxHype(const vector<vector<int>> &adjList, const vector<int> &hype) : GraphAlgorithm(adjList, hype) {}
    void dfs1(int u, vector<int> &visited, stack<int> &order) // get the order of nodes for second dfs
    {
        visited[u] = 1;
        for (auto &adjNode : adj[u])
        {
            if (!visited[adjNode])
            {
                dfs1(adjNode, visited, order);
            }
        }
        order.push(u);
    }
    void dfs2(int u, const vector<vector<int>> &revAdj, vector<int> &visited, vector<int> &component)
    {
        // perform dfs for each strongly connected component and compute the size
        visited[u] = 1;
        component.push_back(u);
        for (auto &adjNode : revAdj[u])
        {
            if (!visited[adjNode])
            {
                dfs2(adjNode, revAdj, visited, component);
            }
        }
    }
    void Query() override // overriding pure virtual function
    {
        stack<int> order;
        int n = h.size() - 1;
        vector<int> visited(n + 1, 0); // visited array
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                dfs1(i, visited, order);
            }
        }
        vector<vector<int>> revAdj(n + 1); // transpose the graph to find strongly connected components
        for (int i = 1; i <= n; i++)
        {
            for (auto &adjNode : adj[i])
            {
                revAdj[adjNode].push_back(i);
            }
        }
        for (int i = 1; i <= n; i++)
        {
            visited[i] = 0; // reset visited array
        }
        vector<int> rootIndex(n + 1), roots;
        while (!order.empty()) // perform dfs2 in order of stack
        {
            int node = order.top();
            order.pop();
            if (!visited[node])
            {
                vector<int> component;
                dfs2(node, revAdj, visited, component);
                int root = *min_element(component.begin(), component.end());
                roots.push_back(root);
                for (auto &it : component)
                {
                    rootIndex[it] = root;
                }
            }
        }
        // Form condensed graph
        vector<set<int>> condensedAdj(n + 1);
        for (int i = 1; i <= n; i++)
        {
            for (auto &adjNode : adj[i])
            {
                if (rootIndex[i] != rootIndex[adjNode])
                {
                    condensedAdj[rootIndex[i]].insert(rootIndex[adjNode]);
                }
            }
        }
        // sum hype values of each component
        vector<int> condensedHype(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            condensedHype[rootIndex[i]] += h[i];
        }

        // topo sort on condensed graph
        vector<int> indegree(n + 1, 0); // Initialize indegree vector
        for (auto &it : roots)
        {
            for (auto &adjNode : condensedAdj[it])
            {
                indegree[adjNode]++;
            }
        }
        queue<int> q;
        for (auto &node : roots)
        {
            if (indegree[node] == 0)
            {
                q.push(node); // Independent vertices ,push into queue
            }
        }
        vector<int> topo; // topological order
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for (auto &adjNode : condensedAdj[node])
            {
                if (--indegree[adjNode] == 0) // remove dependancy
                {
                    q.push(adjNode);
                }
            }
        }

        // dp on topo sort
        vector<int> dp(n + 1, 0);
        int maxHype = 0;

        for (int i = 1; i <= n; i++)
        {
            dp[rootIndex[i]] = condensedHype[rootIndex[i]];
            maxHype = max(maxHype, dp[rootIndex[i]]);
        }

        for (auto &node : topo)
        {
            maxHype = max(maxHype, dp[node]);
            for (auto &adjNode : condensedAdj[node])
            {
                dp[adjNode] = max(dp[adjNode], dp[node] + condensedHype[adjNode]);
                maxHype = max(maxHype, dp[adjNode]);
            }
        }
        cout << maxHype << '\n';
        return;
    }
};
// comparator to use in sorting adjList
bool Comparator(int i, int j)
{
    return (i < j);
};
int main()
{

    // input
    int n, m;
    cin >> n >> m;
    vector<int> hype(n + 1);
    vector<vector<int>> adjList(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> hype[i];
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        sort(adjList[i].begin(), adjList[i].end(), Comparator); // sort using comparator
    }

    // create objects of each type
    isCycle isCycleObject(adjList, hype);
    indepComponent indepComponentObject(adjList, hype);
    validOrder validOrderObject(adjList, hype);
    maxHype maxHypeObject(adjList, hype);

    // queries
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            isCycleObject.Query();
        }
        else if (type == 2)
        {
            indepComponentObject.Query();
        }
        else if (type == 3)
        {
            validOrderObject.Query();
        }
        else if (type == 4)
        {
            maxHypeObject.Query();
        }
    }

    return 0;
}

#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

int minDistance(vector<int> dist, vector<bool> sptSet)
{
    //returns the argmin (vertex number) of dist, which has not been searched yet.
    int val = INT_MAX;
    int ver;
    for (int i = 0; i < dist.size(); i++)
    {
        if (!sptSet[i])
        {
            if (dist[i] < val)
            {
                val = dist[i];
                ver = i;
            }
        }
    }
    return ver;
}

void djikstra(vector<vector<int>> &edges, vector<int> &dist, int src)
{
    //edges is a 2D vector that represents an undirected graph represented by an Adjacency Matrix
    //dist is a vector to save the distance of each vertex from src. dist WILL BE INITIALIZED.
    //src is the starting vertex
    //It is assumed that the cost of each existing side is a positive number

    vector<bool> sptSet(edges.size(), 0);      //sptSet will record which vertex has been searched
    dist = vector<int>(edges.size(), INT_MAX); //initialize distance of each vertex to inf
    dist[src] = 0;                             //set the distance of source to 0 so it gets chosen first

    //repeat N-1 times to search the distance to each vertex
    for (int count = 0; count < edges.size() - 1; count++)
    {
        int u = minDistance(dist, sptSet); //determine the next vertex to be searched
        sptSet[u] = 1;                     //set it to searched

        //search the edges connected to vertex u
        for (int i = 0; i < edges.size(); i++)
        {
            //update the dist if it hasnt been searched and the cost is not 0
            if (!sptSet[i] && edges[u][i])
            {
                dist[i] = min(dist[i], dist[u] + edges[u][i]);
            }
        }
    }
}

//running sample
int main(void)
{
    //considering there is N amount of vertex, M amount of sides, start the search from src. src<N
    int N, M, src;
    cin >> N >> M >> src;
    vector<vector<int>> edges(N, vector<int>(N, 0));
    vector<int> dist;

    for (int i = 0; i < M; i++)
    {
        int x, y, cost;
        cin >> x >> y >> cost;
        edges[x][y] = cost;
        edges[y][x] = cost;
    }

    djikstra(edges, dist, src);

    for (int i = 0; i < N; i++)
    {
        cout << dist[i] << " ";
    }

    return 0;
}
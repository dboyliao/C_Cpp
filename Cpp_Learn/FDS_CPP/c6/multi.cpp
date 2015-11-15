enum Boolean {FALSE, TRUE};

class Graph;

class GraphEdge {
friend Graph;
private:
    Boolean m;
    int vertex1, vertex2;
    GraphEdge *path1, *path2;
};

typedef GraphEdge *EdgePtr;

class Graph {
private:
    EdgePtr *HeadNodes;
    int n;
public:
    Graph(const int);
};

Graph::Graph(const int vertices = 0) : n(vertices)
{
     HeadNodes = new EdgePtr[n];
     for (int i = 0; i < n; i++) HeadNodes[i] = 0;
}

main()
{
    Graph g(5);
}
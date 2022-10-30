#include <stdio.h>
#include <string.h>


typedef struct N{
    int value;
    short int infinityFlag;
    long int dist;
} Node;

typedef struct G{
    int ord;
    long int sum;
} Graph;

int takeInput()
{
    int c = getchar();
    int num = 0;
    while(c < '0' || c > '9')
        c = getchar();
    while(c >= '0' && c <= '9')
    {
        num *= 10;
        num += c - '0';
        c = getchar();
    }
    return num;
}

void minHeapify(Node Q[], int dim, int m)
{
    int l = 2 * m + 1;
    int r = 2 * m + 2;
    int posmin = m;
    if(l < dim && Q[l].infinityFlag == 0 && Q[m].infinityFlag == 0 && Q[l].dist < Q[m].dist)
        posmin = l;
    if(l < dim && Q[l].infinityFlag == 0 && Q[m].infinityFlag == 1)
        posmin = l;
    if(r < dim && Q[posmin].infinityFlag == 0 && Q[r].infinityFlag == 0 && Q[r].dist < Q[posmin].dist)
        posmin = r;
    if(r < dim && Q[posmin].infinityFlag == 1 && Q[r].infinityFlag == 0)
        posmin = r;
    if (posmin != m)
    {
        Node swap = Q[m];
        Q[m] = Q[posmin];
        Q[posmin] = swap;
        minHeapify(Q, dim, posmin);
    }
}

void maxHeapify(Graph A[], int dim, int m)
{
    int l = 2 * m + 1;
    int r = 2 * m + 2;
    int posmax = m;
    if(l < dim && A[l].sum > A[m].sum)
        posmax = l;
    if(r < dim && A[r].sum > A[posmax].sum)
        posmax = r;
    if (posmax != m)
    {
        Graph swap = A[m];
        A[m] = A[posmax];
        A[posmax] = swap;
        maxHeapify(A, dim, posmax);
    }
}

void buildMinHeap(Node Q[], int dim)
{
    for(int i = (dim - dim % 2) / 2; i >= 0; i--)
    {
        minHeapify(Q, dim, i);
    }
}

void buildMaxHeap(Graph A[], int dim)
{
    for(int i= (dim - dim%2)/2; i>=0; i--)
    {
        maxHeapify(A, dim, i);
    }
}

Node deleteMin(Node Q[], int dim)
{
    Node min = Q[0];
    Q[0] = Q[dim - 1];
    Q[dim - 1] = min;
    minHeapify(Q, dim - 1, 0);
    return min;
}

Graph deleteMax(Graph A[], int dim)
{
    Graph max = A[0];
    A[0] = A[dim-1];
    A[dim-1] = max;
    maxHeapify(A, dim - 1, 0);
    return max;
}

int parent(int n)
{
    if(n % 2 == 1)
        return (n - 1) / 2;
    else
        return (n - 2) / 2;
}

void insertMaxHeap(Graph A[], int dim, Graph graph)
{
    A[dim - 1] = graph;
    int i = dim - 1;
    while(i > 0 && A[parent(i)].sum < A[i].sum)
    {
        Graph temp = A[parent(i)];
        A[parent(i)] = A[i];
        A[i] = temp;
        i = parent(i);
    }
}

void insertMinHeap(Node Q[], int pos)
{
    while(pos > 0 && (Q[parent(pos)].dist > Q[pos].dist || Q[parent(pos)].infinityFlag == 1))
    {
        Node temp = Q[parent(pos)];
        Q[parent(pos)] = Q[pos];
        Q[pos] = temp;
        pos = parent(pos);
    }
}

unsigned int dijkstraQueue(const int dim, unsigned int *edges)
{
    unsigned int sum = 0;
    int heapsize = dim;
    Node u;
    Node Q[heapsize];
    Q[0].value = 0;
    Q[0].infinityFlag = 0;
    Q[0].dist = 0;
    for(int i = 1; i < dim; i++)
    {
        Q[i].value = i;
        Q[i].infinityFlag = 1;
        Q[i].dist = 0;
    }
    while(heapsize != 0)
    {
        u = deleteMin(Q, heapsize);
        heapsize--;
        if(u.infinityFlag == 1)
            break;
        for(int i = 0; i < heapsize; i++)
        {
            unsigned int *pointer = edges + (u.value * dim) + Q[i].value;
            if(*pointer != 0)
            {
                if(Q[i].infinityFlag == 0)
                {
                    unsigned int ndis = u.dist + *pointer;
                    if(Q[i].dist > ndis)
                    {
                        Q[i].dist = ndis;
                        insertMinHeap(Q, i);
                    }
                }
                else if(Q[i].infinityFlag == 1)
                {
                    Q[i].dist = u.dist + *pointer;
                    Q[i].infinityFlag = 0;
                    buildMinHeap(Q, heapsize);
                }
            }
        }
    }
    for(int i = 0; i < dim; i++)
    {
        sum += Q[i].dist;
    }
    return sum;
}

Graph addGraph(const int dim, int n, Graph graph)
{
    graph.ord = n;
    unsigned int edges[dim][dim];
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
            edges[i][j] = takeInput();
    }
    graph.sum = dijkstraQueue(dim, &edges[0][0]);
    return graph;
}

void classifyGraph(int n, int k, Graph graph, Graph rank[])
{
    if(n < k)
    {
        rank[n] = graph;
    }
    if (n == k)
        buildMaxHeap(rank, k);
    if (n >= k && graph.sum < rank[0].sum)
    {
        deleteMax(rank, k);
        insertMaxHeap(rank, k, graph);
    }
}

void topK(int n, int k, Graph rank[])
{
    if(n == 0 || k == 0)
        printf("\n");
    else if(n > k)
    {
        for(int i = 0; i < k - 1; i++)
        {
            printf("%u ", rank[i].ord);
        }
        printf("%u\n", rank[k - 1].ord);
    }
    else
    {
        for(int i = 0; i < n - 1; i++)
        {
            printf("%u ", i);
        }
        printf("%u\n", n - 1);
    }
}


int main()
{
    int dim, k, n = 0;
    Graph graph;
    char command[14];
    dim = takeInput();
    k = takeInput();
    Graph rank[k];
    while(fgets(command, 14, stdin))
    {
        if(strncmp(command, "AggiungiGrafo", 13) == 0)
        {
            graph = addGraph(dim, n, graph);
            classifyGraph(n, k, graph, rank);
            n++;
        }
        if(strncmp(command, "TopK", 4) == 0)
        {
            topK(n, k, rank);
        }
    }
    return 0;
}

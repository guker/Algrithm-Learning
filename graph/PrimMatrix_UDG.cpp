/**
 * C: Prim�㷨 Dijkstra�㷨(�ڽӾ���)
 *
 * @author skywang
 * @date 2014/04/24
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX         100                 // �����������
#define INF         (~(0x1<<31))        // ���ֵ(��0X7FFFFFFF)
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// �ڽӾ���
typedef struct _graph
{
    char vexs[MAX];       // ���㼯��
    int vexnum;           // ������
    int edgnum;           // ����
    int matrix[MAX][MAX]; // �ڽӾ���
}Graph, *PGraph;

// �ߵĽṹ��
typedef struct _EdgeData
{
    char start; // �ߵ����
    char end;   // �ߵ��յ�
    int weight; // �ߵ�Ȩ��
}EData;

/*
 * ����ch��matrix�����е�λ��
 */
static int get_position(Graph G, char ch)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(G.vexs[i]==ch)
            return i;
    return -1;
}

/*
 * ��ȡһ�������ַ�
 */
static char read_char()
{
    char ch;

    do {
        ch = getchar();
    } while(!isLetter(ch));

    return ch;
}

/*
 * ����ͼ(�Լ�����)
 */
Graph* create_graph()
{
    char c1, c2;
    int v, e;
    int i, j, weight, p1, p2;
    Graph* pG;
    
    // ����"������"��"����"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }
    
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"��"����"
    pG->vexnum = v;
    pG->edgnum = e;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i] = read_char();
    }

    // 1. ��ʼ��"��"��Ȩֵ
    for (i = 0; i < pG->vexnum; i++)
    {
        for (j = 0; j < pG->vexnum; j++)
        {
            if (i==j)
                pG->matrix[i][j] = 0;
            else
                pG->matrix[i][j] = INF;
        }
    }
    // 2. ��ʼ��"��"��Ȩֵ: �����û���������г�ʼ��
    for (i = 0; i < pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ���㣬�������㣬Ȩֵ
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();
        scanf("%d", &weight);

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1)
        {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = weight;
        pG->matrix[p2][p1] = weight;
    }

    return pG;
}

/*
 * ����ͼ(�����ṩ�ľ���)
 */
Graph* create_example_graph()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int matrix[][9] = {
             /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
      /*A*/ {   0,  12, INF, INF, INF,  16,  14},
      /*B*/ {  12,   0,  10, INF, INF,   7, INF},
      /*C*/ { INF,  10,   0,   3,   5,   6, INF},
      /*D*/ { INF, INF,   3,   0,   4, INF, INF},
      /*E*/ { INF, INF,   5,   4,   0,   2,   8},
      /*F*/ {  16,   7,   6, INF,   2,   0,   9},
      /*G*/ {  14, INF, INF, INF,   8,   9,   0}};
    int vlen = LENGTH(vexs);
    int i, j;
    Graph* pG;
    
    // ����"������"��"����"
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"
    pG->vexnum = vlen;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
        pG->vexs[i] = vexs[i];

    // ��ʼ��"��"
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            pG->matrix[i][j] = matrix[i][j];

    // ͳ�Ʊߵ���Ŀ
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            if (i!=j && pG->matrix[i][j]!=INF)
                pG->edgnum++;
    pG->edgnum /= 2;

    return pG;
}

/*
 * ���ض���v�ĵ�һ���ڽӶ����������ʧ���򷵻�-1
 */
static int first_vertex(Graph G, int v)
{
    int i;

    if (v<0 || v>(G.vexnum-1))
        return -1;

    for (i = 0; i < G.vexnum; i++)
        if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INF)
            return i;

    return -1;
}

/*
 * ���ض���v�����w����һ���ڽӶ����������ʧ���򷵻�-1
 */
static int next_vertix(Graph G, int v, int w)
{
    int i;

    if (v<0 || v>(G.vexnum-1) || w<0 || w>(G.vexnum-1))
        return -1;

    for (i = w + 1; i < G.vexnum; i++)
        if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INF)
            return i;

    return -1;
}

/*
 * ���������������ͼ�ĵݹ�ʵ��
 */
static void DFS(Graph G, int i, int *visited)
{                                   
    int w; 

    visited[i] = 1;
    printf("%c ", G.vexs[i]);
    // �����ö���������ڽӶ��㡣����û�з��ʹ�����ô����������
    for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
    {
        if (!visited[w])
            DFS(G, w, visited);
    }
       
}

/*
 * ���������������ͼ
 */
void DFSTraverse(Graph G)
{
    int i;
    int visited[MAX];       // ������ʱ��

    // ��ʼ�����ж��㶼û�б�����
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("DFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        //printf("\n== LOOP(%d)\n", i);
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");
}

/*
 * ����������������������Ĳ�α�����
 */
void BFS(Graph G)
{
    int head = 0;
    int rear = 0;
    int queue[MAX];     // �������
    int visited[MAX];   // ������ʱ��
    int i, j, k;

    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("BFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c ", G.vexs[i]);
            queue[rear++] = i;  // �����
        }
        while (head != rear) 
        {
            j = queue[head++];  // ������
            for (k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k)) //k��Ϊ���ʵ��ڽӶ���
            {
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k]);
                    queue[rear++] = k;
                }
            }
        }
    }
    printf("\n");
}

/*
 * ��ӡ�������ͼ
 */
void print_graph(Graph G)
{
    int i,j;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%10d ", G.matrix[i][j]);
        printf("\n");
    }
}



/* 
 * ��ȡͼ�еı�
 */
EData* get_edges(Graph G)
{
    int i,j;
    int index=0;
    EData *edges;

    edges = (EData*)malloc(G.edgnum*sizeof(EData));
    for (i=0;i < G.vexnum;i++)
    {
        for (j=i+1;j < G.vexnum;j++)
        {
            if (G.matrix[i][j]!=INF)
            {
                edges[index].start  = G.vexs[i];
                edges[index].end    = G.vexs[j];
                edges[index].weight = G.matrix[i][j];
                index++;
            }
        }
    }

    return edges;
}

/* 
 * �Ա߰���Ȩֵ��С��������(��С����)
 */
void sorted_edges(EData* edges, int elen)
{
    int i,j;

    for (i=0; i<elen; i++)
    {
        for (j=i+1; j<elen; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                // ����"��i����"��"��j����"
                EData tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}

/*
 * ��ȡi���յ�
 */
int get_end(int vends[], int i)
{
    while (vends[i] != 0)
        i = vends[i];
    return i;
}

/*
 * ��³˹������Kruskal)��С������
 */
void kruskal(Graph G)
{
    int i,m,n,p1,p2;
    int length;
    int index = 0;          // rets���������
    int vends[MAX]={0};     // ���ڱ���"������С������"��ÿ�������ڸ���С���е��յ㡣
    EData rets[MAX];        // ������飬����kruskal��С�������ı�
    EData *edges;           // ͼ��Ӧ�����б�

    // ��ȡ"ͼ�����еı�"
    edges = get_edges(G);
    // ���߰���"Ȩ"�Ĵ�С��������(��С����)
    sorted_edges(edges, G.edgnum);

    for (i=0; i<G.edgnum; i++)
    {
        p1 = get_position(G, edges[i].start);   // ��ȡ��i���ߵ�"���"�����
        p2 = get_position(G, edges[i].end);     // ��ȡ��i���ߵ�"�յ�"�����

        m = get_end(vends, p1);                 // ��ȡp1��"���е���С������"�е��յ�
        n = get_end(vends, p2);                 // ��ȡp2��"���е���С������"�е��յ�
        // ���m!=n����ζ��"��i"��"�Ѿ���ӵ���С�������еĶ���"û���γɻ�·
        if (m != n)
        {
            vends[m] = n;                       // ����m��"���е���С������"�е��յ�Ϊn
            rets[index++] = edges[i];           // ������
        }
    }
    free(edges);

    // ͳ�Ʋ���ӡ"kruskal��С������"����Ϣ
    length = 0;
    for (i = 0; i < index; i++)
        length += rets[i].weight;
    printf("Kruskal=%d: ", length);
    for (i = 0; i < index; i++)
        printf("(%c,%c) ", rets[i].start, rets[i].end);
    printf("\n");
}

/*
 * prim��С������
 *
 * ����˵����
 *       G -- �ڽӾ���ͼ
 *   start -- ��ͼ�еĵ�start��Ԫ�ؿ�ʼ��������С��
 */
void prim(Graph G, int start)
{
    int min,i,j,k,m,n,sum;
    int index=0;         // prim��С������������prims���������
    char prims[MAX];     // prim��С���Ľ������
    int weights[MAX];    // �����ߵ�Ȩֵ

    // prim��С�������е�һ������"ͼ�е�start������"����Ϊ�Ǵ�start��ʼ�ġ�
    prims[index++] = G.vexs[start];

    // ��ʼ��"�����Ȩֵ����"��
    // ��ÿ�������Ȩֵ��ʼ��Ϊ"��start������"��"�ö���"��Ȩֵ��
    for (i = 0; i < G.vexnum; i++ )
        weights[i] = G.matrix[start][i];
    // ����start�������Ȩֵ��ʼ��Ϊ0��
    // �������Ϊ"��start�����㵽������ľ���Ϊ0"��
    weights[start] = 0;

    for (i = 0; i < G.vexnum; i++)
    {
        // ���ڴ�start��ʼ�ģ���˲���Ҫ�ٶԵ�start��������д���
        if(start == i)
            continue;

        j = 0;
        k = 0;
        min = INF;
        // ��δ�����뵽��С�������Ķ����У��ҳ�Ȩֵ��С�Ķ��㡣
        while (j < G.vexnum)
        {
            // ��weights[j]=0����ζ��"��j���ڵ��Ѿ��������"(����˵�Ѿ���������С��������)��
            if (weights[j] != 0 && weights[j] < min)
            {
                min = weights[j];
                k = j;
            }
            j++;
        }

        // ��������Ĵ������δ�����뵽��С�������Ķ����У�Ȩֵ��С�Ķ����ǵ�k�����㡣
        // ����k��������뵽��С�������Ľ��������
        prims[index++] = G.vexs[k];
        // ��"��k�������Ȩֵ"���Ϊ0����ζ�ŵ�k�������Ѿ��������(����˵�Ѿ���������С�������)��
        weights[k] = 0;
        // ����k�����㱻���뵽��С�������Ľ��������֮�󣬸������������Ȩֵ��
        for (j = 0 ; j < G.vexnum; j++)
        {
            // ����j���ڵ�û�б�����������Ҫ����ʱ�ű����¡�
            if (weights[j] != 0 && G.matrix[k][j] < weights[j])
                weights[j] = G.matrix[k][j];
        }
    }

    // ������С��������Ȩֵ
    sum = 0;
    for (i = 1; i < index; i++)
    {
        min = INF;
        // ��ȡprims[i]��G�е�λ��
        n = get_position(G, prims[i]);
        // ��vexs[0...i]�У��ҳ���j��Ȩֵ��С�Ķ��㡣
        for (j = 0; j < i; j++)
        {
            m = get_position(G, prims[j]);
            if (G.matrix[m][n]<min)
                min = G.matrix[m][n];
        }
        sum += min;
    }
    // ��ӡ��С������
    printf("PRIM(%c)=%d: ", G.vexs[start], sum);
    for (i = 0; i < index; i++)
        printf("%c ", prims[i]);
    printf("\n");
}

/*
 * Dijkstra���·����
 * ����ͳ��ͼ(G)��"����vs"������������������·����
 *
 * ����˵����
 *        G -- ͼ
 *       vs -- ��ʼ����(start vertex)��������"����vs"��������������·����
 *     prev -- ǰ���������顣����prev[i]��ֵ��"����vs"��"����i"�����·����������ȫ�������У�λ��"����i"֮ǰ���Ǹ����㡣
 *     dist -- �������顣����dist[i]��"����vs"��"����i"�����·���ĳ��ȡ�
 */
void dijkstra(Graph G, int vs, int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��
    
    // ��ʼ��
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // ����i�����·����û��ȡ����
        prev[i] = 0;              // ����i��ǰ������Ϊ0��
        dist[i] = G.matrix[vs][i];// ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
    }

    // ��"����vs"������г�ʼ��
    flag[vs] = 1;
    dist[vs] = 0;

    // ����G.vexnum-1�Σ�ÿ���ҳ�һ����������·����
    for (i = 1; i < G.vexnum; i++)
    {
        // Ѱ�ҵ�ǰ��С��·����
        // ������δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���(k)��
        min = INF;
        for (j = 0; j < G.vexnum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // ���"����k"Ϊ�Ѿ���ȡ�����·��
        flag[k] = 1;

        // ������ǰ���·����ǰ������
        // �������Ѿ�"����k�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"��
        for (j = 0; j < G.vexnum; j++)
        {
            tmp = (G.matrix[k][j]==INF ? INF : (min + G.matrix[k][j])); // ��ֹ���
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // ��ӡdijkstra���·���Ľ��
    printf("dijkstra(%c): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}

void main()
{
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    Graph* pG;

    // �Զ���"ͼ"(����������)
    //pG = create_graph();
    // �������е�"ͼ"
    pG = create_example_graph();

    //print_graph(*pG);       // ��ӡͼ
    //DFSTraverse(*pG);       // ������ȱ���
    //BFS(*pG);               // ������ȱ���
    prim(*pG, 0);           // prim�㷨������С������
    //kruskal(*pG);           // kruskal�㷨������С������

    // dijkstra�㷨��ȡ"��4������"�����������������̾���
    //dijkstra(*pG, 3, prev, dist);
}
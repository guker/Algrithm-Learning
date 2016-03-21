/**
 * C: Prim�㷨 Dijkstra�㷨(�ڽӱ�)
 *
 * @author skywang
 * @date 2014/04/24
 * @modify by hqwsky
 * @date 2016/3/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX         100
#define INF         (~(0x1<<31))        // ���ֵ(��0X7FFFFFFF)
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// �ڽӱ��б��Ӧ������Ķ���
typedef struct _ENode
{
    int ivex;                   // �ñߵĶ����λ��
    int weight;                 // �ñߵ�Ȩ
    struct _ENode *next_edge;   // ָ����һ������ָ��
	
}ENode, *PENode;

// �ڽӱ��б�Ķ���
typedef struct _VNode
{
    char data;              // ������Ϣ
    ENode *first_edge;      // ָ���һ�������ö���Ļ�
}VNode;

// �ڽӱ�
typedef struct _LGraph
{
    int vexnum;             // ͼ�Ķ������Ŀ
    int edgnum;             // ͼ�ıߵ���Ŀ
    VNode vexs[MAX];
}LGraph;

/*
 * ����ch��matrix�����е�λ��
 */
static int get_position(LGraph G, char ch)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(G.vexs[i].data==ch)
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
 * ��node���ӵ�list��ĩβ
 */
static void link_last(ENode *list, ENode *node)
{
    ENode *p = list;

    while(p->next_edge)
        p = p->next_edge;
    p->next_edge = node;
}

/*
 * �����ڽӱ��Ӧ��ͼ(�Լ�����)
 */
LGraph* create_lgraph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    int weight;
    ENode *node1, *node2;
    LGraph* pG;

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
 
    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = v;
    pG->edgnum = e;
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����,��������,Ȩ
        printf("edge(%d): ", i);
        c1 = read_char();
        c2 = read_char();
        scanf("%d", &weight);

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);

        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        node1->weight = weight;
		node1->next_edge = NULL;   // added by hqwsky
        // ��node1���ӵ�"p1���������ĩβ"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
        // ��ʼ��node2
        node2 = (ENode*)malloc(sizeof(ENode));
        node2->ivex = p1;
        node2->weight = weight;
		node2->next_edge = NULL;  // added by hqwsky
        // ��node2���ӵ�"p2���������ĩβ"
        if(pG->vexs[p2].first_edge == NULL)
            pG->vexs[p2].first_edge = node2;
        else
            link_last(pG->vexs[p2].first_edge, node2);
    }

    return pG;
}

// �ߵĽṹ��
typedef struct _edata
{
    char start; // �ߵ����
    char end;   // �ߵ��յ�
    int weight; // �ߵ�Ȩ��
}EData;

// ����
static char  gVexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
// ��
static EData gEdges[] = {
  // ��� �յ� Ȩ
    {'A', 'B', 12}, 
    {'A', 'F', 16}, 
    {'A', 'G', 14}, 
    {'B', 'C', 10}, 
    {'B', 'F',  7}, 
    {'C', 'D',  3}, 
    {'C', 'E',  5}, 
    {'C', 'F',  6}, 
    {'D', 'E',  4}, 
    {'E', 'F',  2}, 
    {'E', 'G',  8}, 
    {'F', 'G',  9}, 
};

/*
 * �����ڽӱ��Ӧ��ͼ(�����ṩ������)
 */
LGraph* create_example_lgraph()
{
    char c1, c2;
    int vlen = LENGTH(gVexs);
    int elen = LENGTH(gEdges);
    int i, p1, p2;
    int weight;
    ENode *node1, *node2;
    LGraph* pG;

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // ��ʼ��"�ڽӱ�"�Ķ���
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = gVexs[i];
        pG->vexs[i].first_edge = NULL;
    }

    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����,��������,Ȩ
        c1 = gEdges[i].start;
        c2 = gEdges[i].end;
        weight = gEdges[i].weight;

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);

        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        node1->weight = weight;
		node1->next_edge = NULL;      // added by hqwsky
        // ��node1���ӵ�"p1���������ĩβ"
        if(pG->vexs[p1].first_edge == NULL)
            pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
        // ��ʼ��node2
        node2 = (ENode*)malloc(sizeof(ENode));
        node2->ivex = p1;
        node2->weight = weight;
		node2->next_edge = NULL;      // added by hqwsky
        // ��node2���ӵ�"p2���������ĩβ"
        if(pG->vexs[p2].first_edge == NULL)
            pG->vexs[p2].first_edge = node2;
        else
            link_last(pG->vexs[p2].first_edge, node2);
    }

    return pG;
}

/*
 * ���������������ͼ�ĵݹ�ʵ��
 */
static void DFS(LGraph G, int i, int *visited)
{
    ENode *node;

    visited[i] = 1;
    printf("%c ", G.vexs[i].data);
    node = G.vexs[i].first_edge;
    while (node != NULL)
    {
        if (!visited[node->ivex])
            DFS(G, node->ivex, visited);
        node = node->next_edge;
    }
}

/*
 * ���������������ͼ
 */
void DFSTraverse(LGraph G)
{
    int i;
    int visited[MAX];       // ������ʱ��

    // ��ʼ�����ж��㶼û�б�����
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("DFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");
}

/*
 * ����������������������Ĳ�α�����
 */
void BFS(LGraph G)
{
    int head = 0;
    int rear = 0;
    int queue[MAX];     // �������
    int visited[MAX];   // ������ʱ��
    int i, j, k;
    ENode *node;

    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("BFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c ", G.vexs[i].data);
            queue[rear++] = i;  // �����
        }
        while (head != rear) 
        {
            j = queue[head++];  // ������
            node = G.vexs[j].first_edge;
            while (node != NULL)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k].data);
                    queue[rear++] = k;
                }
                node = node->next_edge;
            }
        }
    }
    printf("\n");
}

/*
 * ��ӡ�ڽӱ�ͼ
 */
void print_lgraph(LGraph G)
{
    int i;
    ENode *node;

    printf("List Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%d(%c): ", i, G.vexs[i].data);
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            printf("%d(%c) ", node->ivex, G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

/*
 * ��ȡG�б�<start, end>��Ȩֵ����start��end������ͨ�ģ��򷵻������
 */
int get_weight(LGraph G, int start, int end)
{
    ENode *node;

    if (start==end)
        return 0;

    node = G.vexs[start].first_edge;
    while (node!=NULL)
    {
        if (end==node->ivex)
            return node->weight;
        node = node->next_edge;
    }

    return INF;
}


/* 
 * ��ȡͼ�еı�
 */
EData* get_edges(LGraph G)
{
    int i;
    int index=0;
    ENode *node;
    EData *edges;

    edges = (EData*)malloc(G.edgnum*sizeof(EData));
    for (i=0; i<G.vexnum; i++)
    {
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            if (node->ivex > i)
            {
                edges[index].start  = G.vexs[i].data;           // ���
                edges[index].end    = G.vexs[node->ivex].data;  // �յ�
                edges[index].weight = node->weight;             // Ȩ
                index++;
            }
            node = node->next_edge;
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
void kruskal(LGraph G)
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
 *       G -- �ڽӱ�ͼ
 *   start -- ��ͼ�еĵ�start��Ԫ�ؿ�ʼ��������С��
 */
void prim(LGraph G, int start)
{
    int min,i,j,k,m,n,tmp,sum;
    int index=0;         // prim��С������������prims���������
    char prims[MAX];     // prim��С���Ľ������
    int weights[MAX];    // �����ߵ�Ȩֵ

    // prim��С�������е�һ������"ͼ�е�start������"����Ϊ�Ǵ�start��ʼ�ġ�
    prims[index++] = G.vexs[start].data;

    // ��ʼ��"�����Ȩֵ����"��
    // ��ÿ�������Ȩֵ��ʼ��Ϊ"��start������"��"�ö���"��Ȩֵ��
    for (i = 0; i < G.vexnum; i++ )
        weights[i] = get_weight(G, start, i);

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
        prims[index++] = G.vexs[k].data;
        // ��"��k�������Ȩֵ"���Ϊ0����ζ�ŵ�k�������Ѿ��������(����˵�Ѿ���������С�������)��
        weights[k] = 0;
        // ����k�����㱻���뵽��С�������Ľ��������֮�󣬸������������Ȩֵ��
        for (j = 0 ; j < G.vexnum; j++)
        {
            // ��ȡ��k�����㵽��j�������Ȩֵ
            tmp = get_weight(G, k, j);
            // ����j���ڵ�û�б�����������Ҫ����ʱ�ű����¡�
            if (weights[j] != 0 && tmp < weights[j])
                weights[j] = tmp;
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
            tmp = get_weight(G, m, n);
            if (tmp < min)
                min = tmp;
        }
        sum += min;
    }
    // ��ӡ��С������
    printf("PRIM(%c)=%d: ", G.vexs[start].data, sum);
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
void dijkstra(LGraph G, int vs, int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1��ʾ"����vs"��"����i"�����·���ѳɹ���ȡ��
    
    // ��ʼ��
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;                    // ����i�����·����û��ȡ����
        prev[i] = 0;                    // ����i��ǰ������Ϊ0��
        dist[i] = get_weight(G, vs, i);  // ����i�����·��Ϊ"����vs"��"����i"��Ȩ��
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
            tmp = get_weight(G, k, j);
            tmp = (tmp==INF ? INF : (min + tmp)); // ��ֹ���
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // ��ӡdijkstra���·���Ľ��
    printf("dijkstra(%c): \n", G.vexs[vs].data);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs].data, G.vexs[i].data, dist[i]);
}

void main()
{
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    LGraph* pG;

    // �Զ���"ͼ"(�Լ���������)
    //pG = create_lgraph();
    // �������е�"ͼ"
    pG = create_example_lgraph();

    //print_lgraph(*pG);    // ��ӡͼ
    //DFSTraverse(*pG);     // ������ȱ���
    //BFS(*pG);             // ������ȱ���
    prim(*pG, 0);         // prim�㷨������С������
    //kruskal(*pG);         // kruskal�㷨������С������

    // dijkstra�㷨��ȡ"��4������"�����������������̾���
    //dijkstra(*pG, 3, prev, dist);
}
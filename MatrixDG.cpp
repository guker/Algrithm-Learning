/**
 * C: �ڽӾ����ʾ��"����ͼ(Matrix Directed Graph)"
 *
 * @author skywang
 * @date 2014/04/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// �ڽӾ���
typedef struct _graph
{
    char vexs[MAX];       // ���㼯��
    int vexnum;           // ������
    int edgnum;           // ����
    int matrix[MAX][MAX]; // �ڽӾ���
}Graph, *PGraph;

/*
 * ����ch��matrix�����е�λ��
 */
static int get_position(Graph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)
        if(g.vexs[i]==ch)
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
    int i, p1, p2;
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

    // ��ʼ��"��"
    for (i = 0; i < pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1)
        {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
    }

    return pG;
}

/*
 * ����ͼ(�����ṩ�ľ���)
 */
Graph* create_example_graph()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'B'}, 
        {'B', 'C'}, 
        {'B', 'E'}, 
        {'B', 'F'}, 
        {'C', 'E'}, 
        {'D', 'C'}, 
        {'E', 'B'}, 
        {'E', 'D'}, 
        {'F', 'G'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    Graph* pG;
    
    // ����"������"��"����"
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // ��ʼ��"����"
    for (i = 0; i < pG->vexnum; i++)
    {
        pG->vexs[i] = vexs[i];
    }

    // ��ʼ��"��"
    for (i = 0; i < pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����ͽ�������
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        pG->matrix[p1][p2] = 1;
    }

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
        if (G.matrix[v][i] == 1)
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
        if (G.matrix[v][i] == 1)
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
            printf("%d ", G.matrix[i][j]);
        printf("\n");
    }
}

void main()
{
    Graph* pG;

    // �Զ���"ͼ"(����������)
    //pG = create_graph();
    // �������е�"ͼ"
    pG = create_example_graph();

    print_graph(*pG);       // ��ӡͼ
    DFSTraverse(*pG);       // ������ȱ���
    BFS(*pG);               // ������ȱ���
}
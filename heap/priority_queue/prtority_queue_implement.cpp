#include<iostream>
#include<algorithm>
#include<vector>
/*
std::priority_queue<Type, Container, Functional>
其中Type 为数据类型， Container 为保存数据的容器，Functional 为元素比较方式
Container 必须是用数组实现的容器，比如 vector, deque 但不能用 list.
STL里面默认用的是 vector. 比较方式默认用 operator< , 所以如果你把后面俩个参数缺省的话，
优先队列就是大顶堆，队头元素最大。

#include <iostream>
#include <queue>
 
using namespace std;
 
int main(){
    priority_queue<int> q;
     
    for( int i= 0; i< 10; ++i ) q.push( rand() );
    while( !q.empty() ){
        cout << q.top() << endl;
        q.pop();
    }
     
    getchar();
    return 0;
}


如果要用到小顶堆，则一般要把模板的三个参数都带进去。
STL里面定义了一个仿函数 greater<>，对于基本类型可以用这个仿函数声明小顶堆


#include <iostream>
#include <queue>
 
using namespace std;
 
int main(){
    priority_queue<int, vector<int>, greater<int> > q;
     
    for( int i= 0; i< 10; ++i ) q.push( rand() );
    while( !q.empty() ){
        cout << q.top() << endl;
        q.pop();
    }
     
    getchar();
    return 0;
}

对于自定义类型，则必须自己重载 operator< 或者自己写仿函数

#include <iostream>
#include <queue>
 
using namespace std;
 
struct Node{
    int x, y;
    Node( int a= 0, int b= 0 ):
        x(a), y(b) {}
};
 
struct cmp{
    bool operator() ( Node a, Node b ){
        if( a.x== b.x ) return a.y> b.y;
         
        return a.x> b.x; }
};
 
int main(){
    priority_queue<Node, vector<Node>, cmp> q;
     
    for( int i= 0; i< 10; ++i )
    q.push( Node( rand(), rand() ) );
     
    while( !q.empty() ){
        cout << q.top().x << ' ' << q.top().y << endl;
        q.pop();
    }
     
    getchar();
    return 0;
} 
*/

using namespace std;

/// protity_queue调用STL的make_heap(),pop_back(),push_heap()算法实现
/// 下面的priority_queue实现与STL里面的priority_queue用法相似，可以加深对priority_queue理解
class priority_queue
{
    private:
        vector<int> data;
         
    public:
        void push( int t ){ 
            data.push_back(t); 
            push_heap( data.begin(), data.end()); 
        }
         
        void pop(){
            pop_heap( data.begin(), data.end() );
            data.pop_back();
        }
         
        int top() { return data.front(); }
        int size() { return data.size(); }
        bool empty() { return data.empty(); }
};
 
 
int main()
{
    priority_queue test;
    test.push( 3 );
    test.push( 5 );
    test.push( 2 );
    test.push( 4 );
     
    while( !test.empty() ){
        std::cout << test.top() << endl;
        test.pop(); }
         
    return 0;
 
}



# 图
## 1 图的定义

G = (V, E) 其中 V 为点集，E 为边集。

**概念**
结点的度：与结点相连的边数（有向图：入度、出度）


## 2 图的分类

有向图/无向图  
有环图/无环图

## 3 图的存储

### 3.1 邻接矩阵

`int g[N][N];`

其中 $N$ 为结点数且一般地  
$N \le 2000$

*数组全初始化为正无穷*

**如果无向图，切记**：  
```cpp
g[i][j] = w;
g[j][i] = w;
```
即正反两边都要初始化

#### 初始化模板

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, m, g[N][N], deg[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    memset(g, 0x3f, sizeof g); // 初始化为正无穷

    // 视有无边权决定


    return 0;
}
```

```cpp
    // 无边权(边权默认为 1)

    cin >> n >> m;
    for(int u, v; m--;){
        cin >> u >> v;
        g[u][v] = 1;
        g[v][u] = 1; // 有向图无需这行
        deg[u] ++;deg[v] ++;
    }

    // 有边权

    cin >> n >> m;
    for(int u, v, w; m--;){
        cin >> u >> v >> w;
        g[u][v] = w;
        g[v][u] = w; // 有向图无需这行
        deg[u] ++;deg[v] ++;
    }

```


### 3.2 邻接表

用 `vector<node>` 数组，每个点的所有边存在每个 `vector<node>` 中，点存在 `vector<node>` 数组中。

```cpp

struct node{
    int v, w;
};


int main(){

    vector<node> g[N]; // 如果要考虑栈空间溢出的事可以看看下面的链式前向星

    cin >> n >> m;
    for(int u, v, w; m--){
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w}); // 有向图无需这行
    }

}


```

### 3.3 链式前向星（链表省空间）

用 `node edge[M]` 维系所有边，其中

```cpp

struct node{
    int to, w, nxt; // 即分别为 右端点 权值 下一条边的下标
};

```

`nxt` 指向同一节点的下一条边，所以其实是维系了一个链表。

那么就用 `head[N]` 来维系每一个点连接的所有边构成链表的头节点。

使用自定义函数来读入图，方便一些

```cpp
#include <bits/stdc++.h>
using namespace std;
// 结点数与边数常量视题目而定
const int N = 1e5+10;
const int M = 1e6+10;

int n, m, cnt, head[N]; 

struct node{
    int to, w, nxt;
} edge[M << 1]; // 如果是无向图，切记要开边数的两倍！

void init(){
    cnt = 0;
    memset(head, -1, sizeof head);
}
void add(int u, int v, int w){
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt++;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	init();
	cin >> n >> m;
	for(int u, v, w; m--;){
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w); // 有向图无需这行
	} 
	
	
	return 0;
}

```

## 4 图的遍历

### 4.1 广度优先搜索（BFS）

常用于**拓扑排序**，将入度为 $0$ 的结点入队（若要求按字典序则使用**优先队列**），并按队列顺序删除队首元素所有出的边，将对应结点的入度减 $1$。再遍历有没有入度为 $0$ 的结点，入队，如此往复。


**拓扑排序**
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    // 假设我已经使用链式前向星存了一张图
    // 并使用 indeg[N] 存了各个点的入度

    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> tp;

    for(int i = 1; i<=n; i++){
        if(!indeg[i]) pq.push(i);
    }

    while(!pq.empty()){
        int u = pq.top(); pq.pop();

        // 此时 u 出队的顺序符合拓扑序，如果不确定无环，可以先用动态数组 tp 维护
        tp.push_back(u);

        for(int j = head[u]; ~j; j = edge[j].nxt){ // ~j 等价于 j != -1
            int v = edge[j].to;
            if(!--indeg[v]) pq.push(v);
        }
    }

    for(int i = 1; i <= n; i++){
        if(indeg[i]){  // 有环，无法生成拓扑序
            cout << -1; 
            return 0;
        }
    }

    // 按序遍历动态数组 tp 并输出即为拓扑序
    for (int v : tp) cout << v << ' ';

    return 0;
}


```
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <map>
#define ff first
#define ss second

using namespace std;

const int INF = 1e9 + 9;
/*
struct Segment {
    vector<pair<int, int>> T;

    Segment() {};
    Segment(vector<int> a) {
        int n = 1;
        while (n < a.size()) n *= 2;
        a.resize(n, INF);
        T.resize(2 * n, {0, 0});
        for(int i = 0; i < n; i++) {
            T[i + n].ff = a[i];
            T[i + n].ss = i;
        }
        for (int i = n - 1; i > 0; i--) {
            T[i] = min(T[i * 2], T[i * 2 + 1]);
        }
    }

    pair<int, int> find_mn(){};
};*/

vector<vector<int>> g;
vector<int> h, size, tin, tout;
int T;

void dfs_calc(int v, int p, int h1) {
    size[v] = 1;
    h[v] = h1 + 1;
    tin[v] = ++T;
    for (auto el: g[v]) if (el != p) {
            dfs_calc(el, v, h[v]);
            size[v] += size[el];
        }
    tout[v] = T++;
}

vector<pair<int, int>> v2tree;
vector<int> tree2v;
vector<vector<int>> tree;


void dfs_choose(int v, int p) {
    //cout << "? " << v + 1 << " " << p + 1<< endl;
    v2tree[v].ff = tree.size() - 1;
    v2tree[v].ss = tree[tree.size() - 1].size();
    tree[tree.size() - 1].push_back(v);
    //cout << v2tree[v] << endl;
    if (g[v].size() <= 0) return;
    int mx_i = 0;
    bool was = 0;
    for (int i = 0; i < g[v].size(); i++) if (g[v][i] != p && (size[g[v][i]] > size[g[v][mx_i]] || !was)) {
            mx_i = i;
            was = 1;
        }
    //cout << mx_i << was << endl;
    if (was) {
        dfs_choose(g[v][mx_i], v);
    } else {
        mx_i = -1;
    }
    for (int i = 0; i < g[v].size(); i++) if (g[v][i] != p && i != mx_i) {
            tree2v.push_back(v);
            tree.push_back({});
            //tree2v.
            dfs_choose(g[v][i], v);
        }
}

/*inline int query_on_path(int old, int tid, int a, int b) {
    return 0;
}*/

pair<int, int> lca(int a, int b) {
    int ans = -1;
    while (v2tree[b].ff != v2tree[a].ff) {
        if (h[tree[v2tree[b].ff][0]] < h[tree[v2tree[a].ff][0]]) swap(a, b);
        /// 0 ... b ... garbage. Query(0, v2tree[b].ss)
        //ans = query_on_path(ans, v2tree[b].ff, 0, v2tree[b].ss);
        b = tree2v[v2tree[b].ff];
    }
    if (h[a] > h[b]) swap(a, b);
    //ans = query_on_path(ans, v2tree[b].ff, v2tree[a].ss, v2tree[b].ss);
    return {a, ans}; /// !!! + 1
}

int main() {
    cin.sync_with_stdio(0);
    while (1) {
        T = 0;
        g.clear();
        h.clear();
        size.clear();
        tin.clear();
        tout.clear();
        int n, m;
        cin >> n;
        if (n == 0) return 0;
        g.resize(n);
        h.resize(n);
        size.resize(n);
        tin.resize(n);
        tout.resize(n);
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        dfs_calc(0, 0, 0);
        v2tree.resize(n);
        tree.push_back({});
        tree2v.push_back(-1);
        dfs_choose(0, 0)
        cin >> m;
        int root = 0;
        for (int i = 0; i < m; i++) {
            char t;
            cin >>t;
            if (t == '?') {
                int a, b;
                cin >> a >> b;
                a--, b--;
                cout << (lca(a, b).ff ^ lca(a, root).ff ^ lca(b, root).ff) + 1 << endl;
            } else {
                cin >> root;
                root--;
            }
        }
    }
    return 0;
}

/*
4
1 2
1 3
2 4
 */
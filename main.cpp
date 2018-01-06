#include <iostream>
#include <vector>
#include <random>
#include <map>

using namespace std;

mt19937 gen(179);

struct node {
    node* L, *R;
    int x, y, sz;
    int cnt;

    node (int x1 = 0) {
        x = x1;
        y = gen() * RAND_MAX + gen();
        L = R = nullptr;
        sz = 1;
        cnt = 1;
    }

    void update() {
        sz = cnt;
        if (L) sz += L->sz;
        if (R) sz += R->sz;
    }
};

ostream& operator<< (ostream& out, const node& we) {
    out << "[ ";
    if (we.L) out << (*we.L);
    out << " ]" << " " << we.x << "{" << we.sz << "}" << " " << "( ";
    if (we.R) out << (*we.R);
    out << " )";
    return out;
}

struct Cartesian {
    node storage[(int)(1e5 + 1000)];
    node* root;
    int empty;

    Cartesian() {
        root = nullptr;
        empty = 0;
        //cout << "$" << endl;
        /*storage.push_back(node(x));
        root = *storage[0];*/
    }

    node* find(int x) {
        node* curr = root;
        //cout << (*curr) << endl;
        while (curr != nullptr && curr->x != x) {
            //cout << curr <<" " << curr-> x <<" " << x << endl;
            if (curr->x > x) {
                curr = curr->L;
            }
            else {
                curr = curr->R;
            }
            //cout << (*curr) << " " << curr->x << " " << (x == curr->x) << endl;
        }
        //cout << "FIND ENDED: " << (nullptr == curr) << endl;
        return curr;
    }

    int by_order(int x) {
        int res = 0;
        node* curr = root;
        while (curr != nullptr && curr->x != x) {
            if (curr->x > x) {
                curr = curr->L;
            }
            else {
                curr = curr->R;
            }
        }
        return res;
    }


    node* merge(node* L, node* R) {
        if (!L) return R;
        if (!R) return L;
        //cout << "M" << " "<< L->x << " " << R->x << " "<< (L->y < R->y) << endl;
        if (L->y < R->y) {
            R->L = merge(L, R->L);
            R->update();
            return R;
        } else {
            L->R = merge(L->R, R);
            L->update();
            return L;
        }
    }

    void split(node* curr, int x, node*& L, node*& R) {
        if (!curr) {
            L = R = nullptr;
            return;
        }
        //cout << "#" << (*curr) << endl;
        if (curr->x < x) {
            split(curr->R, x, curr->R, R);
            L = curr;
        } else {
            split(curr->L, x, L,curr->L);
            R = curr;
        }
        curr->update();
    }

    void rec(node* curr, int x) {
        if (!curr || curr->x == x) return;
        if (curr->x > x) rec(curr->L, x);
        else rec(curr->R, x);
        curr->update();
    }

    void insert(int x) {
        auto we = find(x);
        if (we) {
            we->cnt++;
            we->sz++;
            rec(root, x);
            return;
        }

        storage[empty] = node(x);
        node *w = &storage[empty++];
        //cnt[w] = empty;
        /// Attention to equal elements;
        node *r1 = nullptr, *r2 = nullptr;
        //cout << "SPLIT" << endl;
        split(root, x, r1, r2);
        /*if (r1) cout << (*r1) << endl;
        else cout << "NO-R1" << endl;
        if (r2) cout << (*r2) << endl;
        else cout << "NO-R2" << endl;
        cout << "MERGE1" << endl;*/
        r1 = merge(r1, w);
        /*if (r1) cout << (*r1) << endl;
        else cout << "<?>" << endl;
        if (r2) cout << (*r2) << endl;
        else cout << "<?>" <<endl;
        cout << "MERGE2" << endl;
        cout << w->x << endl;*/
        root = merge(r1, r2);
        /*if (r1) cout << (*r1) << endl;
        else cout << "<?>" << endl;
        if (r2) cout << (*r2) << endl;
        else cout << "<?>" <<endl;*/
    }

    void erase(int x) {
        auto need = find(x);
        if (!need) {
            return;
        }
        need->cnt--;
        need->sz--;
        rec(root, x);
        if (need->cnt != 0) return;
        //cout << (*need) << endl;
        node *r1 = nullptr, *r2 = nullptr;
        split(root, need->x, r1, r2); /// x will move to the right subtree;
        //cout << "SPIT1 " << "OK" << endl;
        if (r1) cout << "R1: " << (*r1) << endl;
        if (r2) cout << "R2: " << (*r2) << endl;
        split(r2, need->x + 1, root, r2);
        //cout << "SPLIT2 " << "OK" << endl;
        root = merge(r1, r2);
        //cout << "MERGE " << "OK" << endl;
    }

};



int main() {
    Cartesian T;
    //cout << "##" << endl;
    while (1) {
        int t;
        int q;
        cin >> t >> q;
        if (t == 0) {
            T.erase(q);
        } else {
            T.insert(q);
        }
        //cout << "$" << endl ;
        //cout << "ENDED" << endl;
        if (T.root) cout << (*T.root) << endl;
        else cout << "EMPTY" << endl;
        //cout << endl << endl;
    }
    return 0;
}
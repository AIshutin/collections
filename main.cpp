#include <iostream>
#include <vector>
#define ff first
#define ss second
#define int long long

using namespace std;

const int INF = 1e9 + 179;

struct Node {
    int val, mod;
    Node() {}
    Node(int val): val(val), mod(0) {};
};

bool operator<(const Node& A, const Node& B) {
    return A.val < B.val;
}

ostream& operator<<(ostream& out, const Node& A) {
    out << "{" << A.val << "; " << A.mod << "}";
    return out;
}

struct SegmentTree {
    vector<Node> arr;
    const Node BAD = {0};
    SegmentTree(vector<int> brr) {
        int N = 1;
        while (N < brr.size()) N *= 2;
        brr.resize(N);
        arr.resize(2 * N, BAD);
        for (int i = 0; i < N; i++) {
            arr[i + N] = Node(brr[i]);
        }
        for (int i = N - 1; i >= 1; i--) {
            arr[i] = min(arr[i * 2], arr[i * 2 + 1]);
        }
    }

    void push(int i, int mod, int l) {
        arr[i].mod += mod;
        arr[i].val += l * mod;
    }

    /*
    void push(int i, int mod, int l) {
        //arr[i].val += arr[i].mod * n;
        arr[i].mod = 0;
        if (2 * i >= arr.size()) {
            return;
        }
        arr[2 * i].mod += arr[i].mod;
        arr[2 * i].val += l1 * arr[i].mod;
        arr[2 * i + 1].mod += arr[i].mod;
        arr[2 * i + 1].val += l2 * arr[i].mod;
    }
     */

    void pull(int i) {
        arr[i].val = arr[2 * i].val + arr[2 *i + 1].val;
        arr[i].mod = 0;
    }

    int sum_on_segm(int i, int l, int r, int ql, int qr) {
        //cout << "# " << i << " " << arr[i] << " " << l << " " << r << " " << ql << " " << qr<< endl;
        if (qr < l || ql > r || l > r) return 0;
        if (l >= ql && r <= qr) return arr[i].val;
        int m = (l + r) / 2;
        auto res1 = 0, res2 = 0;
        push(2 * i, arr[i].mod, m - l + 1);
        push(2 * i + 1, arr[i].mod, r - m);
        if (ql <= m) {
            res1 = sum_on_segm(i * 2, l, m, ql, min(m, qr));
        }
        if (m + 1 <= qr) {
            res2 = sum_on_segm(i * 2 + 1, m + 1, r, max(m, ql), qr);
        }
        pull(i);
        //cout << ">> " << i << " " << arr[i] << endl;
        //cout << res1 << " " << res2 << endl;
        return res1 + res2;
    }

    void add_on_segm(int i, int l, int r, int ql, int qr, int s) {
        //cout << "# " << i << " " << arr[i] << " " << l << " " << r << " " << ql << " " << qr<< endl;
        if (qr < l || ql > r || l > r) return;
        if (l >= ql && r <= qr) {
            arr[i].mod += s;
            arr[i].val += s * (r - l + 1);
            //cout << "% " << i << " " << arr[i] << endl;
            return;
        }
        int m = (l + r) / 2;
        push(2 *i, arr[i].mod, m - l + 1);
        push(i * 2 + 1, arr[i].mod, r - m);
        if (ql <= m) {
            add_on_segm(i * 2, l, m, ql, min(m, qr), s);
        }
        if (m + 1 <= qr) {
            add_on_segm(i * 2 + 1, m + 1, r, max(m + 1, ql), qr, s);
        }
        //cout << ">> " << arr[i * 2] << " " << arr[i * 2 + 1] << endl;
        pull(i);
        //cout << ">> " << i << " " << arr[i] << endl;
    }

    int sum_on_segm(int l, int r) {
        return sum_on_segm(1, 0, arr.size() / 2 -1, l, r);
    };

    void add_on_segm(int l, int r, int s) {
        add_on_segm(1, 0, arr.size() / 2 - 1, l, r, s);
    }
};

/*
10 5
1 0 9 10
1 1 5 -3
2 4 8
1 0 6 25
2 0 2
 */


signed main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    SegmentTree T(arr);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, a, b;
        //cout << endl << endl;
        cin >> t >> a >> b;
        b--;
        if (t == 1) {
            int s;
            cin >> s;
            T.add_on_segm(a, b, s);
        } else {
            cout << T.sum_on_segm(a, b) << endl;
        }
    }
    cout << endl;
    return 0;
}
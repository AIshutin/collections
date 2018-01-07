#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF = -1e9 - 100;

template<typename node> struct Segment{
    vector<node> body;
    vector<int> who;
    node (*func)(node , node);

    Segment(vector<node> inp, node (*func1)(node , node)) {
        int N = 1;
        func = func1;
        while (N < inp.size()) {
            N *= 2;
        }
        //cout << N << endl;
        inp.resize(N, INF); /// ATTENTION!!!
        body.resize(N * 2);
        who.resize(N * 2);
        for (int i = N; i < body.size(); i++) {
            //cout << "#" << i << " " << (i - N) << endl;
            body[i] = inp[i - N];
            who[i] = i - N;
        }
        for (int i = N - 1; i >= 1; i--) {
            body[i] = func(body[i << 1], body[(i << 1) + 1]);
            if (body[i] == body[i << 1]) who[i] = who[i << 1];
            else who[i] = who[(i << 1) + 1];
        }/*
        for (auto el: body) {
            if (el > 20) el = -1;
            cout << el <<"  ";
        }
        cout << endl;
        for (auto el: who) cout<< el << "  ";
        cout << endl;
        for (int i = 0; i < who.size(); i++) cout << i <<"  ";
        cout << endl;*/
    };

    node get(int i) {
        return body[body.size() / 2 + i];
    }

    node change(int i, node item) {
        i += body.size() / 2;
        body[i] = item;
        i /= 2;
        while (i >= 1) {
            body[i] = func(body[i << 1], body[(i << 1) + 1]);
            if (body[i] == body[i << 1]) who[i] = who[i << 1];
            else who[i] = who[(i << 1) + 1];
            i = i >> 1;
        }
    }

    pair<int, node> find_on_segm(int l, int r) { /// Attention for some funcs first returning value might be meaningless;
        l += body.size() / 2;
        r += body.size() / 2;
        node ans = INF;//node();
        ///  ^^WARNING!!!^^ Uncomment to work properly with template; Not only here;
        int j = body.size() + 16;
        while (l < r) {

            if (l % 2 == 1) {
               auto q = func(ans, body[l]);
                if ((body[l] == q && who[l] <  j) || ans != q) {
                    ans = q;
                    j = who[l];
                }
                l++;
            }
            //cout << "% " << l << " " << r << " " << ans << " " << j << endl;
            if (r % 2 == 0) {
                auto q = func(ans, body[r]);
                if ((body[r] == q && who[r] <  j) || ans != q) {
                    ans = q;
                    j = who[r];
                }
                r--;
            }
            //cout << "% " << l << " " << r << " " << ans << " " << j << endl;

            l /= 2;
            r /= 2;
        }
        if (l == r) {
            auto q = func(ans, body[l]);
            //cout << q << " " << who[l] << endl;
            if ((who[l] <  j && ans == body[l]) || ans != q) {
                ans = q;
                j = who[l];
            }
        }
        //cout << "**" << l << " " << r << " " << ans << " " << j << endl;
        return {j, ans};
    }


    int size() {
        return body.size() / 2;
    }

};

template<typename node> ostream& operator<< (ostream& out, Segment<node> we) {
    if (we.body.size() == 0) return out;
    for (int i = 1; i < we.body.size() - 1; i++) {
        out << we[i] << " ";
    } out << we[we.body.size() - 1];
    return out;
}

int min_func(int a, int b) {
    return max(a, b);
}

int main() {
    vector<int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        a.push_back(b);
    }
    Segment<int> T(a, min_func);
    int q;
    cin >> q;
    for (; q > 0; q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        auto q = T.find_on_segm(l, r);
        cout << q.second << " " << q.first + 1 << endl;
    }

    //cout << "Hello, World!" << endl;
    return 0;
}
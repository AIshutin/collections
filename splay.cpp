#include <bits/stdc++.h>

using namespace std;

struct Node {
	Node *L, *R, *p;
	int key;
	Node() {}
	Node(int key, Node* p=nullptr): key(key), p(p), L(nullptr), R(nullptr) {}
};

typedef Node* nodeptr;

ostream& operator<<(ostream& out, nodeptr we) {
	if (!we) return out;
	out << "{ " << we->L << " }";
	int y = -1;
	if (we->p) y = we->p->key;
	out << we->key << "(" << y << ") ";
	out << "[ " << we->R << " ]";
	return out;
}

inline void set_p(nodeptr we, nodeptr p) {
	if (we) {
		we->p = p;
	}
}

inline void set_sons(nodeptr we) {
	set_p(we->L, we);
	set_p(we->R, we);
}

inline void rotate(nodeptr par, nodeptr child) {
	if (!child || !par) return;
	auto subroot = par->p;
	bool left = 0;
	if (subroot && subroot->L == par) left =1;

	if (par->L == child) {
		par->L = child->R; 
		child->R = par;
	} else {
		par->R = child->L;
		child->L = par;
	}
	
	set_sons(child);
	set_sons(par);

	if (subroot) {
		if (left) subroot->L = child;
		else subroot->R = child;
	}
	child->p = subroot;
}

inline int which_son(nodeptr par, nodeptr son) {
	if (!par) return 0;
	if (par->L == son) return -1;
	else return 1;
}

nodeptr splay(nodeptr we) {
	if (!we->p) return we;
	auto par = we->p;
	if (!par->p) {
		rotate(par, we);
		return we;
	}
	auto subroot = par->p;

	int sum = which_son(par, we) + which_son(subroot, par);
	if (abs(sum) == 2) { // zig-zig case
		rotate(subroot, par);
		rotate(par, we);
	} else { // zig-zag case
		rotate(par, we);
		rotate(subroot, we);
	}

	return splay(we);
}

nodeptr find(nodeptr root, int key) {
	if (!root) return nullptr;
	if (root->key == key) return splay(root);
	if (key < root->key && root->L) {
		return find(root->L, key);
	}
	if (key > root->key && root->R) {
		return find(root->R, key);
	}
	return splay(root); //? return splay(root); // not found
}

const int SZ = 1e3 + 13;
Node T[SZ];
nodeptr root;
int _last;

void split(nodeptr root, int x, nodeptr& L, nodeptr& R) { // diff
	if (!root) {
		L = R = nullptr;
		return;
	}

	// 0..key - 1 | key key + 1 ..

	root = find(root, x);

	if (!root) {
		cout << "oops 104" << endl;
	}

	if (root->key < x) {
		R = root->R;
		L = root;
		set_p(root->R, nullptr);
		root->R = nullptr;
	} else {
		L = root->L;
		R = root;
		set_p(root->L, nullptr);
		root->L = nullptr;
	}
}

nodeptr insert(nodeptr root, int key) {
	T[_last] = {key};
	nodeptr we = &T[_last++];

	nodeptr L = nullptr, R = nullptr;
	split(root, key, L, R);
	we->L = L;
	we->R = R;
	set_sons(we);

	return we;
}

nodeptr get_left(nodeptr root) {
	if (!root) return nullptr;
	while (root->L) {
		root = root->L;
	}
	return splay(root);
}

nodeptr merge(nodeptr L, nodeptr R) {
	if (!L) return R;
	if (!R) return L;
	R = get_left(R);
	R->L = L;
	set_sons(R);
	return R;
}

nodeptr erase(nodeptr root, int key) {
	root = find(root, key);
	if (!root) return nullptr;
	set_p(root->L, nullptr);
	set_p(root->R, nullptr);
	root = merge(root->L, root->R);
	return root;
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	while (n-->0) {
		char t;
		cin >> t;
		int key;
		cin >> key;
		if (t == '?') {
			root = find(root, key);
			if (root && root->key == key) cout << "yes" << endl;
			else cout << "no" <<endl;
		} else if (t == '+') {
			root = insert(root, key);
		} else if (t == '-') {
			root = erase(root, key);
		}
		//cout << "T: " << root << endl;
	}
	return 0;	
}

/*
5
+ 0
+ 7
- 7
- 0
? 7

*/
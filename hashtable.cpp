#include <bits/stdc++.h>

using namespace std;

template<class Key, class Value> 
struct LinkedList {
	struct Node {
		Key key;
		Value val;
		Node* nxt;
		Node(): nxt(nullptr) {}
		Node(Key key, Value val): key(key), val(val), nxt(nullptr) {}
	};

	Node* root;

	void add(Key key, Value val) {
		if (!root) {
			root = new Node(key, val);
		} else {
			//cout << "ADD " << key << " " << val << endl;
			auto curr = root;
			while (curr->nxt) {
				curr = curr->nxt;
			}
			curr->nxt = new Node(key, val);
			cout << curr->key << ": " << curr->nxt << endl;
			assert(curr->nxt != 0);
		}
	}

	bool erase(Key key) {
		if (root && root->key == key) {
			auto copy = root;
			root = root->nxt;
			delete copy;
			return 1;
		} else if (!root) return 0;
		auto prev = root;
		while (prev->nxt && prev->nxt->key != key) prev = prev->nxt;
		if (!prev->nxt) return 0;
		auto nxt2 = prev->nxt->nxt;
		delete prev->nxt;
		prev->nxt = nxt2;
		return 1;
	}

	LinkedList(): root(nullptr) {}

	void rec_delete(Node* curr) {
		if (curr == nullptr) return;
		rec_delete(curr->nxt);
		delete curr;
	}

	Value* get(Key key) {
		auto curr = root;
		//cout << "GET: " << key << endl;
		while (curr) {
			//cout << "step: " << curr->key << " " << curr->nxt << endl;
			if (curr->key == key) return &curr->val;
			curr = curr->nxt;
		}
		return nullptr;
	}

	~LinkedList() {
		rec_delete(root);
	}
};

template<class Key, class Value, int N>
struct HashTable {
	struct Node {
		Node* nxt;
		Value val;
		Key key;
		bool empty;
		Node(): empty(1), nxt(nullptr) {}
		Node(Key key, Value val): key(key), val(val), empty(1), nxt(nullptr) {}
		void add(Node* nxt) {
			nxt = nxt;
		}
	};

	LinkedList<Key, Value> table[N];
	size_t (*hash)(Key);

	HashTable(size_t (*hashf)(Key)) {
		hash = hashf;
	} 

	void add(Key key, Value val) {
		table[(*hash)(key)].add(key, val);
	}

	Value* get(Key key) {
		return table[(*hash)(key)].get(key);
	}

	bool erase(Key key) {
		return table[(*hash)(key)].erase(key);
	}
};

size_t hashf(int key) {
	return key % 17;
}

HashTable<int, int, 17> T(hashf);

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);﻿
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout << "START " << endl;

	while (1) {
		int key, val;
		int* res;
		char t;
		cin >> t;
		//cout << "T: " << t << endl;
		if (t == '+') {
			cin >> key >> val;
			T.add(key, val);
		} else if (t == '-') {
			cin >> key;
			cout << T.erase(key) << endl;
		} else if (t == '?') {
			cin >> key;
			res = T.get(key);
			if (res == nullptr) cout << "<nothing>" << endl;
			else cout << *res << endl;
		} else if (t == 'x') {
			break;
		}
	}

	return 0;
}
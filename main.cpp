#include<iostream>
#include<string>
#include<vector>
#include<list>

using namespace std;

//루트노드는 삭제 하지 않을 것지 보장되고, 트리에 값의 입력엔 중복되지 않은 값 입력이 보장됨
//루트노드에는 반드시 1의 값이 들어있음

class Node {
public:
	Node(int elem = 0 , Node* parent = nullptr)
		:elem{elem} , parent{parent}
	{
		
	}




private:
	int elem;
	Node* parent;
	list<Node*> children;
	list<Node*>::iterator pos_in_parent;
	list<Node*>::iterator pos_seq;
	int depth;


	friend class Tree;
};

class Tree {
public:
	Tree()
		: root{new Node(1)}
	{
		root->depth = 0;

		root->pos_seq = node_seq.insert(node_seq.end(), root);


	}

	~Tree() {
		erase(root);
	}

	bool insert(int x, int c) {
		list<Node*>::iterator it = find(x);

		if (it == node_seq.end() || find(c) != node_seq.end()) return false;



		Node* newNode = new Node(c,*it);

		newNode->pos_in_parent = (*it)->children.insert((*it)->children.end(), newNode);

		newNode->pos_seq = node_seq.insert(node_seq.end(), newNode);

		newNode->depth = (*it)->depth + 1;


		return true;
	}

	bool erased(int x) {
		list<Node*>::iterator it = find(x);
		if (it == node_seq.end()) return false;
		erase(*it);

		return true;
	}

	int pasrent(int x) {
		list<Node*>::iterator it = find(x);
		if (it == node_seq.end() || (*it)->parent == nullptr) return -1;
		
		return (*it)->parent->elem;
		

	}

	void children(int x) {
		list<Node*>::iterator it = find(x);
		if (it == node_seq.end()) // 노드가 없을때 예외처리
		{
			cout << -1 << endl;
		}
		else if ((*it)->children.empty()) {
			cout << 0 << endl;
		}
		else {

			for (Node* child : (*it)->children) {
				cout << child->elem << " ";

			}
			cout << endl;

		}

	}

	int depth(int x) {
		list<Node*>::iterator it = find(x);
		if (it == node_seq.end()) return -1;


		return (*it)->depth;

	}



	list<Node*>::iterator find(int x) {
		return find_seq(node_seq, x);
	}

private:
	Node* root;

	list<Node*> node_seq;


	list<Node*>::iterator find_recursion(Node* target, int x) {
		if (target->elem == x) return target->pos_seq;

		for (Node* child : target->children) {
			list<Node*>::iterator it = find_recursion(child, x);

			if (it != node_seq.end()) return it;
		}
		//반복문을 넘어왔다는 건, 자신과 자식노드에 찾는 노드가 없다는 뜻.

		return node_seq.end();
	}

	list<Node*>::iterator find_seq(list<Node*>& seq, int x) {

		for (Node* it : seq) {
			if (it->elem == x) {
				return it->pos_seq;
			}
		}

		return seq.end();
	}

	void erase(Node* node) {

		while (!node->children.empty())
		{
			erase(node->children.front());
		}

		node_seq.erase(node->pos_seq);


		if (node != root) {
			node->parent->children.erase(node->pos_in_parent);

		}

		delete node;
	}

};

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int Q;
		cin >> Q;


		Tree* tmp = new Tree();

		for (int j = 0; j < Q; j++) {
			string S;

			cin >> S;



			if (S == "insert") {
				int x, c;
				cin >> x >> c;
				if (!tmp->insert(x, c)) cout << -1 << endl;
				

			}
			else if (S == "erase") {
				int x;
				cin >> x;

				if (!tmp->erased(x)) cout << -1 << endl;

			}
			else if (S == "parent") {
				int x;
				cin >> x;

				cout << tmp->pasrent(x) << endl;

			}
			else if (S == "children") {
				int x;
				cin >> x;
				tmp->children(x);

			}
			else if (S == "depth") {
				int x;
				cin >> x;

				cout << tmp->depth(x) << endl;
			}

		}

		delete tmp;


	}



}
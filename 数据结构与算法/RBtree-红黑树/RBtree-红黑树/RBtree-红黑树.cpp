#include<iostream>
#include<queue>
using namespace std;
template<typename T>
class RBtree {
public:
	RBtree():root(nullptr){}
	~RBtree() {
		if (root != nullptr) {
			queue<Node*>q;
			q.push(root);
			while (!q.empty()) {
				Node* front = q.front();
				q.pop();
				if (front->left != nullptr) {
					q.push(front->left);
				}
				if (front->right != nullptr) {
					q.push(front->right);
				}
				delete front;
			}
		}
	}
	void insert(const T& val) {
		if (root == nullptr) {
			root = new Node(val);
			return;
		}

		Node* parent = nullptr;
		Node* cur = root;
		while (cur != nullptr) {
			if (cur->data > val) {
				parent = cur;
				cur = cur->left;
			}
			else if (cur->data < val) {
				parent = cur;
				cur = cur->right;
			}
			else {
				//��һ������ֵ��ȣ�������
				return;
			}
		}
		//���õ�ǰ�ڵ��parent����ɫ
		Node* node = new Node(val, nullptr, nullptr,parent, RED);
		if (parent->data > val) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		
		//����²���ĺ�ɫ�ڵ㣬���ڵ�Ҳ�Ǻ�ɫ���������������ʣ����в����������
		if (RED == color(parent)) {
			fixAfterInsert(node);
		}
	}
private:
	//�ڵ����ɫ
	enum Color {
		BLACK,
		RED
	};

	//�ڵ�����
	struct Node {
		Node(T data = T(), Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, Color color = BLACK)
			:data(data)
			,left(left)
			,right(right)
			,parent(parent)
			,color(color)
		{ }//���캯��
		T data;
		Node* left;
		Node* right;
		Node* parent;//ָ��ǰ�ڵ�ĸ��ڵ�
		Color color;//�ڵ����ɫ
	};
	Node* root;//������ĸ��ڵ�

	//���ؽڵ����ɫ
	Color color(Node* node) {
		return node == nullptr ? BLACK : node->color;
	}
	//���ýڵ���ɫ
	void setColor(Node* node, Color color) {
		node->color = color;
	}
	//���ؽڵ������
	Node* left(Node* node) {
		return node->left;
	}
	//���ؽڵ���Һ���
	Node* right(Node* node) {
		return node->right;
	}
	//���ؽڵ�ĸ���
	Node* parent(Node* node) {
		return node->parent;
	}
	//����ת
	void leftRotate(Node* node) {
		Node* child = node->right;
		child->parent = node->parent;
		if (node->parent == nullptr) {
			//node�������root�ڵ�
			root = child;
		}
		else {
			if (node->parent->left == node) {
				//node�ڸ��ڵ������
				node->parent->left = child;
			}
			else {
				//node�ڸ��ڵ���Һ�����
				node->parent->right = child;
			}
		}
		
		node->right = child->left;
		if (child->left != nullptr) {
			child->left->parent = node;
		}
		child->left = node;
		node->parent = child;

	}
	//����ת
	void rightRotate(Node* node) {
		 Node* child = node->left;
		 child->parent = node->parent;
		 if (node->parent == nullptr) {
			 root = child;
		 }
		 else {
			 if (node->parent->left == node) {
				 //node���丸�׽�������
				 node->parent->left = child;
			 }
			 else {
				 //node���丸�׽ڵ���Һ���
				 node->parent->right = child;
			 }
		 }
		 node->left = child->right;
		 if (child->right != nullptr) {
			 child->right->parent = node;
		 }
		 

		 child->right = node;
		 node->parent = child;
	}
	//������Ĳ����������
	void fixAfterInsert(Node* node) {
		//�����ǰ��ɫ�ӵ��ǵĸ��ڵ�Ҳ�Ǻ�ɫ����������
		while (color(parent(node)) == RED) {

			if (left(parent(parent(node))) == parent(node)) {
				//����Ľڵ�����������
				Node* uncle = right(parent(parent(node)));
				if (RED == color(uncle)) {
					//���һ
					setColor(parent(node), BLACK);//���ڵ���Ϊ��ɫ
					setColor(uncle, BLACK);//������Ϊ��ɫ
					setColor(parent(parent(node)),RED);//үү�ڵ���Ϊ��ɫ
					node = parent(parent(node));//�������ϵ���
				}
				else {
					//�ȴ��������
					if (right(parent(node)) == node) {
						node = parent(node);
						leftRotate(node);
					}
					
					//ͳһ���������
					setColor(parent(node), BLACK);
					setColor((parent(parent(node))),RED);
					rightRotate(parent(parent(node)));
					break;

				}

			}
			else {
				//����Ľ������������
				Node* uncle = left(parent(parent(node)));
				if (RED == color(uncle)) {
					//���һ
					setColor(parent(node), BLACK);//���ڵ���Ϊ��ɫ
					setColor(uncle, BLACK);//������Ϊ��ɫ
					setColor(parent(parent(node)), RED);//үү�ڵ���Ϊ��ɫ
					node = parent(parent(node));//�������ϵ���
				}
				else {
					//�ȴ��������
					if (left(parent(node)) == node) {
						node = parent(node);
						rightRotate(node);
					}

					//ͳһ���������
					setColor(parent(node), BLACK);
					setColor((parent(parent(node))),RED);
					leftRotate(parent(parent(node)));
					break;

				}
			}
		}
		//�˴�ǿ��rootΪ��ɫ�ڵ�
		setColor(root, BLACK);
	}

};
int main() {
	RBtree<int> rbt;
	for (int i = 1;i <= 10;i++) {
		rbt.insert(i);
	}

	return 0;
}

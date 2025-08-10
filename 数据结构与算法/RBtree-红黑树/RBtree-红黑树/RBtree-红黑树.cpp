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
				//和一个结点的值相等，不插入
				return;
			}
		}
		//设置当前节点的parent和颜色
		Node* node = new Node(val, nullptr, nullptr,parent, RED);
		if (parent->data > val) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		
		//如果新插入的红色节点，父节点也是红色，不满足红黑树性质，进行插入调整操作
		if (RED == color(parent)) {
			fixAfterInsert(node);
		}
	}
private:
	//节点的颜色
	enum Color {
		BLACK,
		RED
	};

	//节点类型
	struct Node {
		Node(T data = T(), Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, Color color = BLACK)
			:data(data)
			,left(left)
			,right(right)
			,parent(parent)
			,color(color)
		{ }//构造函数
		T data;
		Node* left;
		Node* right;
		Node* parent;//指向当前节点的父节点
		Color color;//节点的颜色
	};
	Node* root;//红黑树的根节点

	//返回节点的颜色
	Color color(Node* node) {
		return node == nullptr ? BLACK : node->color;
	}
	//设置节点颜色
	void setColor(Node* node, Color color) {
		node->color = color;
	}
	//返回节点的左孩子
	Node* left(Node* node) {
		return node->left;
	}
	//返回节点的右孩子
	Node* right(Node* node) {
		return node->right;
	}
	//返回节点的父亲
	Node* parent(Node* node) {
		return node->parent;
	}
	//左旋转
	void leftRotate(Node* node) {
		Node* child = node->right;
		child->parent = node->parent;
		if (node->parent == nullptr) {
			//node本身就是root节点
			root = child;
		}
		else {
			if (node->parent->left == node) {
				//node在父节点的左孩子
				node->parent->left = child;
			}
			else {
				//node在父节点的右孩子域
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
	//右旋转
	void rightRotate(Node* node) {
		 Node* child = node->left;
		 child->parent = node->parent;
		 if (node->parent == nullptr) {
			 root = child;
		 }
		 else {
			 if (node->parent->left == node) {
				 //node是其父亲结点的左孩子
				 node->parent->left = child;
			 }
			 else {
				 //node是其父亲节点的右孩子
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
	//红黑树的插入调整操作
	void fixAfterInsert(Node* node) {
		//如果当前红色接地那的父节点也是红色，继续调整
		while (color(parent(node)) == RED) {

			if (left(parent(parent(node))) == parent(node)) {
				//插入的节点在左子树上
				Node* uncle = right(parent(parent(node)));
				if (RED == color(uncle)) {
					//情况一
					setColor(parent(node), BLACK);//父节点置为黑色
					setColor(uncle, BLACK);//叔叔置为黑色
					setColor(parent(parent(node)),RED);//爷爷节点置为红色
					node = parent(parent(node));//继续向上调整
				}
				else {
					//先处理情况三
					if (right(parent(node)) == node) {
						node = parent(node);
						leftRotate(node);
					}
					
					//统一处理情况二
					setColor(parent(node), BLACK);
					setColor((parent(parent(node))),RED);
					rightRotate(parent(parent(node)));
					break;

				}

			}
			else {
				//插入的结点在右子树上
				Node* uncle = left(parent(parent(node)));
				if (RED == color(uncle)) {
					//情况一
					setColor(parent(node), BLACK);//父节点置为黑色
					setColor(uncle, BLACK);//叔叔置为黑色
					setColor(parent(parent(node)), RED);//爷爷节点置为红色
					node = parent(parent(node));//继续向上调整
				}
				else {
					//先处理情况三
					if (left(parent(node)) == node) {
						node = parent(node);
						rightRotate(node);
					}

					//统一处理情况二
					setColor(parent(node), BLACK);
					setColor((parent(parent(node))),RED);
					leftRotate(parent(parent(node)));
					break;

				}
			}
		}
		//此处强制root为黑色节点
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

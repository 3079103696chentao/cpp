#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

//定义AVL树节点类型
template<typename T>
class AVLTree
{
public:
	AVLTree() :root(nullptr) {}
	//AVL树的插入操作
	void insert(const T &val) {
		root = insert(root,val);
	}
private:
	//定义AVL树节点类型
	struct Node {
		Node(T data = T())
			:data(data)
			, left(nullptr)
			, right(nullptr)
			, height(1)
		{ }
		T data;
		Node* left;
		Node* right;
		int height;//记录节点的高度值
	};
	//返回节点的高度值
	int height(Node* node) {
		return node == nullptr ? 0 : node->height;//如果该节点是末尾节点，返回0
	}
	//右旋转操作，以参数node为轴做右旋转操作，并把新的根节点返回
	Node* rightRotate(Node* node) {
		//节点旋转
		Node* child = node->left;
		node->left = child->right;
		child->right = node;
		//高度更新，先更新node,再更新child,child比node高1
		node->height = max(height(node->left), height(node->right)) + 1;
		//child->height = node->height + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;//返回旋转后的子树的新节点
	}
	//左旋转操作，以参数node为轴做左旋转操作，并把新的根节点返回
	Node* leftRotate(Node* node) {
		//节点旋转
		Node* child = node->right;
		node->right = child->left;
		child->left = node;
		//高度更新，先更新node,再更新child,child比node高1
		node->height = max(height(node->left), height(node->right)) + 1;
		//child->height = node->height + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;//返回旋转后的子树的新节点
	}
	//左平衡操作 以参数node为轴，做左右旋转操作，并把新的根节点返回
	Node* leftbalance(Node* node) {
		node ->left = leftRotate(node->left);//左旋转操作，并且node的左孩子更新
		return rightRotate(node);
	}
	//右平衡操作 以参数node为轴，做右左旋转操作，并把新的根节点返回
	Node* rightbalance(Node* node) {
		node->right = rightRotate(node->right);
		return leftRotate(node);

	}
	//AVL树的插入操作
	Node* insert(Node* node, const T& val) {
		if (node == nullptr) {
			//递归结束，找到插入的位置
			return new Node(val);
		}
		if (node->data > val) {
			node->left = insert(node->left, val);//在当前节点的左子树里面插入，返回左子树的根节点
		    //添加1：在递归回溯之后判断节点是否失衡
			if (height(node->left) - height(node->right) > 1) {
				//node的左子树太高,node失衡了
				if (height(node->left->left) >= height(node->left->right)) {
					//节点失衡，由于左孩子的左子树太高
					node = rightRotate(node);//返回旋转之后的根节点，右旋转
				}
				else {
					//节点失衡，由于左孩子的右子树太高
					node = leftbalance(node);
				}
			}		
		}
		else if (node->data < val) {
			node->right = insert(node->right, val);//在当前节点的右子树里面插入，返回右子树的根节点
			//添加2：在递归回溯之后判断节点是否失衡
			if (height(node->right) - height(node->left) > 1) {
				//node的右子树太高,node失衡了
				if (height(node->right->right) >= height(node->right->left)) {
					//节点失衡，由于右孩子的右子树太高
					node = leftRotate(node);//返回旋转之后的根节点，左旋转
				}
				else {
					//节点失衡，由于左孩子的右子树太高
					node = rightbalance(node);
				}
			}
		}
		else {
			;//找到相同节点，不用再往下递归了，直接向上回溯
		}
		//添加3 因为子树中增加了新的结点，在递归回溯时检测更新结点的高度
		node->height = max(height(node->left), height(node->right)) + 1;
		return node;
	}

	Node* root;//指向根节点
};

int main() {

	AVLTree<int> avl;
	for (int i = 1; i <= 10; i++) {
		avl.insert(i);
	}

	return 0;
}
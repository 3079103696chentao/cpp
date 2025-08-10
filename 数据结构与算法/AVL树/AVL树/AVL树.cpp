#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

//����AVL���ڵ�����
template<typename T>
class AVLTree
{
public:
	AVLTree() :root(nullptr) {}
	//AVL���Ĳ������
	void insert(const T &val) {
		root = insert(root,val);
	}
   //ɾ������
	void remove(const T val) {
		root = remove(root, val);
	}
private:
	//����AVL���ڵ�����
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
		int height;//��¼�ڵ�ĸ߶�ֵ
	};
	//���ؽڵ�ĸ߶�ֵ
	int height(Node* node) {
		return node == nullptr ? 0 : node->height;//����ýڵ���ĩβ�ڵ㣬����0
	}
	//����ת�������Բ���nodeΪ��������ת�����������µĸ��ڵ㷵��
	Node* rightRotate(Node* node) {
		//�ڵ���ת
		Node* child = node->left;
		node->left = child->right;
		child->right = node;
		//�߶ȸ��£��ȸ���node,�ٸ���child,child��node��1
		node->height = max(height(node->left), height(node->right)) + 1;
		//child->height = node->height + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;//������ת����������½ڵ�
	}
	//����ת�������Բ���nodeΪ��������ת�����������µĸ��ڵ㷵��
	Node* leftRotate(Node* node) {
		//�ڵ���ת
		Node* child = node->right;
		node->right = child->left;
		child->left = node;
		//�߶ȸ��£��ȸ���node,�ٸ���child,child��node��1
		node->height = max(height(node->left), height(node->right)) + 1;
		//child->height = node->height + 1;
		child->height = max(height(child->left), height(child->right)) + 1;
		return child;//������ת����������½ڵ�
	}
	//��ƽ����� �Բ���nodeΪ�ᣬ��������ת�����������µĸ��ڵ㷵��
	Node* leftbalance(Node* node) {
		node ->left = leftRotate(node->left);//����ת����������node�����Ӹ���
		return rightRotate(node);
	}
	//��ƽ����� �Բ���nodeΪ�ᣬ��������ת�����������µĸ��ڵ㷵��
	Node* rightbalance(Node* node) {
		node->right = rightRotate(node->right);
		return leftRotate(node);

	}
	//AVL���Ĳ������
	Node* insert(Node* node, const T& val) {
		if (node == nullptr) {
			//�ݹ�������ҵ������λ��
			return new Node(val);
		}
		if (node->data > val) {
			node->left = insert(node->left, val);//�ڵ�ǰ�ڵ��������������룬�����������ĸ��ڵ�
		    //���1���ڵݹ����֮���жϽڵ��Ƿ�ʧ��
			if (height(node->left) - height(node->right) > 1) {
				//node��������̫��,nodeʧ����
				if (height(node->left->left) >= height(node->left->right)) {
					//�ڵ�ʧ�⣬�������ӵ�������̫��
					node = rightRotate(node);//������ת֮��ĸ��ڵ㣬����ת
				}
				else {
					//�ڵ�ʧ�⣬�������ӵ�������̫��
					node = leftbalance(node);
				}
			}		
		}
		else if (node->data < val) {
			node->right = insert(node->right, val);//�ڵ�ǰ�ڵ��������������룬�����������ĸ��ڵ�
			//���2���ڵݹ����֮���жϽڵ��Ƿ�ʧ��
			if (height(node->right) - height(node->left) > 1) {
				//node��������̫��,nodeʧ����
				if (height(node->right->right) >= height(node->right->left)) {
					//�ڵ�ʧ�⣬�����Һ��ӵ�������̫��
					node = leftRotate(node);//������ת֮��ĸ��ڵ㣬����ת
				}
				else {
					//�ڵ�ʧ�⣬�������ӵ�������̫��
					node = rightbalance(node);
				}
			}
		}
		else {
			;//�ҵ���ͬ�ڵ㣬���������µݹ��ˣ�ֱ�����ϻ���
		}
		//���3 ��Ϊ�������������µĽ�㣬�ڵݹ����ʱ�����½��ĸ߶�
		node->height = max(height(node->left), height(node->right)) + 1;
		return node;
	}
	//ɾ������ʵ��
	Node* remove(Node* node,const T val) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node->data > val) {
			node->left = remove(node->left, val);
			//������ɾ���ڵ�������������̫��
			if (height(node->right) - height(node->left) > 1) {
				if (height(node->right->right) >= height(node->right->left)) {
					//����ת����,�Һ��ӵ�������̫��
					node = leftRotate(node);
				}
				else {
					//�Һ��ӵ�������̫�ߣ���ƽ�����
					node = rightbalance(node);
				}
			}
		}
	
		else if (node->data < val) {
			node->right = remove(node->right, val);
			//������ɾ���ڵ㣬�������������̫��
			if (height(node->left) - height(node->right)>1) {
				//���ӵ�������̫��
				if (height(node->left->left) >= height(node->left->right)) {
					node = rightRotate(node);
				}
				else {
					//���ӵ�������̫�� ��ƽ�����
					node = leftbalance(node);
				}
			}
		}
		else {
			//node->data == val
			//�ȴ������������ӵ����
			if (node->left != nullptr && node->right != nullptr) {
				//Ϊ�˱���ɾ��ǰ�����ߺ�̽ڵ���ɽڵ�ʧ�⣬˭��ɾ��˭
				if (height(node->left) >= height(node->right)) {
					//ɾ��ǰ��
					Node* pre = node->left;
					while (pre->right != nullptr) {
						pre = pre->right;
					}
					node->data = pre->data;//��ǰ���ڵ��ֵ�����ɾ���ڵ��ֵ
					node->left = remove(node->left, pre->data);//Ȼ������node����������pre->data,ɾ��

				}
				else {
					//ɾ���
					Node* post = node->right;
					while (post->left != nullptr) {
						post = post->left;
					}//�ҵ���̽ڵ�
					node->data = post->data;
					node->right = remove(node->right, post->data);//ɾ����̽ڵ�
				}
			}
			else {
				//��ɾ���ڵ������һ������
				Node* child = node->left != nullptr ? node->left : node->right;
				delete node;
				return child;

			}
				
		}
			node->height = max(height(node->left), height(node->right)) + 1;
			return node;
	}

	Node* root;//ָ����ڵ�
};

int main() {

	AVLTree<int> avl;
	for (int i = 1; i <= 10; i++) {
		avl.insert(i);
	}
	avl.remove(9);
	avl.remove(10);
	avl.remove(6);
	avl.remove(1);
	avl.remove(2);
	avl.remove(3);

	return 0;
}
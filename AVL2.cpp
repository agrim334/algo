#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	struct Node *left;
	struct Node *right;
	int height;
	
	Node(int x){
		data = x;
		left = NULL;
		right = NULL;
		height = 1;
	}
};
struct Node* deleteNode(struct Node* root, int data);
int max(int a, int b);
int height(struct Node *N) {
	if (N == NULL)
		return 0;
	return N->height;
}
int max(int a, int b) {
	return (a > b)? a : b;
}

struct Node *rightRotate(struct Node *y) {
	struct Node *x = y->left;
	struct Node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;
	return x;
}
struct Node *leftRotate(struct Node *x) {
	struct Node *y = x->right;
	struct Node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;
	return y;
}
int getBalance(struct Node *N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
 
struct Node* insert(struct Node* node, int data) {
	if (node == NULL)
		return(new Node(data));
	if (data < node->data)
		node->left  = insert(node->left, data);
	else if (data > node->data)
		node->right = insert(node->right, data);
	else 
		return node;
	node->height = 1 + max(height(node->left),height(node->right));
	int balance = getBalance(node);

	if (balance > 1 && data < node->left->data)
		return rightRotate(node);

	if (balance < -1 && data > node->right->data)
		return leftRotate(node);

	if (balance > 1 && data > node->left->data) {
		node->left =  leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && data < node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}
struct Node * minValueNode(struct Node* node) {
	struct Node* current = node;
	while (current->left != NULL)
		current = current->left;
 
	return current;
}
int heigh(struct Node* Node) {
   /* base case tree is empty */
   if(Node == NULL)
	   return 0;
 
   /* If tree is not empty then height = 1 + max of left
	  height and right heights */
   return 1 + max(heigh(Node->left), heigh(Node->right));
} 
bool isBalanced(struct Node *root) {
   int lh; /* for height of left subtree */
   int rh; /* for height of right subtree */ 
 
   /* If tree is empty then return true */
   if(root == NULL)
	return 1; 
 
   /* Get the height of left and right sub trees */
   lh = heigh(root->left);
   rh = heigh(root->right);
 
   if( abs(lh-rh) <= 1 &&
	   isBalanced(root->left) &&
	   isBalanced(root->right))
	 return 1;
 
   /* If we reach here then tree is not height-balanced */
   return 0;
}

int _B_(Node *root) {
	if(root==NULL)
		return 0;
	int lH = _B_(root->left);
	if(lH==-1)return -1;
	int rH = _B_(root->right);
	if(rH==-1)
		return -1;

	if(abs(lH-rH)>1)
		return -1;
	return max(lH,rH)+1;
}

bool _B(Node *root) {
	if(_B_(root)==-1)
		return false;
	else 
		return true;
}

bool I_(Node* root) {
	static struct Node *prev = NULL;
	 
	if (root) {
		if (!I_(root->left))
		  return false;
 
		if (prev != NULL && root->data <= prev->data)
		  return false;
 
		prev = root;
 
		return I_(root->right);
	}
 
	return true;
}

vector<int> z;

void inOrder(struct Node *root) {
	if(root != NULL){

		inOrder(root->left);
		z.push_back(root->data);
		inOrder(root->right);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int> a;
		struct Node *root = NULL;
		for(int i=0;i<n;i++){
			int k;
			cin>>k;
			a.push_back(k);
			root = insert(root, k);
		}

		int k;
		cin>>k;
		root = deleteNode(root, k);

		bool f=true;


		if(!isBalanced(root))
			f=false;


		z.clear();
		inOrder(root);

		set<int> s(a.begin(),a.end());
		vector<int>zz(s.begin(),s.end());

		if(z.size()!=zz.size()-1)
			f=false;

		if(f)
			cout<<1<<endl;
		else 
			cout<<0<<endl;
	}
	return 0;
}
Node* FindSuccessor(Node* node){
	Node* temp = node -> right;
	Node* t2 = node;
	while(temp -> left){
		t2 = temp;
		temp = temp -> left;
	}
	if(temp != node -> right){
		t2 -> left = temp -> right;
		temp -> left = node -> left;
		temp -> right = node -> right;
	}
	else
		temp -> left = node -> left;

	return temp;
}
Node* BalanceAVL(Node* node){
	int l,r,BF;
	l = r = 0;
	if(node -> left)
		l = heigh(node -> left);
	if(node -> right)
		r = heigh(node -> right);
	BF = l - r;

	if(BF >= -1 && BF <= 1)
		return node;

	else if(BF >= 2){
		Node* Anode = node;
		Node* Bnode = Anode -> left;
		Node* Ar = Anode -> right;
		Node* Cnode,*Cl,*Cr;

		if(Bnode){
			Cnode = Bnode -> right;
			if(Cnode){
				Cl = Cnode -> left;
				Cr = Cnode -> right;
			}
		}

		int temp;
		if(heigh(Bnode -> left) >= heigh(Bnode -> right)){
			Anode -> left = Bnode -> left;
			Anode -> right = Bnode;
			Bnode -> left = Bnode -> right;
			Bnode -> right = Ar;

			temp = Anode -> data;
			Anode -> data = Bnode -> data;
			Bnode -> data = temp;
		}
		else{
			Anode -> left = Bnode;
			Anode -> right = Cnode;

			Bnode -> right = Cl;
			Cnode -> left = Cr;
			Cnode -> right = Ar;
		
			temp = Anode -> data;
			Anode -> data = Cnode -> data;
			Cnode -> data = temp;
		}
	return Anode;
	}
	else{
		Node* Anode = node;
		Node* Bnode = Anode -> right;
		Node* Cnode,*Cl,*Cr;
		Node* Al = Anode -> left;
		if(Bnode){
			Cnode = Bnode -> left;
			if(Cnode){
				Cl = Cnode -> left;
				Cr = Cnode -> right;
			}
		}
		int temp;
		if(heigh(Bnode -> left) <= heigh(Bnode -> right) ){
			Anode -> right = Bnode -> right;
			Anode -> left = Bnode;
			Bnode -> right = Bnode -> left;
			Bnode -> left = Al;

			temp = Anode -> data;
			Anode -> data = Bnode -> data;
			Bnode -> data = temp;
		}
		else{
			Anode -> left = Cnode;
			Anode -> right = Bnode;

			Bnode -> left = Cr;
			Cnode -> right = Cl;
			Cnode -> left = Al;

			temp = Anode -> data;
			Anode -> data = Cnode -> data;
			Cnode -> data = temp;
		}
	return Anode;
	}
}

Node* deleteNode(Node* node, int data) {
	int BF = 0;
	if(node -> data > data) 
		node -> left = deleteNode(node -> left,data);
	else if(node -> data < data)
		node -> right = deleteNode(node -> right,data);
	else {
		if(node -> left && node -> right){
			Node* next = FindSuccessor(node);
			next = BalanceAVL(next);
			return next;
		}
		else if(node -> left && node -> right == 0)
			return BalanceAVL(node -> left);
		else if(node -> left == 0 && node -> right)
			return BalanceAVL(node -> right);
		else
			return 0;
	}
	node = BalanceAVL(node);
	return node;
}
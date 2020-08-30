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

int heigh(struct Node* Node) {
	if(Node == NULL)
	   return 0;

	return 1 + max(heigh(Node->left), heigh(Node->right));
} 

bool isBalanced(struct Node *root)
{
   int lh;
   int rh; 
 
   if(root == NULL)
	return 1; 
 
   lh = heigh(root->left);
   rh = heigh(root->right);
 
   if( abs(lh-rh) <= 1 &&
	   isBalanced(root->left) &&
	   isBalanced(root->right))
	 return 1;
 
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
Node* insertToAVL(Node* Node, int data);

vector<int> z;
void inorder(Node *root) {
	if(root==NULL)
		return;

	inorder(root->left);
	z.push_back(root->data);
	inorder(root->right);
}

int main() {
	int t;
	cin>>t;
	while(t--)
	{
		int q;
		cin>>q;
		Node *root = NULL;
		bool f= true;
		vector<int> a;
		while(q--)
		{
			int k;
			cin>>k;
			a.push_back(k);
			root = insertToAVL(root,k);

			if(!isBalanced(root)){
				f=false;
				break;
			}
		}
	
		z.clear();
	
		inorder(root);
	
		set<int> s(a.begin(),a.end());
		vector<int>zz(s.begin(),s.end());

		if(z.size()!=zz.size())
			f=false;
		else{
		
			for(int i=0;i<z.size();i++) {
				if(z[i]!=zz[i])
					f=false;
			}
		}

	if(f)
		cout<<1<<endl;
	else 
		cout<<0<<endl;
	}

	return 0;
}

int max(int a,int b){
	return a > b ? a : b;
}
Node* insertToAVL(Node* node, int data) {
	if(!node){
		node = new Node(data);
		node -> height = 0;
		node -> left = 0;
		node -> right = 0;
		return node;
	}
	else {
		int BF = 0;
		if(node -> data > data) 
			node -> left = insertToAVL(node -> left,data);
		else if(node -> data < data)
			node -> right = insertToAVL(node -> right,data);
        else
            return node;
		int l,r;
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
			if(heigh(Bnode -> left) > heigh(Bnode -> right)){
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
			if(heigh(Bnode -> left) < heigh(Bnode -> right)){
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
}
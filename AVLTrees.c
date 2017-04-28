#include <stdio.h>
#include <stdlib.h>

struct node{
	int key;
	struct node *left;
	struct node *right;
	int height;
};

int max(int a,int b){
	return a > b ? a : b;
}

struct node* newNode(int key){
	struct node *node = (struct node*)malloc(sizeof(struct node));
	node->key = key;
	node->left = node->right = NULL;
	node->height = 1;
	return node;
}

void create_AVL(struct node **root,int key){
	*root = (struct node*)malloc(sizeof(struct node));
	(*root)->key = key;
	(*root)->left = (*root)->right = NULL;
	(*root)->height = 1;
}

int height(struct node *node){
	if(node == NULL) return 0;
	return node->height;
}

struct node* rightRotate(struct node *y){
	struct node *x = y->left , *T = x->right;
	x->right = y;
	y->left = T;
	
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	
	return x;
}

struct node* leftRotate(struct node *x){
	struct node *y = x->right , *T = y->left;
	y->left = x;
	x->right = T;
	
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	
	return y;
}

int getBalance(struct node *node){
	if(node == NULL) return 0;
	return height(node->left) - height(node->right);
}

struct node* insert(struct node *node,int key){
	int balance;
	if(node == NULL) return newNode(key); //if(node == NULL) create_AVL(&node,key);
	else if(key < node->key) node->left = insert(node->left,key);
	else node->right = insert(node->right,key);
	
	node->height = max(height(node->left),height(node->right))+1;
	
	balance = getBalance(node);
	
	if((balance > 1) && (key < node->left->key))
		return rightRotate(node);
	if((balance < -1) && (key > node->right->key))
		return leftRotate(node);
	if((balance > 1) && (key > node->left->key)){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if((balance < -1) && (key < node->right->key)){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void preOrder_yardimci(struct node *node){
	if(node != NULL){
		printf("%d(%2d ) ",node->key,node->height);
		preOrder_yardimci(node->left);
		preOrder_yardimci(node->right);
	}
}

void preOrder(struct node *node){
	preOrder_yardimci(node);
	printf("\n");
}

struct node* minValueNode(struct node *root){
	struct node *current = root;
	if(current == NULL) return NULL;
	while(current->left) current = current->left;
	return current; 
}

struct node* minValueNode_Recursive(struct node *root){
	struct node* current = root;
	if(!current->left) return current;
	else return minValueNode_Recursive(current->left);
}

struct node* maxValueNode(struct node *root){
	struct node *current = root;
	if(!current) return NULL;
	while(current->right) current = current->right;
	return current;
}

struct node* maxValueNode_Recursive(struct node *root){
	struct node *current = root;
	if(!current->right) return current;
	else return maxValueNode_Recursive(current->right);
}

struct node *deleteNode(struct node *root, int key){
    if(root==NULL) return root;
    if(key <root->key) root->left=deleteNode(root->left,key);
    else if(key>root->key) root->right=deleteNode(root->right,key);
    else {
        if(root->left == NULL || root->right == NULL){
            struct node *temp=root->left ?root->left:root->right;
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else *root=*temp; // root->key=temp->key; root->rigt = temp->rigt; root->left= 
            free(temp);
        }
        else {
            struct node *temp=minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }
    }
    
    if(root==NULL) return root;
    
    root->height=max(height(root->left),height(root->right))+1;
    int balance=getBalance(root);
    
    if(balance>1 && getBalance(root->left) >=0){
    	printf("rightRotate.");
    	return rightRotate(root);
	}
    if(balance>1 && getBalance(root->left) < 0){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance <-1 && getBalance(root->right) <=0)
        return leftRotate(root);
    if(balance < -1 && getBalance(root->right)>0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;    
}

int main(){
	struct node *root = NULL;
	root = insert(root,38);
	root = insert(root,43);
	root = insert(root,27);
	root = insert(root,24);
	root = deleteNode(root,43);
	/*root = insert(root,87);
	root = insert(root,76);
	root = insert(root,32);
	root = insert(root,25);
	root = insert(root,51);
	root = insert(root,83);
	root = insert(root,94);
	root = insert(root,82);*/
	//root = insert(root,97);
	//root = deleteNode(root,55);
	//root = deleteNode(root,44);
	//printf("least is = %d\n",minValueNode_Recursive(root)->key);
	preOrder(root);
}

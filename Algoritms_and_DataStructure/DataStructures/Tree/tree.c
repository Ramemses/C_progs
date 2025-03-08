#include <stdio.h>
#include <stdlib.h>

//------------STRUCTURES FOR TREE-----------------------
typedef struct node_t{
	int data;
	struct node_t* left;
	struct node_t* right;	
} Node;

typedef struct tree_t{
	Node* root;
} Tree;

//-------------------------------------------------------



//------------------NODE AND TREE CONSTRUCTORS--------------------
Node* create_node(int data)
{
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return NULL;
	}

	node->data = data;
	node->left = node->right = NULL;

	return node;
}

Tree* create_tree()
{
	Tree* tree = calloc(1, sizeof(Tree));
	if (tree == NULL){
		 fprintf(stderr, "Error memory allocation!\n");
		 return NULL;
	}

	tree->root = NULL;
	return tree;
}
//---------------------------------------------------------------


//------TREE METHODS----------------
void _insert_(Node** node, int data)
{
	if (*node == NULL){
		*node = calloc(1, sizeof(Node));
		if (*node == NULL) return;

		(*node)->data = data;
		(*node)->left = (*node)->right = NULL;
		return;
	}

	if (data == (*node)->data) return;
	if (data < (*node)->data) _insert_( &(*node)->left, data);
	if (data > (*node)->data) _insert_( &(*node)->right, data);
}
void insert(Tree* tree, int data)
{
	if (tree == NULL){
		fprintf(stderr, "Tree is not created!!\n");
		return;
	}

	_insert_(&(tree->root), data);
}

Node* _find_min_(Node* node)
{
	Node *ptr = node;
	while(ptr->left != NULL)
		ptr = ptr->left;
	return ptr;
}

void _delete_(Node** node, int data)
{
	if ((*node) == NULL) return;
	if ((*node)->data > data) _delete_(&(*node)->left, data);
	if ((*node)->data < data) _delete_(&(*node)->right, data);
	
	if ((*node)->data == data){
		if ((*node)->left == NULL){
			Node* tmp = *node;
			*node = (*node)->right;		
			free(tmp);
		}
		else if ((*node)->right == NULL){
			Node* tmp = *node;
			*node = (*node)->left;
			free(tmp);
		}
		else{
			Node* tmp  = _find_min_((*node)->right);
			(*node)->data = tmp->data;
			free(tmp);
		}
	}
}

void delete(Tree* tree, int data)
{
	if (tree == NULL || tree->root == NULL){
		printf("Nothing to delete. Tree is empty!\n");
		return;
	}
	
	_delete_(&(tree->root), data);
}



//------TREE METHODS----------------



//----------------------TREE ORDERS--------------------------------

void _inorder_(Node* root)
{
	if (root == NULL) return;
	_inorder_(root->left);
	printf("%d ", root->data);
	_inorder_(root->right);
}
void inorder(Tree* tree)
{
	_inorder_(tree->root);
	printf("\n");
}


void _postorder_(Node* root)
{
	if (root == NULL) return;
	_postorder_(root->left);
	_postorder_(root->right);
	printf("%d ", root->data);
}
void postorder(Tree* tree)
{
	_postorder_(tree->root);
	printf("\n");
}

void _preorder_(Node* root)
{
	if (root == NULL) return;
	printf("%d ", root->data);
	_preorder_(root->left);
	_preorder_(root->right);
}
void preorder(Tree* tree)
{
	_preorder_(tree->root);
	printf("\n");
}

//------------------------------------------------------------------


int main(void)
{
	Tree* tr = create_tree();
	insert(tr, 4);
	insert(tr, -100);
	insert(tr, 1);
	insert(tr, 24);
	insert(tr, 2);
	insert(tr, 0);
	insert(tr, 5);
	insert(tr, 6);
	insert(tr, 10);

	

	inorder(tr);
	delete(tr, 24);
	delete(tr, 24);
	inorder(tr);	
	delete(tr, 0);
	inorder(tr);


	return 0;
}

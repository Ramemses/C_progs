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


typedef struct stack_t{
	Node* top;
	struct stack_t* next;
} Stack;

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

void _clear_(Node** node)
{
	if (*node == NULL) return;
	_clear_(&((*node)->left));
	_clear_(&((*node)->right));
	if ((*node)->left == NULL && (*node)->right == NULL){
		free(*node);
		*node = NULL;
		return;
	}

}

void clear(Tree* tree)
{
	_clear_(&(tree->root));
}

//----------------------------------------------------------


//--------STACK METHODS FOR TREE ORDER----------
Stack* create_stack(Node* node)
{
	Stack* st = calloc(1, sizeof(Stack));	
	if (st == NULL) return NULL;
	
	st->top = node;
	st->next = NULL;
}

Node* pop(Stack** stack)
{
	if ((*stack)->top == NULL){
		fprintf(stderr, "Error pop: the stack is empty!\n");
		return NULL;
	}

	Stack* tmp = (*stack);
	Node* node = tmp->top;
	*stack = (*stack)->next;
	free(tmp);

	
	return node;
}

void push(Stack** stack, Node* node)
{
	if ((*stack)->top == NULL){
		(*stack)->top = node;
		return;
	}
	Stack* st = create_stack(node);
	st->next = (*stack);
	(*stack) = st;
}

//--------------------------------------------



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


void level_order(Tree* tree)
{
	Stack* st = create_stack(tree->root);

	while(st != NULL && st->top != NULL){	
		Stack* st_ = create_stack(NULL);
		while(st != NULL && st->top != NULL){
			Node* node = pop(&st);
			printf("%d ", node->data);	
	
			if (node->left != NULL) push(&st_, node->left);
			if (node->right != NULL) push(&st_, node->right);
		
		}
	    st = st_;
	}	
	printf("\n");

}
//------------------------------------------------------------------





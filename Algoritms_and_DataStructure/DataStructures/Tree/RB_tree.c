#include <stdio.h>
#include <stdlib.h>


typedef enum color_t {BLACK = 0, RED = 1} Color;

//------------STRUCTURES FOR TREE-----------------------


typedef struct node_t{
	int data;
	struct node_t* left;
	struct node_t* parent;
	struct node_t* right;
	Color color;	
} Node;

typedef struct tree_t{
	Node* root;
	Node* TNULL;
} Tree;


//-------------------------------------------------------


//------------------NODE AND TREE CONSTRUCTORS--------------------


Node* create_node(int data)
{
	Node* node =(Node*)calloc(1, sizeof(Node));
	if (node == NULL) return NULL;

	node->data = data;
	node->left = node->right = node->parent = NULL;
	node->color = BLACK;

	return node;
}

Tree* create_tree()
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	if (tree == NULL)  return NULL;

	tree->TNULL = create_node(0);
	tree->TNULL->color = BLACK;
	tree->root = tree->TNULL;

	return tree;
}


//---------------------------------------------------------------

//TREE METHODS FOR BALANCE




void _left_rotate_(Tree* tree, Node* x)
{
	Node* y = x->right;
	x->right = y->left;

	if (y->left != tree->TNULL){
		y->left->parent = x;	
	}

	y->parent = x->parent;
	if (x->parent == tree->TNULL) tree->root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;

	y->left = x;
	x->parent = y;
}

void _right_rotate_(Tree* tree, Node* x)
{
	Node* y = x->left;
	x->left = y->right;

	if (y->right != tree->TNULL){
		y->right->parent = x;	
	}

	y->parent = x->parent;
	if (x->parent == tree->TNULL) tree->root = y;
	else if (x == x->parent->right) x->parent->right = y;
	else x->parent->left = y;

	y->right = x;
	x->parent = y;
}



//------TREE METHODS----------------


Node* _find_min_(Tree* tree, Node* node)
{
	Node *ptr = node;
	while(ptr->left != tree->TNULL)
		ptr = ptr->left;
	return ptr;
}

int find_min(Tree* tree)
{
	Node* node = _find_min_(tree, tree->root);
	return node->data;
}


void insert_fixup(Tree* tree, Node* node)
{
	

	Node* y;
	while (node->parent->color == RED){
		if (node->parent == node->parent->parent->left){
			y = node->parent->parent->right;
			if (y->color == RED){
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				 if (node == node->parent->right){
					node = 	node->parent;
					_left_rotate_(tree, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				_right_rotate_(tree, node->parent->parent);
			}
		}else{
			y = node->parent->parent->left;
			if (y->color == RED){
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				 if (node == node->parent->left){
					node = 	node->parent;
					_right_rotate_(tree, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				_left_rotate_(tree, node->parent->parent);
			}
		}
	}

	tree->root->color = BLACK;

}

void insert(Tree* tree, int data)
{
	
	Node* node = create_node(data);
	if (node == NULL) return ;
	
	Node* y = tree->TNULL;
	Node* x = tree->root;

	while (x != tree->TNULL){
		y = x;
		if (node->data == x->data){
			free(node); 	
			return;
		}
		if (node->data < x->data) x = x->left;
		else x = x->right;
	}
	node->parent = y;
	if (y == tree->TNULL) tree->root = node;
	else if (node->data < y->data) y->left = node;
	else y->right = node;

	node->right = node->left = tree->TNULL;
	node->color = RED;

	insert_fixup(tree, node);
}

void delete_fixup(Tree* tree, Node* x)
{
	Node* w;
	while (x != tree->root && x->color == BLACK){
		if (x == x->parent->left){
			w = x->parent->right;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				_left_rotate_(tree, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color ==BLACK){
					w->left->color = BLACK;
					w->color = RED;
					_right_rotate_(tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;	
				x->parent->color = BLACK;
				w->right->color = BLACK;
				_left_rotate_(tree, x->parent);
				x = tree->root;
			}

		} else {
			w = x->parent->left;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				_right_rotate_(tree, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color ==BLACK){
					w->right->color = BLACK;
					w->color = RED;
					_left_rotate_(tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;	
				x->parent->color = BLACK;
				w->left->color = BLACK;
				_right_rotate_(tree, x->parent);
				x = tree->root;
			}
		}
	}
	
	x->color = BLACK;
}

void delete(Tree* tree, int data)
{

	Node* z = tree->root;
	Node* x, *y;
	Color orig_color;

	while(z != tree->TNULL){
		if (z->data == data) break;
		else if(z->data < data) z = z->right;
		else z = z->left;
	}
	if (z == tree->TNULL) return;

	if (z->left == tree->TNULL || z->right == tree->TNULL) y = z;
	else y = _find_min_(tree, z->right);

	if (y->left != tree->TNULL) x = y->left;
	else if (y->right != tree->TNULL) x = y->right;
	else x = tree->TNULL;

	if (x != tree->TNULL) x->parent = y->parent;
	
	if (y->parent == tree->TNULL) tree->root = x;
	else if (y->parent->left == y) y->parent->left = x;
	else y->parent->right = x;
	
	if (y != z) z->data = y->data;
	if (y->color == BLACK && x != tree->TNULL) delete_fixup(tree, x);
	
	free(y);
}


void __inorder__(Node* node, Node* tnull)
{
	if (node == tnull) return;
	__inorder__(node->left, tnull);
	printf("%d ", node->data);
	if (node->color == BLACK) printf("BLACK\n");
	else printf("RED\n");
	__inorder__(node->right, tnull);

}

void inorder(Tree* tree)
{
	__inorder__(tree->root, tree->TNULL);
	printf("\n");

}

void __preorder__(Node* node, Node* tnull)
{
	if (node == tnull) return;
	printf("%d ", node->data);
	if (node->color == BLACK) printf("BLACK\n");
	else printf("RED\n");
	__preorder__(node->left, tnull);
	__preorder__(node->right, tnull);

}

void preorder(Tree* tree)
{
	__preorder__(tree->root, tree->TNULL);
	printf("\n");

}

//----------------------------------------------------------



int main(void)
{
	Tree* t = create_tree();
	insert(t, 4);
	insert(t, 8);
	insert(t, 3);
	insert(t, 5);
	insert(t, 1);
	insert(t, 2);
	insert(t, 10);
	insert(t, 12);
	insert(t, 14);
	insert(t, 23);
	insert(t, -31);
	insert(t, 0);


	inorder(t);
	preorder(t);

	delete(t,4);

	preorder(t);
	inorder(t);
	return 0;

}

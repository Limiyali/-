#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_NAME 21
#define SIZE 20
typedef unsigned long long ULL;
enum rb_color
{
	RB_BLACK,
	RB_RED,
};

typedef struct rbtree_node
{
	struct rbtree_node* parent;
	struct rbtree_node* left;
	struct rbtree_node* right;
	enum rb_color color;
	void*  key;
	void *data;
}rbtree_node;

typedef int(*rbtree_cmp_fn_t)(void *key_a, void *key_b);
typedef void(*ptdata)(void *data, FILE *stream);
typedef void(*rtdata)(void*data, FILE *stream);
typedef struct rbtree
{
	struct rbtree_node* root;
	rbtree_cmp_fn_t compare;
}rbtree;
void padding(char ch, int n)
{
	int i;

	for (i = 0; i < n; i++)
		putchar(ch);
}
void delete_case1(struct rbtree* tree, struct rbtree_node* node);
void delete_case2(struct rbtree* tree, struct rbtree_node* node);
void delete_case3(struct rbtree* tree, struct rbtree_node* node);
void delete_case4(struct rbtree* tree, struct rbtree_node* node);
void delete_case5(struct rbtree* tree, struct rbtree_node* node);
void delete_case6(struct rbtree* tree, struct rbtree_node* node);

static inline enum rb_color get_color(struct rbtree_node* node)
{
	if (node == NULL)
		return RB_BLACK;
	else
		return node->color;
}

static inline void set_color(enum rb_color color, struct rbtree_node* node)
{
	assert(node != NULL);
	node->color = color;
}

static inline struct rbtree_node*  get_parent(struct rbtree_node* node)
{
	assert(node != NULL);
	return node->parent;
}

static inline void set_parent(struct rbtree_node* parent, struct rbtree_node* node)
{
	assert(node != NULL);
	node->parent = parent;
}

static int is_root(struct rbtree_node* node)
{
	assert(node != NULL);
	return (get_parent(node) == NULL);
}

struct rbtree_node* sibling(rbtree_node* node)
{
	assert(node != NULL);
	assert(node->parent != NULL); /* Root node has no sibling */
	if (node == node->parent->left)
		return node->parent->right;
	else
		return node->parent->left;
}
static inline rbtree_node* get_min(struct rbtree_node* node)
{
	assert(node != NULL);
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

struct rbtree_node* rbtree_min(struct rbtree *tree)
{
	if (tree->root == NULL)
		return NULL;
	else
	{
		return get_min(tree->root);
	}
}

struct rbtree_node* rbtree_createnode(void *key, void* data)
{
	struct rbtree_node* newnode = (struct rbtree_node*)malloc(sizeof(struct rbtree_node));
	if (newnode == NULL)
		return NULL;

	newnode->key = key;
	newnode->data = data;
	newnode->parent = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

struct rbtree_node* do_lookup(void* key, struct rbtree* tree, struct rbtree_node** pparent)
{
	struct rbtree_node *current = tree->root;

	while (current)
	{
		int ret = tree->compare(current->key, key);
		if (ret == 0)
			return  current;
		else
		{
			if (pparent != NULL)
			{
				*pparent = current;
			}
			if (ret < 0)
				current = current->right;
			else
				current = current->left;
		}
	}
	return NULL;

}

void*  rbtree_lookup(struct rbtree* tree, void* key)
{
	assert(tree != NULL);
	struct rbtree_node* node;
	node = do_lookup(key, tree, NULL);
	return node == NULL ? NULL : node->data;
}

static void set_child(struct rbtree* tree, struct rbtree_node* node, struct rbtree_node* child)
{
	int ret = tree->compare(node->key, child->key);
	assert(ret != 0);

	if (ret > 0)
	{
		node->left = child;
	}
	else {
		node->right = child;
	}
}

static void rotate_left(struct rbtree_node* node, struct rbtree* tree)
{
	struct rbtree_node* p = node;
	struct rbtree_node* q = node->right;
	struct rbtree_node* parent = node->parent;
	if (parent == NULL)
	{
		tree->root = q;
	}
	else
	{
		if (parent->left == p)
			parent->left = q;
		else
			parent->right = q;
	}
	set_parent(parent, q);
	set_parent(q, p);

	p->right = q->left;
	if (q->left)
		set_parent(p, q->left);
	q->left = p;

}

static void rotate_right(struct rbtree_node *node, struct rbtree *tree)
{
	struct rbtree_node *p = node;
	struct rbtree_node *q = node->left; /* can't be NULL */
	struct rbtree_node *parent = get_parent(p);

	if (!is_root(p)) {
		if (parent->left == p)
			parent->left = q;
		else
			parent->right = q;
	}
	else
		tree->root = q;
	set_parent(parent, q);
	set_parent(q, p);

	p->left = q->right;
	if (p->left)
		set_parent(p, p->left);
	q->right = p;
}

struct rbtree* rbtree_init(rbtree_cmp_fn_t compare)
{
	struct rbtree* tree = (struct rbtree*)malloc(sizeof(struct rbtree));
	if (tree == NULL)
		return NULL;
	else
	{
		tree->root = NULL;
		tree->compare = compare;
	}

	return tree;
}
struct rbtree_node* __rbtree_insert(struct rbtree_node* node, struct rbtree *tree)
{
	struct rbtree_node* samenode = NULL;
	struct rbtree_node*parent = NULL;

	samenode = do_lookup(node->key, tree, &parent);
	if (samenode != NULL)
		return samenode;

	node->left = node->right = NULL;
	set_color(RB_RED, node);
	set_parent(parent, node);

	if (parent == NULL)
		tree->root = node;
	else
	{
		set_child(tree, parent, node);
	}

	while ((parent = get_parent(node)) != NULL && parent->color == RB_RED)
	{
		struct rbtree_node* grandpa = get_parent(parent);
														 
														 
		if (parent == grandpa->left)
		{
			struct rbtree_node* uncle = grandpa->right;
			if (uncle && get_color(uncle) == RB_RED)
			{
				set_color(RB_RED, grandpa);
				set_color(RB_BLACK, parent);
				set_color(RB_BLACK, uncle);
				node = grandpa;
			}
			else
			{
				if (node == parent->right)
				{
					rotate_left(parent, tree);
					node = parent;
					parent = get_parent(parent);
				}
				set_color(RB_BLACK, parent);
				set_color(RB_RED, grandpa);
				rotate_right(grandpa, tree);
			}

		}
		else
		{
			struct rbtree_node* uncle = grandpa->left;
			if (uncle && uncle->color == RB_RED)
			{
				set_color(RB_RED, grandpa);
				set_color(RB_BLACK, parent);
				set_color(RB_BLACK, uncle);
				node = grandpa;
			}
			else
			{
				if (node == parent->left)
				{
					rotate_right(parent, tree);
					node = parent;
					parent = get_parent(node);
				}
				set_color(RB_BLACK, parent);
				set_color(RB_RED, grandpa);
				rotate_left(grandpa, tree);
			}
		}
	}

	set_color(RB_BLACK, tree->root);
	return NULL;
}

int  rbtree_insert(struct rbtree *tree, void*  key, void* data)
{
	struct rbtree_node * node = rbtree_createnode(key, data);
	struct rbtree_node* samenode = NULL;
	if (node == NULL)
		return -1;
	else
		samenode = __rbtree_insert(node, tree);
	if (samenode != NULL)
		return -2;
	return 0;
}

void replace_node(struct rbtree* t, rbtree_node *oldn, rbtree_node* newn)
{
	if (oldn->parent == NULL)
	{
		t->root = newn;
	}
	else
	{
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL)
	{
		newn->parent = oldn->parent;
	}
}

void delete_case1(struct rbtree* tree, struct rbtree_node* node)
{
	if (node->parent == NULL)
		return;
	else
		delete_case2(tree, node);
}

void delete_case2(struct rbtree* tree, struct rbtree_node* node)
{
	if (get_color(sibling(node)) == RB_RED)
	{
		node->parent->color = RB_RED;
		sibling(node)->color = RB_BLACK;
		if (node == node->parent->left)
		{
			rotate_left(node->parent, tree);
		}
		else
		{
			rotate_right(node->parent, tree);
		}
	}
	delete_case3(tree, node);
}

void delete_case3(struct rbtree* tree, struct rbtree_node* node)
{
	if (node->parent->color == RB_BLACK &&
		get_color(sibling(node)) == RB_BLACK &&
		get_color(sibling(node)->right) == RB_BLACK &&
		get_color(sibling(node)->left) == RB_BLACK)
	{
		sibling(node)->color = RB_RED;
		delete_case1(tree, node->parent);
	}
	else
	{
		delete_case4(tree, node);
	}

}

void delete_case4(struct rbtree* t, struct rbtree_node* n)
{
	if (get_color(n->parent) == RB_RED &&
		get_color(sibling(n)) == RB_BLACK &&
		get_color(sibling(n)->left) == RB_BLACK &&
		get_color(sibling(n)->right) == RB_BLACK)
	{
		sibling(n)->color = RB_RED; 
		n->parent->color = RB_BLACK;
	}
	else
		delete_case5(t, n);
}

void delete_case5(struct rbtree *t, rbtree_node *n)
{
	if (n == n->parent->left &&
		get_color(sibling(n)) == RB_BLACK &&
		get_color(sibling(n)->left) == RB_RED &&
		get_color(sibling(n)->right) == RB_BLACK)
	{
		sibling(n)->color = RB_RED;
		sibling(n)->left->color = RB_BLACK;
		rotate_right(sibling(n), t);
	}
	else if (n == n->parent->right &&
		get_color(sibling(n)) == RB_BLACK &&
		get_color(sibling(n)->right) == RB_RED &&
		get_color(sibling(n)->left) == RB_BLACK)
	{
		sibling(n)->color = RB_RED;
		sibling(n)->right->color = RB_BLACK;
		rotate_left(sibling(n), t);
	}
	delete_case6(t, n);
}

void delete_case6(struct rbtree*  t, rbtree_node* n)
{
	sibling(n)->color = get_color(n->parent);
	n->parent->color = RB_BLACK;
	if (n == n->parent->left)
	{
		assert(get_color(sibling(n)->right) == RB_RED);
		sibling(n)->right->color = RB_BLACK;
		rotate_left(n->parent, t);
	}
	else
	{
		assert(get_color(sibling(n)->left) == RB_RED);
		sibling(n)->left->color = RB_BLACK;
		rotate_right(n->parent, t);
	}
}
void __rbtree_remove(struct rbtree_node* node, struct rbtree* tree)
{
	struct rbtree_node *left = node->left;
	struct rbtree_node* right = node->right;
	struct rbtree_node* child = NULL;
	if (left != NULL && right != NULL)
	{
		struct rbtree_node* next = get_min(right);
		node->key = next->key;
		node->data = next->data;
		node = next;
	}

	assert(node->left == NULL || node->right == NULL);
	child = (node->right == NULL ? node->left : node->right);
	if (get_color(node) == RB_BLACK)
	{
		set_color(get_color(child), node);
		delete_case1(tree, node);
	}
	replace_node(tree, node, child);
	if (node->parent == NULL && child != NULL)
		set_color(RB_BLACK, child);
	free(node);
}

int  rbtree_remove(struct rbtree* tree, void *key)
{
	struct rbtree_node* node = do_lookup(key, tree, NULL);
	if (node == NULL)
		return -1;
	else
		__rbtree_remove(node, tree);
	return 0;
}


void print_node(struct rbtree_node *root, int level)
{

	if (root == NULL)
	{
		padding('\t', level);
		puts("NIL");

	}
	else
	{
		print_node(root->right, level + 1);
		padding('\t', level);
		if (root->color == RB_BLACK)
		{
			printf("(%s)\n", (char*)(root->key));
		}
		else
			printf("%s\n", (char*)(root->key));
		print_node(root->left, level + 1);
	}
}

void print_tree(struct rbtree* tree)
{
	print_node(tree->root, 0);
	printf("-------------------------------------------\n");
}


void  process_null_node(struct rbtree_node* node, FILE* stream)
{
	fprintf(stream, "0\n");
}
void __tree2dot(struct rbtree_node* node, FILE* stream, ptdata pt)
{
	fprintf(stream, "1\n");
	if (node->color == RB_BLACK)
		fprintf(stream, "1\n");    //0 r  1 b
	else
		fprintf(stream, "0\n");
	pt(node, stream);
	if (node->left)
		__tree2dot(node->left, stream, pt);
	else
	{
		process_null_node(node, stream);
	}
	if (node->right)
		__tree2dot(node->right, stream, pt);
	else
		process_null_node(node, stream);
}
int tree2dot(struct rbtree* tree, char* filename, ptdata pt)
{
	assert(tree != NULL && filename != NULL);
	FILE* stream = fopen(filename, "w+");
	if (stream == NULL)
	{
		fprintf(stderr, "open failed \n");
		return -1;
	}
	if (!tree->root) { fclose(stream); return 0; }
	__tree2dot(tree->root, stream, pt);
	fclose(stream);
	return 0;

}

void __treefdot(struct rbtree_node* pre, int LorR, FILE* stream, rtdata rt)
{
	int con, color;
	fscanf(stream, "%d", &con);
	if (!con) return;
	fscanf(stream, "%d", &color);
	struct rbtree_node* newnode = (struct rbtree_node*)malloc(sizeof(struct rbtree_node));
	newnode->left = NULL;
	newnode->right = NULL;
	if (color)
		set_color(RB_BLACK, newnode);
	else
		set_color(RB_RED, newnode);
	set_parent(pre, newnode);
	if (LorR == -1)
		pre->left = newnode;
	else if (LorR == 1)
		pre->right = newnode;
	rt(newnode, stream);
	__treefdot(newnode, -1, stream, rt);
	__treefdot(newnode, 1, stream, rt);
}
int __rtreefdot(struct rbtree_node* root, FILE* stream, rtdata rt)
{
	int con, color;
	if (fscanf(stream, "%d", &con)==EOF) return 0;
	if (!con) return 1;
	fscanf(stream, "%d", &color);
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	if (color)
		set_color(RB_BLACK, root);
	else
		set_color(RB_RED, root);
	rt(root, stream);
	__treefdot(root, -1, stream, rt);
	__treefdot(root, 1, stream, rt);
}
int treefdot(struct rbtree* tree, char* filename, rtdata rt)
{
	assert(tree != NULL && filename != NULL);
	FILE* stream = fopen(filename, "r");
	if (stream == NULL)
	{
		fprintf(stderr, "open failed \n");
		return -1;
	}
	tree->root = (rbtree_node*)malloc(sizeof(rbtree_node));
	if (!__rtreefdot(tree->root, stream, rt)) {
		free(tree->root); 
		tree->root = NULL;
	}
	fclose(stream);
	return 0;

}


#ifndef RBTREE_H
#define RBTREE_H

#define RB_RED   0
#define RB_BALCK 1

struct rb_node
{
	struct rb_node *parent;
	struct rb_node *left;
	struct rb_node *right;
	int color;
	int key;
};

struct rb_tree
{
	struct rb_node *root;
};

void rb_insert(struct rb_tree *tree, int key);
void rb_insert_fixup(struct rb_tree *tree, struct rb_node *node);

void rb_remove(struct rb_tree *tree, int key);
void rb_remove_fixup(struct rb_tree *tree, struct rb_node *node, struct rb_node *parent);

void rb_free_tree(struct rb_tree *tree);
void rb_free_node(struct rb_node *node);

struct rb_node *rb_search(struct rb_tree *tree, int key);

struct rb_node *rb_create_node();
struct rb_node *rb_uncle(struct rb_node *node, struct rb_node *parent);
struct rb_node *rb_sibling(struct rb_node *node, struct rb_node *parent);
struct rb_node *rb_grandparent(struct rb_node *node, struct rb_node *parent);

void rb_rotate_left(struct rb_tree *tree, struct rb_node *node);
void rb_rotate_right(struct rb_tree *tree, struct rb_node *node);

void rb_replace_node(struct rb_tree *tree, struct rb_node *src, struct rb_node *dst);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

void rb_insert(struct rb_tree *tree, int key)
{
	struct rb_node *node = rb_create_node();
	node->color = RB_RED;
	node->key = key;

	if (tree->root == NULL) {
		tree->root = node;
	} else {
		struct rb_node *parent = tree->root;
		for (;;) {
			if (key < parent->key) {
				if (parent->left == NULL) {
					parent->left = node;
					node->parent = parent;
					break;
				}
				parent = parent->left;
			} else if (key > parent->key) {
				if (parent->right == NULL) {
					parent->right = node;
					node->parent = parent;
					break;
				}
				parent = parent->right;
			} else {
				printf("key %d has exist.\n", key);
				return;
			}
		}
	}

	rb_insert_fixup(tree, node);
}

void rb_insert_fixup(struct rb_tree *tree, struct rb_node *node)
{
	if (tree->root == node) {
		/*
		 * case 1
		 * case 1
		 */
		node->color = RB_BALCK;
	} else if (node->parent->color == RB_BALCK) {
		/*
		 * case 2
		 * do not need to fixup
		 */
	} else {
		struct rb_node *grandparent = rb_grandparent(node, node->parent);
		struct rb_node *uncle = rb_uncle(node, node->parent);

		if (uncle != NULL && uncle->color == RB_RED) {
			/*
			 * case 3
			 * case 3
			 */
			node->parent->color = RB_BALCK;
			uncle->color = RB_BALCK;
			grandparent->color = RB_RED;			
			rb_insert_fixup(tree, grandparent);
		} else {
			/*
			 * case 4
			 * case 4
			 */
			if (node == node->parent->right && node->parent == grandparent->left) {
				rb_rotate_left(tree, node->parent);
				node = node->left;			
			} else if (node == node->parent->left && node->parent == grandparent->right) {
				rb_rotate_right(tree, node->parent);
				node = node->right;	
			}

			/*
			 * case 5
			 * case 5
			 */
			grandparent->color = RB_RED;
			node->parent->color = RB_BALCK;
			if (node == node->parent->left && node->parent == grandparent->left) {
				rb_rotate_right(tree, grandparent);
			} else {
				rb_rotate_left(tree, grandparent);
			}
		}
	}
}


void rb_remove(struct rb_tree *tree, int key)
{
	struct rb_node *node = rb_search(tree, key);
	if (node == NULL) {
		printf("key %d has not exist.\n", key);
		return;
	}

	if (node->left != NULL && node->right != NULL) {
		struct rb_node *max = NULL;
		for (max = node->left; max->right != NULL; max = max->right)
			;
		node->key = max->key;
		node = max;
	}

	struct rb_node *child = node->left == NULL ? node->right : node->left;
	rb_replace_node(tree, child, node);

	if (node->color == RB_BALCK) {
		if (child != NULL && child->color == RB_RED) {
			child->color = RB_BALCK;
		}
		else {
			rb_remove_fixup(tree, child, node->parent);
		}
    }
	
	free(node);
}

void rb_remove_fixup(struct rb_tree *tree, struct rb_node *node, struct rb_node *parent)
{
	if (tree->root != node) {		
		struct rb_node *sibling = rb_sibling(node, parent);
		if (sibling != NULL && sibling->color == RB_RED) {
			/*
			 * case 2
			 * case 2
			 */
			sibling->color = RB_BALCK;
			parent->color = RB_RED;
			if (node == parent->left) {
				rb_rotate_left(tree, parent);
			} else {
				rb_rotate_right(tree, parent);
			}
		}
		
		/* case 2 changed the sibling node */
		sibling = rb_sibling(node, parent);
		if ((sibling != NULL && sibling->color == RB_BALCK)
			&& (sibling->left == NULL || sibling->left->color == RB_BALCK)
			&& (sibling->right == NULL || sibling->right->color == RB_BALCK)
			&& (parent->color == RB_BALCK)) {
				/*
				 * case 3
				 * case 3
				 */
				sibling->color = RB_RED;
				rb_remove_fixup(tree, parent, parent->parent);
		} else {
			if ((sibling != NULL && sibling->color == RB_BALCK)
				&& (sibling->left == NULL || sibling->left->color == RB_BALCK)
				&& (sibling->right == NULL || sibling->right->color == RB_BALCK)
				&& (parent->color == RB_RED)) {
					/*
					 * case 4
					 * case 4
					 */
					sibling->color = RB_RED;
					parent->color = RB_BALCK;
			} else {
				/*
				 * case 5
				 * case 5
				 */
				if (node == parent->left 
					&& (sibling != NULL && sibling->color == RB_BALCK)
					&& (sibling->left != NULL && sibling->left->color == RB_RED)
					&& (sibling->right == NULL || sibling->right->color == RB_BALCK)) {
						sibling->color = RB_RED;
						sibling->left->color = RB_BALCK;
						rb_rotate_right(tree, sibling);
				} else if (node == parent->right
					&& (sibling != NULL && sibling->color == RB_BALCK)
					&& (sibling->right != NULL && sibling->right->color == RB_RED)
					&& (sibling->left == NULL || sibling->left->color == RB_BALCK)) {
						sibling->color = RB_RED;
						sibling->right->color = RB_BALCK;
						rb_rotate_left(tree, sibling);				
				}

				/*
				 * case 6
				 * case 6
				 */
				/* case 5 changed the sibling node */
				sibling = rb_sibling(node, parent);
				sibling->color = parent->color;
				parent->color = RB_BALCK;
				if (node == parent->left) {
						sibling->right->color = RB_BALCK;
						rb_rotate_left(tree, parent);
				} else {
						sibling->left->color = RB_BALCK;
						rb_rotate_right(tree, parent);
				}				
			}
		}	
	}
}


void rb_free_tree(struct rb_tree *tree)
{
	if (tree->root != NULL) {
		rb_free_node(tree->root);
		tree->root = NULL;
	}
}

void rb_free_node(struct rb_node *node)
{
	if (node != NULL) {
		rb_free_node(node->left);
		rb_free_node(node->right);
		free(node);
	}
}


struct rb_node *rb_search(struct rb_tree *tree, int key)
{
	struct rb_node *node = tree->root;
	while (node != NULL) {
		if (key < node->key) {
			node = node->left;
		} else if (key > node->key) {			
			node = node->right;
		} else {			
			break;
		}
	}

	return node;
}


struct rb_node *rb_create_node()
{
	struct rb_node *node = (struct rb_node *)malloc(sizeof(struct rb_node));
	memset(node, 0, sizeof(struct rb_node));
	return node;
}

struct rb_node *rb_uncle(struct rb_node *node, struct rb_node *parent)
{
	struct rb_node *uncle = NULL;
	struct rb_node *grandparent = rb_grandparent(node, parent);
	if (grandparent != NULL) {
		if (parent = grandparent->left) {
			uncle = grandparent->right;
		} else {
			uncle = grandparent->left;
		}
	}

	return uncle;
}

struct rb_node *rb_sibling(struct rb_node *node, struct rb_node *parent)
{
	struct rb_node *sibling = NULL;
	if (parent != NULL) {
		if (node = parent->left) {
			sibling = parent->right;
		} else {
			sibling = parent->left;
		}
	}

	return sibling;
}

struct rb_node *rb_grandparent(struct rb_node *node, struct rb_node *parent)
{
	struct rb_node *grandparent = NULL;
	if (parent != NULL) {
		grandparent = parent->parent;
	}

	return grandparent;
}


void rb_rotate_left(struct rb_tree *tree, struct rb_node *node)
{
	struct rb_node *parent = node->parent;
	struct rb_node *right = node->right;
	struct rb_node *right_left = node->right->left;

	if (parent != NULL) {
		if (node == parent->left) {
			parent->left = right;
		} else {
			parent->right = right;
		}
	}

	node->right = right_left;
	node->parent = right;

	right->left = node;
	right->parent = parent;

	if (right_left != NULL) {
		right_left->parent = node;
	}

	if (tree->root == node) {
		tree->root = right;
	}
}

void rb_rotate_right(struct rb_tree *tree, struct rb_node *node)
{
	struct rb_node *parent = node->parent;
	struct rb_node *left = node->left;
	struct rb_node *left_right = node->left->right;

	if (parent != NULL) {
		if (node == parent->left) {
			parent->left = left;
		} else {
			parent->right = left;
		}
	}

	node->left = left_right;
	node->parent = left;

	left->right = node;
	left->parent = parent;

	if (left_right != NULL) {
		left_right->parent = node;
	}

	if (tree->root == node) {
		tree->root = left;
	}
}


void rb_replace_node(struct rb_tree *tree, struct rb_node *src, struct rb_node *dst)
{
	if (dst != NULL) {
		if (src != NULL) {
			src->parent = dst->parent;
		}
		if (dst->parent != NULL) {
			if (dst == dst->parent->left) {
				dst->parent->left = src;
			} else {
				dst->parent->right = src;
			}
		}
		if (tree->root == dst) {
			tree->root = src;
		}
	}
}



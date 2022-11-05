#ifndef AVL_H
#define AVL_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>

typedef struct avl_node {
  struct avl_node *parent;
  struct avl_node *left;
  struct avl_node *right;
  int val;
  int height;
} avl_node;

typedef struct avl_tree {
  avl_node *root;
} avl_tree;

static inline int max(int x, int y) { return x > y ? x : y; }

static inline int height(avl_node *_node) {
  if (_node == NULL) {
    return -1;
  }
  return _node->height;
}

static inline void update_height(avl_node *_node) {
  if (_node == NULL) {
    return;
  }
  _node->height = max(height(_node->left), height(_node->right)) + 1;
}

static inline void child_replace(avl_node *old_child, avl_node *new_child,
                                 avl_node *parent, avl_tree *t) {
  if (parent != NULL) {
    if (old_child == parent->left) {
      parent->left = new_child;
    } else {
      parent->right = new_child;
    }
  } else {
    t->root = new_child;
  }
}

static inline avl_node *prior(avl_node *_node) {
  // _node has 2 children
  avl_node *ret = _node->left;
  while (ret->right != NULL) {
    ret = ret->right;
  }
  return ret;
}

static inline avl_node *next(avl_node *_node) {
  avl_node *ret = _node->right;
  while (ret->left != NULL) {
    ret = ret->left;
  }
  return ret;
}

static inline void swap(avl_node *x, avl_node *y) {
  int temp = x->val;
  x->val = y->val;
  y->val = temp;
}

void rotate_left(avl_node *_node, avl_tree *t);

void rotate_right(avl_node *_node, avl_tree *t);

void rebalence(avl_node *_node, avl_tree *t);

void insert(avl_tree *t, int val);

void erase_helper(avl_tree *t, avl_node *_node, int val);
void erase(avl_tree *t, int val);

#ifdef __cplusplus
}
#endif

#endif
#include "avl.h"
#include <stdlib.h>

void rotate_left(avl_node *_node, avl_tree *t) {
  avl_node *right = _node->right;

  if ((right->parent = _node->parent)) {
    // _node is not the root
    if (_node->parent->left == _node) {
      // _node is the left child
      right->parent->left = right;
    } else {
      // _node is the right child
      right->parent->right = right;
    }
  } else {
    // _node's is the root
    t->root = right;
  }

  if ((_node->right = right->left)) {
    // right's left child is not NULL
    right->left->parent = _node;
  }

  right->left = _node;
  _node->parent = right;
}

void rotate_right(avl_node *_node, avl_tree *t) {
  avl_node *left = _node->left;

  if ((left->parent = _node->parent)) {
    if (_node->parent->left == _node) {
      left->parent->left = left;
    } else {
      left->parent->right = left;
    }
  } else {
    t->root = left;
  }

  if ((_node->left = left->right)) {
    _node->left->parent = _node;
  }

  left->right = _node;
  _node->parent = left;
}

void rebalence(avl_node *_node, avl_tree *t) {
  while (_node) {
    int _height = _node->height;
    update_height(_node);

    avl_node *left = _node->left, *right = _node->right;
    int lheight = height(left), rheight = height(right), flag = 0;
    flag |= (lheight > rheight + 1);
    flag |= ((rheight > lheight + 1) << 1);
    if (flag == 1) {
      // left is higher than right
      if (height(left->left) > height(left->right)) {
        rotate_right(_node, t);
        update_height(_node), update_height(_node->parent);
      } else {
        rotate_left(left, t);
        update_height(left), update_height(left->parent);
        rotate_right(_node, t);
        update_height(_node), update_height(_node->parent);
      }
    } else if(flag == 2) {
      // right is higher than left
      if (height(right->right) > height(right->left)) {
        rotate_left(_node, t);
        update_height(_node), update_height(_node->parent);
      } else {
        rotate_right(right, t);
        update_height(right), update_height(right->parent);
        rotate_left(_node, t);
        update_height(_node), update_height(_node->parent);
      }
    }
    if (_height == _node->height) {
      return;
    }
    _node = _node->parent;
  }
}

void insert(avl_tree *t, int val) {
  avl_node *cur = t->root, *parent = NULL;
  int flag = 0; // 0 -> left, 1 -> right
  if (cur == NULL) {
    t->root = (avl_node *)malloc(sizeof(avl_node));
    t->root->parent = t->root->left = t->root->right = NULL;
    t->root->val = val;
    update_height(t->root);
    return;
  }

  while (cur) {
    if (val > cur->val) {
      parent = cur;
      cur = cur->right;
      flag = 1;
    } else if (val < cur->val) {
      parent = cur;
      cur = cur->left;
      flag = 0;
    } else {
      // val == cur->val
      return;
    }
  }

  // cur == NULL
  cur = (avl_node *)malloc(sizeof(avl_node));
  cur->val = val;
  cur->left = cur->right = NULL;
  cur->parent = parent;
  flag ? (parent->right = cur) : (parent->left = cur);

  update_height(cur);
  rebalence(cur->parent, t);
}

void erase_helper(avl_tree *t, avl_node *_node, int val) {
  if (_node == NULL) {
    return;
  }
  if (val < _node->val) {
    erase_helper(t, _node->left, val);
  } else if (val > _node->val) {
    erase_helper(t, _node->right, val);
  } else {
    int flag = 0;
    flag |= (_node->left != NULL);
    flag |= ((_node->right != NULL) << 1);
    if (flag == 0) {
      // no child
      child_replace(_node, NULL, _node->parent, t);
      rebalence(_node->parent, t);
      free(_node);
    } else if (flag == 1) {
      // only has left child
      child_replace(_node, _node->left, _node->parent, t);
      _node->left->parent = _node->parent;
      rebalence(_node->parent, t);
      free(_node);
    } else if (flag == 2) {
      // only has right child
      child_replace(_node, _node->right, _node->parent, t);
      _node->right->parent = _node->parent;
      rebalence(_node->parent, t);
      free(_node);
    } else {
      avl_node *pre = prev(_node);
      swap(pre, _node);
      erase_helper(t, pre, val);
    }
  }
}

void erase(avl_tree *t, int val) { erase_helper(t, t->root, val); }

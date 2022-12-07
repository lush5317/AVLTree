#include "avl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \033[1;31m  -> red
 * \033[1;33m  -> yellow
 * \033[0m     -> reset
 */

typedef struct queue_node {
  avl_node *_node;
  int has_parent;
} queue_node;

typedef struct queue {
  queue_node a[10000];
  int front;
  int size;
} queue;

void queue_push(queue *q, queue_node _node) {
  q->a[q->size + q->front] = _node;
  q->size++;
}

void queue_pop(queue *q) { q->size--, q->front++; }

void print_level_order(avl_node *_node) {
  if (_node == NULL) {
    return;
  }
  int _height = _node->height, cnt = _height, all_n = pow(2, _height + 1) * 10;

  queue *q = (queue *)malloc(sizeof(queue));
  q->front = 0;
  queue_push(q, (queue_node){_node, 0});

  // check if existing a node has parent
  int flag = 1;
  while (flag) {
    flag = 0;
    int size = q->size, unit_whitespace = all_n / pow(2, _height - cnt + 1);
    for (int i = 1; i <= size; ++i) {
      avl_node *_node = q->a[q->front]._node;
      int has_parent = q->a[q->front].has_parent;
      int offset = i == 1 ? unit_whitespace : 2 * unit_whitespace;
      if (_node == NULL) {
        queue_pop(q);
        queue_push(q, (queue_node){NULL, 0});
        queue_push(q, (queue_node){NULL, 0});
        has_parent ? printf("\033[0m%*s,%2d", offset - 4, "null", -1)
                   : printf("\033[0m%*s", offset, "");
      } else {
        flag = 1;
        queue_push(q, (queue_node){_node->left, 1});
        queue_push(q, (queue_node){_node->right, 1});
        queue_pop(q);
        printf("\033[1;33m%*d\033[0m,%2d", offset - 4, _node->val,
               height(_node));
      }
    }
    printf("\n\n");
    fflush(stdout);
    cnt--;
  }
}

void print_inorder(avl_node *_node) {
  if (_node == NULL) {
    return;
  }
  print_inorder(_node->left);
  printf("\033[1;33m%d ", _node->val);
  print_inorder(_node->right);
}

void print_preorder(avl_node *_node) {
  if (_node == NULL) {
    return;
  }
  printf("\033[1;33m%d ", _node->val);
  print_preorder(_node->left);
  print_preorder(_node->right);
}

void print_table() {
  printf("\033[0m>>>>>>>>>>>>>>>>OPERATION:<<<<<<<<<<<<<<<<<<<<\n");
  printf("insert: 1. For example, \"1 44\" means insert 44.\n");
  printf("erase: 2. For example, \"2 44\" means erase  44.\n");
  printf("print tree by level order: 3\n");
  printf("print tree by inorder: 4\n");
  printf("exit: 0\n");
}

int main() {
  avl_tree *t = (avl_tree *)malloc(sizeof(avl_tree));
  t->root = NULL;

  int flag;
  print_table();
  scanf("%d", &flag);
  while (flag) {
    int val;
    switch (flag) {
    case 1:
      scanf("%d", &val);
      insert(t, val);
      printf("\033[1;31m-------------------------------------------------------"
             "----------"
             "----"
             "---------------------------------------\n");
      print_level_order(t->root);

      break;
    case 2:
      scanf("%d", &val);
      erase(t, val);
      printf("\033[1;31m-------------------------------------------------------"
             "----------"
             "----"
             "---------------------------------------\n");
      print_level_order(t->root);
      break;
    case 3:
      printf("\033[1;31m-------------------------------------------------------"
             "----------"
             "----"
             "---------------------------------------\n");
      print_level_order(t->root);
      break;
    case 4:
      printf("\033[1;31m-------------------------------------------------------"
             "----------"
             "----"
             "---------------------------------------\n");
      print_inorder(t->root);
      printf("\n\n");
      break;
    default:
      fprintf(stderr, "no such opertion\n");
    }
    print_table();
    scanf("%d", &flag);
  }
}
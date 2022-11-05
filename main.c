#include "avl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

  queue *q = malloc(sizeof(queue));
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
        has_parent ? printf("%*s,%2d", offset - 4, "null", -1)
                   : printf("%*s", offset, "");
      } else {
        flag = 1;
        queue_push(q, (queue_node){_node->left, 1});
        queue_push(q, (queue_node){_node->right, 1});
        queue_pop(q);
        printf("%*d,%2d", offset - 4, _node->val, height(_node));
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
  printf("%d ", _node->val);
  print_inorder(_node->right);
}

void print_preorder(avl_node *_node) {
  if (_node == NULL) {
    return;
  }
  printf("%d ", _node->val);
  print_preorder(_node->left);
  print_preorder(_node->right);
}

int main() {

  avl_tree *t = malloc(sizeof(avl_tree));
  t->root = NULL;
  insert(t, 100);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 150);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 125);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 175);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 50);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 25);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  insert(t, 75);

  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  erase(t, 25);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);
  
  erase(t, 125);
  printf("---------------------------------------------------------------------"
         "---------------------------------------\n");
  print_level_order(t->root);

  // getchar();
}
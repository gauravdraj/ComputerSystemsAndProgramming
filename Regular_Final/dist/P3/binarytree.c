/**********************
 *  binarytree.c:
 ************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

NODE* new_node()
{ 
  return ((NODE*)malloc(sizeof(NODE)));
}

NODE* init_node(int d1, NODE* p1, NODE* p2)
{ 
  NODE* t;
  
  t = new_node();
  t->d = d1;
  t->left = p1;
  t->right = p2;
  return t;
}


void insert_node( int d1, NODE* p1 ){
  if( p1->d < d1 && p1->right == NULL )
    p1->right = init_node( d1, NULL, NULL );
  else if( p1->d > d1 && p1->left == NULL )
    p1->left = init_node( d1, NULL, NULL );
  else if( p1->d < d1 && p1->right != NULL )
    insert_node( d1, p1->right );
  else
    insert_node( d1, p1->left );
}


/* create a binary search tree from an array */
NODE* create_tree(int a[], int size )
{
  int i ;
  NODE* root = init_node( a[0] , NULL , NULL );

  for( i = 1 ; i < size ; i ++ )
    insert_node( a[i] , root  );

  return root;
}

// Return 1: if they are at the same level
// Return 0: if they are at different levels
int same_level(NODE* root, int node1, int node2) {
  // Write your code here!
  int level1, level2;
  NODE* rootcopy = root;

  if (root -> d == node1) level1 = 0;
  if (root -> d == node2) level2 = 0;
  while (rootcopy -> d != node1) {
    if (node1 > rootcopy -> d) { 
      rootcopy = rootcopy -> right;
      level1++;
    } else {
      rootcopy = rootcopy -> left;
      level1++;
    }
  }

  while (root -> d != node2) {
    if (node2 > root -> d) { 
      root = root -> right;
      level2++;
    } else {
      root = root -> left;
      level2++;
    }
  }

  if (level1 == level2) return 1;
  return 0;
} 


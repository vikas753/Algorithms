#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct
{
  int key;
  int* lchild;
  int* rchild;
  int* parent;
}tree_node_t;

// Returns the node with minimum key for a root
tree_node_t* min_node_tree(tree_node_t* root)
{
  tree_node_t* node_iter = root;  
  while(node_iter->lchild != NULL)
  {
    node_iter = (tree_node_t*)node_iter->lchild;  
  }
  return node_iter;
}

// Returns the succcesfor of a node in a tree
tree_node_t* succesor_node_tree(tree_node_t* node)
{
  tree_node_t* node_iter=node;
  int key_sentinel = node->key;
  
  if(node_iter->rchild != NULL)  
  {
    return (tree_node_t*)node_iter->rchild;
  }
  
  node_iter = (tree_node_t*)node_iter->parent;
  
  while((node_iter != NULL) && (node_iter->key < key_sentinel))
  {
    node_iter = (tree_node_t*)node_iter->parent;
  }
  
  return node_iter;
}

void insert_node(tree_node_t* root , int key)
{
  tree_node_t* next = NULL , *node_iter = root , *node_alloc = (tree_node_t*)malloc(sizeof(tree_node_t));
  
  node_alloc->key = key;
  
  node_alloc->lchild = NULL;
  node_alloc->rchild = NULL;
  node_alloc->parent = NULL;
  
  do{
    if(key > node_iter->key)
    {
      next=(tree_node_t*)node_iter->rchild;   
      if(next!=NULL)
      {
        node_iter = (tree_node_t*)node_iter->rchild;
      }
    }
    else
    {
      next=(tree_node_t*)node_iter->lchild;
      if(next!=NULL)
      {
        node_iter = (tree_node_t*)node_iter->lchild;
      }
    }
  } while(next != NULL);
  
  node_alloc->parent = (int*)node_iter;
  
  if(key > node_iter->key)
  {
    node_iter->rchild = (int*)node_alloc;   
  }
  else
  {
    node_iter->lchild = (int*)node_alloc;
  }
}

// Insert nodes , succesively in a sequence to the tree
void make_tree(tree_node_t* root)
{
  insert_node(root,18);
  insert_node(root,17);
  insert_node(root,20);
  insert_node(root,6);
  insert_node(root,7);
  insert_node(root,3);
  insert_node(root,13);
}

// Performs an inorder traversal of a tree with below root
void inorder_display(tree_node_t* root)
{
  tree_node_t* node_iter = min_node_tree(root);
  cout<<node_iter->key<<"->";
  node_iter=succesor_node_tree(node_iter);

  while(node_iter!=NULL)
  {
    cout<<node_iter->key<<"->";
    node_iter=succesor_node_tree(node_iter);
  }
}

int main() {
  // your code goes here
  tree_node_t* root = (tree_node_t*)malloc(sizeof(tree_node_t));

  root->key = 15;
  root->lchild = NULL;
  root->rchild = NULL;
  root->parent = NULL;
  
  make_tree(root);
  inorder_display(root);
  
  return 0;
}

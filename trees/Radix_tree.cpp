#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct
{
  char* key;
  int* lchild;
  int* rchild;
  int* parent;
}tree_node_t;

void insert_node(tree_node_t* root , char s[] , int length)
{
  tree_node_t* node_iter = root; 
  for(int i=0;i<length;i++)
  {
    if(s[i] == '1')
    {
      if(node_iter->rchild == NULL)
      {
        node_iter->rchild = (int*)malloc(sizeof(tree_node_t));
        ((tree_node_t*)(node_iter->rchild))->parent = (int*)node_iter;
        ((tree_node_t*)(node_iter->rchild))->key = NULL;
      }
      else
      {
        // do nothing
      }

      node_iter = (tree_node_t*)node_iter->rchild;
      
    }
    else
    {
      if(node_iter->lchild == NULL)
      {
        node_iter->lchild = (int*)malloc(sizeof(tree_node_t));
        ((tree_node_t*)(node_iter->lchild))->parent = (int*)node_iter;
        ((tree_node_t*)(node_iter->lchild))->key = NULL;
      }
      else
      {
        // do nothing
      }

      node_iter = (tree_node_t*)node_iter->lchild;
    }
  }
  node_iter->key = s;
}

// Insert nodes , succesively in a sequence to the tree
void make_tree(tree_node_t* root)
{
  insert_node(root,"1011",4);
  insert_node(root,"10",2);
  insert_node(root,"011",3);
  insert_node(root,"100",3);
  insert_node(root,"0",1);
}

// Performs an inorder traversal of a tree with below root
void inorder_display(tree_node_t* root)
{
  
  if(root!= NULL)
  {
    inorder_display((tree_node_t*)root->lchild);
    if(root->key != NULL)
    {
      cout<<root->key<<"->";
    }
    inorder_display((tree_node_t*)root->rchild);
  }
  
}

int main() {
  // your code goes here
  tree_node_t* root = (tree_node_t*)malloc(sizeof(tree_node_t));

  root->key = NULL;
  root->lchild = NULL;
  root->rchild = NULL;
  root->parent = NULL;
  
  make_tree(root);
    
  inorder_display(root);
  
  return 0;
}

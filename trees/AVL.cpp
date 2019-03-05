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

#define SUBTREE_ROTATE_CASE_SLL 0
#define SUBTREE_ROTATE_CASE_SLR 1
#define SUBTREE_ROTATE_CASE_SRL 2 
#define SUBTREE_ROTATE_CASE_SRR 3

void subtree_rotate(tree_node_t* subtreePtr , int caseID)
{
  switch(caseID)
  {
    case SUBTREE_ROTATE_CASE_SLL:{
      if(subtreePtr->parent != NULL)
      {
        if(((tree_node_t*)subtreePtr->parent)->lchild == (int*)subtreePtr)
        {
          ((tree_node_t*)subtreePtr->parent)->lchild = (int*)subtreePtr->lchild;
          ((tree_node_t*)subtreePtr->lchild)->rchild = (int*)subtreePtr;
        }
        else
        {
          ((tree_node_t*)subtreePtr->parent)->rchild = (int*)subtreePtr->lchild;
          ((tree_node_t*)subtreePtr->lchild)->rchild = (int*)subtreePtr;
        }
      }
      else
      {
        subtreePtr = (tree_node_t*)subtreePtr->lchild;
        subtreePtr->rchild = (int*)subtreePtr->parent;
      }
      break;      
    }
    case SUBTREE_ROTATE_CASE_SLR:{
      if(subtreePtr->parent != NULL)
      {
        if(((tree_node_t*)subtreePtr->parent)->lchild == (int*)subtreePtr)
        {
          ((tree_node_t*)subtreePtr->parent)->lchild = ((tree_node_t*)subtreePtr->lchild)->rchild;
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->lchild = (int*)subtreePtr->lchild; 
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->rchild = (int*)subtreePtr;
          subtreePtr->lchild = NULL;
        }
        else
        {
          ((tree_node_t*)subtreePtr->parent)->rchild = ((tree_node_t*)subtreePtr->lchild)->rchild;
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->lchild = (int*)subtreePtr->lchild; 
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->rchild = (int*)subtreePtr;
          subtreePtr->lchild = NULL;
        }
      }
      else
      {
        subtreePtr = (tree_node_t*)((tree_node_t*)subtreePtr->lchild)->rchild;
        subtreePtr->lchild = (int*)subtreePtr->parent;
        subtreePtr->rchild = (int*)(((tree_node_t*)subtreePtr->parent)->parent);
        ((tree_node_t*)subtreePtr->rchild)->lchild = NULL;
      }
      break;      
    }
    case SUBTREE_ROTATE_CASE_SRR:{
      if(subtreePtr->parent != NULL)
      {
        if(((tree_node_t*)subtreePtr->parent)->lchild == (int*)subtreePtr)
        {
          ((tree_node_t*)subtreePtr->parent)->lchild = (int*)subtreePtr->rchild;
          ((tree_node_t*)subtreePtr->rchild)->lchild = (int*)subtreePtr;
        }
        else
        {
          ((tree_node_t*)subtreePtr->parent)->rchild = (int*)subtreePtr->rchild;
          ((tree_node_t*)subtreePtr->rchild)->lchild = (int*)subtreePtr;
        }
      }
      else
      {
        subtreePtr = (tree_node_t*)subtreePtr->rchild;
        subtreePtr->lchild = (int*)subtreePtr->parent;
      }
      break;      
    }
    case SUBTREE_ROTATE_CASE_SRL:{
      if(subtreePtr->parent != NULL)
      {
        if(((tree_node_t*)subtreePtr->parent)->lchild == (int*)subtreePtr)
        {
          ((tree_node_t*)subtreePtr->parent)->lchild = ((tree_node_t*)subtreePtr->rchild)->lchild;
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->rchild = (int*)subtreePtr->rchild; 
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->lchild = (int*)subtreePtr;
          subtreePtr->lchild = NULL;
        }
        else
        {
          ((tree_node_t*)subtreePtr->parent)->rchild = ((tree_node_t*)subtreePtr->rchild)->lchild;
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->rchild = (int*)subtreePtr->rchild; 
          ((tree_node_t*)(((tree_node_t*)subtreePtr->parent)->lchild))->lchild = (int*)subtreePtr;
          subtreePtr->lchild = NULL;
        }
      }
      else
      {
        subtreePtr = (tree_node_t*)((tree_node_t*)subtreePtr->rchild)->lchild;
        subtreePtr->rchild = (int*)subtreePtr->parent;
        subtreePtr->lchild = (int*)(((tree_node_t*)subtreePtr->parent)->parent);
        ((tree_node_t*)subtreePtr->lchild)->rchild = NULL;
      }
      break;      
    }
    default:{
      cout<<"WARNING ! DEFAULT SUBTREE rotate case hit";
    }
  }
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
    tree_node_t* node_iter_parent =  (tree_node_t*)node_iter->parent;
    if((node_iter_parent->lchild == (int*)node_iter) && (node_iter_parent->rchild == NULL))
    {
      subtree_rotate(node_iter_parent , SUBTREE_ROTATE_CASE_SLR);
    }
    else if((node_iter_parent->rchild == (int*)node_iter) && (node_iter_parent->lchild == NULL))
    {
      subtree_rotate(node_iter_parent , SUBTREE_ROTATE_CASE_SRR);
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    node_iter->lchild = (int*)node_alloc;
    tree_node_t* node_iter_parent =  (tree_node_t*)node_iter->parent;

    if((node_iter_parent->lchild == (int*)node_iter) && (node_iter_parent->rchild == NULL))
    {
      subtree_rotate(node_iter_parent , SUBTREE_ROTATE_CASE_SRL);
    }
    else if((node_iter_parent->rchild == (int*)node_iter) && (node_iter_parent->lchild == NULL))
    {
      subtree_rotate(node_iter_parent , SUBTREE_ROTATE_CASE_SLL);
    }
    else
    {
      // do nothing
    }
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

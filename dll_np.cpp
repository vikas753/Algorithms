#include <iostream>
#include <stdint.h>
using namespace std;

typedef struct
{
  int data;
  long int* np;
}dll_np_node_t;

#define EXOR(a,b) a^b
#define PTR_VAL(arg) *((long int*)(arg))

template<typename T,typename T2>
T* get_ptr_exor(T2* a , T* b)
{
  long int np_ptr_val = *((long int*)a);
  long int prev_ptr_val = *((long int*)b);
  //cout << "np_ptr_val : " << np_ptr_val << "prev_ptr_val : " << prev_ptr_val << endl;
  long int exor_np_prev_val = EXOR(np_ptr_val , prev_ptr_val);
  T* next = (T*)&exor_np_prev_val;
  return next;
}

void insert(int data,dll_np_node_t* head)
{
  dll_np_node_t* prev = NULL;
  dll_np_node_t* i=head;

  dll_np_node_t* next = get_ptr_exor<dll_np_node_t,long int>(i->np,prev);
  
  while(next != NULL)
  {
    prev = i;
    i = next;
    next = get_ptr_exor<dll_np_node_t,long int>(i->np , prev);
    cout << " insert : prev - " << prev << " , i - " << i << " , next - " << next ;  
  }
  
  dll_np_node_t insertable_node = {0};
  insertable_node.data = data;
  insertable_node.np = (long int*)get_ptr_exor<dll_np_node_t,dll_np_node_t>(i , NULL);
  
  i->np = (long int*)get_ptr_exor<dll_np_node_t,dll_np_node_t>(&insertable_node , prev);
  
}

dll_np_node_t* search(int data,dll_np_node_t* head)
{
  dll_np_node_t* prev = NULL;
  dll_np_node_t* i=head;
  dll_np_node_t* next = (dll_np_node_t*)get_ptr_exor<dll_np_node_t,long int>(i->np , prev);
  
  while(next != NULL)
  {
    prev = i;
    i = next;
    
    cout<<i->data<<"(np)->";
    
    if(i->data == data)
    {
      return i;
    }
    
    next = (dll_np_node_t*)get_ptr_exor<dll_np_node_t,long int>(i->np , prev);
  }
  
  return (i->data == data)?i:NULL;
}

int main() {
	// your code goes here
	dll_np_node_t ll_head;
	ll_head.data = 25;
	ll_head.np = NULL;
	insert(26,(dll_np_node_t*)&ll_head);
	insert(30,(dll_np_node_t*)&ll_head);
	insert(28,(dll_np_node_t*)&ll_head);
	insert(32,(dll_np_node_t*)&ll_head);
	insert(36,(dll_np_node_t*)&ll_head);
	dll_np_node_t* node_search=search(30,(dll_np_node_t*)&ll_head);
	int node_success = (node_search!=NULL)?2:0;
	
	cout << " Test case status " << node_success; 
	
	return 0;
}

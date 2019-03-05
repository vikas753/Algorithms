#include <iostream>
#include <stdbool.h>
using namespace std;

#define TEST_ARR_LEN 8
#define NULL_SENTINEL 0xFFFFFFFF
#define PAINT_SENTINEL 0x5A5A5A5A

typedef struct
{
  int key;
  int prev;
  int next;
}ll_arbitrator_t;

void make_list(ll_arbitrator_t ll_arbitrator[])
{
  ll_arbitrator[1].next = 2;
  ll_arbitrator[1].key = 4;
  ll_arbitrator[1].prev = 5;
  
  ll_arbitrator[2].next = NULL_SENTINEL;
  ll_arbitrator[2].key = 1;
  ll_arbitrator[2].prev = 1;
  
  ll_arbitrator[5].next = 1;
  ll_arbitrator[5].key = 16;
  ll_arbitrator[5].prev = 6;
  
  ll_arbitrator[6].next = 5;
  ll_arbitrator[6].key = 9;
  ll_arbitrator[6].prev = NULL_SENTINEL;
  
}

void paint_list_arbitrator(ll_arbitrator_t ll_arbitrator[])
{
  for(int i=0;i<TEST_ARR_LEN;i++)
  {
    ll_arbitrator[i].key = PAINT_SENTINEL;
    ll_arbitrator[i].prev = PAINT_SENTINEL;
    ll_arbitrator[i].next = PAINT_SENTINEL;
  }
}

void swap(ll_arbitrator_t* ll_a1 , ll_arbitrator_t* ll_a2)
{
  int key = ll_a2->key , prev = ll_a2->prev , next = ll_a2->next;
  
  ll_a2->key = ll_a1->key;
  ll_a2->prev = ll_a1->prev;
  ll_a2->next = ll_a1->next;
  
  ll_a1->key = key;
  ll_a1->prev = prev;
  ll_a1->next = next;
  
}

bool is_invalid_list_entry(ll_arbitrator_t* ll_arbitrator)
{
  return (ll_arbitrator->prev==PAINT_SENTINEL);
}

int get_head_index(ll_arbitrator_t ll_arbitrator[])
{
  for(int i=0;i<TEST_ARR_LEN;i++)
  {
    if(ll_arbitrator[i].prev == NULL_SENTINEL)
    {
      return i;
    }
  }
}

void print_list(ll_arbitrator_t ll_arbitrator[] , int head_index)
{
  int iter_index = head_index;
  
  while(1)
  {
    if(iter_index == NULL_SENTINEL)
    {
      break;
    }
	
    cout << "[idx:" << iter_index << ",prev:" << ll_arbitrator[iter_index].prev << ",key:" << ll_arbitrator[iter_index].key << ",next:" << ll_arbitrator[iter_index].next << "]->";
	
    iter_index = ll_arbitrator[iter_index].next;
    
  }
  cout << endl;
}

void rearrange_list(ll_arbitrator_t ll_arbitrator[] , int head_index)
{
  int j=0 , iter_index = head_index;
  
  while(iter_index != NULL_SENTINEL)
  {
    if(ll_arbitrator[iter_index].next == j)
    {
      ll_arbitrator[iter_index].next = iter_index;
    }
    else if(ll_arbitrator[iter_index].prev == j)
    {
      ll_arbitrator[iter_index].prev = iter_index;          
    }
    
    if(ll_arbitrator[j].next == iter_index)
    {
      ll_arbitrator[j].next = j;
    }
    else if(ll_arbitrator[j].prev == iter_index)
    {
      ll_arbitrator[j].prev = j;
    }
    
    swap(&ll_arbitrator[iter_index],&ll_arbitrator[j]);

    if(ll_arbitrator[j].next != NULL_SENTINEL)
    {
      ll_arbitrator[ll_arbitrator[j].next].prev = j;
    }
      
    if(!is_invalid_list_entry(&ll_arbitrator[j]))
    {
      if(ll_arbitrator[j].prev != NULL_SENTINEL)
      {
        ll_arbitrator[ll_arbitrator[j].prev].next = j;
      }
    }
    
    iter_index = ll_arbitrator[j].next;
    j = j+1;
  }
}

int main() {
    ll_arbitrator_t ll_arbitrator[TEST_ARR_LEN];
    paint_list_arbitrator(ll_arbitrator);
    make_list(ll_arbitrator);
    
    int head = get_head_index(ll_arbitrator);
    print_list(ll_arbitrator,head);
    rearrange_list(ll_arbitrator,head);
    head = get_head_index(ll_arbitrator);
    print_list(ll_arbitrator,head);
	// your code goes here
	return 0;
}

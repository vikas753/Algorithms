#include <iostream>
using namespace std;

#define RIGHT_CHILD_IDX(i,start_idx) i+2*(i-start_idx)+2
#define LEFT_CHILD_IDX(i,start_idx) i+2*(i-start_idx)+1
#define LAST_ROOT_NODE(start_idx,i) ((start_idx+(i>>1))-1)
#define TEST_ARR_ELEMS_LEN 14


template <typename T>
void swap(T* a,T* b)
{
  T temp = *b;
  *b = *a;
  *a = temp;
}

template <typename T>
void heapify_node(T a[],int i,int length,int start_idx)
{
  if((LEFT_CHILD_IDX(i,start_idx)<TEST_ARR_ELEMS_LEN) & (a[LEFT_CHILD_IDX(i,start_idx)] > a[i]))
  {
    swap(&a[LEFT_CHILD_IDX(i,start_idx)],&a[i]);
  }
  if((RIGHT_CHILD_IDX(i,start_idx)<TEST_ARR_ELEMS_LEN) & (a[RIGHT_CHILD_IDX(i,start_idx)] > a[i]))
  {
    swap(&a[RIGHT_CHILD_IDX(i,start_idx)],&a[i]);
  }
}

template <typename T>
void heapify_tree(T a[] , int start_idx , int length)
{
  int j=LAST_ROOT_NODE(start_idx,length);
  while(j>=start_idx)
  {
    heapify_node(a,j,length,start_idx);
    j--;
  }
}

int main() {
    int a[TEST_ARR_ELEMS_LEN]={1,2,5,8,9,10,14,16,21,20,22,19,30,28};
    int i=0 , length_shrinker = TEST_ARR_ELEMS_LEN;
	// your code goes here
	while(i<TEST_ARR_ELEMS_LEN)
	{
	  heapify_tree<int>(a,i,length_shrinker);
	  length_shrinker--;
	  i++;
	}
	
	for(int i=0;i<TEST_ARR_ELEMS_LEN;i++)
	{
      cout<<a[i]<<",";
	}
	
	return 0;
}

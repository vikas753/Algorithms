#include <iostream>
#include <vector>

using namespace std;
template<typename T>
void assign_arr(T dest[],T src[],int size)
{
  for(int i=0;i<size;i++)
  {
    dest[i]=src[i];
  }
}

void print_arr(int a[] , int size)
{
  cout<<"[";
  for(int i=0;i<size;i++)
  {
    cout<<a[i]<<",";
  }
  cout<<"]" << endl;
}

void count_sort(int a[] , int size)
{
  int b[size]={0};
  int c[size]={0};
  
  // Create a count record
  for(int i=0;i<size;i++)
  {
    c[a[i]] = c[a[i]]+1;
  }
  
  // Heap the count sorted array
  for(int i=0;i<size;i++)
  {
    if(i>0)
    {
      c[i] = c[(i-1)]+c[i];
    }
  }
  
  for(int i=(size-1);i>=0;i--)
  {
    b[c[a[i]]-1]=a[i];
    c[a[i]] = c[a[i]]-1;
  }
  
  assign_arr<int>(a,b,size);
  
}

#define TEST_ARR_SIZE 12

int main() {
	// your code goes here
	
	int a[TEST_ARR_SIZE]={6,2,2,7,1,3,4,6,1,3,2,8};
	count_sort(a,TEST_ARR_SIZE);
	print_arr(a,TEST_ARR_SIZE);
	
	return 0;
}

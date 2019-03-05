#include <iostream>
using namespace std;

int num_invs_merge(int a[],int array1_start_idx,int array1_end_idx,int array2_start_idx,int array2_end_idx)
{
  int count =0;
  for(int i=array1_start_idx;i<=array1_end_idx;i++)
  {
    for(int j=array2_start_idx;j<=array2_end_idx;j++)
    {
      if(a[j]<a[i])
      {
        count++;  
      }
    }
  }
  return count;
}

int num_invs(int a[],int start_idx , int end_idx)
{
  int count=0;
  
  if((end_idx-start_idx)==1)
  {
    if(a[end_idx] < a[start_idx])
    {
      count=1;
    }
  }
  else if((end_idx-start_idx)==0)
  {
    // do nothing
  }
  else
  {
    int new_mid_idx=start_idx+((end_idx-start_idx)/2);
    int new_start_idx=new_mid_idx+1;
  
    count=count+num_invs(a,start_idx,new_mid_idx);
    count=count+num_invs(a,new_start_idx,end_idx);
    count=count+num_invs_merge(a,start_idx,new_mid_idx,new_start_idx,end_idx);
  }
  return count;
}

#define TEST_ARR_LEN 5
#define TEST_ARR_E_IDX TEST_ARR_LEN-1

int main() {
    int a[TEST_ARR_LEN] = {6,5,4,3,2};
    int count = 0;
    count=num_invs(a,0,TEST_ARR_E_IDX);
    
    cout<<"Number of inversions "<<count;
	// your code goes here
   
	return 0;
}

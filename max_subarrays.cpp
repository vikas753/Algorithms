#include <iostream>
using namespace std;



int sum_arr_elems(int a[] , int start_idx , int end_idx)
{
  int sum=0;
  for(int i=start_idx;i<=end_idx;i++)
  {
    sum=sum+a[i];
  }
  return sum;
}

#define TEST_ARR_ELEMS_LEN 17

int main() {
    int a[TEST_ARR_ELEMS_LEN]={13,-3,25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    int sum , start_idx , end_idx , sum_current = -500 , max_sum_start_idx = 0 , max_sum_end_idx = 0;
    
    for(int len=0;len<TEST_ARR_ELEMS_LEN;len++)
    {
      for(int start_idx=0;(start_idx+len)<TEST_ARR_ELEMS_LEN;start_idx++)
      {
        int sum_elems = sum_arr_elems(a,start_idx,start_idx+len);
        if(sum_elems > sum_current)
        {
          sum_current =  sum_elems; 
          max_sum_start_idx = start_idx;
          max_sum_end_idx = start_idx + len;
        }
      }
    }
    cout << "Max sum : " << sum_current << " , max sum start idx : " << max_sum_start_idx << " , max sum end idx : " << max_sum_end_idx;
    
	return 0;
}

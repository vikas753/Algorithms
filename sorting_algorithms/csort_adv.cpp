#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_CHARS 30

typedef struct
{
  int key;
  string payload;
}radix_datatype_t;

template<typename T>
void assign_arr(T dest[],T src[],int size)
{
  for(int i=0;i<size;i++)
  {
    dest[i]=src[i];
  }
}

template<typename T>
void assign_arr_v2(T dest[],radix_datatype_t src[],int size)
{
  for(int i=0;i<size;i++)
  {
    dest[i]=src[i].payload;
  }
}

template<typename T>
void print_arr(T a[] , int size)
{
  cout<<"[";
  for(int i=0;i<size;i++)
  {
    cout<<a[i]<<",";
  }
  cout<<"]" << endl;
}

void print_datatable(radix_datatype_t a[] , int size)
{
  cout<<"[";
  for(int i=0;i<size;i++)
  {
    cout<<a[i].key<<"-";
    cout<<a[i].payload<<",";
  }
  cout<<"]" << endl;
}

void count_sort(radix_datatype_t a[] , int size)
{
  radix_datatype_t b[size]={0};
  int c[MAX_CHARS]={0};
  
  // Create a count record
  for(int i=0;i<size;i++)
  {
    c[a[i].key] = c[a[i].key]+1;
  }
  
  // Heap the count sorted array
  for(int i=0;i<MAX_CHARS;i++)
  {
    if(i>0)
    {
      c[i] = c[(i-1)]+c[i];
    }
  }
  
  for(int i=(size-1);i>=0;i--)
  {
    b[c[a[i].key]-1]=a[i];
    c[a[i].key] = c[a[i].key]-1;
  }
  
  assign_arr<radix_datatype_t>(a,b,size);
  
}

// 2nd arg , d is the digit which would be used as a key
void get_radix_datatable(string str[],int d,int size,radix_datatype_t datatable[])
{
  char a='A';
  int i=a;
  
  for(int j=0;j<size;j++)
  {
    datatable[j].key=str[j][d]-i;
    datatable[j].payload=str[j];
  }
}

// 2nd arg , d is the digit which would be used as a key
void modify_key_radix_datatable(radix_datatype_t datatable[],int d,int size)
{
  char a='A';
  int i=a;
  
  for(int j=0;j<size;j++)
  {
    datatable[j].key=datatable[j].payload[d]-i;
  }
}

void sort_string(string s[],int size,int d_max)
{
  radix_datatype_t datatable_ex[size]={0};
  get_radix_datatable(s,0,size,datatable_ex);
  
  for(int i=0;i<=d_max;i++)
  {
    count_sort(datatable_ex,size);
    modify_key_radix_datatable(datatable_ex,i,size);
    
  }
  
  print_datatable(datatable_ex,size);
  assign_arr_v2<string>(s,datatable_ex,size);
  
}

#define TEST_ARR_SIZE 16

int main() {
	// your code goes here
	string sort_1[TEST_ARR_SIZE]={"COW","DOG","SEA","RUG","ROW","MOB","BOX","TAB","BAR","EAR","TAR","DIG","BIG","TEA","NOW","FOX"};
	sort_string(sort_1,TEST_ARR_SIZE,2);
	print_arr<string>(sort_1,TEST_ARR_SIZE);
	
	return 0;
}

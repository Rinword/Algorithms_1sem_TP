/*На числовой прямой окрасили  ​
N ​отрезков. Известны координаты левого и правого концов каждого 
отрезка (L ​и R). Найти длину окрашенной части числовой прямой. */

#include <iostream>
#include <math.h>
using namespace std;

struct border
{
  int x; //координата
  bool isOpen; //открывающая граница или нет
};

void swap( border &a, border &b )
{
  border tmp = a;
  a = b;
  b = tmp;
}

void heap_make( border *a, int n)
{
  for (int i = n/2; i >= 1; --i)
  {
    for (int j = i; j <= n/2;)
    {
      int k = j*2;
      if (k+1 <= n and a[k].x < a[k+1].x)
      {
        ++k;
      }
      if (a[j].x < a[k].x)
      {
        swap(a[k],a[j]);
        j = k;
      }
      else
        break;
    }
  }
}

void heap_pop(border *a, int n)
{
  swap(a[n],a[1]);
  for (int i = 1; 2*i < n; )
  {
    i *= 2;
    if (i+1 < n && a[i].x < a[i+1].x)
    {
      i += 1;
    }
    if (a[i/2].x < a[i].x)
    {
      swap(a[i/2], a[i]);
    }
  }
}

void HeapSort (border *data, int n)
{
  heap_make(data - 1, n);
  for ( int i = 0; i < n; ++i )
  {
    heap_pop( data - 1, n - i );
  }
}

int main()
{
  int n = 0;
  cin>>n;
  border* Arr = new border[2*n]; //массив точек

  for( int i = 0; i < 2*n; ++i)
  {
    cin>>Arr[i].x;
    Arr[i].isOpen = true;
    i++;
    cin>>Arr[i].x;
    Arr[i].isOpen = false;
  }
    HeapSort( Arr, 2*n );//сортировка по возрастанию координаты
    int width = 0; //текущая толщина слоя
    int lenght = 0; //длина закрашенной части
    for( int i = 0; i < 2*n; ++i)
    {
      if( Arr[i].isOpen == true )
        width++;
      if( Arr[i].isOpen == false )
        width--;
      if( width >= 1 && i != 2*n )
      {
        lenght += Arr[i+1].x - Arr[i].x;
      }
    }
    cout<< lenght <<endl;
  delete[] Arr;
  return 0;
}

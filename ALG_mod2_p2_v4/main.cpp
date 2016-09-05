/*Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна 
(последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для 
каждого положения окна (от 0 и до n­k) вывести значение максимума в окне. Скорость работы O(n log 
n) 
Формат входных данных. ​
 Вначале вводится n ­ количество элементов массива. Затем вводится n 
строк со значением каждого элемента. Затем вводится k  ­ размер окна. 
Формат выходных данных. ​
 Разделенные пробелом значения максимумов для каждого положения окна. */


#include <iostream>
#include <vector>
using namespace std;

struct HeapElem
{
  int value; //ключ (значение)
  int indexInArray; //индекс
};

void swap(  HeapElem &x,  HeapElem &y )
{
   HeapElem temp;
   temp = x;
   x = y;
   y = temp;
}

//класс Max-кучи
class CHeap
{
  public:
      void heap_insert( HeapElem newElement );
      void heap_pop( );
      HeapElem extract_max( );

      vector<HeapElem> buffer;//буфер, хранящий размер окна +1 элемент
};

void CHeap::heap_insert( HeapElem newElement )
{
  buffer.push_back( newElement );
  int indexNewElem = buffer.size() - 1;
  while( buffer[indexNewElem].value > buffer[(indexNewElem - 1) / 2].value && indexNewElem > 0 )
  {
    swap( buffer[indexNewElem], buffer[(indexNewElem - 1) / 2] );
    indexNewElem = (indexNewElem - 1) / 2;
  }
}

HeapElem CHeap::extract_max()
{
  return buffer[0];
}
//просеивает элемент с индексом index на свое место в куче array
void siftDown( int index, vector<HeapElem> &array, int size )
{
  int maxChild = 0;
  int indexMaxChild = 0;
  while( 2 * index + 1 < size )
  {
    if( 2 * index + 1 == size - 1 )
    {
      maxChild = array[2 * index + 1].value;
      indexMaxChild = 2 * index + 1;
    }
    else
    {
      if( array[2 * index + 1].value < array[2 * index + 2].value )
        {
          maxChild = array[2 * index + 2].value;
          indexMaxChild = 2 * index + 2;
        }
      else
      {
        maxChild = array[2 * index + 1].value;
        indexMaxChild = 2 * index + 1;
      }
    }
    if( array[index].value < maxChild )
    {
      swap(array[index], array[indexMaxChild]);
    }
    else
    {
       break;
    }
    index = indexMaxChild;
  }
}

void CHeap::heap_pop()
{
  swap( buffer[0], buffer[ buffer.size() - 1 ] );
  buffer.pop_back();
  siftDown( 0, buffer, buffer.size() );
}

int main()
{
  int n = 0;
  cin >> n;
  HeapElem *Arr = new HeapElem[n];
  //заполнение массива
  for( int i = 0; i < n; i++ )
  {
    cin >> Arr[i].value;
    array[i].indexInArray = i;
  }
  //размер окна
  int k = 0;
  cin >> k;

  //создание первого окна
  CHeap WHeap;
  for( int i = 0; i < k; i++ )
  {
    WHeap.heap_insert( Arr[i] );
  }
  cout << WHeap.extract_max().value << " "; //вывод максимального элемента ПЕРВОГО окна
  //теперь подгружаем "свежий" элемент из Arr
  for( int i = k; i < n; i++ )
  {
    WHeap.heap_insert( Arr[i] );
    while( WHeap.extract_max().indexInArray <= ( i - k ) )
    {
      WHeap.heap_pop(); //затираем первый элемент старого окна
    }
    cout << WHeap.extract_max().value << " "; // выводим максимум текущего
  }

  delete[] array;
  return 0;
}

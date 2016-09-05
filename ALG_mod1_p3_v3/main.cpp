/*Даны два массива неповторяющихся целых чисел, упорядоченные по неубыванию. A[0..n1]
и B[0..m1].
n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k позиция
элементта B[m-1]
в массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь
результатом поиска элемента B[i-1].
n, k ? 10000.*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int elemCnt = 0; //счетчик совпавших элементов

//возвращает последовательность 0,1,2,4,8,16,32...
int SmartPower ( int value );

//функция возврата указателя на массив пересечения массивов А и В
int* MatchAB( int* A, int sizeA, int* B, int sizeB );

//бинарный поиск элемента k в массиве А от leftBorder до rightBorder
int BinarySearch( int* arr, int right, int left, int element );

int main()
{
  //создание массивов чисел
  int Asize = 0;
  cin>>Asize;
  int* A = new int[Asize];

  int Bsize = 0;
  cin>>Bsize;
  int* B = new int[Bsize];

  //заполнение массивов неубывающими целыми
  for ( int i = 0; i < Asize; i++ )
  {
    cin>>A[i];
  }
  for ( int i = 0; i < Bsize; i++ )
  {
    cin>>B[i];
  }

  int* AB = NULL;//инициализация вектора пересечений

  AB = MatchAB( A, Asize, B, Bsize );

  //вывод результата
  for ( int i = 0; i < elemCnt; i++ )
  {
    cout<<AB[i]<<" ";
  }

  free( AB );
  delete[] A;
  delete[] B;
  return 0;
}

//функция возврата массива пересечения векторов А и В
int* MatchAB( int* A, int sizeA, int* B, int sizeB )
{
  int* AB = NULL;
  for( int i = 0; i  <sizeB; i++ ) //по всем В
  {
    int leftBorder = 0; //левая граница поиска
    int rightBorder = 0;//правая граница поиска
    int k = 0; //положение i-го элемента B в массиве А
    while( B[i] >= A[rightBorder] ) //пока элемент массива A не станет больше текущего в B
    {
      leftBorder = rightBorder; //левой границе ставим прошлый индекс правой
      rightBorder = SmartPower( rightBorder ); //скачем по индексам по степени 2: 2,4,8,16...
      if( rightBorder >= sizeA ) //если очередная правая граница вышла за массив А
      {
        rightBorder = sizeA; //ставим правой ее
        break; //и прерываем цикл
      }
    }

    //далее бинарный поиск элемента k в массиве А от leftBorder до rightBorder
    k = BinarySearch( A, rightBorder, leftBorder, B[i] );
    if( k != -1 ) //если элемент нашелся, выделяем память и идем дальше
    {
      AB = ( int* ) realloc ( AB, (elemCnt+1) * sizeof(int) );
      AB[elemCnt] = A[k];
      elemCnt++;
    }
  }
  return AB;
}

//бинарный поиск элемента k в массиве А от leftBorder до rightBorder
int BinarySearch( int* arr, int right, int left, int element )
{
  int first = left;
  int last = right; // Элемент в last не учитывается.
  while( first < last )
  {
    int mid = ( first + last ) / 2;
    if( element <= arr[mid] )
      last = mid;
    else
      first = mid + 1;
  }
  // Все элементы слева от first строго больше искомого.
  return ( first == right || arr[first] != element ) ? -1 : first; //если элемент не найден или массив пуст вернется-1
}


//возвращает последовательность 0,1,2,4,8,16...
int SmartPower ( int value )
{
  if( value == 0 || value == 1 )
    return value + 1;
  else
    return value * 2;
}

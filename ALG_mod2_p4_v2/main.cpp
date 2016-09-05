#include <iostream>
#include <cassert>
using namespace std;

int Med3Index(int* vector, int right, int left )
{
  int refElem = 0;
  if( vector[right] > vector[left] )
  {
    if( vector[( left + right ) / 2] > vector[right] )
      refElem = right;
    else if( vector[left] > vector[( left + right ) / 2] )
      refElem = left;
    else
      refElem = ( left + right ) / 2;
  }
  else
  {
    if( vector[( left + right ) / 2] < vector[right] )
      refElem = right;
    else if( vector[left] < vector[( left + right ) / 2] )
      refElem = left;
    else
      refElem = ( left + right ) / 2;
  }
  return refElem;
}

int Partition( int* vector, int left, int right )
{
  assert( left <= right);
  if( left == right )
  {
    return left;
  }
  //выбор опорного элемента по медиане трех
  int refElem = Med3Index( vector, right, left );
  //проход от конца в начало массива
  swap( vector[left], vector[refElem] );
  int pivot = vector[left];
  int i = right;
  int j = right;
  while( j > left ) //пока j не дойдет до последнего элемента
  {
    //cout << ")i="<<i<<" j="<<j<<" pivot="<<pivot<<endl;
    for ( ; vector[i] > pivot; --i, --j ){} //проматываем до первого большего, чем опорного
    if( vector[j] <= pivot ) //если этот элемент больше пивота идем дальше
    {
      j--;
    }
    else //если встречается меньший или равный
    {
      swap( vector[i], vector[j] ); //свопаем меньший на место i
      --i; //и плюсуем счетчики
      --j;
    }
  }
  swap( vector[i], vector[left] );//в конце свопаем пивот на свое место
  return i;
}

//int Partition( int* vector, int left, int right )
//{
//  assert( left <= right);
//  if( left == right )
//  {
//    return left;
//  }
//  //выбор опорного элемента по медиане трех
//  int refElem = Med3Index( vector, right, left );
//  //проход от конца в начало массива
//  swap( vector[right], vector[refElem] );
//  int pivot = vector[right];
//  int i = left;
//  int j = left;
//  while( j < right ) //пока j не дойдет до последнего элемента
//  {
//    //cout << ")i="<<i<<" j="<<j<<" pivot="<<pivot<<endl;
//    for ( ; vector[i] <= pivot; ++i, ++j ){} //проматываем до первого большего, чем опорного
//    if( vector[j] > pivot ) //если этот элемент больше пивота идем дальше
//    {
//      j++;
//    }
//    else //если встречается меньший или равный
//    {
//      swap( vector[i], vector[j] ); //свопаем меньший на место i
//      ++i; //и плюсуем счетчики
//      ++j;
//    }
//  }
//  swap( vector[i], vector[right] );//в конце свопаем пивот на свое место
//  return i;
//}

int KStat( int* vector, int n, int k )
{
  assert( k >= 0 && k < n );
  int left = 0;
  int right = n - 1;
  while( true )
  {
    int pivotIndex = Partition( vector, left, right );
    if( pivotIndex == k )
    {
      return vector[pivotIndex];
    }
    else if( pivotIndex < k )
    {
      left = pivotIndex + 1;
    }
    else
    {
      right = pivotIndex - 1;
    }
  }
}


int main()
{
  int n = 0;
  cin>> n;
  int k = 0;
  cin >> k;
  int* vector = new int[n];
  for( int i = 0; i < n; ++i)
  {
    cin >> vector[i];
  }
  cout <<"Stat:"<< KStat( vector, n , k )<<endl;
  for( int i = 0; i < n; ++i)
  {
    cout << vector[i]<<" ";
  }
  delete[] vector;
  return 0;
}

// Задано N точек на плоскости. Указать (N­-1)­звенную несамопересекающуюся замкнутую ломаную, 
// проходящую через все эти точки. Точки на ломаной расположите в порядке убывания углов лучей от
// начальной точки до всех остальных точек.

#include <iostream>
#include <math.h>
using namespace std;

struct CCoords
{
  double x;
  double y;
  bool operator < (const CCoords& other) const;
};

bool CCoords::operator <( const CCoords& other) const
{
  return  ( atan2( x, y ) < atan2( other.x, other.y ) ||
          ( atan2( x, y ) == atan2( other.x, other.y ) && x < other.x ) ||
          ( atan2( x, y ) == atan2( other.x, other.y ) && x == other.x  && y < other.y));

//  return  ( atan( x/y ) < atan( other.x/other.y ) ||
//          ( atan( x/y ) == atan( other.x/other.y ) && x < other.x ) ||
//          ( atan( x/y ) == atan( other.x/other.y ) && x == other.x  && y < other.y));
}

class CMyFunctor {
public:
        explicit CMyFunctor( bool _doCompare ) : doCompare( _doCompare ) {}
        bool operator()( const CCoords& left, const CCoords& right ) { return  left < right; }

private:
        bool doCompare;
};

//сортировка вставками
void InsertionSort( CCoords* a, int n, CMyFunctor functor )
{
  int j = 0;
  for ( int i = 1; i < n; ++i )
  {
    CCoords tmp = a[i];
    for ( j = i; j > 0 && functor( tmp, a[j-1] ); --j )
    {
      a[j] = a[j-1];
    }
    a[j] = tmp;
  }

}

int main()
{
  int n = 0;
  cin>>n;
  int xmin = 0;
  int ymin = 0;
  CCoords* Arr = new CCoords[n];
  for( int i = 0; i < n; ++i )
  {
    cin >> Arr[i].x;
    cin >> Arr[i].y;
    if( i == 0 ) //начальная инициализация минимумов
    {
      xmin = Arr[i].x;
      ymin = Arr[i].y;
    }
    if( Arr[i].x < xmin )
      xmin = Arr[i].x;
    if( Arr[i].y < ymin )
      ymin = Arr[i].y;
  }
  //перенесем ближнюю к началу координат точку в 0 координат (и все остальные тоже сдвинем)
  for ( int i = 0; i < n; ++i )
  {
    Arr[i].x = Arr[i].x - xmin;
    Arr[i].y = Arr[i].y - ymin;
  }
  CMyFunctor myFunctor ( false );
  InsertionSort( Arr, n, myFunctor );
  cout<<endl;
  //возвращаем точкам начальные координаты
  for ( int i = 0; i < n; ++i )
  {
    Arr[i].x = Arr[i].x + xmin;
    Arr[i].y = Arr[i].y + ymin;
  }
  for( int i = 0; i < n; ++i )
  {
    cout << Arr[i].x << " " << Arr[i].y << endl;
  }
  delete Arr;
  return 0;
}

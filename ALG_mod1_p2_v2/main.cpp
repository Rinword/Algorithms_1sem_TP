/*Вычислить площадь выпуклого nугольника,
заданного координатами своих вершин. Вначале вводится
количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода
против часовой стрелки.
n < 1000, координаты < 10000.*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Coord
{
  int x;
  int y;
};

double NArea( Coord *NAng, int n )
{
  //Coord* MidEval = new Coord [n];
  Coord* MidEval = new Coord[n];
  for( int i = 0; i <n ; i++ )
  {
    Coord CurrSum ={0,0};
    CurrSum.x = (NAng[i]).y * (NAng[i+1]).x; //записываем результат перемножения разноименных координат соседних вершин
    CurrSum.y = (NAng[i]).x * (NAng[i+1]).y;
    MidEval[i] = CurrSum;
  }
  int XSum = 0;
  int YSum = 0;
  //цикл суммирования столбцов
  for ( int i = 0; i < n ; i++ )
  {
    XSum = XSum + MidEval[i].x;
    YSum = YSum + MidEval[i].y;
  }
  delete [] MidEval;
  return ( ( (double) abs( XSum - YSum ) ) / 2 ) ;
}

int main()
{
  int n = 0;
  cin>>n;
  Coord* NAng = new Coord[n+1];
  for ( int i = 0; i < n; i++ )
  {
    Coord CurrCoord = {0,0};
    cin>>CurrCoord.x;
    cin>>CurrCoord.y;
    NAng[i] = CurrCoord;
  }
  //в конец накидываем коорд первой вершины
  NAng[n] = NAng[0];
  cout<<NArea( NAng,n );
  delete [] NAng;
  return 0;
}


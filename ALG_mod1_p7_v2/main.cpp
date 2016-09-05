/*В большой ITфирме
есть только одна переговорная комната. Желающие посовещаться заполняют заявки с
желаемым временем начала и конца. Ваша задача определить максимальное количество
заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел — начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число — максимальное число заявок.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "string.h"
#include <cstdio>

using namespace std;

//функтор сортировки: по возрастанию левой границы
struct sort_class_left
{
    bool operator() ( pair <int,int> i, pair <int,int>  j)
    {
      if( i.first == j.first )
        return ( i.second < j.second );

      return ( i.first < j.first );
    }
} sort_objectLeft;

//функция заполнения вектора интервалами времени собеседований
void EnterTime ( vector < pair <int,int> > &App );

//функция вывода содержимого вектора в консоль
void ShowApp (vector < pair <int,int> > App);

//возвращает максимально возможное число собеседований
//при входном векторе интервалов собеседований
int Find_Inter_Count(vector < pair <int,int> > &App);



int main()
{
  vector < pair <int,int> > App; //инициализация вектора с интервалами
  EnterTime ( App ); //заполнение интервалов собеседований
  cout<<Find_Inter_Count( App );//сортировка и нахождение числа возможных интервалов
  return 0;
}



//функция заполнения вектора интервалами времени собеседований
void EnterTime ( vector < pair <int,int> > &App )
{
  int left = 0;
  int right = 0;
  pair <int,int> pairBuffer;

  //ввод координат отрезков (промежутков совещаний)
  while( cin>>left>>right )
  {
    pairBuffer.first = left;
    pairBuffer.second = right;
    App.push_back( pairBuffer );
  }
}

//функция вывода содержимого вектора в консоль
void ShowApp (vector < pair <int,int> > App)
{
  for( int i = 0; i < App.size(); i++)
    cout<<i<<") "<<(App[i]).first<<"-"<<(App[i]).second<<endl;
}

//возвращает максимально возможное число собеседований
//при входном векторе интервалов собеседований
int Find_Inter_Count(vector < pair <int,int> > &App)
{
  sort( App.begin(), App.end(), sort_objectLeft ); //сортировка по возрастанию времени начала переговоров
  ShowApp ( App );
  int leftBorder = -1; //текущая левая граница
  int rightBorder = 0; //текущая правая граница
  int AppCnt = 0; //счетчик собеседований

  for( int i = 0; i < App.size(); i++ )
  {
    if ( rightBorder > App[i].first && rightBorder < App[i].second ) //если правая граница прошлого отрезка дальше левой текущего
      continue; //то этот отрезок "внутри" уже принятого только левым концом,
    // он как минимум не лучше текущего,идем на следующий

    // а если он полностью внутри текущего, то он лучше во всем
    // и раньше гарантировано нет из-за сортировки по возрастанию левой границы
    //if ( leftBorder < App[i].first && rightBorder < App[i].second )

    if( leftBorder < App[i].first ) //если левая граница подвинулась (кончились интервалы с этого часа)
    {
      AppCnt++; //плюсуем счетчик
      leftBorder = App[i].first; //обновляем границы на текущий отрезок
      rightBorder = App[i].second;
      continue; //и идем на следующий, вдруг там найдется короче
    }
    if ( leftBorder == App[i].first ) //если интервалы начинаются в одно время
    {
      rightBorder = min( rightBorder, App[i].second ); //то выбираем тот, что короче
    }
  }
  return AppCnt;
}

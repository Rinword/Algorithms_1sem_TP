//Дано N кубиков. Требуется определить каким количеством способов можно выстроить
//из этих кубиков пирамиду. Каждый следующий слой не больше нижележащего

#include <iostream>

using namespace std;


int main()
{
  int N=0;
  cin>>N;
  // пустая пирамидка тоже считается пирамидкой, а также пирамидка с "пустым" кубиком считается другой
  N++;
  unsigned long long**   ResArr = new unsigned long long* [N];
  for( int i = 0; i < N; i++ )
  {
    ResArr[i] = new unsigned long long [N];
  }
  for( int i = 0; i < N;i++ ) //по N
  {
    for( int j = 0; j < N; j++ ) //по k
    {
      if( i == 0 || i == 1 || j == 0 || j == 1 ) //первые 2 строки и столбца единицы
      {
        ResArr[i][j] = 1;
        continue;
      }
      if( i < j ) //если основание больше числа кубиков
      {
        ResArr[i][j] =  ResArr[i][j-1];
        continue;
      }

      if( i == j ) //если основание равно количеству кубиков
      {
        ResArr[i][j] =  ResArr[i][j-1] + 1;
        continue;
      }
        ResArr[i][j] = ResArr[i][j-1] + ResArr[i-j][j];
    }
  }
  cout<<ResArr[N-1][N-1];
  for( int i = 0; i < N; i++)
  {
    delete ResArr[i];
  }
  delete[] ResArr;

  return 0;
}

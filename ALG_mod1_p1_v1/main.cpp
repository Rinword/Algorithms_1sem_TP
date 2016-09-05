//Найти на сколько нулей заканчивается n!=1*2*3..*n
#include <iostream>
#include <math.h>

using namespace std;

int ZeroCount(int n)
{
  int pyat=0;
  for(int i=1;i<=n;i++)
  {

    double currentMember=i;

    while (1)//пока не останется последняя кратность
    {
      currentMember= currentMember/5; //делим на 5
       if (floor(currentMember) == currentMember) //если нацело
       {
         pyat++; //плюсуем счетчик пятерок
       }
       else break;
    }
  }
 return pyat;
}

int main()
{
  int n=1;
  cin>>n;
  cout<<ZeroCount(n);
  return 0;
}

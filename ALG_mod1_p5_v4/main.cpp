/*Дано выражение в инфиксной записи. Вычислить его,
 используя перевод выражения в постфиксную запись.
Выражение не содержит отрицательных чисел.*/


#include "stack"
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

#define MAX_STACK 100

//структура элемента
struct element
{
  char type; //тип элемента, N если число, +, -,*,/,(,)
  int data; //хранимое число, если оно есть, для операндов -1
};

//возвращает приоритет операнда
int Dominate(char operand);

//выводит текущий стек элементов в консоль
void ShowPostFix(vector<element> PostFixVector);

//выводит в консоль стек операторов
void ShowOpers (stack<char> CurrentOperand);

//преобразует строку с инфиксным числовым выражением
//в постфиксный вектор элементов
vector<element> InFixStirng_to_PostFixVector(string Str);

//Сортирует полученный знак операции в стек операций или в вектор записи
void SortOperations(char Oper, stack<char> &CurrentOperand, vector<element> &PostFixVector);

//возвращает результат выражения, поданного в виде
//постфиксного вектора элементов
int CalculatePostFixVector(vector<element>);

int main()
{
//Часть 1. Преобразование инфиксной в постфиксную с занесением в результирующий стек

  vector<element> PostFixVector; //инициализация вектора для формирования постфиксной записи
  PostFixVector.clear();
  string InFixNote; //строка для записи инфикского выражения

  cin>>InFixNote;
  PostFixVector=InFixStirng_to_PostFixVector(InFixNote);

//Часть 2. Вычислитель постфиксных выражений

  cout<<CalculatePostFixVector(PostFixVector);

  return 0;
}

//преобразует строку с инфиксным числовым выражением
//в постфиксный вектор элементов
vector<element> InFixStirng_to_PostFixVector(string Str)
{
  vector<element> PostFixVector;
  stack<char> CurrentOperand; //стек для хранения текущих операндов
  string CurrNum="0"; //для считывания двухзначных и более чисел
  element CurrElem; //текущий элемент для вставки
  for(int i=0;i<Str.size();i++)
  {
    CurrElem.type ='0';
    CurrElem.data = -2;
    if( isdigit(Str[i]) == 0) //если символ не цифра
    {
    //запись созревшего числа в стек
      if (i !=0 && CurrNum != "0") //и это не первый символ, и число не наращивается
      {
        CurrElem.data =atoi(CurrNum.c_str());
        CurrElem.type = 'N';
        PostFixVector.push_back(CurrElem); //записываем число в стек постфиксной записи
        CurrNum = "0";
      }
      //формирование стека операций
      SortOperations(Str[i], CurrentOperand, PostFixVector);
    }
    else
    {
      CurrNum.push_back(Str[i]); //иначе это цифра и запишем ее в буфер будущего числа, пока не встретится операция
    }
      //отладочный вывод
  //    cout<<i<<") Data: "<<CurrElem.data<<" Type: "<<CurrElem.type<<endl;
  //    cout<<"Out: ";
  //    ShowPostFix(PostFixVector);
  //    cout<<"Opers: ";
  //    ShowOpers(CurrentOperand);
  //    cout<<endl;
  }

    //костыль, для корректного считывания последнего операнда он не зайдет в начальный перевод
    //поэтому последний досчитаем тут
  if (CurrNum !="0")
  {
    CurrElem.data =atoi(CurrNum.c_str());
    CurrElem.type = 'N';
    PostFixVector.push_back(CurrElem);
  }
  while(!CurrentOperand.empty())// пока есть операнды
  {
    CurrElem.type=CurrentOperand.top();
    CurrElem.data = -1;
    PostFixVector.push_back(CurrElem);//выталкиваем операнды в стек
    CurrentOperand.pop(); //удаляем операнд из стека операндов
  }
  return PostFixVector;
}

//Сортирует полученный знак операции в стек операций или в вектор записи
void SortOperations(char Oper, stack<char> &CurrentOperand, vector<element> &PostFixVector)
{
  element CurrElem; //текущий элемент для вставки
  switch (Oper)
  {
  case '(': //если открывающая скобка - загоняем в стек операндов
      CurrentOperand.push('(');
      break;

  case ')': //если ЗАкрывающая скобка - выталкиваем операнды в PostFixVector пока не появится ОТкрывающая
      while ( CurrentOperand.top() != '(')
      {
        CurrElem.type = CurrentOperand.top();
        CurrElem.data = -1;
        PostFixVector.push_back(CurrElem);//выталкиваем операнды в стек
        CurrentOperand.pop(); //удаляем операнд из стека операндов
      }
      CurrentOperand.pop(); //удаляем открывающую скобку из стека
      break;
  case'+':
  case'-':
  case'*':
  case'/':
  {
    if (CurrentOperand.size() == 0) //для первого операнда
    {
      CurrentOperand.push(Oper);
    }
    else
    {
      while (Dominate(Oper) <= Dominate(CurrentOperand.top()) ) //пока приоритет текущего операнда меньше вершины стекового
      {
        CurrElem.type=CurrentOperand.top();
        CurrElem.data = -1;
        PostFixVector.push_back(CurrElem);//выталкиваем операнды в стек
        CurrentOperand.pop(); //удаляем операнд из стека операндов
        //если стек операндов остался после этого пустым, прерываем цикл
        if (CurrentOperand.size() == 0) break;
      }
      //когда приоритет текущего равен или ниже
      CurrentOperand.push(Oper);//записываем текущий операнд в стек операндов
    }
    break;
  }
  default: //если это неучтенное значение
    cout<<"Unknown char"<<endl;
    cout<<"Curr char: "<<Oper<<endl;
  }
}

//возвращает результат выражения, поданного в виде
//постфиксного вектора элементов
int CalculatePostFixVector(vector<element> PostFixVector)
{
  int operand1=0;
  int operand2=0;
  element CurrElem; //текущий элемент для вставки
  stack<element> Buffer; //стек хранения промежуточных вычислений
  while( PostFixVector.size() != 0 )
  {
    CurrElem =PostFixVector[0]; //снимаем первый элемент вектора
    PostFixVector.erase( PostFixVector.begin() ); //сразу удаляем его
    if (CurrElem.type =='N') //если это число
    {
      Buffer.push(CurrElem);
    }
    else //если оператор
    {
      operand1 = Buffer.top().data; //извлекаем 2 ближайших числа из стека
      Buffer.pop();
      operand2 = Buffer.top().data;
      Buffer.pop();

      switch (CurrElem.type)
      {
      case '+':
          CurrElem.data= operand2 + operand1;
          CurrElem.type='N';
          break;

      case '-':
          CurrElem.data= operand2 - operand1;
          CurrElem.type='N';
          break;

      case '*':
          CurrElem.data= operand2 * operand1;
          CurrElem.type='N';
          break;

      case '/':
          CurrElem.data= operand2 / operand1;
          CurrElem.type='N';
          break;
      default:
          cout<<"Smth wrong";
          break;
      }
      Buffer.push(CurrElem); //записываем результат обратно в стек
    }
  }
  //cout<<Buffer.top().data;
  return Buffer.top().data;
}

//возвращает приоритет операнда
int Dominate(char operand)
{
  switch(operand)
  {
    case '*':
    case '/':
      return 3;

    case '-':
    case '+':
      return 2;
    case '(':
    case ')':
      return 1;
    default:
      cout<<"Dominate!";
      return 0;
  }
}

//выводит текущий стек элементов в консоль
void ShowPostFix(vector<element> PostFixVector)
{
    for(int i = 0; i < PostFixVector.size(); i++)
    {
      if (PostFixVector[i].type == 'N')
      {
        cout<<PostFixVector[i].data<<" ";
      }
      else
      {
        cout<<PostFixVector[i].type<<" ";
      }
    }
    //cout<<" >>";
    cout<<endl;
}

//выводит в консоль стек операторов
void ShowOpers (stack<char>CurrentOperand)
{
    stack<char> ShowStack; //копия входного стака для вывода
    ShowStack=CurrentOperand;
    cout<<"<< ";
    while(ShowStack.size() !=0)
    {
      cout<<ShowStack.top()<<" ";
      ShowStack.pop();
    }
    cout<<endl;
}

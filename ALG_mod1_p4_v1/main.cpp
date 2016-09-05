//Реализовать очередь с динамически зацикленным буфером
#include <iostream>
#include <assert.h>

#define START_BUFFER_SIZE 4

using namespace std;

//интерфейс АСД "Очередь", реализация на массиве
class CQueue
{
  public:
    CQueue (int);
    ~CQueue() {delete[] buffer;}

    //добавление и извлечение элемента
    void Enqueue (int a);
    int Dequeue();

    //проверка на пустоту
    bool IsEmpty() const {return realSize == 0;}

    //увеличение буфера при превышении
    void grow();

    void Show();
  private:
    int* buffer; //хранимые данные
    int buffersize; //размер буфера
    int realSize; //текущее количество элементов в массиве
    int queueSize; //текущее количество элементов в ОЧЕРЕДИ
    int head;//указывает на первый элемент очереди
    int tail; //указывает на последний элемент очереди
};

CQueue::CQueue (int size):
  buffersize (size),
  head (0),
  tail (0),
  realSize (0),
  queueSize (0)
{
  buffer = new int[buffersize]; //создание буфера
  for(int i = head; i < buffersize; i++ )
      buffer[i]=0;
  //cout<<"Current buffer: "<<buffersize<<endl;
}

//добавление элемента (PushBack*)
void CQueue::Enqueue(int a)
{
    realSize++;
    queueSize++; //прибавляем счетчик элементов в очереди
    if (queueSize == buffersize)
    {
      grow();
    }
  //assert( realSize < buffersize && buffer != 0);
    buffer[tail] = a;
    tail =  (tail+1)% buffersize ;


}

//извлечение элемента (PopFront*)
int CQueue::Dequeue()
{
  if (queueSize == 0) return -1;
  queueSize--; //сокращаем количество реальных элементов в очереди, чтобы адрес хвоста остался тем же
  int result = buffer[head];
  head = (head+1)% buffersize; //двигаем голову на 1 вперед
  return result;
}

void CQueue::grow()
{
  int newBufferSize = max( buffersize * 2, START_BUFFER_SIZE );
  int* newBuffer = new int[newBufferSize];

  for(int i = head; i < newBufferSize; i++ )
      newBuffer[i]=0;

  int newCnt=0;
  for (int i = head; i < buffersize; i++ ) //запись куска от головы до границы прошлого buffer
  {
      newBuffer[newCnt] = buffer[i];
      newCnt++;
  }
  if (tail != buffersize-1)//если есть кусочек хвоста сначала
  {
    for( int i = 0; i < tail; ++i )// запись перецикленного куска, когда tail перед head в массиве
    {
      newBuffer[newCnt] = buffer[i];
      newCnt++;
    }
  }
  head =0; //голову в начало нового буфера
  tail =buffersize-1; //хвост конец старого
  delete[] buffer; //стираем старый
  buffer = newBuffer; //заправляем новый
  buffersize = newBufferSize;
  //cout<<"Buffer was increaced by "<<newBufferSize<<endl;
}

void CQueue::Show()
{
   for(int i=0;i<buffersize;i++)
   {
     cout<<i+1<<") "<<buffer[i]<<" ";
     if (head == i) cout<<" head ";
     //else cout<<endl;
     if (tail == i+1) cout<<" tail ";
     cout<<endl;
   }
}

int main()
{
  int command_cnt=0;
  cin>>command_cnt;
  bool IsAllRight = true;
  CQueue QueueCurr (START_BUFFER_SIZE);//создание очереди на 1 элемент

  int Curr_Command=0;
  int Curr_Data=0;
  for (int i=0;i<command_cnt;i++)
  {
    cin>>Curr_Command>>Curr_Data;
    //cout<<"Comm: "<<Curr_Command<<" Data: "<<Curr_Data<<endl;
    switch (Curr_Command)
    {
    case 2://pop front извлечение из начала (head)
          if (QueueCurr.Dequeue() == Curr_Data) break; // запросили дату из head - все ок
          else
          {
            //cout<<"[error] Wrong Data."; //вызываемая дата не совпала -косяк
            //IsAllRight = false;
            cout<<"NO";
            return 0;
            break;
          }

    case 3://push_back добавление элемента в конец (tail)
        QueueCurr.Enqueue(Curr_Data);
        break;

    default: {cout<<"NO";}
    }
    QueueCurr.Show();
//    if (IsAllRight) cout<<"YES ";
//    else cout<<"NO ";
  }
  cout<<"YES";
  return 0;
}

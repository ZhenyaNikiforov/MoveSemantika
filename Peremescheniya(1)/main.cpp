/*- Задание -1 (перемещение объектов) -*/
#include <iostream>
#include <vector>
using namespace std;

template <typename O>
void move_vectors(vector<O> &one, vector<O> &two) // перекидка векторов местами
{
  two = move(one);
  return;
}

int main()
{
  vector<string> one = {"test_string1", "test_string2"};
  vector<string> two;
  move_vectors(one, two); // меняем местами содержимое векторов

  if (one.size() == 0) // проверяем, что осталось в первом векторе
  {
    cout << "1 pustoj" << endl;
  };

  for (int i = 0; i < two.size(); ++i) // смотрим, что во втором векторе;
  {
    cout << two[i] << " ";
  }
  cout << endl;

  return 0;
}
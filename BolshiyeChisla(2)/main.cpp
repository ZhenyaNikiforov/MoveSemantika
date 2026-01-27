/*- Большие числа (задание -2) -*/

#include <iostream>
#include <vector>
using namespace std;

class big_integer
{
public:
  void add(vector<int> &lineOne, vector<int> &lineTwo)
  {
    this->acc.clear(); // очищаем накопитель

    vector<int> longLine = {};  // более длинная строка
    vector<int> shortLine = {}; // более короткая строка

    if (lineOne.size() > lineTwo.size()) // если первая строка длиннее второй
    {
      longLine = move(lineOne);  // длинная строка это первая
      shortLine = move(lineTwo); // короткая строка это вторая
    }
    else // если вторая строка длиннее первой или такая же
    {
      longLine = move(lineTwo);  // длинная это вторая
      shortLine = move(lineOne); // короткая это первая
    }
    int transfer = 0;                              // перенос в старший разряд (изначально 0)
    int j = shortLine.size() - 1;                  // конец короткой строки
    for (int i = longLine.size() - 1; i > -1; --i) // обходим длинную строку с конца
    {
      if (j > -1) // если короткая строка не кончилась
      {
        int res = longLine[i] + shortLine[j] + transfer;
        if (res > 9)
        {
          res = res - 10;
          transfer = 1;
        }
        else
        {
          transfer = 0;
        }
        this->acc.insert(this->acc.begin(), res);
        j--;
      }
      else // если короткая строка кончилась
      {
        int res = longLine[i] + transfer;
        if (res > 9)
        {
          res = res - 10;
          transfer = 1;
        }
        else
        {
          transfer = 0;
        }
        this->acc.insert(this->acc.begin(), res);
      }
    };
    if (transfer != 0) // если обе строки кончились, а перенос не 0
    {
      this->acc.insert(this->acc.begin(), transfer);
    }
    return;
  };
  void mul(vector<int> &line, int number)
  {
    if (number > 9)
    {
      cout << ">9!" << endl;
      return;
    };
    this->acc.clear();
    int transfer = 0;
    for (int i = line.size() - 1; i > -1; i--)
    {
      int res = line[i] * number + transfer;
      if (res > 9)
      {
        int result = res % 10;
        transfer = (res - result) / 10;
        this->acc.insert(this->acc.begin(), result);
      }
      else
      {
        transfer = 0;
        this->acc.insert(this->acc.begin(), res);
      }
    };
    if (transfer != 0)
    {
      this->acc.insert(this->acc.begin(), transfer);
    };
    return;
  };

  big_integer &operator=(big_integer &&other) noexcept // перемещающий оператор присваивания
  {
    if (this != &other)
    {
      this->acc.clear();
      this->acc = move(other.acc);
    }
    return *this;
  };

  void show() // демонстрация накопителя
  {
    for (int i = 0; i < this->acc.size(); ++i)
    {
      cout << this->acc[i];
    }
    cout << endl;
    return;
  }

private:
  vector<int> acc = {};
};

int main()
{
  big_integer BI;
  BI.show();

  vector<int> sl1 = {2};
  vector<int> sl2 = {5};
  BI.add(sl1, sl2);
  BI.show();

  sl1 = {9};
  sl2 = {9};
  BI.add(sl1, sl2);
  BI.show();

  sl1 = {9, 9};
  sl2 = {4};
  BI.add(sl1, sl2);
  BI.show();

  sl1 = {9, 9};
  sl2 = {9, 9};
  BI.add(sl1, sl2);
  BI.show();

  sl1 = {5};
  int m = 2;
  BI.mul(sl1, m);
  BI.show();

  sl1 = {5};
  m = 5;
  BI.mul(sl1, m);
  BI.show();

  sl1 = {2, 5};
  m = 5;
  BI.mul(sl1, m);
  BI.show();

  big_integer BI2;
  cout << "BI2 do: ";
  BI2.show();

  BI2 = move(BI);

  cout << "BI2 posle: ";
  BI2.show();

  cout << "BI posle: ";
  BI.show();

  return 0;
};
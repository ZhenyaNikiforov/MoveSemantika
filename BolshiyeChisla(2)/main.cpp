/*- Большие числа (задание -2) -*/

#include <iostream>
#include <string>
using namespace std;

class big_integer
{
public:
  big_integer(string line) // обычный конструктор
  {
    this->acc = move(line);
  };

  big_integer(big_integer &&other) noexcept // перемещающий конструктор
  {
    this->acc = move(other.acc);
  }

  /*...деструкторов здесь нет, поскольку строка (std::string) очищает память автоматически*/

  big_integer operator+(big_integer &other)
  {
    string otherNumber = other.show();
    int maxSize = 0;                           //-наибольший размер
    if (this->acc.size() > otherNumber.size()) // узнаём, какой размер длиннее
    {
      maxSize = this->acc.size();
    }
    else
    {
      maxSize = otherNumber.size();
    };

    int countFirstLine = this->acc.size() - 1;    // показывает на последний элемент нашего накопителя
    int countSecondLine = otherNumber.size() - 1; // показывает на последний элемент другого накопителя
    string result = "";                           // результирующая строка
    int transfer = 0;                             // перенос в старший разряд

    for (int i = 0; i < maxSize; ++i) // обходим размер наидлиннейшей из строк
    {
      int firstTerm = 0;
      int secondTerm = 0;
      if (countFirstLine > -1)
      {
        firstTerm = this->acc[countFirstLine] - '0';
      }
      else
      {
        firstTerm = 0;
      };
      if (countSecondLine > -1)
      {
        secondTerm = otherNumber[countSecondLine] - '0';
      }
      else
      {
        secondTerm = 0;
      }
      int res = firstTerm + secondTerm + transfer;
      if (res < 10)
      {
        transfer = 0;
      }
      else
      {
        transfer = 1;
        res -= 10;
      }
      result.insert(result.begin(), res + '0');
      countFirstLine--;
      countSecondLine--;
    };
    if (transfer != 0)
    {
      result.insert(result.begin(), transfer + '0');
    };
    return big_integer(result);
  };

  big_integer operator*(int factor) const
  {
    if (factor > 9)
    {
      cout << "Unknow factor!" << endl;
      return big_integer("0");
    };

    int lineSize = this->acc.size();
    int transfer = 0;
    string result = "";

    for (int i = lineSize - 1; i > -1; i--)
    {
      int partMultiplicand = this->acc[i] - '0';
      int res = partMultiplicand * factor + transfer;
      if (res < 10)
      {
        transfer = 0;
        result.insert(result.begin(), res + '0');
      }
      else
      {
        int res2 = res % 10;
        result.insert(result.begin(), res2 + '0');
        transfer = (res - res2) / 10;
      };
    };
    if (transfer != 0)
    {
      result.insert(result.begin(), transfer + '0');
    };
    return big_integer(result);
  };

  big_integer &operator=(big_integer &&other) noexcept // перемещающий оператор присваивания
  {
    if (this != &other)
    {
      this->acc.clear();
      this->acc = move(other.acc);
    }
    return *this;
  }

  string show()
  {
    return this->acc;
  }

private:
  string acc = "";
};

ostream &operator<<(ostream &out, big_integer &b)
{
  out << b.show();
  return out;
}

int main()
{
  auto number1 = big_integer("114575");
  auto number2 = big_integer("78524");
  auto result = number1 + number2;
  cout << result << endl;

  auto number3 = big_integer("25");
  auto result2 = number3 * 5;
  cout << result2 << endl;

  result = move(result2);
  cout << result << endl;

  big_integer nmb1 = big_integer("1234567890");
  cout << "nmb1 do: " << nmb1 << endl;

  big_integer rslt = std::move(nmb1);
  cout << "rslt : " << rslt << endl;

  cout << "nmb1 posle: " << nmb1 << endl;

  return 0;
};
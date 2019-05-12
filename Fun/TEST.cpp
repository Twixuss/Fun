#include <iostream>
struct Account
{
   int id;
   Account()
   {
      this->id = -1;
   }
   Account(int _id)
   {
      this->id = _id;
   }
   Account(const Account& other)
   {
      this->id = other.id;
   }
   Account& operator=(const Account& other)
   {
      this->id = other.id;
      return *this;
   }
};
struct Vector
{
   Account* arr;
   unsigned count;
   Vector(unsigned size)
   {
      arr = new Account[size];
      count = size;
   }
   Account& Add(const Account& item)
   {
      Account* newPlace = new Account[count + 1];
      for (int i = 0;i < count;i++)
      {
         newPlace[i] = arr[i];
      }
      delete[] arr;
      newPlace[count] = item;
      arr = newPlace;
      return arr[count++];
   }
   Account& operator[](unsigned i)
   {
      if (i < 0 || i >= count)
      {
         __debugbreak();
      }
      return arr[i];
   }
   ~Vector()
   {
      delete[] arr;
   }
};
int main()
{
   Vector vec(2);
   vec[0].id = 10;
   vec[1].id = 30;
   vec.Add( Account(4) ).id = 15;

   std::cout << vec[0].id << '\n';
   std::cout << vec[1].id << '\n';
   std::cout << vec[2].id << '\n';

   system("pause");

}
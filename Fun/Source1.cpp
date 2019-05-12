#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <atomic>
#include <vector>
#include <random>
#include <filesystem>
using namespace std;
struct Counter
{
   float delta;
   float totalTime = 0.f;
   int totalCounts = 0;
   Counter()
   {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);
      ticksOld = currentTime.QuadPart;
   }
   void Update()
   {
      LARGE_INTEGER currentTime;
      QueryPerformanceCounter(&currentTime);

      UINT64 tickCount = currentTime.QuadPart - ticksOld;
      ticksOld = currentTime.QuadPart;

      //if (tickCount < 0LL) {
      //    tickCount = 0LL;
      //}

      LARGE_INTEGER frequencyCount;
      QueryPerformanceFrequency(&frequencyCount);
      auto countsPerSecond = frequencyCount.QuadPart;
      delta = (float)tickCount / countsPerSecond;
      totalTime += delta;
      totalCounts++;
   }
private:
   UINT64 ticksOld;
};

#if 0
namespace multi
{
   thread *t = nullptr;
   mutex mtx;
   atomic_int v;
#define SLEEP_AFTER_UNLOCK_US 25
   void physics_part1()
   {
      while (1)
      {
         mtx.lock();
         this_thread::sleep_for(chrono::milliseconds(3 + rand() % 5));
         //v.fetch_add(1);
         mtx.unlock();
         this_thread::sleep_for(chrono::microseconds(SLEEP_AFTER_UNLOCK_US));
      }
   }
   void physics_part2()
   {
      this_thread::sleep_for(chrono::milliseconds(3 + rand() % 5));
      //v.fetch_add(2);
   }
   void draw()
   {
      this_thread::sleep_for(chrono::milliseconds(6));
      //v.fetch_sub(3);
   }
   void run()
   {
      // init
      t = new thread(physics_part1);
      int ticks = 0;
      float avgDelta = 0;
      while (1)
      {
         mtx.lock();
         Counter t;
         physics_part2();
         draw();
         t.Update();
         avgDelta += t.delta;
         ticks++;
         if (ticks & 0x10)
         {
            ticks = 0;
            SetConsoleTitle(
               //to_string(v.load())
               //.append(" - Framerate: ")
               string(" - Framerate: ")
               .append(to_string(1.0f / (avgDelta / 0x10)))
               .c_str());
            avgDelta = 0;
         }
         mtx.unlock();
         this_thread::sleep_for(chrono::microseconds(SLEEP_AFTER_UNLOCK_US));
      }
      t->join();
      delete t;
   }
}
namespace single
{
   void physics_part1()
   {
      this_thread::sleep_for(chrono::milliseconds(3 + rand() % 5));
   }
   void physics_part2()
   {
      this_thread::sleep_for(chrono::milliseconds(3 + rand() % 5));
   }
   void draw()
   {
      this_thread::sleep_for(chrono::milliseconds(6));
   }
   void run()
   {
      // init
      int ticks = 0;
      float avgDelta = 0;
      while (1)
      {
         Counter t;
         physics_part1();
         physics_part2();
         draw();
         t.Update();
         avgDelta += t.delta;
         ticks++;
         if (ticks & 0x10)
         {
            ticks = 0;
            SetConsoleTitle(
               string(" - Framerate: ")
               .append(to_string(1.0f / (avgDelta / 0x10)))
               .c_str());
            avgDelta = 0;
         }
      }
   }
}
int main()
{
   multi::run();
   //single::run();
}
#endif
#if 0
unsigned constructs = 0, copies = 0, moves = 0, destructs = 0;
struct MyStruct
{
   MyStruct()
   {
      constructs++;
   }
   MyStruct(const MyStruct &other)
   {
      copies++;
   }
   MyStruct(const MyStruct &&other)
   {
      cout << "move" << endl;
   }
   ~MyStruct()
   {
      destructs++;
   }
};
int main()
{
   //MyStruct a;
   //MyStruct b = move(a);
   vector<MyStruct> v;
   //v.reserve(1024);
   cout << "capacity: " << v.capacity() << endl;
   for (int i = 0;i < 1024;i++)
   {
      v.emplace_back();
   }
   cout << "constructs: " << constructs << " - copies: " << copies << " - moves: " << moves << " - destructs: " << destructs << endl;
   constructs = 0;
   copies = 0;
   moves = 0;
   destructs = 0;
   v.clear();
   cout << "capacity: " << v.capacity() << endl;
   for (int i = 0;i < 1024;i++)
   {
      v.emplace_back();
   }
   cout << "constructs: " << constructs << " - copies: " << copies << " - moves: " << moves << " - destructs: " << destructs << endl;
   constructs = 0;
   copies = 0;
   moves = 0;
   destructs = 0;
   system("PAUSE");
}
#endif
#if 0
#define _declMethod(x) virtual void method ## x() = 0;
#define declMethod(x) _declMethod(x)
struct __declspec(novtable) Base
{
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
   declMethod(__LINE__);
};
struct Derived1 : public Base
{
   int x;
   Derived1()
   {
      x = rand() + 1;
   }
   void method169() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method170() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method171() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method172() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method173() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method174() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method175() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method176() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method177() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method178() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method179() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method180() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method181() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method182() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method183() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method184() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method185() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method186() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method187() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method188() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method189() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method190() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method191() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method192() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method193() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method194() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method195() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method196() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method197() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method198() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method199() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method200() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
};
struct Derived2 : public Base
{
   int x;
   Derived2()
   {
      x = rand();
   }
   void method169() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method170() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method171() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method172() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method173() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method174() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method175() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method176() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method177() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method178() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method179() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method180() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method181() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method182() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method183() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method184() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method185() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method186() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method187() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method188() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method189() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method190() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method191() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method192() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method193() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method194() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method195() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method196() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method197() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method198() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method199() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
   void method200() override
   {
      std::cout << (rand() + __LINE__ + x);
   }
};
int main()
{
   constexpr int count = 1;
   auto arr = rand() & 1 ? (Base*)new Derived1[count] : (Base*)new Derived2[count];
   system("PAUSE");
   for (int i = 0;i < count;i++)
   {
      arr[i].method169();
      arr[i].method170();
      arr[i].method171();
      arr[i].method172();
      arr[i].method173();
      arr[i].method174();
      arr[i].method175();
      arr[i].method176();
      arr[i].method177();
      arr[i].method178();
      arr[i].method179();
      arr[i].method180();
      arr[i].method181();
      arr[i].method182();
      arr[i].method183();
      arr[i].method184();
      arr[i].method185();
      arr[i].method186();
      arr[i].method187();
      arr[i].method188();
      arr[i].method189();
      arr[i].method190();
      arr[i].method191();
      arr[i].method192();
      arr[i].method193();
      arr[i].method194();
      arr[i].method195();
      arr[i].method196();
      arr[i].method197();
      arr[i].method198();
      arr[i].method199();
      arr[i].method200();
   }
   delete arr;
}
#endif
#if 0
int main()
{
#define size 65536
#define char WCHAR
#define cout wcout
   //#define char char
   //#define cout cout
   //#define rand rand()
#define rand mt()
   char str[size]{};
   mt19937 mt(time(0));
   uniform_int_distribution<int> dist(numeric_limits<char>::min(), numeric_limits<char>::max());
   char c;
   Counter cn;
   while (1)
   {
      int iters = 1 << 15;
      cn.Update();
      while (iters--)
      {
         c = rand;
         for (int i = 0;i < size - 1;i++)
         {
            str[i] = c + i;
         }
      }
      cn.Update();
      cout << cn.delta << ' ' << (short)str[c] << endl;
   }
   system("pause");
}
#endif
#if 0
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
   switch (msg)
   {
   case WM_CHAR:
      wcout << (wchar_t)wp;
      if (wcout.bad())
      {
         MessageBox(0, 0, 0, 0);
      }
      break;
   }
   return DefWindowProc(hwnd, msg, wp, lp);
}
int WINAPI WinMain(HINSTANCE h, HINSTANCE, LPSTR, int)
{
   AllocConsole();
#pragma warning(disable:4996)
   freopen("CONOUT$", "w", stdout);
   WNDCLASS wc{ 0 };
   wc.hInstance = h;
   wc.lpfnWndProc = WndProc;
   wc.lpszClassName = "c";
   wc.style = CS_OWNDC;
   if (!RegisterClass(&wc))
   {
      cout << "register" << endl;
   }
   HWND hwnd = CreateWindow("c", "W", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, 0, 0, h, 0);
   ShowWindow(hwnd, SW_SHOW);
   while (1)
   {
      MSG msg;
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }
}
#endif
#if 0
int main()
{
   BYTE arr1[256];
   BYTE arr2[256];
   constexpr int itersCount = 1 << 20;
   int iters = itersCount;
   Counter c;
   while (iters--)
   {
      for (int i = 0;i < 256;i++)
      {
         arr1[i] = arr2[i];
         arr2[i] = rand();
      }
   }
   c.Update();
   cout << c.delta << endl;
   iters = itersCount;
   c.Update();
   while (iters--)
   {
      memcpy(arr1, arr2, 256);
      for (int i = 0;i < 256;i++)
      {
         arr2[i] = rand();
      }
   }
   c.Update();
   cout << c.delta << endl;
   system("pause");
}
#endif
#if 0
template<class Scalar>
Scalar Pow(Scalar x, int p)
{
   int result = x;
   for (int i = 1;i < p;i++)
   {
      result *= x;
   }
   return result;
}
int Factorial(int x)
{
   if (x < 2)
      return 1;
   return x * Factorial(x - 1);
}
float Sin(float x, int precision)
{
   float result = x;
   for (int n = 1;n < precision + 1; n++)
   {
      result += Pow(-1.0f, n) / Factorial(2 * n + 1) * Pow(x, 2 * n + 1);
   }
   return result;
}
int main()
{
   cout << Pow(2, 10) << endl;
   cout << Sin(3.14159, 10) << endl;
   system("pause");
}
#endif
/*for xy vs for yx*/#if 0
int main()
{
   constexpr auto w = 5000, h = 5000;
   constexpr auto n = w * h * 4;
   Counter c;
   float sum = 0;
   {
      cout << "Initialization... ";
      c.Update();
      auto a = new float[n];
      for (int i = 0;i < n;i++)
         a[i] = (rand() - RAND_MAX / 2) * 2.5f;
      c.Update();
      cout << c.delta << "\nSummation... ";
      c.Update();
      for (int x = 0;x < w;x++)
         for (int y = 0;y < h;y++)
         {
            int i = y * 1024 + x;
            sum += a[i];
         }
      c.Update();
      cout << c.delta << '\n';
      delete[] a;
   }
   {
      c.Update();
      cout << "Initialization... ";
      auto a = new float[n];
      for (int i = 0;i < n;i++)
         a[i] = rand() * 2.5f;
      c.Update();
      cout << c.delta << "\nSummation... ";
      c.Update();
      for (int y = 0;y < h;y++)
         for (int x = 0;x < w;x++)
         {
            int i = y * 1024 + x;
            sum += a[i];
         }
      c.Update();
      cout << c.delta << '\n';
      delete[] a;
   }
   system("pause");
   return sum;
}
#endif
/*MEM ACCESS*/#if 0
int main()
{
   int sum = 0;
   Counter c;
   constexpr int size = 30000000;
   {
      c.Update();
      cout << "Initialization... ";
      c.Update();
      auto arr = new int[size];
      for (auto i = arr; i < arr + size;i++)
      {
         *i = rand();
      }
      c.Update();
      cout << c.delta << "\nExecution... ";
      c.Update();
      for (int i = 0;i < size;i++)
      {
         arr[i] += arr[(i + 1) % size];
         sum += arr[i];
      }
      c.Update();
      cout << c.delta << '\n';
      c.Update();
   }
   {
      c.Update();
      cout << "Initialization... ";
      c.Update();
      auto arr = new int*[size];
      for (auto i = 0; i < size;i++)
      {
         arr[i] = new int;
         *arr[i] = rand();
      }
      c.Update();
      cout << c.delta << "\nExecution... ";
      c.Update();
      for (int i = 0;i < size;i++)
      {
         *arr[i] += *arr[(i + 1) % size];
         sum += *arr[i];
      }
      c.Update();
      cout << c.delta << '\n';
      c.Update();
   }
   system("pause");
   return sum;
}
#endif
#if 1
int main()
{
   float g = 9.8, y = 0, vy = 0;
   float t = 0, timestep = 0.0001;
   while (1)
   {
      t += timestep;
      vy += g * timestep * 0.5;
      y += vy * timestep;
      cout << "Y: " << y << ". T * T * G: " << t * t * g << '\n';
   }
}
#endif
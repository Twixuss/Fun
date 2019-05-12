#include <iostream>
using namespace std;
template<class T>
struct node
{
	T data;
	node* next = nullptr;
	node* proshl = nullptr;
	node() = default;
	node(T data) : data(data)
	{
	}
	node* push_back(T t)
	{
		if (next)
			return next->push_back(t);
		next = new node(t);
		next->proshl = this;
		return next;
	}
	int size()
	{
		if (next)
			return 1 + next->size();
		return 1;
	}
	T get(unsigned i)
	{
		if (i == 0)
			return data;
		return next->get(i - 1);
	}
	T pop_back()
	{
		if (!next)
			return 0;
		if (next->next)
			return next->pop_back();
		T copy = next->data;
		delete next;
		next = nullptr;
		return copy;
	}
	bool remove(unsigned i) {
		if (i >= size())
			return false;
		if (i)
			next->remove(i - 1);
		else {
			if (next)
				next->proshl = proshl;
			proshl->next = next;
			delete this;
		}
		return true;
	}
	void delete_back()
	{
		if (!next)
			return;
		if (next->next)
		{
			next->delete_back();
			return;
		}
		delete next;
		next = nullptr;
	}
	T operator [](int i) {
		return get(i);
	}
	void free()
	{
		while (next)
			delete_back();
	}
};
int main()
{
   _CrtMemState _ms;
   _CrtMemCheckpoint( &_ms );
   {
      node<int> head( 5 );
      head.push_back( 10 );
      head.push_back( 15 );
      head.push_back( 20 );

      cout << "list:\n";
	  int Size = head.size();
      for ( int i = 0; i < Size; i++ )
         cout << head.get( i ) << '\n';

      cout << "delete:\n";
	  head.remove(1);

      cout << "list:\n";
	  Size = head.size();
	  for ( int i = 0; i < Size; i++ )
         cout << head.get( i ) << '\n';
	  head.free();
   }
   
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
   _CrtMemDumpAllObjectsSince( &_ms );
   system( "pause" );
}
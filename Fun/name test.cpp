#include <iostream>
using namespace std;
template<class T>
struct node
{
   T data;
   node* next = nullptr;
   node( T data ) : data( data )
   {
   }
   node* push_back( T t )
   {
      if ( next )
         return next->push_back( t );
      return next = new node( t );
   }
   unsigned size()
   {
      if ( next )
         return 1 + next->size();
      return 1;
   }
   T get( unsigned i )
   {
      if ( i == 0 )
         return data;
      return next->get( i - 1 );
   }
   T pop_back()
   {
      if ( !next )
         return 0; // если нечего поп бэчить
      if ( next->next )// если есть чего поп бэчить
         return next->pop_back();
      T copy = next->data;
      delete next;
      next = nullptr;
      return copy;
   }
   void delete_back()
   {
      if ( !next )
         return;
      if ( next->next )
      {
         next->delete_back();
         return;
      }
      delete next;
      next = nullptr;
   }
   ~node()
   {
      while ( next )
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
      for ( int i = 0; i < head.size(); i++ )
         cout << head.get( i ) << '\n';

      cout << "pop_back:\n";
      cout << head.pop_back() << '\n';

      cout << "list:\n";
      for ( int i = 0; i < head.size(); i++ )
         cout << head.get( i ) << '\n';
   }
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
   _CrtMemDumpAllObjectsSince( &_ms );
   system( "pause" );
}
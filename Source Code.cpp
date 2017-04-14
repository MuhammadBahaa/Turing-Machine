#include <iostream>
#include <cctype>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int  pos_head  ;
char acp_rej ;
int  state = 0;

int chechInput ( int no ) ;
string turing (int number_of_states , int size_of_alphabet , queue <int > Q1 , queue <char> Q2 , string tape );


int main()
{
   int number_of_states ,  size_of_alphabet , int_transition  , check_transition , flag  ;
   char c ;
   string tape , transition ;
   queue <int> Q1;
   queue <char> Q2 ;
   vector <char> alphabet ;

   check_transition = flag  =  0 ;

   cout << "Enter the number of states   :   " ;
   number_of_states = chechInput(number_of_states);

   cout << "Enter size of alphabet       :   ";
   size_of_alphabet = chechInput(size_of_alphabet);

   for ( int i = 0 ; i < size_of_alphabet ; i++)
   {
       cout << "Enter alphabet  " << i+1 << "            :   ";
       cin >> c ;
       cin.get();
       alphabet.push_back(c);

   }


   while ( check_transition == 0 )
   {

    for ( int j = 1 ; j <= number_of_states * size_of_alphabet  ; j++)
    {
       cout << "Enter transition  " << j << "          :   ";


       getline(cin , transition );

       while ( transition.length() != 13 )
       {
          cout << "Wrong input ! \n " ;
          getline(cin , transition );
       }


       int_transition = (int) transition[1] - 48 ;

       while ( int_transition > number_of_states)
       {
           cout << "Wrong input , enter state again     " << transition ;
           for ( int i = 0 ; i < 12 ; i++)
             cout << "\b" ;

            cin >> transition[1] ;
            cin.get();
            int_transition = (int) transition[1] - 48 ;
       }
       Q1.push(int_transition) ;


       while ( flag == 0)
       {
         for ( int i = 0 ; i < size_of_alphabet  ; i++ )
           {
           if ( transition[3] == alphabet[i])
             {
              flag = 1 ;
              break ;
             }
           }

           if ( flag == 0 )
           {
            cout << "Wrong input , enter alphabet again      " << transition ;
            for ( int i = 0 ; i < 10 ; i++)
              cout << "\b" ;

            cin >>  transition[3] ;
            cin.get();
           }
       }
       Q2.push(transition[3]);
       flag = 0 ;


       int_transition = (int) transition[7] - 48 ;

       while ( int_transition > number_of_states)
       {
           cout << "Wrong input , Enter state again     " << transition ;
           for ( int i = 0 ; i < 6 ; i++)
             cout << "\b" ;

            cin >>  transition[7] ;
            cin.get();
            int_transition = (int) transition[1] - 48 ;
       }
       Q1.push(int_transition) ;




       while ( flag == 0)
       {
         for ( int i = 0 ; i < size_of_alphabet  ; i++ )
           {
           if ( transition[9] == alphabet[i])
             {
              flag = 1 ;
              break ;
             }
           }

           if ( flag == 0 )
           {
            cout << "Wrong input , Enter alphabet again        " << transition ;
            for ( int i = 0 ; i < 4 ; i++)
              cout << "\b" ;

            cin >>  transition[9] ;
            cin.get();
           }
       }
       Q2.push(transition[9]);
       flag = 0 ;

     transition[11] = toupper(transition[11] );
        while ( transition[11] != 'R'  and transition[11] != 'L'  and transition[11] != 'Y' and transition[11] != 'N' )
        {
            cout << "Wrong input          " << transition ;
            for ( int i = 0 ; i < 2  ; i++)
              cout << "\b" ;

            cin >>  transition[11] ;
            cin.get();
        }
        if ( transition[11] == 'Y' or transition[11] == 'N' ) check_transition = 1 ;

        Q2.push(transition [11]);

   }
   if (check_transition == 0)
    cout << "Wrong in transition functions !, Enter a transition functions again  \n" ;
   }

   cout << "Enter tape           :             ";
   cin >> tape;
   cin.get();

   cout << "Enter head position  :             " ;

  pos_head = chechInput(pos_head) ;

  while ( pos_head > tape.length())
  {
      cout << "Wrong head position \n" ;
      pos_head = chechInput(pos_head) ;
  }

  tape =turing ( number_of_states , size_of_alphabet , Q1 , Q2 ,tape);

  cout << "Final configuration        :          "<< tape << endl;
  cout << "Head in position           :          "<< pos_head << endl;
  cout << "State                      :          ";

   if ( acp_rej == 'Y')
     cout << "Accept    ,   ";
   else if ( acp_rej == 'N')
    cout << "Reject     ,   " ;
   else
    cout << " Wrong in transition functions   ,  ";

    cout << state ;

    return 0;
}


int chechInput( int no )
{
     while (  !(cin >> no) or no < 0 )
        {
         cin.clear();
         while ( cin.get() != '\n') continue;
         cout << " Wrong input !\n";
         }
    while ( cin.get() != '\n') continue;
    return no ;
}

string turing( int number_of_states , int size_of_alphabet, queue <int > Q1 , queue <char> Q2 , string tape )
{
    int x ;
    char y ;

    for ( int i = 1 ; i <= number_of_states * size_of_alphabet ; i++ )
    {
      x = Q1.front() ;
      Q1.pop();
      y = Q2.front() ;
      Q2.pop();

      if (  state == x and tape[pos_head] == y )
      {
        x = Q1.front();
        state = x ;
        Q1.pop();
        y = Q2.front() ;
        Q2.pop();
        tape[pos_head] = y ;

        y = Q2.front() ;
        Q2.pop();

        if ( y == 'Y' )
        {
            acp_rej = 'Y' ;
            break ;
        }
        if ( y == 'N')
        {
           acp_rej = 'N' ;
           break ;
        }
        if ( y == 'R' )
            pos_head++;
        if ( y == 'L' )
           pos_head--;

      }
      else
      {
        x = Q1.front() ;
        Q1.pop();
        y = Q2.front() ;
        Q2.pop();
        y = Q2.front() ;
        Q2.pop();

      }
    }
    return tape ;
}


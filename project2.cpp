// header files
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// global constants

  // declare struct
  struct symbols{

     char name[8];
     int bonusVal;
     bool bonus;
     };

// function prototypes

void displayTitle();
int menu( symbols slotMachine[10][3], symbols potentialSymb[6] );
void populateMachine( symbols slotMachine[10][3], symbols potentialSymb[6]);
void displayConfig( symbols slotMachine[10][3] );
void returnToMenu( symbols slotMachine[10][3], symbols potentialSymb[6] );
void readExistingFile( symbols slotMachine[10][3], symbols potentialSymb[6] );
void downloadConfig( symbols slotMachine[10][3] );
void viewPosition( symbols slotMachine[10][3], symbols potentialSymb[6] );
void stringCopy( char destStr[], char sourceStr[] );
int strlen( const char str[] );
int strcmp( const char one[], const char other[] );
void spinReels( symbols slotMachine[10][3] );
void setBonus( symbols slotMachine[10][3], symbols potentialSymb[6] );

// main program

int main()
   {
    // declare variables
    symbols slotMachine[10][3] = {0};
    symbols potentialSymb[6] = {0};
    

    // display menu
    menu( slotMachine, potentialSymb );
   }

// supporting function implementations

void spinReels( symbols slotMachine[10][3] )
   {
    // declare variables
    int randNum, paylineBonus = 0;

    // indent before printing to screen
    cout << '\t';

    for( int index = 0; index != 3; index++)
       {
        // generate random number
        randNum = rand() % 6+0;

        // display symbol at that index on reel
        cout << slotMachine[randNum][index].name << '\t';

        // update payline bonus
        if( slotMachine[randNum][index].bonus )
           {
            paylineBonus = slotMachine[randNum][index].bonusVal + paylineBonus;
           }
       } 
     
     // display payline bonus total
     cout << '\t' << "Spin Bonus: " << paylineBonus << endl;
   }

void viewPosition( symbols slotMachine[10][3], symbols potentialSymb[6] )
   {
    // declare variables
    int reelNum, stopNum, bonusIndex = 0;
    bool validReelNum = false, validStopNum = false;
    char selectedSymbol[8];

        // check if a current configuration exists
    if( slotMachine[0][0].name == 0 )
       {
         // print error message
         cout << "Error: Configuration does not currently exist" << endl;
       }

    else
       {
        while( validReelNum == false )
           {
            // prompt for reel number
            cout << " Enter the reel you wish to view (1, 2 or 3): ";
            cin >> reelNum;
       
              // check for valid reel number
              if( reelNum < 1 || reelNum > 3 )
                 {
                  // print error message
                  cout << " Error: Not a valid reel number" << endl << endl;
                 }

              else
                 {
                   // set valid reel to true;
                   validReelNum = true;
                 }
           }

         while( validStopNum == false )
            {
             // prompt for stop number
             cout << " Enter the stop number that you wish to view (1-10): ";
             cin >> stopNum;

               // check for valid stop number
               if( stopNum < 1 || stopNum > 10 )
                  {
                   // print error message
                   cout << " Error: Not a valid stop number" << endl << endl;
                  }

               else
                  {
                   // set valid stop to true
                   validStopNum = true; 
                  }
             }

          // display titles
          cout << endl << '\t' << "Symbol on reel " << reelNum << " at stop number " 
               << stopNum << '\t' << "Bonus Value" << endl << endl;

          // adjust values to equal position in array
          reelNum--;
          stopNum--;

      
          // display symbol and bonus value at position
          cout << '\t' << '\t' << '\t' << slotMachine[stopNum][reelNum].name << '\t' << '\t' << '\t'<< '\t'
               << slotMachine[stopNum][reelNum].bonusVal << endl;
       }
   }

void downloadConfig( symbols slotMachine[10][3] )
   {
    // declare variables
    ofstream fout;
    char outFileName[20];
    int rowIndex = 0, colIndex = 0;

    // prompt for output file name
    cout << "Enter the name for the output file: ";
    cin >> outFileName;

    // create file name
    fout.open( outFileName );

    while( rowIndex != 10 )
       {
        fout << slotMachine[rowIndex][colIndex].name;
        
        if( colIndex == 2)
          {
           colIndex = 0;
           rowIndex++;
           fout << endl;
          }

        else
           {
            fout << '\t';
            colIndex++;
           }
        }

     // close the file
     fout.close();

    // display success message
    cout << "File Successfully Downloaded" << endl;
   }

void readExistingFile( symbols slotMachine[10][3], symbols potentialSymb[6] )
   {
    // declare variables
    ifstream fin;
    bool goodFile = false;
    char fileName[15];
    int rowIndex = 0, colIndex = 0;

  // determine symbols and bonus value for  potential symbols
    
       // open symbols file
        
         // clear the stream 
         fin.clear();

         // open symbols file
         fin.open( "symbols" );

    // upload symbols and bonus value from file
        for( int index = 0; index < 6; index++ )
           {
            fin >> potentialSymb[index].name >> potentialSymb[index].bonusVal;
            
            // set bonus bool
            if( potentialSymb[index].bonusVal == 0)
              {
               potentialSymb[index].bonus = false;
              }

            else
              {
               potentialSymb[index].bonus = true;
              }
           }
        // close file
        fin.close(); 

    // loop until valid file name
    while( goodFile == false )
       {
        // prompt for file
        cout << "Enter the name of the file you wish to open: ";
        cin >> fileName;

        // clear the stream
        fin.clear();

        // open the file
        fin.open( fileName );

        if( fin.good() )
           {
            cout << "File Opened Successfully" << endl << endl;
            goodFile = true;
           }

        else
           {
            cout << "File Not Found" << endl << endl;
           }
        }   

     // upload the data
     while( rowIndex != 10 )
        {
         fin >> slotMachine[rowIndex][colIndex].name;

         if( colIndex == 2 )
            {
             colIndex = 0;
             rowIndex++;
            }

         else
            {
             colIndex++;
            }
        }
     
     // close the file
     fin.close();

     // determine the bonus values of symbols from file
     setBonus( slotMachine, potentialSymb );

     // display success message
     cout << "File Uploaded Successfully" << endl;
   }

void displayConfig( symbols slotMachine[10][3] )
   {
    // declare variables
    int rowIndex = 0, colIndex = 0;
  
    // check for a current configuration
    if( slotMachine[0][0].name == 0)
       {
         // print error message
         cout << "Error: Configuration does not currently exist" << endl;
       }
       
    // otherwise display configuration
    else
       {
        // add a tab before the symbols
        cout << '\t';

        // print the symbols to the screen
        while( rowIndex != 10 )
           {
            cout << slotMachine[rowIndex][colIndex].name;

            if( colIndex == 2 )
               {
                colIndex = 0;
                rowIndex++;
                cout << endl << '\t';
               }

            else
               {
                cout << '\t';
                colIndex++;
               }
           }
       }         
   }

void returnToMenu( symbols slotMachine[10][3], symbols potentialSymb[6] )
   {
    // add a endline
    cout << endl;

    // hold the screen and display message
    cout << "Press ENTER To Return To The Menu";
    cin.ignore();
    cin.get();

    // return to the menu
    menu( slotMachine, potentialSymb );
   }

void stringCopy( char destStr[], char sourceStr[] )
   {
    // declare variables
    int index = 0;

    // copy string
    while( sourceStr[index] != '\0' )
       {
        destStr[index] = sourceStr[index];
        index++;
       }

    // add null character
    destStr[index] = '\0';
   }

void populateMachine( symbols slotMachine[10][3], symbols potentialSymb[6])
   {
    // declare variables
    ifstream fin;
    int randomVal, rowIndex = 0, colIndex = 0;

    // determine symbols and bonus value
    
      // open symbols file

        // clear the stream
        fin.clear();

        // open symbols file
        fin.open( "symbols" );

         // check for good file
          if( !fin.good() )
             {
              cout << "Error: File \"symbols\" could not be found" << endl;
             }

         else
            {
             // seed random number generator
             srand( time( NULL ) );

             // upload symbols and bonus value from file
             for( int index = 0; index < 6; index++ )
                {
                 fin >> potentialSymb[index].name >> potentialSymb[index].bonusVal;

                   // set bonus bool
                   if( potentialSymb[index].bonusVal == 0)
                      {
                       potentialSymb[index].bonus = false;
                      }

                   else
                     {
                      potentialSymb[index].bonus = true;
                     }
                }

             // close file
             fin.close();

             while( rowIndex != 10 )
                { 
                 // generate random number
                 randomVal = rand() % 6+0;

                 //copy random symbol to slot machine
		 stringCopy(slotMachine[rowIndex][colIndex].name, potentialSymb[randomVal].name );

                 // copy bonus value to slot machine
                 slotMachine[rowIndex][colIndex].bonusVal = potentialSymb[randomVal].bonusVal;

                 // copy bonus bool to slot machine
                 slotMachine[rowIndex][colIndex].bonus = potentialSymb[randomVal].bonus;

                 if( colIndex == 2 )
                    {
                     colIndex = 0;
                     rowIndex++;
                    }
             
                  else
                     {
                      colIndex++;
                     }
                }
              // display success message
              cout << " Machine successfully populated" << endl;
            }
   }

void displayTitle()
   {
    // display title
    cout << endl;
    cout << '\t' << '\t' << '\t' << "Slot Machine" << endl;
    cout << '\t' << '\t' << '\t' << "============" << endl << endl;
   }

int menu( symbols slotMachine[10][3], symbols potentialSymb[6] )
   {
    // declare variables
    char selection;

    // display title
    displayTitle();

    // display menu options
    cout << '\t' << "1. Populate new slot machine" << endl;
    cout << '\t' << "2. Read in existing configuration from file" << endl;
    cout << '\t' << "3. Show current configuration" << endl;
    cout << '\t' << "4. Download current configuration to file" << endl;
    cout << '\t' << "5. View symbol at specific wheel position" << endl;
    cout << '\t' << "6. Spin the reels" << endl;
    cout << '\t' << "7. Exit program" << endl << endl;


    //prompt for user selection
    cout << '\t' << "Enter selection: ";
    cin >> selection;
    cout << endl;

    // implement user selection
    switch( selection )
       {
        // check for option one
        case '1':

          // populate slot machine
          populateMachine( slotMachine, potentialSymb );

          // return to menu
          returnToMenu( slotMachine, potentialSymb );
          break;
     
        // check for option two
        case '2': 

          // upload file
          readExistingFile( slotMachine, potentialSymb );
       
          // return to menu
          returnToMenu( slotMachine, potentialSymb);
          break;

        // check for option three
        case '3':
         
          // display current configuration
          displayConfig( slotMachine);

          // return to menu
          returnToMenu( slotMachine, potentialSymb);
          break;

        // check for option four
        case '4': 
        
          // download file
          downloadConfig( slotMachine );

          // return to menu
          returnToMenu( slotMachine, potentialSymb);
          break;

        // check for option five
        case '5': 

          // display wheel position
          viewPosition( slotMachine, potentialSymb );
          
          // return to menu
          returnToMenu( slotMachine, potentialSymb );
          break;

        // check for option six
        case '6':

          // spin reels
          spinReels( slotMachine );

          // return to menu
          returnToMenu( slotMachine, potentialSymb );

        break;

        // check for option seven
        case '7':

         // end program
         return 0;
         break;

        // set default option
        default:
        
          //display error message
          cout << '\t' << "Error: Invalid Selection" << endl << endl;

        // redisplay menu
        menu( slotMachine, potentialSymb);
       }
   }

int strlen( const char str[] )
   {
    int index = 0;

    while( str[index] != '\n' )
       {
        index++;
       }
    return index;
   }
   

int strcmp( const char one[], const char other[] )
   {
    // declare variables
    int diff, index = 0;

    while( one[index] != '\n' && other[index] != '\n' )
       {
        diff = one[index] - other[index];
        
        if( diff!= 0)
          {
           return diff;
          }
  
        index++;
       }

return strlen(one) - strlen(other);
   }

void setBonus( symbols slotMachine[10][3], symbols potentialSymb[6] )
   {
    // declare variables
    int index1 = 0, index2 = 0, index3 = 0, index4 = 0;
   
    // loop through every row
    while(index1 != 10 )
       {
        // check if first char of symbol matches
        if( slotMachine[index1][index2].name[index3] == potentialSymb[index4].name[index3] )
          {
           index3++;
      
            // check if next char of symbol matches
            if( slotMachine[index1][index2].name[index3] == potentialSymb[index4].name[index3] )
               {
                // set bonus val
                slotMachine[index1][index2].bonusVal = potentialSymb[index4].bonusVal;

                // set bonus bool
                slotMachine[index1][index2].bonus = potentialSymb[index4].bonus;

                // update indexs
                index2++;
                index3 = 0;
                index4 = 0;
               }

             else
                {
                 index3 = 0;
                 index4++;
                }
    
             if( index2 == 3 )
                {
                 index2 = 0;
                 index1++;
                }
          }

        else
           {
            index4++;
           }
       }
   }












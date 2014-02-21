// $Id: ht2sp.cpp,v 1.5 1998-10-11 00:09:10-04 rl Exp $

///////////////////////////////////////////////////////////////////////////
//                                                                        /
// ht2sp.cpp                                                              /
// Substitute spaces for horizontal tabs in a text file                   /
// 1994-10-04, Rolf Lochbuehler                                           /
//                                                                        /
///////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

// Characters:
#define ASCII_HT ('\t')
#define ASCII_SP (' ')
#define ASCII_0  ('0')
#define ASCII_LINEBREAK ('\n')


void help( void );


void main ( int argc, char *argv[] )
  {
  
  int i;
  int colsPerTab;
  int col;
  int skip;
  char c;

  if( (argc < 3) || (argc > 4) )
    {
    help();
    return;
    }
  
  if( (0 == stricmp(argv[1],"/h")) || (0 == stricmp(argv[1],"-h")) )
    {
    help();
    return;
    }

  // Create input file stream
  ifstream ifs( argv[1], ios::in|ios::nocreate );
  if( !ifs )
    {
    cout << "*Ht2Sp Error* Cannot read " << argv[1] << ". File may not exist." << endl;
    return;
    }
  
  // Create output file stream
  ofstream ofs( argv[2], ios::out|ios::noreplace );
  if( !ofs )
    {
    cout << "*Ht2Sp Error* Cannot write " << argv[2] << ". File may exist already." << endl;
    return;
    }
  
  // Default number of columns per tab
  if( 3 == argc )
    colsPerTab = 8;
  else
    colsPerTab = atoi( argv[3] );
  if( colsPerTab < 1 )
    {
    cout << "*Ht2Sp Error* " << colsPerTab << " is not a valid columns-per-tab value. This value must be 1 or greater!" << endl;
    return;
    }
  
  // Read input stream and substitute spaces for tabs
  col = 1;
  skip = colsPerTab;
  while( ifs.get(c) )
    switch( c )
      {

      case ASCII_LINEBREAK :
        {
        col = 1;
        skip = colsPerTab;
        ofs.put( ASCII_LINEBREAK );
        break;
        }

      case ASCII_HT :
        {
        for( i = 1; i <= skip; ++i ) 
          ofs.put( ASCII_SP );
        col += skip;
        skip = colsPerTab - ((col % colsPerTab) - 1);
        if( 0 == (col % colsPerTab) ) 
          skip = 1;
        break;
        }

      default :
        {
        ofs.put( c );
        col += 1;
        skip = colsPerTab - ((col % colsPerTab) - 1);
        if( 0 == (col % colsPerTab) )
          skip = 1;
        // break;
        }

      }   // end switch, end while

  if( !ifs.eof() )
    {
    cout << "*Ht2Sp Error* Error while reading " << argv[1] << endl;
    return;
    }
  
  return;
  
  }   // end main()

                  

///////////////////////////////////////////////////////////////////////////
//                                                                        /
// help()                                                                 /
// Print help for user                                                    /
//                                                                        /
///////////////////////////////////////////////////////////////////////////
void help ( void )
  {
  cout << endl;
  cout << "Ht2Sp $Revision: 1.5 $, Rolf Lochbuehler <rolf@together.net>" << endl;
  cout << "Purpose:" << endl;
  cout << "  Substitute space characters for horizontal tab characters in a text file," << endl;
  cout << "  preserving column alignment" << endl;
  cout << "Usage:" << endl;
  cout << "  ht2sp [/h] [IN OUT [NUM]]" << endl;
  cout << "Arguments:" << endl;
  cout << "  (none)       Print this help info, then exit" << endl;
  cout << "  /h (or -h)   Print this help info, then exit" << endl;
  cout << "  IN           Name of input text file" << endl;
  cout << "  OUT          Name of output file" << endl;
  cout << "  NUM          Number of columns per tab (default: 8)" << endl;
  cout << "Examples:" << endl;
  cout << "  ht2sp a.txt b.txt" << endl;
  cout << "  ht2sp x.txt y.txt 6" << endl;
  cout << "Note:" << endl;
  cout << "  The number of columns per tab specified as NUM (or the default of 8 columns)" << endl;
  cout << "  should be equal to the number of columns per tab used when the file was" << endl;
  cout << "  formatted originally. Otherwise ht2sp may disturb the column alignment." << endl;
  return;
  }


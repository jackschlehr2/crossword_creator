/*
 * This program is for lab8 of CSE20311.
 *
 * This is the main function for the project. In this file ther is one function main(),
 * in which everything is run. The program takes a set of words from the user either 
 * the user entering them from the keyboard or from a text file. Either way the program
 * knows when to stop when a period is entered. The program either prints to a file
 * or to the screen. The program generates the crossword puzzle through a brute force 
 * method. The program provides the clues for the crossword puzzle in the form
 * of an anagram.
 *
 *
 * The name of this file is playcross.c
 *
 * @author Jack Schlehr
 * @version 10/18/20
 *
 */

#include "crossfunc.h"

const int MAXLENGTH  = 15;
const int BOARDSIZE = 15;
const char PERIOD = '.';
const char HASHTAG = '#';
const char SPACE = ' ';
const int ASCII_A = 65;
const int ASCII_Z = 90;


/*
 *
 *
 * The main function contains many important parts of the program. The main function
 * can tell how many commend line arguements there are and it acts accordingly. 
 * WHhn there is command line arguement, then the program prompts the user to enter
 * the words. When there are 2 arguements it is assumed that the second one is the
 * text file containing the words. When there are 3 arguemnts then the it is assumed 
 * that the last arguement is a file where the user wants the solutions to be printed. 
 *
 *
 *
 *
 * @param int argc is the number of arguements
 * @param char *argv[] is the char array that contains the arguements
 *
 * @return 1 if there is an error, 0 otherise
 *
 *
 *
 */
int main( int argc, char *argv[] ){
	
	
		
	//char words[MAXNUMWORDS][MAXLENGTH];
	char board[BOARDSIZE][BOARDSIZE];
	char solutions[BOARDSIZE][BOARDSIZE];
	char direcBoard[BOARDSIZE][BOARDSIZE];
	FILE *fp;
	FILE *output;
	int maxPathLength = 1024;
	bool run = true;
	bool isInteractive = false;
	char input[MAXLENGTH];
    int i, j;	
	int numWords = 0;



	WordStruct words[MAXLENGTH];


	initBoards( board, solutions, words, direcBoard);
	
		


	if( argc == 1 ){
		puts( "Anagram Crossword Puzzle Generator" );
		puts( "----------------------------------" );
		printf( "\nEnter a list of words:\n");
		isInteractive = true;
	}
	else if( argc == 2 ){
		
		puts( "Anagram Crossword Puzzle Generator" );
		puts( "----------------------------------" );
		isInteractive = false;
	}
	else if( argc == 3 ){
		char pwd[maxPathLength];
		getcwd( pwd, maxPathLength);
		strcat( pwd, "/" );
		strcat( pwd, argv[2] );
		output = fopen( pwd, "w+" );
		fprintf(output,  "Anagram Crossword Puzzle Generator\n" );
		fprintf( output, "----------------------------------\n" );
	}
		
	else if( argc > 3 ){
		puts( "Too many arguments." );
		return 1;
	}


	if( !isInteractive ){
		fp = fopen( argv[1], "r" );
		if( !fp ){
	 		printf( "The file %s is not found\n", argv[1] );
			return 1;
		}
	}
	

	while( run ) {
		
		if( isInteractive )  
			scanf( "%s", &input );  
		else
			fscanf( fp, "%s", input );
		
		int length = strlen( input );
		
		

			
		if( isValidWord( input, length  ) )
		{
				
			strcpy( words[numWords].word, input );
			
			
				
			if( input[0] == '.' )
				run = false;
		
			numWords++;
		}
		else{
			puts( "Invalid input, try again" );
		}

		
		
		if( numWords > MAXLENGTH ){
			printf( "Max number of words reached.\n" );
			run = false;
		}

	}
	numWords--;

	
	sort( words,  numWords );

	
	if( argc == 3 ){

		putWords( board, words, numWords, direcBoard, true, output  );
		fprintf(output,  "SOLUTION:\n");
		display( board, true, output );
	
		fprintf( output, "SOLUTION\n" );
		makeSolution( board, solutions );
		display( solutions, true, output );

		printClues( words, numWords, true, output );



	}
	else{
		putWords( board, words, numWords, direcBoard, false, output  );
		puts( "SOLUTION:");
		display( board, false, output );
	
		puts( "PUZZLE" );
		makeSolution( board, solutions );
		display( solutions, false, output );

	
		printClues( words, numWords, false, output );
	}
	
		
	return 0;
	
}


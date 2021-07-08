/*
 * This program is for lab8 of CSE20311 
 *
 *
 *	This file contains the functions for the crossword puzzle project.
 *
 *
 *
 *
 * This file is crossfunc.c
 *
 *@author Jack Schlehr
 *@version 10/18/20
 */

#include "crossfunc.h"

extern const int MAXLENGTH; 
extern const int BOARDSIZE;
extern const char PERIOD;
extern const char HASHTAG;
extern const char SPACE;
extern const int ASCII_A;
extern const int ASCII_Z;


/*
 * This function is designed to take the board and print it. 
 * The function also puts a boarder around
 * the board. This function will either print to the screen or to the output 
 * file.
 *
 * @param the 2d char array that is the board
 * @oaram true if printing to file, false otherwise
 * @param the FILE pointer that is the output file
 */
void display( char board[][BOARDSIZE], bool toOutput, FILE *output ){
	

	if( !toOutput ){

		int i, j, k;

		for(  i = 0; i < BOARDSIZE + 2; i++ ){
			printf( "-" );
		}
	
		printf( "\n" );

		for( i = 0; i < BOARDSIZE; i ++ ){
			printf( "|" );
			for(  j = 0; j < BOARDSIZE; j++ ){
				printf( "%c", board[i][j] );
			}
			printf( "|" );
			printf( "\n" );
		}

		for(  i = 0; i < BOARDSIZE+ 2; i++ ){
			printf( "-" );
		}

		printf( "\n" );
	}
	else{

		int i, j, k;

		for(  i = 0; i < BOARDSIZE + 2; i++ ){
			fprintf( output, "-" );
		}
	
		fprintf( output, "\n" );

		for( i = 0; i < BOARDSIZE; i ++ ){
			fprintf( output, "|" );
			for(  j = 0; j < BOARDSIZE; j++ ){
				fprintf( output, "%c", board[i][j] );
			}
			fprintf( output, "|" );
			fprintf( output, "\n" );
		}

		for(  i = 0; i < BOARDSIZE+ 2; i++ ){
			fprintf( output, "-" );
		}

		fprintf( output, "\n" );





	}

}


/*
 * This funciton takes the 2d char board and sets them to either periods or hashtags
 * depending on which one. The function also contains a 2d char direcBoard array that will contain
 * whether or not a given word placed down is horizontal or vertical.
 *
 *
 * @param the 2d char array that is the board with the solutions
 * @param the 2d char array that is the board with the Hastags or spaces
 * @param the array of WordStruct structs
 * @param the the 2d char array that is either space, 'V' or 'H'
 *
 */
void initBoards(char board[][BOARDSIZE], char solutions[][BOARDSIZE], WordStruct words[], char direcBoard[][BOARDSIZE] ){
	

	int i,j;

	for( i = 0; i < BOARDSIZE; i++){
		for( j= 0; j < BOARDSIZE; j++ ){
			board[i][j] = PERIOD;
			solutions[i][j] = HASHTAG;
			direcBoard[i][j] = SPACE;
			}
	}


	for( i = 0; i < MAXLENGTH; i++ ){
	
		words[i].x = -1;
		words[i].y = -1;
		words[i].hasBeenPlaced = false;
		words[i].isHorizontal = true;
	}
}



/*
 *
 *	This function is used when reading in words to check whether or not a given word is valid.
 *	If a word contians anything other than letters it is invalid.
 *
 *
 * 	@parma the String that is the word being tested
 * 	@param the int length of the word being tested
 *	@return true if valid word, false otherwise
 *
 */
bool isValidWord( char input[], int length ){
	
	

	if( length == 1 && input[0] == '.' )
		return true;
	else if( strlen( input ) > 15 || strlen( input ) < 2)
		return false;
	
	int i;
	for( i = 0; i < length; i++ ){
		int ascii = (int)(toupper(input[i]));
		if( ascii < ASCII_A || ascii > ASCII_Z )
			return false;
		

	}
	return true;
}

/*
 *	This function is used to sort the words into descending length.
 *	The function creates a temporary array to sort.
 *
 *
 *	@param the array of WordStruct
 *	@parm the in number of words in the array
 *
 */
void sort( WordStruct words[], int numWords ){

	int i, j;


	char temp[numWords][MAXLENGTH];

	for( i = 0; i < numWords; i++ ){
		strcpy( temp[i], words[i].word );
	}
	



	int maxLength = strlen( temp[0] );
	int index = 0;

	for( i = 0; i < numWords; i++ ){
		for( j = 0; j < numWords; j++ ){
			if( strlen( temp[j] ) > maxLength ){
				maxLength = strlen( temp[j] );
				index = j;
			}
		}
		strcpy( words[i].word, temp[index]);
		strcpy( temp[index], "" );
		maxLength = 0;

	}
	
	int length = 0;

	for( i = 0; i < numWords; i++ ){
		length = strlen( words[i].word );
		for( j = 0; j < length; j++ ){
			char temp;
			temp = toupper( (words[i].word)[j] );
			(words[i].word)[j] = temp;
		}
	}
}


/*
 * This function is used to try find a place to put down all of the words. The function will put down the largest word in the middle
 * of the board and then it puts the second largest word intersecting the largest. After this if preforms a brute force method that finds 
 * an avaliable letter then tests if a given word can be interested with this letter. If the letter can be placed there then it is
 * placed onto the board. If a word can not be put on the board on the first pass, then a message is sent to alert the user. 
 * Then the function attempts to place the words that have not been placed on the board again. The function will continue to true to put
 * words on the board as long as a word in the previous iteration was placed. In other words, if a word is placed on the board, then a new 
 * opportunity to place a word down could have arisen so it is tried to be placed again.
 *
 *
 *
 * @param the 2d char array that is the board with the solutions
 * @param the array of WordStruct structs
 * @param the int number of words that are in the array
 * @param the direcBoard which is a 2d char array that is direction of all of the words
 * @param true if printing to file, false otherwise
 * @param the FILE pointer that is the output file
 */

void putWords( char board[][BOARDSIZE], WordStruct words[], int numWords, char direcBoard[][BOARDSIZE], bool isOutput, FILE *output ){
	
	int i, j, k, z;


	int x = ( 15 - strlen( words[0].word ) ) / 2;
	int y = BOARDSIZE / 2;

	putWordDown( x, y, words, 0, board, true, direcBoard );

	

	for( k = 0; k < strlen( words[0].word ); k++ ){
		
		if( strchr( words[1].word, board[y][x+k]  ) != NULL && !words[1].hasBeenPlaced ){
			
			for( i = 0; i < strlen( words[1].word ); i ++ ){

				if( ( (words[1].word)[i] == board[y][x+k] )  && canBePlaced( x + k , y - i, words[1], false, board, i) ){

					putWordDown( x+k , y - i, words, 1, board, false, direcBoard );
					break;	
				}
			}
		}
	}



	
	
	for( z = 2; z < numWords; z ++ ){
		for( x = 0; x < BOARDSIZE; x++ ){
			for( y = 0; y < BOARDSIZE; y++ ){
				if( strchr( words[z].word, board[y][x] ) != NULL && !words[z].hasBeenPlaced ){
					for( i = 0; i < strlen( words[z].word ); i ++ ){	
						if( ( (words[z].word)[i]  == board[y][x] ) && canBePlaced( x, y - i, words[z], false, board, i ) && direcBoard[y][x] == 'H' ){
							putWordDown( x, y - i, words, z , board, false, direcBoard );		
							break;
						}else if( ( (words[z].word)[i]  == board[y][x] ) && canBePlaced( x - i, y, words[z], true, board, i ) && direcBoard[y][x] == 'V'){
							putWordDown( x - i, y, words, z , board, true,  direcBoard );
							break;
						}
				
					}
				}
			}
		}
		if( !words[z].hasBeenPlaced && !isOutput)
			printf( "The word: %s could not be placed in the first pass\n", words[z].word );
		else if( !words[z].hasBeenPlaced && isOutput )
			fprintf( output, "The word: %s could not be placed in the first pass\n", words[z].word );

	}

	bool wordPlaced = true;
	
	
	while( wordPlaced ){
		
		wordPlaced = false;
		
		for( z = 2; z < numWords; z ++ ){
			for( x = 0; x < BOARDSIZE; x++ ){
				for( y = 0; y < BOARDSIZE; y++ ){
					if( strchr( words[z].word, board[y][x] ) != NULL && !words[z].hasBeenPlaced ){
						for( i = 0; i < strlen( words[z].word ); i ++ ){	
							if( ( (words[z].word)[i]  == board[y][x] ) && canBePlaced( x, y - i, words[z], false, board, i ) && direcBoard[y][x] == 'H' ){
								putWordDown( x, y - i, words, z , board, false, direcBoard );
								wordPlaced = true;
								break;
							}else if( ( (words[z].word)[i]  == board[y][x] ) && canBePlaced( x - i, y, words[z], true, board, i ) && direcBoard[y][x] == 'V'){
								putWordDown( x - i, y, words, z , board, true,  direcBoard );
								wordPlaced = true;
								break;
							}
				
						}
					}
				}
			}
		}
	}

	
}

/*
 *	This function is simply used to print the clues to the user. The function will print to either the terminal window
 *	or the file it is being output to.
 *
 *
 * @param the array of WordStruct structs
 * @param the number of words in the array
 * @oaram true if printing to file, false otherwise
 * @param the FILE pointer that is the output file
 * */

void printClues( WordStruct words[], int numWords, bool isOutput, FILE *output ){

	if( !isOutput ){

		int i;
	
		puts( "CLUES:" );

		puts( "Location | Direction | Anagram " );


		char temp[numWords][MAXLENGTH];

		for( i = 0; i < numWords; i ++ ){			
			strcpy( temp[i], words[i].word  );
			strfry( temp[i] );
		}
	
		char direc[] = "Across";
		for( i = 0; i < numWords; i ++ ){
			if( !words[i].hasBeenPlaced ){
				printf( "The word: %s could not be placed\n", words[i].word );
				continue;
			}
	 		if( words[i].isHorizontal )
				strcpy( direc, "Across" );
	 		else
				strcpy( direc, "Down" );
 	  	printf( "%5d,%2d |%10s | %s \n", words[i].x, words[i].y, direc,  temp[i] ) ;
		}
	}
	else{
		int i;
	
		fprintf( output, "CLUES:\n" );

	 	fprintf( output, "Location | Direction | Anagram\n" );


		char temp[numWords][MAXLENGTH];

		for( i = 0; i < numWords; i ++ ){			
			strcpy( temp[i], words[i].word  );
			strfry( temp[i] );
		}
	
		char direc[] = "Across";
		for( i = 0; i < numWords; i ++ ){
			if( !words[i].hasBeenPlaced ){
				fprintf(output,  "The word: %s could not be placed\n", words[i].word );
				continue;
			}
	 		if( words[i].isHorizontal )
				strcpy( direc, "Across" );
	 		else
				strcpy( direc, "Down" );
 	  	fprintf( output, "%5d,%2d |%10s | %s \n", words[i].x, words[i].y, direc,  temp[i] ) ;
		}



	}
}






/*
 * This function is extremely important because it is used to tell whether or not a given word can be placed at
 * a given coordinate. 
 *
 *
 *
 * @param the int value for x coordinate
 * @param the int vlaue for y coordinate
 * @param the element of WordStruct
 * @param the boolean element to tell whether or not the word is being placed horizontally or not
 * @param the 2d char array that is the board
 * @param int value that is how many characters in the word is being intersected
 *
 *
 * @return true if the word can be placed, false otherwise
 */
bool canBePlaced( int x, int y, WordStruct oneWord, bool horiz, char board[][BOARDSIZE], int offset ){
	
	int i, j;
	
	int len = strlen( oneWord.word );
	

	
	if( horiz  && ( len + x > BOARDSIZE || x < 0 ) )
		return false;
	else if( !horiz && ( len + y > BOARDSIZE || y < 0 ) )
		return false;

	

	if( horiz )
	{
		for( i = 0; i < len; i ++ ){
			if(  i != offset && i != offset - 1 && i != offset + 1 && !letterAvaliable( x + i, y, board   )){
				return false;
			}
			else if( i == offset - 1 && ( checkLeft( x+i, y, board) || checkBelow( x+i,y,board) || checkAbove(x+i, y, board ) ) ){ //left
				return false;
			}else if( i==offset && (  checkRight( x+i, y, board)  || checkLeft( x+i, y, board ) ) ) { //intersection
				return false;
			}else if( i==offset+1 && ( checkRight(x+i, y, board ) || checkAbove( x+i, y,board ) || checkBelow(x+i, y, board )  ) ){ //right
				return false;
			}

		}

		
	}
	else	
	{
		for( i = 0; i < len; i++ ){
			if( i != offset && i != offset - 1 && i != offset + 1 && !letterAvaliable( x, y + i , board ) ){
				return false;
			}else if( i==offset-1 && ( checkAbove( x, y + i, board ) || checkRight( x, y + i , board ) || checkLeft( x, y + i, board ) ) ){ //above
				return false;
			}else if( i==offset && (  checkAbove(x, y+i, board) || checkBelow( x, y+i, board ) )){ //intersection
				return false;
			}else if( i==offset+1 && ( checkRight( x, y+i, board) || checkLeft( x, y+i, board) || checkBelow( x, y+i, board ) ) ){ //below
				return false;
			}
		}

	}

	return true;

}




/*
 * This function is used to tell if a letter can be placed in a given point.
 *
 * @param the int x value
 * @param the int y value
 * @param the 2d char array that is the board
 *
 *
 * @return true if the letter can be placed, false otheriwse
 */
bool letterAvaliable(  int x, int y, char board[][BOARDSIZE] ){
	
	
	
	if( board[y][x] != PERIOD )
		return false;

 	if( x < BOARDSIZE - 1 && board[y][x+1] != PERIOD ) //right
		return false;
	else if( x > 0 && board[y][x-1] != PERIOD ) //left
		return false;
	else if( y < BOARDSIZE - 1 && board[y+1][x] != PERIOD ) //top
		return false;
	else if( y > 0 && board[y-1][x] != PERIOD ) //bottom
		return false;


	return true;
}


/*
 * This function checks if a letter has anything above it.
 *
 *
 * @param the int x value
 * @param the int y value
 * @param the 2d char array that is the board
 * @return true if nothing above the letter
 */
bool checkAbove( int x, int y, char board[][BOARDSIZE] ){
	return ( y > 0 && board[y-1][x] != PERIOD );
}
/*
 * This function checks if a letter has anything below it.
 *
 *
 *
 * @param the int x value
 * @param the int y value
 * @param the 2d char array that is the board
 *
 * @return true if nothing below the letter
 *
 *
 */
bool checkBelow( int x, int y, char board[][BOARDSIZE] ){
	return ( y < BOARDSIZE - 1 && board[y+1][x] != PERIOD );
		
}
/*
 * This function checks to see if a letter ahs anything to the right of it.
 *
 *
 * @param the int x value
 * @param the int y value
 * @param the 2d char array that is the board
 * @return true if nothing to the right of the letter
 */
bool checkRight( int x, int y, char board[][BOARDSIZE] ){
	return ( x < BOARDSIZE - 1 && board[y][x+1] != PERIOD );
}
/*
 *
 * This function checks to see if a letter has anything to the left of it. 
 *
 * @param the int x value
 * @param the int y value
 * @param the 2d char array that is the board
 * @return true if nothing to hte left of the letter
 */
bool checkLeft( int x, int y, char board[][BOARDSIZE] ){
	return ( x > 0 && board[y][x-1] != PERIOD ) ;
}



/*
 *
 * This funciton is used to put a letter onto the board. The function updates the board[][] and the direcBoard[][].
 *
 *
 * @param the int value for x coordinate
 * @param the int vlaue for y coordinate
 * @param the element of WordStruct
 * @param the int vlaue for the word that is being placed down
 * @param the 2d char array that is the board
 * @param the boolean value that tells whether or not the word will be horizontal
 * @param the 2d char array that is the direction of the letter being placed down
 *
 */
void putWordDown( int x, int y, WordStruct words[], int num, char board[][BOARDSIZE], bool isHorizontal, char direcBoard[][BOARDSIZE] ){



	words[num].x = x;
	words[num].y = y;
	words[num].isHorizontal = isHorizontal;
	words[num].hasBeenPlaced = true;

	int i;
	if( isHorizontal ){
		for( i = 0 ; i < strlen( words[num].word ) ; i++ ){
			board[y][i+x] = (words[num].word)[i];
			direcBoard[y][i+x] = 'H';
		}
	}else{
		for( i = 0 ; i < strlen( words[num].word ) ; i++ ){
			board[y+i][x] = (words[num].word)[i];
			direcBoard[y+i][x] = 'V';
		
		}
	}



}

/*
 * This function is used to create the solution board with contains either a hashtag or a space. 
 *
 *
 * @param the 2d char array that is the board
 * @param the 2d char array that is the solutions
 */
void makeSolution( char board[][BOARDSIZE], char solutions[][BOARDSIZE] ){

	int i, j;
		
	for( i = 0; i < BOARDSIZE; i++ ){
		for( j = 0; j < BOARDSIZE; j++ ){
			if( board[i][j] != PERIOD ){
				solutions[i][j] = SPACE;
			}
		}
	}
}

	

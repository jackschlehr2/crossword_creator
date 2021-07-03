/*
 * This is the header file for the playcross.c file.
 
 *This program is for lab8 of CSE20311
 *
 * @version 10/18/20
 * @author Jack Schlehr
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


extern const int MAXLENGTH;
extern const int BOARDSIZE;
extern const char PERIOD;
extern const char HASHTAG;
extern const char SPACE;
extern const int ASCII_A;
extern const int ASCII_Z;


typedef struct{
	char word[15];
	char anagram[15];
	int x;
	int y;
	bool hasBeenPlaced;
	bool isHorizontal;
} WordStruct;

void initBoards( char board[][BOARDSIZE], char solutions[][BOARDSIZE], WordStruct words[], char direcBoard[][BOARDSIZE] );
void display( char board[][BOARDSIZE], bool isOutput, FILE *output);

void sort(  WordStruct words[], int numWords );

void putWords( char board[][BOARDSIZE], WordStruct words[], int numWords, char direcBoard[][BOARDSIZE], bool isOutput, FILE *output );

void printClues( WordStruct words[], int numWords, bool isOutput, FILE *output );

bool canBePlaced( int x, int y, WordStruct oneWord, bool horiz, char board[][BOARDSIZE], int offset );

bool letterAvaliable( int x, int y, char board[][BOARDSIZE] );

void putWordDown( int x, int y, WordStruct words[], int word, char board[][BOARDSIZE], bool isHorizontal, char direcBoard[][BOARDSIZE] );

bool checkBelow( int x, int y, char board[][BOARDSIZE] );

bool checkRight( int x, int y, char board[][BOARDSIZE] );

bool checkLeft( int x, int y, char board[][BOARDSIZE] );

bool checkAbove( int x, int y, char board[][BOARDSIZE] );

void makeSolution( char board[][BOARDSIZE], char solutions[][BOARDSIZE] );

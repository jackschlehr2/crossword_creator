# Anagram Crossword Puzzle Generator


This is a C program that allows the user to input a list of words to create a crossword puzzle.
The program will create anagrams to represent the clues, the x and y of the starting letter,
and the direction.

1. To make type:
   `make`
2. To run program with custom wordlist: 
   `./crossword`
2. To run program with provided wordlist:
   `./crossword < words2.txt`
  
```
Anagram Crossword Puzzle Generator
----------------------------------

Enter a list of words:
The word: LOOP could not be placed in the first pass
SOLUTION:
-----------------
|...............|
|..........K....|
|........C.E....|
|........O.Y....|
|U..P....D.B....|
|NOTREDAME.O....|
|D..O......A.C..|
|.FIGHTINGIRISH.|
|...R......D.E..|
|...A...........|
|.COMPUTER......|
|...M...........|
|.I.I...N.......|
|.FUNCTION......|
|...G...T.......|
-----------------
PUZZLE
-----------------
|###############|
|########## ####|
|######## # ####|
|######## # ####|
| ## #### # ####|
|         # ####|
| ## ###### # ##|
|#             #|
|### ###### # ##|
|### ###########|
|#        ######|
|### ###########|
|# # ### #######|
|#        ######|
|### ### #######|
-----------------
CLUES:
Location | Direction | Anagram 
    1, 7 |    Across | HINFRSGIIGTIH 
    3, 4 |      Down | GIARRNPGMMO 
    0, 5 |    Across | ENTAMDROE 
    1,10 |    Across | RCPUTOME 
   10, 1 |      Down | KOEYADRB 
    1,13 |    Across | ICFUNTNO 
    8, 2 |      Down | CDOE 
The word: LOOP could not be placed
    0, 4 |      Down | DUN 
   12, 6 |      Down | CES 
    7,12 |      Down | NOT 
    1,12 |      Down | FI 
 ```

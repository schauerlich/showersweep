// Author: Eric Warburg

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "box.h"


using namespace std;

bool takeTurn(Board *board) {
  short row, col;
  
  cout << *board;
  while (1) {
    cout << "row col: ";
    cin >> row >> col;
    
    if (row == -1)
      return false;
  
    if (board->checkMove(row, col)) {
      if (!board->makeMove(row, col)) {
        cout << "You clicked a mine. Boo!\n";
        return false;
      } // if spot is mine
      break;
    } // if move is legal
    else {
      cout << "Bad move, partner.\n";
    } // else move is illegal
  } // while 1
  
  return true;
} // takeTurn()

int main(int argc, char *argv[]) {
  char size;
  
  if (argc > 1)
    size = *argv[1];
  
  if (argc != 2 || !(size == 's' || size == 'm' || size == 'l')
      || strlen(argv[1]) != 1) {
    cout << "You're doing it wrong.\n";
    return 1;
  } // if not used correctly
  
  Board *board = new Board(size);
  
  while(takeTurn(board));

  delete board;

  return 0;
} // main()


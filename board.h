// Author: schauerlich (edavidburgATgmail.com)

#ifndef BOARD_H
#define BOARD_H

#include "box.h"

class Board {
  Box ***grid;
  short numMines;
  short size;

public:
  Board();
  Board(char s);
  ~Board();
  
  int countNeighbors(short row, short col) const;
  bool checkMove(short row, short col);
  bool makeMove(short row, short col);
  bool poke(short row, short col);
    
  friend ostream &operator<<(ostream &os, Board &rhs);
}; // class Board

#endif
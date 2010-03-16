// Author: Eric Warburg

#ifndef BOX_H
#define BOX_H

#include <iostream>

using namespace std;

class Box {
  short numMineNeighbors;
  short row;
  short col;
  bool is_mine;
  bool is_visible;
  bool is_flagged;

public:
  Box();
  Box(short r, short c);
  
  bool isMine();
  bool isVisible();
  bool isFlagged();
  
  void makeMine();
  void makeVisible();
  void flag();
  void unflag();
  
  short getRow();
  short getCol();
  short getNumNeighbors();
  
  void setNumNeighbors(short num);
  
  friend ostream &operator<<(ostream &os, Box &rhs);
}; // class Box

#endif
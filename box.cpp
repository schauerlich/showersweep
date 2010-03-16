// Author: schauerlich (edavidburgATgmail.com)

#include "box.h"

Box::Box() : 
  numMineNeighbors(0), row(-1), col(-1), 
  is_mine(false), is_visible(false), is_flagged(false) {
  
} // Box()


Box::Box(short r, short c) : 
  numMineNeighbors(0), row(r), col(c),
  is_mine(false), is_visible(false), is_flagged(false) {
  
} // Box()


bool Box::isMine() {
  return is_mine;
} // isMine()


bool Box::isVisible() {
  return is_visible;
} // isVisibile;


bool Box::isFlagged() {
  return is_flagged;
} // isFlagged()


void Box::makeMine() {
  is_mine = true;
  is_visible = false;
} // makeMine()


void Box::makeVisible() {
  is_visible = true;
} // makeVisible()


void Box::flag() {
  is_flagged = true;
} // flag()

void Box::unflag() {
  is_flagged = false;
} // unflag()


short Box::getRow() {
  return row;
} // getRow()


short Box::getCol() {
  return col;
} // getCol()


short Box::getNumNeighbors() {
  return numMineNeighbors;
} // getNumNeighbors()


void Box::setNumNeighbors(short num) {
  numMineNeighbors = num;
} // setNumNeighbors()


ostream &operator<<(ostream &os, Box &rhs) {
  if (rhs.is_visible) {
    if (rhs.numMineNeighbors > 0)
      os << rhs.numMineNeighbors;
    else
      os << ' ';
  } // if is_visible
  else {
      os << '*';
  } // else invisible
  return os;
} // operator<<
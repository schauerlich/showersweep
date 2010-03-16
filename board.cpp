// Author: Eric Warburg

#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

#include "board.h"

using namespace std;

Board::Board() {
  
} // Board()


Board::Board(char s) {
  // small, medium or large
  switch (s) {
    case 's':
      size = 8;
      numMines = 10;
      break;
    case 'm':
      size = 16; 
      numMines = 40; 
      break;
    case 'l':
      size = 22;
      numMines = 99;
      break;
  } // switch (s)
  
  // allocate board
  grid = new Box**[size];
  for (int row = 0; row < size; row++)
    grid[row] = new Box*[size];
  
  // populate board with normal boxes
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      grid[row][col] = new Box(row, col);
    } // for col
  } // for row
  
  // make random boxes into mines
  srand(time(NULL));
  for (int i = 0; i < numMines;){
    int row = rand() % size;
    int col = rand() % size;
    if (!grid[row][col]->isMine()){
      grid[row][col]->makeMine();
      i++;
    } // if not mine
  } // for i
  
  // count up everyone's neighbors
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      grid[row][col]->setNumNeighbors(countNeighbors(row, col));
    } // for col
  } // for row
  
} // Board()


Board::~Board() {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      delete grid[row][col];
    } // for col
  } // for row
} // ~Board()


int Board::countNeighbors(short row, short col) const {
  // returns how many of the cell's neighbors are mines
  
  int left = col - 1;
  int right = col + 1;
  int up = row + 1;
  int down = row - 1;
  int count = 0;
  
  // TODO: this looks like shit. there's /got/ to be a better way of doing this.
  //       But, it works for now...
  
  if (up >= size) {// if at top row
    
    if (left < 0) { // if at left edge
      count += grid[row][right]->isMine() + grid[down][right]->isMine() + 
               grid[down][col]->isMine();
    } // if at left edge
    
    else if (right >= size) { // else at right edge
      count += grid[row][left]->isMine() + grid[down][left]->isMine() +
               grid[down][col]->isMine();
    } // else right edge
    
    else { // else anywhere else on top row
      count += grid[row][left]->isMine() + grid[down][left]->isMine() +
               grid[down][col]->isMine() + grid[down][right]->isMine() +
               grid[row][right]->isMine();
    } // else anywhere else on top row
    
  } // if at top row
  
  else if (down < 0) { // else if at bottom row
    
    if (left < 0) { // if at left edge
      count += grid[row][right]->isMine() + grid[up][right]->isMine() + 
               grid[up][col]->isMine();
    } // if at left edge
    
    else if (right >= size) { // else at right edge
      count += grid[row][left]->isMine() + grid[up][left]->isMine() +
               grid[up][col]->isMine();
    } // else if at right edge
    
    else { // else anywhere else on bottom row
      count += grid[row][left]->isMine() + grid[up][left]->isMine() +
               grid[up][col]->isMine() + grid[up][right]->isMine() +
               grid[row][right]->isMine();
    } // else anywhere else on bottom row
    
  } // else if at bottom row
  
  else { // else in middle rows
    
    if (left < 0) { // if at left edge
      count += grid[up][col]->isMine() + grid[up][right]->isMine() +
               grid[row][right]->isMine() + grid[down][right]->isMine() +
               grid[down][col]->isMine();
    } // if at left edge
    
    else if (right >= size) { // else if at right edge
      count += grid[up][col]->isMine() + grid[up][left]->isMine() +
               grid[row][left]->isMine() + grid[down][left]->isMine() +
               grid[down][col]->isMine();
    } // else if at right edge
    
    else { // else anywhere else in middle rows
      count += grid[up][col]->isMine() + grid[up][left]->isMine() +
               grid[row][left]->isMine() + grid[down][left]->isMine() +
               grid[down][col]->isMine() + grid[down][right]->isMine() +
               grid[row][right]->isMine() + grid[up][right]->isMine();
    } // else anywhere else in middle rows
    
  } // else in middle rows
  
  
  return count;
} // countNeighbors()


bool Board::checkMove(short row, short col) {
  // returns true if the move is legal, and false if it is not.
  // Legal means the row and col are on the board, and the box they
  // want to reveal is not currently visible.
  
  if (row >= size || row < 0 || col >= size || col < 0 || grid[row][col]->isVisible())
    return false;

  return true;
} // checkMove()


bool Board::makeMove(short row, short col) {
  // returns false if the move reveals a mine. 
  // otherwise, makes box visible and returns true.
  
  if (grid[row][col]->isMine())
    return false;
  
  poke(row, col);
  
  return true;
} // makeMove()


bool Board::poke(short row, short col) {
  // recursively reveals surrounding empty squares
  // returns false once it's done in that direction
  
  int left = col - 1;
  int right = col + 1;
  int up = row + 1;
  int down = row - 1;
  
  // if we're off the edge of the board
  if (!(row >= 0 && row < size && col >= 0 && col < size)) {
    //cout << "off edge" << endl;
    return false;
  }
  //cout << "Testing row: " << row << " col: " << col << endl;
  //cout << "numNeighbors: " << grid[row][col]->getNumNeighbors() << endl;
  // if box is already visible, or it has neighbors
  if (grid[row][col]-> isVisible() || grid[row][col]->getNumNeighbors() != 0) {
    grid[row][col]->makeVisible();
    //cout << "Has neighbors" << endl;
    return false;
  } // if
  
  grid[row][col]->makeVisible();
  
  return (poke(row, left) || poke(up, left) || poke(up, col)
       || poke(up, right) || poke(row, right) || poke(down, right) 
       || poke(down, col) || poke(down, left));
} // poke()

ostream &operator<<(ostream &os, Board &rhs) {
  // prints board
  
  os << "   ";
  
  for (int i = 0; i < rhs.size; i++) {
    os << "----";
  } // for i
  
  os << "-" << endl;
  
  for (int row = rhs.size - 1; row >= 0; row--) {
    os << setw(2) << row << " ";
    
    for (int col = 0; col < rhs.size; col++) {
      os << "| "<< *(rhs.grid[row][col]) << " ";
    } // for j
    
    os << "|" << endl << "   ";
    
    for (int i = 0; i < rhs.size; i++) {
      os << "----";
    } // for i
    
    os << "-" << endl;
  } // for i
  
  os << "  ";
  for (int i = 0; i < rhs.size; i++) {
    os << setw(4) << i;
  } // for i
  
  os << endl;
  
  return os;
} // operator<<
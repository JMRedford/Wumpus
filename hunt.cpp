// g++ hunt.cpp -o test in command line compiles a c++ file test.cpp into an executable mytest

  //IDEA: Hunt the wumpus which is simultaneously more confusing and less misleading
  //Problem with wumpus: labeling doors of rooms north, south, east, west induces an
  //assumption about what rooms connects to which and how.  E.G. If one leaves a room
  //north, one assumes that going south will take them back to the original room,
  //which need not be the case in the original wumpus.
  //Solution: Give the exits to each room arbitrary names and tell the user which door
  //the room was entered FROM, i.e. which room will lead them back to the previous 
  //room.  Possible sets of names: [red,green,blue,yellow], [00,01,10,11], [Anna,
  //Beth, Claire, Dorcas]
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include "room.h"
#include "helpers.h"

using namespace std;

int main() {
  srand (time(NULL));
  Room *playerPosition = createRandomBoard(10);
  bool gameOver = false;
  while (!gameOver){
    describeRoom(playerPosition);
    gameOver = parseInput(*&playerPosition);
  }
  return 0;
};

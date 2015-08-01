// g++ test.cpp -o mytest in command line compiles a c++ file test.cpp into an executable mytest

#include <stdio.h>

int main() {
  //IDEA: Hunt the wumpus which is simultaneously more confusing and less misleading
  //Problem with wumpus: labeling doors of rooms north, south, east, west induces an
  //assumption about what rooms connects to which and how.  E.G. If one leaves a room
  //north, one assumes that going south will take them back to the original room,
  //which need not be the case in the original wumpus.
  //Solution: Give the exits to each room arbitrary names and tell the user which door
  //the room was entered FROM, i.e. which room will lead them back to the previous 
  //room.  Possible sets of names: [red,green,blue,yellow], [00,01,10,11], [Anna,
  //Beth, Claire, Dorcas]
}
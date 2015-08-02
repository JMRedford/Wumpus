// g++ test.cpp -o mytest in command line compiles a c++ file test.cpp into an executable mytest

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
#include <cstdlib>

using namespace std;

class Room {
  private:
    Room *neighbors [4];
    string names [4];
    bool wumpus;
    bool pit;
  public:
    Room(string exits[4]);
    ~Room();
    void setNeighbor(int n);
    Room * getNeighbor(int n);

};

Room::Room( string exits[4] ){
  this->wumpus = false;
  this->pit = false;
};

Room::~Room( void ){

};

string wumpusNear = "You smell a wumpus.";
string pitNear = "You feel a draft.";
string wumpus = "A wumpus eats you.  You are dead.";
string pit = "You fall... ... You are dead.";

string exitNames[17][4] = {{"red", "green", "blue", "yellow"},
                         {"adam","ben","charlie","dave"},
                         {"alice","bonnie","claire","dorcas"},
                         {"ape","bear","crocodile","dragon"},
                         {"Matthew","Mark","Luke","John"},
                         {"John","Paul","George","Ringo"},
                         {"Lennon","McCartney","Harrison","Star"},
                         {"England","Scotland","Wales","North Ireland"},
                         {"winter","spring","summer","fall"},
                         {"earth","air","fire","water"},
                         {"+","-","*","/"},
                         {"gua","ade","cyt","thy"},
                         {"00","01","10","11"},
                         {"1","2","10","11"},
                         {"1","2","3","10"},
                         {"1","2","3","4"},
                         {"justice","prudence","temperence","fortitude"}};

Room * createRandomBoard(int n) {
  bool pitPlaced = false;
  bool wumpusPlaced = false;
  bool playerPlaced = false;
  Room *roomArray[n];

  for (int i = 0; i < n; i++){
    int exitsTypes = rand()%17;
    roomArray[i] = new Room(exitNames[exitsTypes]);
  }
  //start testing
  return roomArray[n];
  //end testing
};


int main() {
  Room *playerPosition = createRandomBoard(10);
  bool dead = false;
  while (!dead){
    //start testing
    dead = true;
    cout << "test sat\n";
    //end testing
  }
  return 0;
};

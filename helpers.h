#ifndef WUMPUS_HELPERS
#define WUMPUS_HELPERS

using namespace std;

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
                           {"England","Scotland","Wales","NorthIreland"},
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
  bool exitsUsed[n][4];

  for (int i = 0; i < n; i++){
    for (int j = 0; j < 4; j++){
      exitsUsed[i][j] = false;
    }
    int exitsType = rand()%17;
    roomArray[i] = new Room(exitNames[exitsType]);
  }

  for (int i = 0; i < 2*n; i++) {
    bool madeNeighbors = false;
    int firstRoomExit;
    int secondRoomExit;
    int firstRoomNum;
    int secondRoomNum;
    while (!madeNeighbors){
      firstRoomExit  = rand()%4;
      secondRoomExit = rand()%4;
      firstRoomNum   = rand()%n;
      secondRoomNum  = rand()%n;
      if (firstRoomNum != secondRoomNum && 
          roomArray[firstRoomNum]->getNeighbor(firstRoomExit) == 0 &&
          roomArray[secondRoomNum]->getNeighbor(secondRoomExit) == 0 ){
        madeNeighbors = true;
        makeNeighbors(firstRoomExit,secondRoomExit,roomArray[firstRoomNum],roomArray[secondRoomNum]);
      }
    }
  }
  int wumpusNum = rand()%(n-2)+1;
  int pitNum = wumpusNum+1;
  roomArray[wumpusNum]->setWumpus();
  roomArray[pitNum]->setPit();
  return roomArray[0];
};

void describeRoom(Room *playerRoom){
  cout << "You are in a damp cave.\n";
  cout << "There are four exits:\n";
  cout << "  " << playerRoom->getName(0); 
  cout << "  " << playerRoom->getName(1);
  cout << "  " << playerRoom->getName(2);
  cout << "  " << playerRoom->getName(3) << '\n';
  if ( playerRoom->getNeighbor(0)->isWumpus() ||
       playerRoom->getNeighbor(1)->isWumpus() ||
       playerRoom->getNeighbor(2)->isWumpus() ||
       playerRoom->getNeighbor(3)->isWumpus() ) {
    cout << wumpusNear << '\n';
  }
  if ( playerRoom->getNeighbor(0)->isPit() ||
       playerRoom->getNeighbor(1)->isPit() ||
       playerRoom->getNeighbor(2)->isPit() ||
       playerRoom->getNeighbor(3)->isPit() ) {
    cout << pitNear << '\n';
  } 
}

bool parseInput(Room *&playerRoom){
  char * input;
  cin >> input;
  char * inputToken = strtok (input," ");
  for (int i = 0; i < 4; i++){
    if ( inputToken == playerRoom->getName(i) ){
      if (playerRoom->getNeighbor(i)->isPit()){
        //DEBUG
        cout << inputToken << " is " << playerRoom->getName(i) << '\n';
        //END DEBUG
        cout << pit << '\n';
        return true;
      } else if (playerRoom->getNeighbor(i)->isWumpus()){
        cout << wumpus << '\n';
        return true;
      }
      for (int j = 0; j < 4; j++){
        bool displayedOneYet = false;
        if (playerRoom->getNeighbor(i)->getNeighbor(j) == playerRoom){
          if (!displayedOneYet){
            cout << "You enter the room by the door labeled " << playerRoom->getNeighbor(i)->getName(j) << ".\n";
            displayedOneYet = true;
          } else {
            cout << "Or did you enter by the door labeled " << playerRoom->getNeighbor(i)->getName(j) << "?\n";
          }
        }
      }
      playerRoom = playerRoom->getNeighbor(i);
      break;
    }
    //DEBUG
    else {
      cout << inputToken << " is not " << playerRoom->getName(i) << '\n';
    }
    //END DEBUG
  }
  if (inputToken == "shoot") {
    inputToken = strtok(NULL," ");
    for (int i = 0; i < 4; i++){
      if (inputToken == playerRoom->getName(i)){
        if (playerRoom->getNeighbor(i)->isWumpus()){
          cout << "You shot the wumpus! Congratulations!" << '\n';
          return true;
        } else {
          cout << "You have used your only bullet." << '\n';
          cout << "There is no hope.  The wumpus will eat you. GAME OVER" << '\n';
          return true;
        }
      }
    }
    cout << "To shoot into an adjacent room type shoot <doorname>" << '\n';
  }
  return false;
}

#endif

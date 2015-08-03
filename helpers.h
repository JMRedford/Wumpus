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
  string input;
  string parsedInput [2];
 
  parsedInput[0] = "";
  parsedInput[1] = "";

  getline (cin, input);
  
  int j = 0;
  for (int i = 0; i < input.length(); i++){
    if (j < 2 && input[i] != ' '){
      parsedInput[j] += input[i];
    } else {
      j++;
    }
  }

  for (int i = 0; i < 4; i++){  
    if ( parsedInput[0] == playerRoom->getName(i) ){
      if (playerRoom->getNeighbor(i)->isPit()){
        cout << pit << '\n';
        return true;
      } else if (playerRoom->getNeighbor(i)->isWumpus()){
        cout << wumpus << '\n';
        return true;
      }
      bool displayedOneYet = false;
      for (int j = 0; j < 4; j++){
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
  }
  if (parsedInput[0] == "shoot") {
    for (int i = 0; i < 4; i++){
      if (parsedInput[1] == playerRoom->getName(i)){
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

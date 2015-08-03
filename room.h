#ifndef WUMPUS_ROOM
#define WUMPUS_ROOM

using namespace std;

class Room {
  private:
    Room *neighbors [4];
    string names [4];
    bool wumpus;
    bool pit;
  public:
    Room(string exits []);
    ~Room();

    void setNeighbor(int , Room *);
    Room * getNeighbor(int n){return neighbors[n];}

    void setWumpus() {wumpus = true;}
    bool isWumpus() {return wumpus;}

    void setPit() {pit = true;}
    bool isPit() {return pit;}

    string getName(int n) {return names[n];}
};

Room::Room( string exits [] ){
  this->wumpus = false;
  this->pit = false;
  for (int i = 0; i < 4; i++){
    this->names[i] = exits[i];
  }
};

Room::~Room( void ){
};

void Room::setNeighbor(int n, Room *theNeighbor){
  this->neighbors[n] = theNeighbor;
}

void makeNeighbors(int m, int n, Room *mRoom, Room *nRoom){
  mRoom->setNeighbor(m,nRoom);
  nRoom->setNeighbor(n,mRoom);
}




#endif

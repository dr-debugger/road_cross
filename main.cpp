#include<iostream>
#include<deque>
using namespace std;

class Player{
  public:
    int x, y;

    // player position on start
    void playerPos(int width){
      x = width / 2;
      y = 0;
    }
};

class Lane{
    // blocks will be boolean, true means player can pass through the block, false is the oposite
    deque<bool> cars;

    public:
      Lane(int width){
        // adding blocks to the deque through constructor
        for (int i = 0; i < width; i++)
        {
          // initializing no cars on the road
          cars.push_front(false);
        }
        
      }

      void moveCars(){
        // randomly pushing blocks on the road
        if(rand() % 10 == 1){
          cars.push_front(true);
        }else{
          cars.push_front(false);
        }

        cars.pop_back();
      }

      bool checkPos(int pos){
        // getting car from specific position
        return cars[pos];
      }
};

class Game{
  bool quit;

  public:
    void draw();
    void input();
    void logic();
    void run();
 
};

int main(){
  
  return 0;
}

void Game :: draw(){
  
}

void Game :: input(){

}

void Game :: logic(){

}

void Game :: run(){
 while (!quit)
    {
      input();
      draw();
      logic();
    }
    
}
#include<iostream>
#include<string>
#include<deque>
#include <vector>
#include <unistd.h>
#include <time.h>
#include<conio.h> // for getting user input, only works on windows
using namespace std;

class Player{
  public:
    // player position on start
    Player(int width){
      x = width / 2;
      y = 0;
    }
    int x, y;

};

class Lane{
    // blocks will be boolean, true means player can pass through the block, false is the oposite
    deque<bool> cars;
    bool right;

  public:
    Lane(int width)
    {
      // adding blocks to the deque through constructor
      for (int i = 0; i < width; i++)
      {
        // initializing no cars on the road
        cars.push_front(true);

        right = rand() % 2;
      }
        
      }

      void moveCars(){
        // randomly pushing blocks on the road
        if(right){
          cars.push_front(rand() % 10 == 1);
          cars.pop_back();
        }else{
          cars.push_back(rand() % 10 == 1);
          cars.pop_front();
        }
      }

      bool checkPos(int pos){
        // getting car from specific position
        return cars[pos];
      }

      void changeDir() { right = !right; }
};

class Game{
  bool quit;
  int numOfLanes;
  int width;
  int score = 0;
  Player* player;
  vector<Lane*> map;
  
  public:
    Game(int w = 20, int h = 10)
    {
        numOfLanes = h;
        width = w;
        quit = false;
        for (int i = 0; i < numOfLanes; i++){
          map.push_back(new Lane(width));
        }
        player = new Player(width);
    }

// free the memory
    ~Game(){
        delete player;
        for (int i = 0; i < map.size(); i++){
          Lane* current = map.back();
          map.pop_back();
          delete current;
        }
    }

    void draw();
    void input();
    void logic();
    void run();
    void gameQuit(string);
  };

int main(){

    srand(time(NULL));

    Game _game(30, 5);
    _game.run();

    // _game.gameQuit("manual");

    getchar();
    return 0;
}

void Game :: draw(){
  system("cls"); // to clear the screen

  for (int i = 0; i < numOfLanes; i++){
        for (int j = 0; j < width; j++){

          if(i == 0 && (j ==0 || j == width -1)) cout << "$";
          if(i == numOfLanes - 1 && (j ==0 || j == width -1))cout << "$";

    
          if(map[i] -> checkPos(j) && i != 0 && i != numOfLanes -1)  cout << "#";
          else if(player -> x == j && player -> y == i)cout << "V";
          else cout << " ";
        }

        cout << endl;
  }
  cout << "your score is " << score << endl;
}

void Game :: input(){
  if(_kbhit()){
        char current = _getch();
        if(current == 'a')  player->x--;
        if(current == 'd')  player->x++;
        if(current == 'w')  player->y--;
        if(current == 's')  player->y++;
        if(current == 'q')  {
          quit = true;
          // sleep(3);
          
          gameQuit("manual");
        }
  }

}

void Game :: logic(){
  // ignoring first and last lane
  for (int i = 1; i < numOfLanes - 1; i++){
    if(rand() % 10 == 1)
          map[i]->moveCars();
    if(map[i] -> checkPos(player -> x) && player -> y == i){
        quit = true;
        gameQuit("gameOver");
    }
    if(player -> y == numOfLanes -1){
        score++;
        player->y = 0;
        cout << "\x07"; // score sound
        map[rand() % numOfLanes]->changeDir();
    } 
        
  }
}

void Game :: run(){
  cout << "press q to quit"<< endl;
 while (!quit)
    {
      input();
      draw();
      logic();
    }
    
}

void Game:: gameQuit(string type){
  if(type == "gameOver"){
    cout << "Game Over"<< endl;
  }
  

  if(type == "gameWin"){
    cout << "You Won" << endl;
  }

  if(type == "manual"){
      cout << "You Quit the game" << endl;
  }
  cout << "your score is " << score << endl;
  cout << "Do you want to restart?" << endl;
  cout << "Type r and hit enter to restart" << endl;
  cout << "Type e and hit enter to exit" << endl;
  if(_kbhit()){
        char input = _getch();
        if(input == 'r') {
          quit = false;
          run();
        }
        if(input == 'e') {
          exit(0);
        }
  }
}
#include <iostream>

#include <cstdlib>

#include <cmath>

using namespace std;

const float g = 9.8;

struct Ball {
  float h = rand() % 300 + 100; // высота h
  float x = 0;
  float y = 0;
  float vx = rand() % 100; // скорость v
  float vy = 0;
  float ax = 0;
  float ay = -g;
  float m = 0;

  Ball() {}
};

float dt_full = 0;
float flightTime = 0;
void move(Ball * ball, float dt) {
  // по оси y

  dt_full += dt;;
  ball -> vy += (ball -> ay) * dt_full;
  ball -> y = ball -> h + ball -> ay * pow(dt_full, 2) / 2;

  //по оси x
  ball -> ax = 0;

  ball -> x += ball -> vx * dt;
  if (ball -> y > 0) flightTime = dt_full;
  if (ball -> y <= 0) { // "прилипает"
    ball -> y = 0;
    ball -> vy = 0;
    ball -> vx = 0;

  }

}

void show(Ball ball) {
  cout << "y= " << ball.y << " vy= " << abs(ball.vy) << " ay= " << abs(ball.ay) << endl;
  cout << "   x= " << ball.x << " vx= " << abs(ball.vx) << " ax= " << abs(ball.ax) << endl;
  cout << endl;

}

//--------------
struct Node {
  float val_vx, val_vy, val_ax, val_ay, t;
  Node * next;

};

void init(Node * node) {

  node -> next = NULL;

}

void showNode(Node * head) {

  while (head -> next != NULL) {

    cout << "t= " << head -> t << " vy = " << abs(head -> val_vy) << " ay =  " << abs(head -> val_ay) << endl;
    cout << "\t  vx = " << abs(head -> val_vx) << " ax = " << abs(head -> val_ax) << endl;
    head = head -> next;

  }
}

void pushNode(Node * head, Node * node) {

  while (head -> next != NULL)
    head = head -> next;

  head -> next = node;
  node -> next = NULL;

}

//------------------------------

void save(Node * head, Node * head_node, float vx, float vy, float ax, float ay, float t) {

  pushNode(head, new Node);
  head_node -> val_ax = ax;

  head_node -> val_ay = ay;
  head_node -> val_vx = vx;
  head_node -> val_vy = vy;
  head_node -> t = t;

  head_node = head_node -> next;

}

int testMove() {

  Ball a;

  float deltaT = 0.01;
  Node * head = new Node;
  Node * head_node = head;
  init(head);
  init(head_node);

  float t = 0;
  for (int i = 0; i < 1000; i++) {

    if (i != 0) move( & a, deltaT);
    pushNode(head, new Node);
    head_node -> val_ax = a.ax;

    head_node -> val_ay = a.ay;
    head_node -> val_vx = a.vx;
    head_node -> val_vy = a.vy;
    head_node -> t = t;

    head_node = head_node -> next;
    t += deltaT;

  }
  if (int(flightTime * 100) != int(sqrt(2 * a.h / g) * 100)) return -1;
  return 0;
}

static void runTest(int( * testFunction)(),
  const std::string & testName) {
  if (testFunction() == 0)
    std::cout << "Test " << testName << " - OK" << std::endl;
  else
    std::cout << "Test " << testName << " - FAIL" << std::endl;
}

int main() {
  runTest(testMove, "testMove");

}

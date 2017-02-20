/* Catalina Vajiac
 * CSE 20311 Final Project
 * snake.cpp
 * implementation for snake object
 */

#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include "./gfxnew.h"
#include "./snake.h"
#include "./list.h"

typedef std::pair<int, int> int_pair_t;

snake::snake() {
  // open  & set up screen 
  int x = gfx_screenwidth(), y = gfx_screenheight() - 30;
  this -> set_size_square(24);
  x -= x % (size_square);
  y -= y % (size_square);
  gfx_open(x, y, "Snake");
  gfx_clear_color(192, 209, 237);
  this -> set_size(std::make_pair(x, y));

  // set initial snake position
  LinkedList snake_pos;
  int dxy = size_square * 3 / 2;
  snake_pos.push_back(std::make_pair(dxy, dxy));
  this -> set_snake_pos(snake_pos);

  // set initial food position & velocity
  srand(time(NULL));
  int x_pos = rand() % x, y_pos = rand() % y;
  x_pos -= x_pos % size_square - size_square / 2;
  y_pos -= y_pos % size_square - size_square / 2;
  this -> set_food_pos(std::make_pair(x_pos, y_pos));
  this -> set_vel(std::make_pair(1, 0));
}

snake::~snake() {
}

// set methods

void snake::set_snake_pos(LinkedList snake_pos) {
  this -> snake_pos = snake_pos;
}

void snake::set_food_pos(int_pair_t food_pos) {
  this -> food_pos = food_pos;
}

void snake::set_size_square(int size_square) {
  this -> size_square = size_square;
}

void snake::set_vel(int_pair_t vel) {
  this -> vel = vel;
}

void snake::set_size(int_pair_t max_size) {
  this -> max_size = max_size;
}

// get methods

LinkedList snake::get_snake_pos() {
  return snake_pos;
}

int_pair_t snake::get_food_pos() {
  return food_pos;
}

int snake::get_size_square() {
  return size_square;
}

int_pair_t snake::get_vel() {
  return vel;
}

int_pair_t snake::get_size() {
  return max_size;
}

void snake::display() {
// display current state of snake game
  gfx_clear();
  gfx_color(255, 242, 12);
  this -> draw_square(food_pos);
  gfx_color(76, 175, 80);

  Node *pos = snake_pos.begin();
  while (pos != snake_pos.end()) {
    this -> draw_square(pos -> value);
    pos = pos->next;
  }

  gfx_color(0, 0, 0);
  std::string score = "Score: ";
  score.append(std::to_string(snake_pos.size()));
  gfx_text(max_size.first - 75, max_size.second - 25, score.c_str());
  gfx_flush();
}

void snake::draw_square(int_pair_t center) {
/* draw square around center
 */
  int dxy = get_size_square() / 2;
  int cx = center.first;
  int cy = center.second;
  for (int i = 0; i <= dxy; i++) {
    gfx_line(cx - dxy + i, cy - dxy + i, cx + dxy - i, cy - dxy + i);
    gfx_line(cx + dxy - i, cy - dxy + i, cx + dxy - i, cy + dxy - i);
    gfx_line(cx + dxy - i, cy + dxy - i, cx - dxy + i, cy + dxy - i);
    gfx_line(cx - dxy + i, cy + dxy - i, cx - dxy + i, cy - dxy + i);
  }
}

bool snake::move() {
/* completes one iteration of snake game
 * returns false if game is lost, true otherwise
 */
  usleep(100000);
  if (gfx_event_waiting() == 1 || gfx_event_waiting() == 2) {
    char key = gfx_wait();
    switch (key) {
      case 'Q':  // left arrow
        if (this -> get_vel() != std::make_pair(1, 0)) {
          this -> set_vel(std::make_pair(-1, 0));
        }
        break;
      case 'R':  // up arrow
        if (this -> get_vel() != std::make_pair(0, 1)) {
          this -> set_vel(std::make_pair(0, -1));
        }
        break;
      case 'S':  // right arrow
        if (this -> get_vel() != std::make_pair(-1, 0)) {
          this -> set_vel(std::make_pair(1, 0));
        }
        break;
      case 'T':  // down arrow
        if (this -> get_vel() != std::make_pair(0, -1)) {
          this -> set_vel(std::make_pair(0, 1));
        }
        break;
      default:
        // Do Nothing.
        break;
    }
  }
  int_pair_t first_pos = snake_pos.first();
  first_pos.first = first_pos.first + size_square * vel.first;
  first_pos.second = first_pos.second + size_square * vel.second;
  snake_pos.push_front(first_pos);

  // check if snake ate food
  if (this -> ate_food()) {
    int x_pos = rand() % max_size.first;
    int y_pos = rand() % max_size.second;
    x_pos -= x_pos % size_square - size_square / 2;
    y_pos -= y_pos % size_square - size_square / 2;
    this -> set_food_pos(std::make_pair(x_pos, y_pos));
  } else {
    snake_pos.pop_back();
  }

  return this -> check_boundary() && this -> check_overlap();
}

bool snake::ate_food() {
/* check if snake position and food position are the same
 * return true if they are, false otherwise
 */
  auto first_pos = snake_pos.first();
  bool x_is_same = first_pos.first == food_pos.first;
  bool y_is_same = first_pos.second == food_pos.second;
  return x_is_same && y_is_same;
}

bool snake::check_boundary() {
/* check if snake fits boundary conditions
 * return true if it does, false otherwise
 */
  auto first_pos = snake_pos.first();
  bool x_is_valid = first_pos.first < max_size.first && first_pos.first > 0;
  bool y_is_valid = first_pos.second < max_size.second && first_pos.second > 0;
  return x_is_valid && y_is_valid;
}

bool snake::check_overlap() {
/* check that snake doesn't run into himself
 */
  return snake_pos.count_occurances(snake_pos.first()) <= 1;
}

/* Catalina Vajiac
 * CSE 20311 Final Project
 * snake.h
 * header file for snake object
 */

#include <ctime>
#include <utility>
#include "./list.h"

typedef std::pair<int, int> int_pair_t;

class snake {
  public:
    // constructor/destructor
    snake();
    ~snake();

    // get/set methods
    void set_snake_pos(LinkedList);
    void set_food_pos(int_pair_t);
    void set_size_square(int);
    void set_vel(int_pair_t);
    void set_size(int_pair_t);

    LinkedList get_snake_pos();
    int_pair_t get_food_pos();
    int get_size_square();
    int_pair_t get_vel();
    int_pair_t get_size();

    // other methods
    void display();
    void draw_square(int_pair_t);
    bool move();
    bool check_boundary();
    bool check_overlap();
    bool ate_food();

  private:
    LinkedList snake_pos;
    int_pair_t food_pos;
    int_pair_t max_size;
    int size_square;
    int_pair_t vel;
};

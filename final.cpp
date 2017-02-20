/* Catalina Vajiac
 * CSE 20311 Final Project
 * final.cpp
 */

#include <unistd.h>
#include <iostream>
#include "./snake.h"
#include "./gfxnew.h"

int main() {
  bool play_again = true;
  while (play_again) {
    bool is_valid = true;
    snake S;
    S.display();
    while (is_valid) {
      is_valid = S.move();
      if (is_valid) {
        S.display();
      } else {
        int center_x = S.get_size().first / 2;
        int center_y = S.get_size().second / 2;
        gfx_text(center_x - 30, center_y, "Game Over!");
        gfx_text(center_x - 130, center_y + 24, "Press Q to quit or any other key to play again");
        gfx_flush();
        usleep(10000);
        play_again = gfx_wait() != 'q';
      }
    }
  }
}

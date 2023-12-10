#ifndef GAME_HPP
#define GAME_HPP

#include <rgb_lcd.h>
#include "Character.hpp"

class Game {
private:
  rgb_lcd lcd;
  const int BUTTON_PIN = D8;
  const int LED_PIN = D5;
  const int BUZZER_PIN = D6;
  const int LCD_COLS = 16;
  const int LCD_ROWS = 2;
  int selectedCharacter;
  int characterPosition;
  int jumpHeight;
  bool isJumping;
  bool buttonPressed;
  bool characterSelected;
  int totalHeart;
  int obstaclePosition;
  Character* currentCharacter;

public:
  Game();
  void setup();
  void loop();
};

#endif

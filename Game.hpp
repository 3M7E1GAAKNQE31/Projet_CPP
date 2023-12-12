#ifndef GAME_HPP
#define GAME_HPP

#include <Arduino.h>


#include <Wire.h>
#include <rgb_lcd.h>
extern rgb_lcd lcd;

#define BUTTON_PIN D8
#define LED_PIN D5
//#define BUZZER_PIN D6
#define LCD_COLS 16
#define LCD_ROWS 2

class Game {
  
public : 
  int selectedCharacter;
  int characterPosition;
  int jumpHeight;
  bool isJumping;
  bool buttonPressed;
  bool characterSelected;
  int totalHeart;
  int obstaclePosition;
  
  // Constructeur
  Game();

  // Destructeur
  ~Game();
  
  void setup();
  void loop();
  
};

#endif

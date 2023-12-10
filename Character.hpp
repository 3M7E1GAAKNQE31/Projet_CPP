#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <rgb_lcd.h>

class Character {
public:
  virtual void display() = 0;
};

class AlienCharacter : public Character {
public:
  void display() override;
};

class SkullCharacter : public Character {
public:
  void display() override;
};

#endif

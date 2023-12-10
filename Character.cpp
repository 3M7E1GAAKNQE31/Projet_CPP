#include "Character.hpp"

void AlienCharacter::display() {
  lcd.write(byte(2));
}

void SkullCharacter::display() {
  lcd.write(byte(6));
}

#include <Wire.h>
#include <rgb_lcd.h>

#define BUTTON_PIN D8
#define LCD_COLS 16
#define LCD_ROWS 2

rgb_lcd lcd;

byte Alien[] = {
  B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011,
  B00000
};

byte Skull[] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};

int selectedCharacter = 0;
bool buttonPressed = false;
bool characterSelected = false;
bool gameOver = false;

int characterPosition = 1; // Position verticale du personnage sur l'écran LCD
int jumpHeight = 3; // Hauteur du saut du personnage
bool isJumping = false; // Variable pour suivre l'état du saut du personnage

int obstaclePosition = LCD_COLS - 1; // Position de départ de l'obstacle à l'extrême droite

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.createChar(2, Alien);
  lcd.createChar(6, Skull);
  lcd.clear();
  lcd.print("Select a character:");

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (!characterSelected) {
    // Sélection du personnage
    if (buttonState == HIGH && !buttonPressed) {
      delay(200);
      selectedCharacter = (selectedCharacter + 1) % 2;
      buttonPressed = true;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selected: ");

      if (selectedCharacter == 0) {
        lcd.write(byte(2));
      } else {
        lcd.write(byte(6));
      }
    } else if (buttonState == LOW) {
      buttonPressed = false;
    }

    if (buttonPressed && digitalRead(BUTTON_PIN) == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Confirm?");
      lcd.setCursor(0, 1);
      lcd.print("Yes: Hold button");
      delay(1000); // Attente pour confirmer la sélection
      if (digitalRead(BUTTON_PIN) == LOW) {
        characterSelected = true;
      }
    }
  } else if (!gameOver) {
    // Vérifie si le bouton est pressé pour déclencher le saut
    if (buttonState == LOW && !buttonPressed) {
      buttonPressed = true;
      isJumping = true;
    } else if (buttonState == HIGH) {
      buttonPressed = false;
    }

    if (!isJumping) {
      // Affichage du personnage quand il ne saute pas
      lcd.clear();
      lcd.setCursor(0, characterPosition);
      if (selectedCharacter == 0) {
        lcd.write(byte(2));
      } else {
        lcd.write(byte(6));
      }

      // Affichage de l'obstacle
      lcd.setCursor(obstaclePosition, LCD_ROWS - 1);
      lcd.write('*');

      delay(200);
    } else {
      // Animation du saut avec déplacement vers la droite simulé
      for (int i = 0; i < jumpHeight; i++) {
        lcd.clear();
        lcd.setCursor(i, characterPosition - i);
        if (selectedCharacter == 0) {
          lcd.write(byte(2));
        } else {
          lcd.write(byte(6));
        }

        // Affichage de l'obstacle
        lcd.setCursor(obstaclePosition, LCD_ROWS - 1);
        lcd.write('*');

        delay(100);
      }
      
      isJumping = false;
      delay(100);
    }

    // Mise à jour de la position de l'obstacle (déplacement vers la gauche)
    obstaclePosition--;
    if (obstaclePosition < 0) {
      obstaclePosition = LCD_COLS - 1; // Réinitialisation de la position de l'obstacle à droite quand il atteint le bord gauche
    }

    // Vérification de la collision
    if (obstaclePosition == 0 && characterPosition == (LCD_ROWS - 1)) {
      gameOver = true;
    }
  } else {
    // Affichage de "Game Over" une fois que le jeu est terminé
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over");
  }
}

#include "Game.hpp"
#include "Buzzer.hpp"

#include <Arduino.h>


//ok fonctionnel : avec buzzer en lib
//                 voir lib led
//                 voir lib boutton
//                 voir lib capteur : buzzer/led/bouton
//                 lib pour charactere a eviter



rgb_lcd lcd;
Buzzer buzzer;

byte Alien[] =
{ B11111,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B11011,
  B00000};

byte Skull[] = 
 {B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000};  

byte Heart[] = {
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B00100,
  B00000};

Game::Game() {
}

Game::~Game() {
}



void Game::setup() {

  //initialisation des variables
  selectedCharacter = 0;
  buttonPressed = false;
  characterSelected = false;
  characterPosition = 0;            // Position verticale du personnage sur l'écran LCD
  jumpHeight = 4;                   // Hauteur du saut du personnage
  isJumping = false;                // Variable pour suivre l'état du saut du personnage
  totalHeart = 3;                   // Nombre de vies que l'on a au loncement du jeu
  obstaclePosition = LCD_COLS - 1;  // Position de départ de l'obstacle à l'extrême droite
  
  
  //initialisation des E/S
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.setRGB(255,255,255);
  
  lcd.createChar(2, Alien);
  lcd.createChar(6, Skull);
  lcd.createChar(3, Heart);
  
  lcd.clear();
  lcd.print("Jumping game");
  delay(3000);
  
}




void Game::loop() {
  
  int buttonState = digitalRead(BUTTON_PIN);
  lcd.setRGB(255,255,255);

  //Gestion de la sélection du personnage
  if (!characterSelected) {
    if(!buttonPressed){
      selectedCharacter = (selectedCharacter + 1) % 2;
      buzzer.BuzzOff();  //digitalWrite(BUZZER_PIN, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selected: ");

      if (selectedCharacter == 0) {
        lcd.write(byte(2));
      } else {
        lcd.write(byte(6));
      }
      delay(800);
    }



    //Gestion du jeux 
    if(digitalRead(BUTTON_PIN) == HIGH){
        buttonPressed = true;
        characterSelected = true;

        lcd.clear();
        for(int i = 0;i<4;i++){
          switch(i){
            case 0:
              lcd.setCursor(1,0);
              lcd.write("3, ");
              break;
            case 1:
              lcd.setCursor(4,0);
              lcd.write("2, ");
              break;
            case 2:
              lcd.setCursor(7,0);
              lcd.write("1, ");
              break;
            default:
              lcd.setCursor(10,0);
              lcd.write("Go!!");
              break;
          }
          delay(400);
        }
        digitalWrite(LED_PIN, HIGH);
    }
  } 
  else {
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
      if(characterPosition != 0){
        characterPosition -= 1;
      }
      lcd.setCursor(characterPosition, 1);
      if (selectedCharacter == 0) {
        lcd.write(byte(2));
      } else {
        lcd.write(byte(6));
      }

      // Affichage de l'obstacle
      lcd.setCursor(obstaclePosition, LCD_ROWS - 1);
      lcd.write('*');

      //Affichage des coeurs du personnage
      for (int i = 0; i <= totalHeart; i++) {
        lcd.setCursor(LCD_COLS - i , 0);
        lcd.write(byte(3));
      }

      delay(200);
    } else {
      // Animation du saut avec déplacement vers la droite simulé
      for (int i = 0; i < jumpHeight; i++) {
        lcd.clear();
        if(i<=jumpHeight-1){
          lcd.setCursor(i, 0);
        }else{
          lcd.setCursor(i, 1);
        }
        
        if (selectedCharacter == 0) {
        lcd.write(byte(2));
        } else {
        lcd.write(byte(6));
        }
        characterPosition = 4;

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
      obstaclePosition = LCD_COLS - 1; 
    }

    // Vérification de la collision entre le personnage et l'obstacle
    if (obstaclePosition == 0) {
      if (characterPosition == 0) {
        if(totalHeart == 0) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("XX Game Over! XX");
          lcd.setRGB(255,0,0);
          buzzer.BuzzOn();  //digitalWrite(BUZZER_PIN, HIGH);
          digitalWrite(LED_PIN, LOW);
          delay(3000); 
          characterSelected = false; // Réinitialisation du jeu après la collision
          obstaclePosition = LCD_COLS - 1; 
          isJumping = false; // Réinitialisation de l'état de saut du personnage
          totalHeart = 3 ;
          buttonPressed = false;
        }
        else{
          totalHeart -= 1 ;
          buzzer.BuzzOn();  //digitalWrite(BUZZER_PIN, LOW);
          lcd.setRGB(255,50,50);
          delay(1000);
          buzzer.BuzzOff();
          lcd.setRGB(255,255,255);

        }
      }
  }}
}

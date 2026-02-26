
// SIMPLE DINO GAME!

#include <LiquidCrystal.h>
#include <string.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int screenPositions[16][2];


bool isGameOver = false;
int score = 0;

class Object {
  public: 
  String icon;
  bool isPlayer;
  int xPos;
  int yPos;
  bool isJumping = false;
  const int jumpAirTimeLimit = 10;
  int timeJumping = 0;

  Object(String i, bool e, int x, int y)
  {
    icon = i; 
    isPlayer = e;
    xPos = x;
    yPos = y;
  }
};


Object player("E",true, 1,1);
Object hurdle("o", false, 15,1);


void setup() {
  // put your setup code here, to run once:
  
 
  

  pinMode(8, INPUT);  
  lcd.begin(16,2);

  lcd.setCursor(player.xPos, player.yPos);
  lcd.print(player.icon);
  lcd.setCursor(hurdle.xPos, hurdle.yPos);
  lcd.print(hurdle.icon);
  
}

void loop() {
  
  if(!isGameOver)
  {
    lcd.clear();
    lcd.setCursor(player.xPos, player.yPos);
    lcd.print(player.icon);
    lcd.setCursor(hurdle.xPos, hurdle.yPos);
    lcd.print(hurdle.icon);
    lcd.setCursor(3,0);
    lcd.print("Score: ");
    lcd.setCursor( 11, 0);
    lcd.print(score);


    if(digitalRead(8) == HIGH && !player.isJumping)  
    {
      player.yPos = 0;
      player.timeJumping = 0;
      player.isJumping = true;
    }
     delay(100);
  
        if(player.isJumping)
        {
          player.timeJumping++;
          if(player.timeJumping >= player.jumpAirTimeLimit)
          {
            player.yPos = 1;
            player.isJumping = false; 
          }

        }
        if(hurdle.xPos == player.xPos &&  hurdle.yPos == player.yPos)
        {
          isGameOver = true;
        }
        hurdle.xPos--;
        if(hurdle.xPos < 0)
        {
          hurdle.xPos = 15;
          score++;
  }
  
  }
  else
  {
    lcd.clear();
    lcd.print("Game Over!");
    lcd.setCursor(0,1);
    lcd.print("You scored: ");
    lcd.setCursor(14, 1);
    lcd.print(score);
    delay(100);
      if(digitalRead(8) == HIGH)
    {
      isGameOver = false;
      score = 0;
      hurdle.xPos = 15;
      player.yPos = 1;
      player.isJumping = false;
    }

  
      
  }
}

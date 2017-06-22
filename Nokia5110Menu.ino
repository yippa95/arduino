#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

boolean backlight = true;
int contrast=50;

int menuitem = 1;
int page = 1;
float eggmaxt=37.7;
float eggmint=37.4;
int eggmaxh=60;
int eggminh=55;
volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544( 5, 4, 3);

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(7,OUTPUT);

  digitalWrite(7,LOW); //Turn Backlight ON
  
  Serial.begin(9600);
  
  display.begin();      
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay(); 
  display.display();   
}

void loop() {
  
  drawMenu();

  downButtonState = digitalRead(2);
  selectButtonState = digitalRead(1);
  upButtonState =   digitalRead(0);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

  if (up && page == 1 ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }else if (up && page == 2 ) {
    up = false;
   menuitem--;
     if(menuitem==3)
  menuitem=6;
  }


  if (down ) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
    }      
  }else if (down ) {
    down = false;
    if(page == 2 && menuitem==4){
       down = false;
       eggmaxt=eggmaxt-0.1;
      }
  if(page == 2 && menuitem==5){
       down = false;
       eggmint=eggmint-0.1;
      }
  
  }


  if (middle) {
    middle = false;
    
    if (page == 1 && menuitem==2) 
    {
      if (backlight) 
      {
        backlight = false;
        turnBacklightOff();
        }
      else 
      {
        backlight = true; 
        turnBacklightOn();
       }
    }

    if(page == 1 && menuitem ==3)
    {
      resetDefaults();
    }


else if (page == 1 && menuitem==1) {
      page=2;
     menuitem=4;
     }
else if (page == 2 && menuitem==4) {
      eggmaxt=eggmaxt+0.1;
     }
   else if (page == 2 && menuitem==5) {
      eggmint=eggmint+0.1;
     }
   
   
   
   
   }
   
  }

  void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
    }
    delay(50);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}

  
  void drawMenu()
  {
    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("AYARLAR");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">SICAKLIK");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print("NEM ");
    
    
    display.display();
    
    if (menuitem==3) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }  
    display.setCursor(0, 35);
    display.print(">Reset");
    display.display();
  }
    
 
  else if (page==2) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("SICAKLIK");
    display.drawFastHLine(0,10,83,BLACK);
if (menuitem==4) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(5, 15);
    display.print("MAX ");
    display.setTextSize(1);
    display.setCursor(40, 15);
    display.print(eggmaxt);
if (menuitem==5) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(5, 25);
    display.print("MIN ");
    display.setTextSize(1);
    display.setCursor(40, 25);
    display.print(eggmint);
    if (menuitem==6) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(5, 35);
    display.print("GERI ");
    display.setTextSize(1);
   
 
    
    
    display.setTextSize(1);
    display.display();
  }
  
  }

  void resetDefaults()
  {
    contrast = 50;
    setContrast();
    backlight = true;
    turnBacklightOn();
  }

  void setContrast()
  {
    display.setContrast(contrast);
    display.display();
  }

  void turnBacklightOn()
  {
    digitalWrite(7,LOW);
  }

    void turnBacklightOff()
  {
    digitalWrite(7,HIGH);
  }




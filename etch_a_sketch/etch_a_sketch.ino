/* 
  Deltabeard - 2014
  Released under the MIT License. See LICENSE for more information.
  See README.md for information on how to use this program.
*/

#include <SPI.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Below is the guide for normal Nokia 5110 LCDs.
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

// Below is the command I had to use to initialise my Nokia 5110 LCD. It will probably be different for you.
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 7, 12, 10);

// Initialising variables for JoyStick Shield V1.A
const byte up_button = 2;    // A
const byte right_button = 3; // B
const byte down_button = 4;  // C
const byte left_button = 5;  // D
const byte start_button = 6;
const byte select_button = 7;
const byte analog_button = 8;
byte x_axis = A0;
byte y_axis = A1;
byte buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, analog_button};

// Resolution of LCD
byte x = 24;
byte y = 42;

byte xmove = 130;
byte ymove = 130;

byte menu_item = 0;

void setup() {  
  //Initialise the Joystick shield
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(1000);

  
}

void loop() {
  mainmenu();
}

void mainmenu() {
  clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  // not println because cursor goes to a new line anyway
  // because the string the largest that can printed on one line.
  display.print("Control using:");
  display.println("A:Analog 1:1");
  display.println("B:Analog");
  display.println("C:Digital");
  display.display();
  while(menu_item == 0) {
    if(digitalRead(up_button) == 0) {
      menu_item = 1;
      usinganalogmapped();
    } else if(digitalRead(right_button) == 0) {
      menu_item = 2;
      usinganalog();
    } else if(digitalRead(down_button) == 0) {
      menu_item = 3;
      usingbuttons();
    }
  }
}

void usinganalog() {
  clearDisplay();
  x = 42;
  y = 24;
  
  while(menu_item == 2) {
    xmove = constrain((map(analogRead(x_axis), 0, 672, 0, 255)), 0, 255);
    ymove = constrain((map(analogRead(y_axis), 0, 672, 0, 255)), 0, 255);
    
    if (xmove < 125) {
      x--;
    } else if (130 < xmove) {
      x++;
    }
    if (ymove < 125) {
      y++;
    } else if (130 < ymove) {
      y--;
    }

    // draw a single pixel
    display.drawPixel(x, y, BLACK);
    display.display();
    delay(20);
    
    if(digitalRead(start_button) == 0) {
      menu_item = 0;
      mainmenu();
    } 
  }
}


void usingbuttons() {
  clearDisplay();
  x = 42;
  y = 24;
  delay(200);
  while(menu_item == 3) {
    if(digitalRead(up_button) == 0) {
      y--;
    }
    if(digitalRead(down_button) == 0) {
      y++;
    }
    if(digitalRead(right_button) == 0) {
      x++;
    }
    if(digitalRead(left_button) == 0) {
      x--;
    }
  
  // draw a single pixel
    display.drawPixel(x, y, BLACK);
    display.display();
    delay(20);
    
    if(digitalRead(start_button) == 0) {
      menu_item = 0;
      mainmenu();
    }
  }
}

void usinganalogmapped() {
  clearDisplay();
  while(menu_item == 1) {
    x = constrain((map(analogRead(x_axis), 0, 672, 0, 84)), 0, 83);
    y = constrain((map(analogRead(y_axis), 0, 672, 0, 48)), 0, 47);
    
  // inversing y - because without this,
  // pushing the analog stick up moves the pixel down.
    y = 47 - y;  

  // draw a single pixel
    display.drawPixel(x, y, BLACK);
    display.display();
    delay(20);
    
    if(digitalRead(start_button) == 0) {
      menu_item = 0;
      mainmenu();
    }
  }
}

void clearDisplay() {
  display.clearDisplay();   // clears the screen and buffer
}

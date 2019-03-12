/* This is the code that runs the fish (Charlie's) feeding time */
/* This was developed by Emmanuel Ogunjirin */

/* 
 *  LCD INSTRUCTIONS: See https://www.arduino.cc/en/Tutorial/LiquidCrystalSerialDisplay
 *  LCD RS pin to digital pin 12
 *  LCD Enable pin to digital pin 11
 *  LCD D4 pin to digital pin 5
 *  LCD D5 pin to digital pin 4
 *  LCD D6 pin to digital pin 3
 *  LCD D7 pin to digital pin 2
 *  LCD R/W pin to ground
 *  10K resistor:
 *  Ends to +5V and ground
 *  Wiper to LCD VO pin (pin 3)
*/

// Includes needed Libraries.
#include <Servo.h>    // Servo library from Arduino.  
#include <LiquidCrystal.h>  // The LCD Library. 

// Declaration Pins. 
int angle = 0;    // Sets the starting angle to 0 degrees. 
int servoPin = 13;   // Makes the servo pin equal to pin 10.
int redLight = 9;   // Makes the red LED pin 9
int yellowLight = 8;  // Makes the yellow LED pin 8
int greenLight = 7;   // Makes the green LED pin 7
int Hours = 11;    // Amount of hours you want to wait for.
int Minutes = 59;    // Amount of minutes you want to wait for. 
int Seconds = 59;    // Amount of seconds you want to wait for. 
const int rs = 12;   // Initializes the LCD Pins. 
const int en = 11;   // Initializes the LCD Pins. 
const int d4 = 5;    // Initializes the LCD Pins. 
const int d5 = 4;    // Initializes the LCD Pins. 
const int d6 = 3;    // Initializes the LCD Pins. 
const int d7 = 2;    // Initializes the LCD Pins.

// Variables. 
Servo feedingServo;   // This is the feeding variable used by the system. 
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);   // These are the LCD Pins. 

// This is run the first time the project is started. 
void setup() 
{
  Serial.begin(9600); // Allows the viewing of data from the Serial Monitor.
  lcd.begin(16, 2);   // Allows us to start the LCD screen. 
  lcd.print("WELCOME!"); // Prints a welcome message. 
  feedingServo.attach(servoPin); // Makes pin 10 behave as the servo variable above.
  pinMode(redLight, OUTPUT);  // Activates the red LED.
  pinMode(yellowLight, OUTPUT); // Activates the yellow LED.
  pinMode(greenLight, OUTPUT);  // Activates the green LED. 
  Serial.println("Serial Monitor started, All Systems Go!");   // System Readiness Level.
  Serial.println();   // Blank line.
  delay(2000);    // Waits a little for system and user. 
}

// This is run on a loop constantly by the system. 
void loop() 
{
  lcd.clear();   // Clears the LCD of any words.
  lightson();   // Turns on all the lights!
  delay(2000);  // Waits for 2 seconds. 
  lightsoff();  // Turns off all the lights!
  
  /* First Rotation of the Servo */
  for (angle = 0; angle < 180; angle += 1)   // Turns the Servo Motor to 180 degrees.
  {
    Serial.println("Green Light On"); // Prints that the Green light is on
    green(); // Turns on the green light. 
    Serial.println("Begin Feeding Charlie..."); // Prints that Charlie is being fed.
    lcd.print("Feeding...");   // Displays what is on the serial monitor on the LCD
    Serial.println();   // Blank line.

    feedingServo.write(angle);   // Rotates the motor to the angle that is specified.
    delay(15);   // Waits a little for the motor to catch up.
    lcd.clear();    // Clears the LCD of any words. 
  }

  /* Second Rotation of the Servo */
  for (angle = 180; angle >= 1; angle -= 1)    // Turns the Servo Motor back to 0 degrees. 
  {
    Serial.println("Red Light On"); // Prints that the Red light is on
    red(); // Turns on the red light.
    Serial.println("End Feeding Charlie..."); // Prints Charlie has stopped being fed.
    lcd.print("Not Feeding...");   // Displays what is on the serial monitor on the LCD
    Serial.println();    // Blank line.
        
    feedingServo.write(angle);   // Rotates the motor to the angle that is specified.
    delay(15);   // Waits a little for the motor to catch up.
    lcd.clear();   // Clears the LCD of any words. 
  }
    
  /* This is how long you want to wait before repeating the process again (in Milliseconds) */
  while (Hours > 0 || Minutes > 0 || Seconds >= 0) 
  {
    Serial.println("Green Light On"); // Prints that the Yellow light is on
    yellow(); // Turns on the yellow light.

    lcd.setCursor(0, 0);  // Sets the cursor to the specified coordinates. 
    lcd.print("Next Feeding in ");   // Prints the text above time. 

    lcd.setCursor(4, 2);  // Sets the cursor to the specified coordinates.
       
    (Hours < 10) ? lcd.print("0") : NULL; // Checks if hours is less than 10
    lcd.print(Hours); // Prints hours
    lcd.print(":"); // Prints separator. 
      
    (Minutes < 10) ? lcd.print("0") : NULL; // Checks if minutes is less than 10
    lcd.print(Minutes); // Prints minutes
    lcd.print(":"); // Prints separator. 
      
    (Seconds < 10) ? lcd.print("0") : NULL; // Checks if seconds is less than 10
    lcd.print(Seconds); // Prints seconds
      
    lcd.display();  // LCD displays the called attributes. 

    Serial.println("Starting Timer");   // Prints that the timer is starting. 
    times();    // Calls the times function.
    Serial.println("Second Timer");   // Prints that the timer is ending. 
    delay(1000);  // Gives the system a break. 
   }
}


/* The code that runs the timer countdown and keeps the time till next feed */
void times()
{ 
  if (Seconds > 0)  // Checks if seconds is 0.
  {
    Seconds -= 1;   // Subtracts 1 from seconds.
  } 
  
  else 
  {
    if (Minutes > 0)    // Checks if minutes is 0.
    {
      Seconds = 59;     // Sets seconds to 59. 
      Minutes -= 1;   // Subtracts 1 from minutes.
    } 
  
    else 
    {
      if (Hours > 0)  // Checks if hours is 0
      {
        Seconds = 59;   // Sets seconds to 59. 
        Minutes = 59;   // Sets minutes to 59. 
        Hours -= 1;   // Subtracts 1 from hours
      } 
      else
      {
        Seconds = 59;     // Resets seconds to 59. 
        Minutes = 59;     // Resets seconds to 59. 
        Hours = 11;     // Resets hours to 11.
        loop();     // Calls Loop again from the start and re-runs process.   
      }
    }
  }
}


// Turns on the Yellow Light.
void yellow()
{
  digitalWrite(redLight, LOW);  // Deactivates the red LED.
  digitalWrite(yellowLight, HIGH); // Activates the yellow LED.
  digitalWrite(greenLight, LOW);  // Deactivates the green LED.
}

// Turns on the Red Light.
void red()
{
  digitalWrite(redLight, HIGH);  // Activates the red LED.
  digitalWrite(yellowLight, LOW); // Deactivates the yellow LED.
  digitalWrite(greenLight, LOW);  // Deactivates the green LED. 
}

// Turns on the Green Light. 
void green()
{
  digitalWrite(redLight, LOW);  // Deactivates the red LED.
  digitalWrite(yellowLight, LOW); // Deactivates the yellow LED.
  digitalWrite(greenLight, HIGH);  // Activates the green LED.
}

// Turns on all the lights.
void lightson()
{
  digitalWrite(redLight, HIGH);  // Activates the red LED.
  digitalWrite(yellowLight, HIGH); // Activates the yellow LED.
  digitalWrite(greenLight, HIGH);  // Activates the green LED.
}

// Turns off all the lights. 
void lightsoff()
{
  digitalWrite(redLight, LOW);  // Deactivates the red LED.
  digitalWrite(yellowLight, LOW); // Deactivates the yellow LED.
  digitalWrite(greenLight, LOW);  // Deactivates the green LED.
}


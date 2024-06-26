    // This sketch combines servo turnout control, sensor inputs and other outputs

// Pins 0, 1 and 2 are protected since these are used for communication
// Pin 13 is the Arduino LED pin and should not be used as an input, but can be used as an output for some applications
// Pins 20 and 21 are reserved for PWM servo control

// We will set the Arduino up to behave like a piece of CMRI hardware called a SUSIC with up to 64 slots
// Each slot has either a 24 or 32 bit input/output card
// 64 x 32 bit cards gives up to 2048 input/outputs!
// However, it's best to only set up the SUSIC with the required inputs/outputs to make the process more efficient.
// We will set cards 0 and 1 to be the sensor inputs (up to 64 inputs) and cards 2 - 5  to support 128 outputs

// Include libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CMRI.h>
#include <Auto485.h>

// CMRI Settings
#define CMRI_ADDR 1 //CMRI node address in JMRI
#define DE_PIN 2

// The number of servos connected
#define numServos 48  //currently 26 +1 for test out of 48

// Define the PCA9685 board addresses
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40); //setup the board address - defaults to 0x40 if not specified
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41); //setup the board address - defaults to 0x40 if not specified
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42); //setup the board address - defaults to 0x40 if not specified


// Setup serial communication
Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins

// Define CMRI connection with 64 inputs and 128 outputs
CMRI cmri(CMRI_ADDR, 64, 128, bus);

// Create tables to hold data about the servo positions
int Status[numServos]; //Create a table to hold the status of each turnout, signal, etc.
int Throw[numServos]; //Create a table to hold the throw value for each servo
int Close[numServos]; //Create a table to hold the close value for each servo

void setup() {
// SET PINS of arduino TO INPUT. this is non needed if a PCA9585 is used

//    for (int i=3; i<20; i++)  {
//           pinMode(i, INPUT_PULLUP);       // define sensor shield pins 3 to 19 as inputs
//        }
//        
//    for (int i=22; i<46; i++)  {
//           pinMode(i, INPUT_PULLUP);       // define sensor shield pins 22 to 45 as inputs
//        }
//
//// SET PINS of arduino TO Output. this is non needed if a PCA9585 is used
//    
//    for (int i=46; i<70; i++)  {
//           pinMode(i, OUTPUT);             // define sensor shield pins 46 to 69 as outputs
//        }

 
  Serial.begin(19200); //Baud rate of 19200, ensure this matches the baud rate in JMRI, using a faster rate can make processing faster but can also result in incomplete data
  bus.begin(19200);
  
  //INITIALISE PCA9685 BOARDS
  //Board1
  pwm1.begin();
  pwm1.setPWMFreq(50);  // This is the maximum PWM frequency
  
  //Board2
  pwm2.begin();
  pwm2.setPWMFreq(50);  // This is the maximum PWM frequency

    //Board3
  pwm3.begin();
  pwm3.setPWMFreq(50);  // This is the maximum PWM frequency

  Turnout_Setup(); 
}

void loop(){
   cmri.process();
   
   // PROCESS SERVOS
   // Assume servos start on bit 0 which corresponds to output address 1001
     for (int i = 0; i < 16; i++) {
         //Board 1 (0x40)
         Status[i] = (cmri.get_bit(i));
         if (Status[i] == 1){
             pwm1.writeMicroseconds(i, Throw[i]);
         }
         else {
             pwm1.writeMicroseconds(i, Close[i]);
         }
         
         //Board 2 (0x41)
         Status[i+16] = (cmri.get_bit(i+16));
         if (Status[i+16] == 1){
             pwm2.writeMicroseconds(i, Throw[i+16]);
         }
         else {     
             pwm2.writeMicroseconds(i, Close[i+16]);
         }
         //Board 3 (0x42)
         Status[i+32] = (cmri.get_bit(i+32));
         if (Status[i+32] == 1){
             pwm3.writeMicroseconds(i, Throw[i+32]);
         }
         else {     
             pwm3.writeMicroseconds(i, Close[i+32]);
         }
     }

   // PROCESS SENSORS
   // Only include lines that are required. This reduces processing time - delete or comment out lines that are not required
   // Ensure bit address matches pin, i.e. a sensor attached to pin 17 corresponds to bit 13 (because we've skipped pins 0, 1, 2 and 13) which is address 1014 for this CMRI node

      // Do not read 0, 1 or 2
      //cmri.set_bit(0, !digitalRead(3));  //Bit 0 = address 1001 in JMRI
      //cmri.set_bit(1, !digitalRead(4));  //Bit 1 = address 1002 in JMRI
      //cmri.set_bit(2, !digitalRead(5));  //Bit 2 = address 1003 in JMRI
      //etc.
      //Do not read 13
      //Do not read 20 or 21  

    // PROCESS OUTPUTS
    // Non servo outputs will start on bit 100, this will be address 1101 in CMRI, bit 101 will be 1102, etc.
    // Only include lines that are required. This reduces processing time - delete or comment out lines that are not required
    
      //  digitalWrite(46, cmri.get_bit(100));
      //  digitalWrite(47, cmri.get_bit(101));
      //  digitalWrite(48, cmri.get_bit(102));        
      //  etc...
      //  digitalWrite(67, cmri.get_bit(121));
      //  digitalWrite(68, cmri.get_bit(122));
      //  digitalWrite(69, cmri.get_bit(123));
}

void Turnout_Setup()  {
    //SET THE THROW AND CLOSE VALUES FOR EACH SERVO BASED ON THE CALIBRATION PROCESS
    //Servo connection 0 - point motor
    //Board 1
    
    Serial.println("Start Setup");
    Throw[0] = 1200;
    Close[0] = 1500;
    Throw[1] = 1200;
    Close[1] = 1500;
    Throw[2] = 1200;
    Close[2] = 1500;
    Throw[3] = 1200;
    Close[3] = 1500;
    Throw[4] = 1200;
    Close[4] = 1500;
    Throw[5] = 1200;
    Close[5] = 1500;    
    Throw[6] = 1200;
    Close[6] = 1500;
    Throw[7] = 1200;
    Close[7] = 1500;
    Throw[8] = 1200;
    Close[8] = 1500;    
    Throw[9] = 1200;
    Close[9] = 1500;
    Throw[10] = 1200;
    Close[10] = 1500;
    Throw[11] = 1200;
    Close[11] = 1500;
    Throw[12] = 1200;
    Close[12] = 1500;
    Throw[13] = 1200;
    Close[13] = 1500;
    Throw[14] = 1200;
    Close[14] = 1500;
    Throw[15] = 1200;
    Close[15] = 1500;
    
    //Board 2
    Throw[16] = 1200;
    Close[16] = 1500;
    Throw[17] = 1200;
    Close[17] = 1500;
    Throw[18] = 1200;
    Close[18] = 1500;
    Throw[19] = 1200;
    Close[19] = 1500;
    Throw[20] = 1200;
    Close[20] = 1500;
    Throw[21] = 1200;
    Close[21] = 1500;
    Throw[22] = 1200;
    Close[22] = 1500;
    Throw[23] = 1200;
    Close[23] = 1500;
    Throw[24] = 1200;
    Close[24] = 1500;
    Throw[25] = 1200;
    Close[25] = 1500;
    Throw[26] = 1200;
    Close[26] = 1500;
    Throw[27] = 1200;
    Close[27] = 1500;
    Throw[28] = 1200;
    Close[28] = 1500;
    Throw[29] = 1200;
    Close[29] = 1500;
    Throw[30] = 1200;
    Close[30] = 1500;
    Throw[31] = 1200;  //used for test
    Close[31] = 1500;
    
    //Board 3
    Throw[32] = 1200;
    Close[32] = 1500;
    Throw[33] = 1200;
    Close[33] = 1500;
    Throw[34] = 1200;
    Close[34] = 1500;
    Throw[35] = 1200;
    Close[35] = 1500;
    Throw[36] = 1200;
    Close[36] = 1500;
    Throw[37] = 1200;
    Close[37] = 1500;
    Throw[38] = 1200;
    Close[38] = 1500;
    Throw[39] = 1200;
    Close[39] = 1500;
    Throw[40] = 1200;
    Close[40] = 1500;
    Throw[41] = 1200;
    Close[41] = 1500;
    Throw[42] = 1200;
    Close[42] = 1500;
    Throw[43] = 1200;
    Close[43] = 1500;
    Throw[44] = 1200;
    Close[44] = 1500;
    Throw[45] = 1200;
    Close[45] = 1500;
    Throw[46] = 1200;
    Close[46] = 1500;
    Throw[47] = 1200;
    Close[47] = 1500;
}

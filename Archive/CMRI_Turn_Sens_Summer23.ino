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
#include <CMRI.h>
#include <Auto485.h>
#include <Servo.h>
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// CMRI Settings
#define CMRI_ADDR 1 //CMRI node address in JMRI
#define DE_PIN 2

// The number of servos connected
#define numServos 30

Servo myServos[numServos];
// Setup serial communication
Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
 
// Define CMRI connection with 64 inputs and 32 outputs
//CMRI cmri(CMRI_ADDR, 64, 32, bus);

// Define CMRI connection with 64 inputs and 128 outputs
CMRI cmri(CMRI_ADDR, 64, 128, bus);

// Create tables to hold data about the servo positions
int Status[numServos]; //Create a table to hold the status of each turnout, signal, etc.
int Throw[numServos]; //Create a table to hold the throw value for each servo
int Close[numServos]; //Create a table to hold the close value for each servo

void setup() {

  // Set pins 3-19 and 22-69 as input pins for sensors
  
    for (int i=3; i<20; i++)  {
           pinMode(i, INPUT_PULLUP);       // set sensor shield pins 3-19 as inputs
           myServos[i].attach(i);
        }
        
    for (int i=22; i<50; i++)  {
           pinMode(i, INPUT_PULLUP);       // set sensor shield pins 22-49 as inputs
        }
    
    for (int i=50; i<70; i++)  {
       pinMode(i, OUTPUT);       // set sensor shield pins 50-69 as outputs
      }
        
  // Start the serial connection
  Serial.begin(19200);  //Baud rate of 19200, ensure this matches the baud rate in JMRI, using a faster rate can make processing faster but can also result in incomplete data
  bus.begin(19200);
  
   // SET THE THROW AND CLOSE VALUES FOR EACH SERVO BASED ON THE CALIBRATION PROCESS

  Throw[2] = 130;
  Close[2] = 90;
  myServos[2].attach(2);
 
  Throw[3] = 110; 
  Close[3] = 85;
  myServos[3].attach(3);
  
  Throw[4] = 107; 
  Close[4] = 90;
  myServos[4].attach(4);
  
  Throw[5] = 110; 
  Close[5] = 85;
  myServos[5].attach(5);
  
  Throw[6] = 100; 
  Close[6] = 80; 
  myServos[6].attach(6);
  

  Throw[7] = 113; 
  Close[7] = 85;
  myServos[7].attach(7);
    
  Throw[8] = 105;
  Close[8] = 85;
  myServos[8].attach(8);
  
  Throw[9] = 105;
  Close[9] = 85;
  myServos[9].attach(9);
  
  Throw[10] = 110;
  Close[10] = 85;
  myServos[10].attach(10);
 
  Throw[11] = 105;
  Close[11] = 85;
  myServos[11].attach(11);
  
  Throw[12] = 80;
  Close[12] = 100;
  myServos[12].attach(12);
  
// PIN 13 canno be used
 
  Throw[14] = 97; //55
  Close[14] = 73;
  myServos[14].attach(14);
  
  Throw[15] = 108; //105
  Close[15] = 85;
  myServos[15].attach(15);

  Throw[16] = 105;
  Close[16] = 85;
  myServos[16].attach(16);
   
  Throw[17] = 105;
  Close[17] = 85;
  myServos[17].attach(17);

  Throw[18] = 105;
  Close[18] = 85;
  myServos[18].attach(18);
  
  Throw[19] = 105;
  Close[19] = 85;
  myServos[19].attach(19);
  
// PIN 20 cannot be used
// PIN 21 cannot be used

  Throw[22] = 45;
  Close[22] = 70;
  myServos[22].attach(22);

  Throw[23] = 85;
  Close[23] = 105;
  myServos[23].attach(23);
}

void loop(){
   cmri.process();

   // PROCESS SERVOS
   // Assume servos start on bit 0 which corresponds to output address 1001 and i-1 as cmri bit
     for (int i = 3; i < numServos; i++) {
         Status[i] = (cmri.get_bit(i-1));
         if (Status[i] == 1){
             myServos[i].write(Throw[i]);
             
         }
         else {
             myServos[i].write( Close[i]);
            
         }
     }

   // PROCESS SENSORS
   // Only include lines that are required. This reduces processing time - delete or comment out lines that are not required
   // Ensure bit address matches pin, i.e. a sensor attached to pin 17 corresponds to bit 13 (because we've skipped pins 0, 1, 2 and 13) which is address 1014 for this CMRI node

     // Do not read 0, 1 or 2
     cmri.set_bit(0, !digitalRead(46));  //Bit 0 = address 1001 in JMRI
     cmri.set_bit(1, !digitalRead(47));  
     cmri.set_bit(2, !digitalRead(48));  
     cmri.set_bit(3, !digitalRead(49));  
//     cmri.set_bit(4, !digitalRead(50));  
//     cmri.set_bit(5, !digitalRead(51));  //Bit 5 = address 1006 in JMRI
//     cmri.set_bit(6, !digitalRead(52));  
//     cmri.set_bit(7, !digitalRead(53));  
//     cmri.set_bit(8, !digitalRead(32));  //Bit 9 = address 109 in JMRI
//     cmri.set_bit(9, !digitalRead(33));  //Bit 0 = address 1001 in JMRI
//     cmri.set_bit(10, !digitalRead(34));  
//     cmri.set_bit(11, !digitalRead(35));  
//     cmri.set_bit(12, !digitalRead(36));  
//     cmri.set_bit(14, !digitalRead(37));  
//     cmri.set_bit(15, !digitalRead(38));  //Bit 5 = address 1006 in JMRI
//     cmri.set_bit(16, !digitalRead(39));  
//     cmri.set_bit(17, !digitalRead(40));  
//     cmri.set_bit(18, !digitalRead(41));  //Bit 9 = address 109 in JMRI
//     cmri.set_bit(19, !digitalRead(42));  //Bit 0 = address 1001 in JMRI
//     cmri.set_bit(22, !digitalRead(43));    
//     cmri.set_bit(22, !digitalRead(44));  
//     cmri.set_bit(23, !digitalRead(45));  //Bit 5 = address 1006 in JMRI
//     cmri.set_bit(24, !digitalRead(46));  
//     cmri.set_bit(25, !digitalRead(47));  
//     cmri.set_bit(26, !digitalRead(48));  //Bit 9 = address 109 in JMRI
//     cmri.set_bit(27, !digitalRead(49));  
//     cmri.set_bit(28, !digitalRead(50));  //Bit 9 = address 109 in JMR
//     cmri.set_bit(29, !digitalRead(51));  //Bit 9 = address 109 in JMRI
//     cmri.set_bit(29, !digitalRead(52));  
//     cmri.set_bit(30, !digitalRead(53));  //Bit 9 = address 109 in JMR
//     

 // PROCESS OUTPUTS
    // Non servo outputs will start on bit 100, this will be address 1101 in CMRI, bit 101 will be 1102, etc.
    // Only include lines that are required. This reduces processing time - delete or comment out lines that are not required
    
        digitalWrite(50, cmri.get_bit(100)); //Bit 100 = address 1100 in JMR
        digitalWrite(51, cmri.get_bit(101));
      //  digitalWrite(48, cmri.get_bit(102));
      //  etc...
      //  digitalWrite(67, cmri.get_bit(121));
      //  digitalWrite(68, cmri.get_bit(122));
      //  digitalWrite(69, cmri.get_bit(123));
}

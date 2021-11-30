// Q1 mini 2.0 - Quadruped Robot (Designed by Jason Workshop)
//
// Firmware version 2.0.0
// Last Update: 28 Mar 2018
//
// Jason Workshop
// Website: http://jasonworkshop.com
// FB page: http://fb.com/jasonworkshop
//
// Related documents and software
// Website: http://q1.jasonworkshop.com
// FB page: http://fb.com/Q1.JasonWorkshop
//
// 3D parts
// Website: http://thingiverse.com/thing:2311678
//
// ---------------------------------------------------------------------------------------------------------------
//
// This Firmware licensed under the Attribution-NonCommercial-ShareAlike 4.0 (CC-BY-NC-SA 4.0)
//
// Attribution: You must give appropriate credit, provide a link to the license, and indicate if changes were made.
// You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
//
// ShareAlike: If you remix, transform, or build upon the material,
// you must distribute your contributions under the same license as the original.
//
// License Deed
// http://creativecommons.org/licenses/by-sa/4.0/
//
// ---------------------------------------------------------------------------------------------------------------
//
//  -----               -----
// |  5  |             |  1  |
// | P07 |             | P02 |
//  ----- -----   ----- -----
//       |  6  | |  2  |
//       | P08 | | P03 |
//        -----   -----
//       |  7  | |  3  |
//       | P11 | | P05 |
//  ----- -----   ----- -----
// |  8  |             |  4  |
// | P16 |             | P15 |
//  -----               -----  (Top View)
//

#include <EEPROM.h>
#include <Servo.h>
#include <SoftwareSerial.h>
// ---------------------------------------------------------------------------------------------------------------

SoftwareSerial BluetoothSerial(12, 13);

String robotName = "Q1 mini"; // Robot name

const int enableCalibration = true; // Enable calibration button

// ---------------------------------------------------------------------------------------------------------------

const int numberOfServos = 8; // Number of servos
const int numberOfACE = 9; // Number of action code elements
int servoCal[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // Servo calibration data
int servoPos[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // Servo current position
int servoPrgPeriod = 20; // 20 ms
Servo servo[numberOfServos]; // Servo object

// Action code
// --------------------------------------------------------------------------------

// Servo zero position
// -------------------------- P02, P03, P05, P15, P07, P08, P11, P16
const int servoAct00 [] PROGMEM = { 135,  45, 135,  45,  45, 135,  45, 135 };

// Zero
int servoPrg00step = 1;
const int servoPrg00 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {  135,  45, 135,  45,  45, 135,  45, 135,  400  }, // zero position
};

// Standby
int servoPrg01step = 2;
const int servoPrg01 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   90,  90,  90,  90,  90,  90,  90,  90,  200  }, // servo center point
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
};

// Forward
int servoPrg02step = 11;
const int servoPrg02 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   90,  90,  90, 110, 110,  90,  45,  90,  100  }, // leg1,4 up; leg4 fw
  {   70,  90,  90, 110, 110,  90,  45,  70,  100  }, // leg1,4 dn
  {   70,  90,  90,  90,  90,  90,  45,  70,  100  }, // leg2,3 up
  {   70,  45, 135,  90,  90,  90,  90,  70,  100  }, // leg1,4 bk; leg2 fw
  {   70,  45, 135, 110, 110,  90,  90,  70,  100  }, // leg2,3 dn
  {   90,  90, 135, 110, 110,  90,  90,  90,  100  }, // leg1,4 up; leg1 fw
  {   90,  90,  90, 110, 110, 135,  90,  90,  100  }, // leg2,3 bk
  {   70,  90,  90, 110, 110, 135,  90,  70,  100  }, // leg1,4 dn
  {   70,  90,  90, 110,  90, 135,  90,  70,  100  }, // leg3 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg3 fw dn
};

// Backward
int servoPrg03step = 11;
const int servoPrg03 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   90,  45,  90, 110, 110,  90,  90,  90,  100  }, // leg4,1 up; leg1 fw
  {   70,  45,  90, 110, 110,  90,  90,  70,  100  }, // leg4,1 dn
  {   70,  45,  90,  90,  90,  90,  90,  70,  100  }, // leg3,2 up
  {   70,  90,  90,  90,  90, 135,  45,  70,  100  }, // leg4,1 bk; leg3 fw
  {   70,  90,  90, 110, 110, 135,  45,  70,  100  }, // leg3,2 dn
  {   90,  90,  90, 110, 110, 135,  90,  90,  100  }, // leg4,1 up; leg4 fw
  {   90,  90, 135, 110, 110,  90,  90,  90,  100  }, // leg3,1 bk
  {   70,  90, 135, 110, 110,  90,  90,  70,  100  }, // leg4,1 dn
  {   70,  90, 135,  90, 110,  90,  90,  70,  100  }, // leg2 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg2 fw dn
};

// Move Left
int servoPrg04step = 11;
const int servoPrg04 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   70,  90,  45,  90,  90,  90,  90,  70,  100  }, // leg3,2 up; leg2 fw
  {   70,  90,  45, 110, 110,  90,  90,  70,  100  }, // leg3,2 dn
  {   90,  90,  45, 110, 110,  90,  90,  90,  100  }, // leg1,4 up
  {   90, 135,  90, 110, 110,  45,  90,  90,  100  }, // leg3,2 bk; leg1 fw
  {   70, 135,  90, 110, 110,  45,  90,  70,  100  }, // leg1,4 dn
  {   70, 135,  90,  90,  90,  90,  90,  70,  100  }, // leg3,2 up; leg3 fw
  {   70,  90,  90,  90,  90,  90, 135,  70,  100  }, // leg1,4 bk
  {   70,  90,  90, 110, 110,  90, 135,  70,  100  }, // leg3,2 dn
  {   70,  90,  90, 110, 110,  90, 135,  90,  100  }, // leg4 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg4 fw dn
};

// Move Right
int servoPrg05step = 11;
const int servoPrg05 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   70,  90,  90,  90,  90,  45,  90,  70,  100  }, // leg2,3 up; leg3 fw
  {   70,  90,  90, 110, 110,  45,  90,  70,  100  }, // leg2,3 dn
  {   90,  90,  90, 110, 110,  45,  90,  90,  100  }, // leg4,1 up
  {   90,  90,  45, 110, 110,  90, 135,  90,  100  }, // leg2,3 bk; leg4 fw
  {   70,  90,  45, 110, 110,  90, 135,  70,  100  }, // leg4,1 dn
  {   70,  90,  90,  90,  90,  90, 135,  70,  100  }, // leg2,3 up; leg2 fw
  {   70, 135,  90,  90,  90,  90,  90,  70,  100  }, // leg4,1 bk
  {   70, 135,  90, 110, 110,  90,  90,  70,  100  }, // leg2,3 dn
  {   90, 135,  90, 110, 110,  90,  90,  70,  100  }, // leg1 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg1 fw dn
};

// Turn left
int servoPrg06step = 8;
const int servoPrg06 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   90,  90,  90, 110, 110,  90,  90,  90,  100  }, // leg1,4 up
  {   90, 135,  90, 110, 110,  90, 135,  90,  100  }, // leg1,4 turn
  {   70, 135,  90, 110, 110,  90, 135,  70,  100  }, // leg1,4 dn
  {   70, 135,  90,  90,  90,  90, 135,  70,  100  }, // leg2,3 up
  {   70, 135, 135,  90,  90, 135, 135,  70,  100  }, // leg2,3 turn
  {   70, 135, 135, 110, 110, 135, 135,  70,  100  }, // leg2,3 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg1,2,3,4 turn
};

// Turn right
int servoPrg07step = 8;
const int servoPrg07 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // standby
  {   70,  90,  90,  90,  90,  90,  90,  70,  100  }, // leg2,3 up
  {   70,  90,  45,  90,  90,  45,  90,  70,  100  }, // leg2,3 turn
  {   70,  90,  45, 110, 110,  45,  90,  70,  100  }, // leg2,3 dn
  {   90,  90,  45, 110, 110,  45,  90,  90,  100  }, // leg1,4 up
  {   90,  45,  45, 110, 110,  45,  45,  90,  100  }, // leg1,4 turn
  {   70,  45,  45, 110, 110,  45,  45,  70,  100  }, // leg1,4 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  100  }, // leg1,2,3,4 turn
};

// Lie
int servoPrg08step = 1;
const int servoPrg08 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {  110,  90,  90,  70,  70,  90,  90, 110,  500  }, // leg1,4 up
};

// Say Hi
int servoPrg09step = 4;
const int servoPrg09 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {  120,  90,  90, 110,  60,  90,  90,  70,  200  }, // leg1, 3 down
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {  120,  90,  90, 110,  60,  90,  90,  70,  200  }, // leg1, 3 down
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
};

// Fighting
int servoPrg10step = 11;
const int servoPrg10 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {  120,  90,  90, 110,  60,  90,  90,  70,  200  }, // leg1, 2 down
  {  120,  70,  70, 110,  60,  70,  70,  70,  200  }, // body turn left
  {  120, 110, 110, 110,  60, 110, 110,  70,  200  }, // body turn right
  {  120,  70,  70, 110,  60,  70,  70,  70,  200  }, // body turn left
  {  120, 110, 110, 110,  60, 110, 110,  70,  200  }, // body turn right
  {   70,  90,  90,  70, 110,  90,  90, 110,  200  }, // leg1, 2 up ; leg3, 4 down
  {   70,  70,  70,  70, 110,  70,  70, 110,  200  }, // body turn left
  {   70, 110, 110,  70, 110, 110, 110, 110,  200  }, // body turn right
  {   70,  70,  70,  70, 110,  70,  70, 110,  200  }, // body turn left
  {   70, 110, 110,  70, 110, 110, 110, 110,  200  }, // body turn right
  {   70,  90,  90,  70, 110,  90,  90, 110,  200  }  // leg1, 2 up ; leg3, 4 down
};

// Push up
int servoPrg11step = 11;
const int servoPrg11 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  300  }, // start
  {  100,  90,  90,  80,  80,  90,  90, 100,  400  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70,  500  }, // up
  {  100,  90,  90,  80,  80,  90,  90, 100,  600  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70,  700  }, // up
  {  100,  90,  90,  80,  80,  90,  90, 100, 1300  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70, 1800  }, // up
  {  135,  90,  90,  45,  45,  90,  90, 135,  200  }, // fast down
  {   70,  90,  90,  45,  60,  90,  90, 135,  500  }, // leg1 up
  {   70,  90,  90,  45, 110,  90,  90, 135,  500  }, // leg2 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  500  }  // leg3, leg4 up
};

// Sleep
int servoPrg12step = 2;
const int servoPrg12 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   30,  90,  90, 150, 150,  90,  90,  30,  200  }, // leg1,4 dn
  {   30,  45, 135, 150, 150, 135,  45,  30,  200  }, // protect myself
};

// Dancing 1
int servoPrg13step = 10;
const int servoPrg13 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   90,  90,  90,  90,  90,  90,  90,  90,  300  }, // leg1,2,3,4 up
  {   50,  90,  90,  90,  90,  90,  90,  90,  300  }, // leg1 dn
  {   90,  90,  90, 130,  90,  90,  90,  90,  300  }, // leg1 up; leg2 dn
  {   90,  90,  90,  90,  90,  90,  90,  50,  300  }, // leg2 up; leg4 dn
  {   90,  90,  90,  90, 130,  90,  90,  90,  300  }, // leg4 up; leg3 dn
  {   50,  90,  90,  90,  90,  90,  90,  90,  300  }, // leg3 up; leg1 dn
  {   90,  90,  90, 130,  90,  90,  90,  90,  300  }, // leg1 up; leg2 dn
  {   90,  90,  90,  90,  90,  90,  90,  50,  300  }, // leg2 up; leg4 dn
  {   90,  90,  90,  90, 130,  90,  90,  90,  300  }, // leg4 up; leg3 dn
  {   90,  90,  90,  90,  90,  90,  90,  90,  300  }, // leg3 up
};

// Dancing 2
int servoPrg14step = 9;
const int servoPrg14 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  45, 135, 110, 110, 135,  45,  70,  300  }, // leg1,2,3,4 two sides
  {  115,  45, 135,  65, 110, 135,  45,  70,  300  }, // leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  300  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  300  }, // leg3,4 dn; leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  300  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  300  }, // leg3,4 dn; leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  300  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  300  }, // leg3,4 dn; leg1,2 up
  {   75,  45, 135, 105, 110, 135,  45,  70,  300  }, // leg1,2 dn
};

// Dancing 3
int servoPrg15step = 10;
const int servoPrg15 [][numberOfACE] PROGMEM = {
  // P02, P03, P05, P15, P07, P08, P11, P16,  ms
  {   70,  45,  45, 110, 110, 135, 135,  70,  300  }, // leg1,2,3,4 bk
  {  110,  45,  45,  60,  70, 135, 135,  70,  300  }, // leg1,2,3 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  300  }, // leg1,2,3 dn
  {  110,  45,  45, 110,  70, 135, 135, 120,  300  }, // leg1,3,4 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  300  }, // leg1,3,4 dn
  {  110,  45,  45,  60,  70, 135, 135,  70,  300  }, // leg1,2,3 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  300  }, // leg1,2,3 dn
  {  110,  45,  45, 110,  70, 135, 135, 120,  300  }, // leg1,3,4 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  300  }, // leg1,3,4 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  300  }, // standby
};

// --------------------------------------------------------------------------------



// Setup
// --------------------------------------------------------------------------------

void setup()
{
  // EEPROM Clear (For Debug Only)
  // eepromClear();

  Serial.begin(115200); // Open serial communications
  BluetoothSerial.begin(115200);
  getServoCal(); // Get servoCal from EEP ROM

  // Servo Pin Set
  servo[0].attach(2);
  servo[1].attach(3);
  servo[2].attach(5);
  servo[3].attach(15);
  servo[4].attach(7);
  servo[5].attach(8);
  servo[6].attach(11);
  servo[7].attach(16);
  runServoPrg(servoPrg00, servoPrg00step); // zero position
}

// --------------------------------------------------------------------------------



// Loop
// --------------------------------------------------------------------------------

void loop()
{
  if (BluetoothSerial.available()) {//检测蓝牙模块串口状态
    char value = BluetoothSerial.read();
    Serial.println(value);
    // When button pressed
    if (value == '1') {
      runServoPrg(servoPrg06, servoPrg06step); // turnLeft
    } else if (value == '2') {
      runServoPrg(servoPrg02, servoPrg02step); // forward
    } else if (value == '3') {
      runServoPrg(servoPrg07, servoPrg07step); // turnRight
    } else if (value == '4') {
      runServoPrg(servoPrg04, servoPrg04step); // moveLeft
    } else if (value == '5') {
      runServoPrg(servoPrg03, servoPrg03step); // backward
    } else if (value == '6') {
      runServoPrg(servoPrg05, servoPrg05step); // moveRight
    } else if (value == '7') {
      runServoPrg(servoPrg01, servoPrg01step); // standby
    } else if (value == '8') {
      runServoPrg(servoPrg09, servoPrg09step); // sayHi
    } else if (value == '9') {
      runServoPrg(servoPrg11, servoPrg11step); // pushUp
    } else if (value == '0') {
      runServoPrg(servoPrg08, servoPrg08step); // lie
    } else if (value == 'a') {
      runServoPrg(servoPrg10, servoPrg10step); // fighting
    } else if (value == 'b') {
      runServoPrg(servoPrg12, servoPrg12step); // sleep
    } else if (value == 'c') {
      runServoPrg(servoPrg13, servoPrg13step); // dancing1
    } else if (value == 'd') {
      runServoPrg(servoPrg14, servoPrg14step); // dancing2
    } else if (value == 'e') {
      runServoPrg(servoPrg15, servoPrg15step); // dancing3
    } else if (value == 'f') {
      runServoPrg(servoPrg00, servoPrg00step); // zero position
    } else if (value == 'g') {
      clearCal(); // Clear Servo calibration data
    } else if (value == 'h') {
      calibration(0, 1);
    } else if (value == 'i') {
      calibration(0, -1);
    } else if (value == 'j') {
      calibration(1, 1);
    } else if (value == 'k') {
      calibration(1, -1);
    } else if (value == 'l') {
      calibration(2, 1);
    } else if (value == 'm') {
      calibration(2, -1);
    } else if (value == 'n') {
      calibration(3, 1);
    } else if (value == 'o') {
      calibration(3, -1);
    } else if (value == 'p') {
      calibration(4, 1);
    } else if (value == 'q') {
      calibration(4, -1);
    } else if (value == 'i') {
      calibration(5, 1);
    } else if (value == 's') {
      calibration(5, -1);
    } else if (value == 't') {
      calibration(6, 1);
    } else if (value == 'u') {
      calibration(6, -1);
    } else if (value == 'v') {
      calibration(7, 1);
    } else if (value == 'w') {
      calibration(7, -1);
    }
  }
}

// --------------------------------------------------------------------------------



// Function
// --------------------------------------------------------------------------------

// EEPROM Clear (For debug only)
void eepromClear()
{
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

// Get servoCal from EEPROM
void getServoCal()
{
  int eeAddress = 0;
  for (int i = 0; i < numberOfServos; i++) {
    EEPROM.get(eeAddress, servoCal[i]);
    eeAddress += sizeof(servoCal[i]);
  }
}

// Put servoCal to EEPROM
void putServoCal()
{
  int eeAddress = 0;
  for (int i = 0; i < numberOfServos; i++) {
    EEPROM.put(eeAddress, servoCal[i]);
    eeAddress += sizeof(servoCal[i]);
  }
}


// Clear Servo calibration data
void clearCal()
{
  for (int i = 0; i < numberOfServos; i++) {
    servoCal[i] = 0;
  }
  putServoCal(); // Put servoCal to EEPROM
  runServoPrg(servoPrg00, servoPrg00step); // zero position
}

// Calibration
void calibration(int i, int change)
{
  servoCal[i] = servoCal[i] + change;
  servo[i].write(pgm_read_word_near(servoAct00+i) + servoCal[i]);
  putServoCal(); // Put servoCal to EEPROM
  delay(400);
}

void runServoPrg(int servoPrg[][numberOfACE], int step)
{
  for (int i = 0; i < step; i++) { // Loop for step
   
    int totalTime = pgm_read_word_near(servoPrg[i]+(numberOfACE - 1)); // Total time of this step

    // Get servo start position
    for (int s = 0; s < numberOfServos; s++) {
      servoPos[s] = servo[s].read() - servoCal[s];
    }
    for (int j = 0; j < totalTime / servoPrgPeriod; j++) { // Loop for time section
      for (int k = 0; k < numberOfServos; k++) { // Loop for servo
        servo[k].write((map(j, 0, totalTime / servoPrgPeriod, servoPos[k], pgm_read_word_near(servoPrg[i]+k))) + servoCal[k]);
      }
      delay(servoPrgPeriod);
    }
  }
}

// --------------------------------------------------------------------------------


// Elegoo Uno R3 - "Inverse Kinematics Engine"
// Goal: Move the robot using Coordinate (cm) instead of Angles.

#include <math.h>

// --- MEASUREMENTS (cm) ---
float L1 = 7.0; // Shoulder to Elbow
float L2 = 7.0; // Elbow to Tip

// --- CALIBRATION FIX ---
// Your robot is physically bent 90 degrees at position 512.
// We subtract ~307 units (90 deg) to make the math match reality.
int ELBOW_OFFSET = -307; 

void setup() {
  Serial.begin(1000000); // Remember to set Serial Monitor to 1,000,000 baud
  delay(2000); 

  // Set Speed
  ax12SetSpeed(5, 100); 
  ax12SetSpeed(4, 100); 
  ax12SetSpeed(1, 100);
  
  // Center Base
  moveAx12(1, 512);
  delay(1000);

  Serial.println("--- READY ---");
}

void loop() {
  // EXAMPLE: Draw a Square to prove we can move in straight lines.
  
  // 1. Bottom Line (Move Reach OUT, keep Height same)
  for(float r=10; r<=15; r+=0.5) {
    moveToIK(r, 2);
    delay(50);
  }
  
  // 2. Right Line (Move Height UP, keep Reach same)
  for(float h=2; h<=7; h+=0.5) {
    moveToIK(15, h);
    delay(50);
  }

  // 3. Top Line (Move Reach IN, keep Height same)
  for(float r=15; r>=10; r-=0.5) {
    moveToIK(r, 7);
    delay(50);
  }

  // 4. Left Line (Move Height DOWN, keep Reach same)
  for(float h=7; h>=2; h-=0.5) {
    moveToIK(10, h);
    delay(50);
  }
}

// =========================================================
// THE INVERSE KINEMATICS ENGINE
// This function converts (Reach, Height) -> (Motor Angles)
// =========================================================
void moveToIK(float targetReach, float targetHeight) {
  // 1. Calculate Distance from Shoulder to Target
  float dist = sqrt(targetReach*targetReach + targetHeight*targetHeight);
  
  // Safety: Don't try to reach further than the arm length
  if (dist > (L1 + L2 - 0.5)) dist = L1 + L2 - 0.5;

  // 2. Inverse Kinematics Math (Law of Cosines)
  float cosTheta2 = (dist*dist - L1*L1 - L2*L2) / (2 * L1 * L2);
  
  // Clamp value to prevent math errors
  if (cosTheta2 > 1.0) cosTheta2 = 1.0;
  if (cosTheta2 < -1.0) cosTheta2 = -1.0;

  float theta2 = acos(cosTheta2); // Elbow Angle (Radians)
  float theta1 = atan2(targetHeight, targetReach) + acos((L1*L1 + dist*dist - L2*L2) / (2 * L1 * dist)); // Shoulder Angle (Radians)

  // 3. Convert Radians to Degrees
  float shoulderDeg = theta1 * (180.0 / PI);
  float elbowDeg = theta2 * (180.0 / PI);

  // 4. Convert Degrees to Servo Position (0-1023)
  // Note: We apply ELBOW_OFFSET here to fix the hardware L-shape
  int shoulderPos = 512 + (shoulderDeg * 3.41); 
  int elbowPos = 512 + ELBOW_OFFSET + (elbowDeg * 3.41); 

  // 5. Move Motors
  moveAx12(5, shoulderPos);
  moveAx12(4, elbowPos);
}

// --- STANDARD HELPER FUNCTIONS ---
void ax12SetSpeed(unsigned char ID, int Speed) {
  unsigned char checksum;
  unsigned char length = 0x05;
  unsigned char instruction = 0x03; 
  unsigned char address = 0x20; 
  unsigned char speedLow = (unsigned char)(Speed & 0xFF);
  unsigned char speedHigh = (unsigned char)((Speed >> 8) & 0xFF);
  checksum = ~(ID + length + instruction + address + speedLow + speedHigh);
  Serial.write(0xFF); Serial.write(0xFF); Serial.write(ID);
  Serial.write(length); Serial.write(instruction);
  Serial.write(address); Serial.write(speedLow); Serial.write(speedHigh);
  Serial.write(checksum);
  delay(10); 
}

void moveAx12(unsigned char ID, int Position) {
  unsigned char checksum;
  unsigned char length = 0x05;
  unsigned char instruction = 0x03; 
  unsigned char address = 0x1E; 
  unsigned char posLow = (unsigned char)(Position & 0xFF);
  unsigned char posHigh = (unsigned char)((Position >> 8) & 0xFF);
  checksum = ~(ID + length + instruction + address + posLow + posHigh);
  Serial.write(0xFF); Serial.write(0xFF); Serial.write(ID);
  Serial.write(length); Serial.write(instruction);
  Serial.write(address); Serial.write(posLow); Serial.write(posHigh);
  Serial.write(checksum);
  delay(2); 
}

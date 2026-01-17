// Elegoo Uno R3 - "3D Kinematics Tracker"
// Controls: Motor 1 (Base), Motor 5 (Shoulder), Motor 4 (Elbow)
// Output: Prints X, Y, Z coordinates

#include <math.h>

// MEASURE ROBOT (in cm)
float L1 = 7.0; // Length between Shoulder (5) and Elbow (4)
float L2 = 7.0; // Length from Elbow (4) to Tip

void setup() {
  Serial.begin(1000000);
  delay(2000);

  // Safety Speed Limits for ALL motors
  ax12SetSpeed(1, 150); // Base Motor
  ax12SetSpeed(5, 150); // Shoulder
  ax12SetSpeed(4, 150); // Elbow
  delay(100);

  // 2. Start at CENTER (Straight out, facing forward)
  moveAx12(1, 512);
  moveAx12(5, 512);
  moveAx12(4, 512);
  delay(2000);
}

void loop() {
  // Move motor from 512 (Center) to 612 (Small turn) 
  for (int i = 0; i <= 100; i++) {
    int currentPos = 512 + i;
   
    moveAx12(1, currentPos); // Base turns
    moveAx12(5, currentPos); // Shoulder lifts
    moveAx12(4, currentPos); // Elbow bends
   
    // Calculate and Print 3D Position
    calculateAndPrint3D(currentPos, currentPos, currentPos);
   
    delay(30); // Slower delay to make text readable
  }
 
  delay(1000);

  // Move Back to Center
  for (int i = 100; i >= 0; i--) {
    int currentPos = 512 + i;
   
    moveAx12(1, currentPos);
    moveAx12(5, currentPos);
    moveAx12(4, currentPos);
   
    calculateAndPrint3D(currentPos, currentPos, currentPos);
    delay(30);
  }
  delay(1000);
}

// The 3D Math Function 
void calculateAndPrint3D(int pos1, int pos5, int pos4) {
  // Convert Positions to Radians
  // (Pos - 512) is the offset from center.
  float thetaBase     = (pos1 - 512) * 0.29 * (PI / 180.0);
  float thetaShoulder = (pos5 - 512) * 0.29 * (PI / 180.0);
  float thetaElbow    = (pos4 - 512) * 0.29 * (PI / 180.0);

  // Calculate Reach (r) and Height (z)
  // This is the 2D math we did before.
  // r is how far out the arm is horizontally from the center pole.
  // z is how high the tip is off the ground (relative to shoulder height).
 
  float r = L1 * cos(thetaShoulder) + L2 * cos(thetaShoulder + thetaElbow);
  float z = L1 * sin(thetaShoulder) + L2 * sin(thetaShoulder + thetaElbow);

  // Calculate 3D X and Y based on Base Rotation
  // We take the Reach (r) and rotate it by the Base angle.
 
  float x = r * cos(thetaBase);
  float y = r * sin(thetaBase);

  // Print
  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Z: "); Serial.println(z);
}

// Helper Functions 
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

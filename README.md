# Kinematic Control of a 3-DOF Robotic Manipulator

## Overview
This project explores the mathematical modeling and control of a robotic arm using an Arduino microcontroller and Dynamixel AX-12 servos. The goal was to move beyond simple motor rotation and implement **coordinate-based control**, allowing the robot to navigate 3D space using X and Y coordinates.

## The Challenge
Controlling a robotic arm is difficult because the motors move in circles (rotational motion), but we often want the hand to move in straight lines (linear motion).
* **Forward Kinematics (Implemented):** The robot calculates the Cartesian position (X, Y, Z) of its end-effector in real-time based on joint angles.
* **Inverse Kinematics (Implemented):** The system calculates the required joint angles to reach a specific target coordinate (X, Y). This allows the robot to plan paths rather than just move motors.

## Implementation & Results
The project successfully implements the geometric algorithms required for spatial navigation:
* **Coordinate Navigation:** The robot accepts (X, Y) target commands.
* **Linear Trajectory Planning:** The software interpolates intermediate points to drive the end-effector in straight lines (e.g., vertical lifting or horizontal reaching) rather than natural arcs.
* **Shape Execution:** The system can programmatically trace geometric paths, such as a square box trajectory.

*Note: While the inverse kinematics algorithms generate linear paths, physical motion is subject to mechanical compliance and backlash inherent in the rapid-prototyping hardware.*


Manipulator
<img width="936" height="535" alt="image" src="https://github.com/user-attachments/assets/0a2d3b3f-6b05-4611-a40c-601d085fd13f" />

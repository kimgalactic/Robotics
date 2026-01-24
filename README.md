# 🦾 Kinematic Control of a 3-DOF Robotic Manipulator
### Mathematical Modeling & Motion Planning

![MATLAB](https://img.shields.io/badge/Simulation-MATLAB-orange)
![C++](https://img.shields.io/badge/Code-C%2B%2B%20%7C%20Arduino-blue)
![Math](https://img.shields.io/badge/Math-Forward%20%26%20Inverse%20Kinematics-red)

## 📝 Overview
This project moves beyond simple motor rotation by implementing **coordinate-based control** for a 3-DOF robotic arm. Using custom mathematical models, the system allows the user to input $(X, Y, Z)$ coordinates, and the robot automatically calculates the required joint angles to reach that position in 3D space.

### 🎥 Simulation Demo
[![Watch the simulation](https://img.youtube.com/vi/VIDEO_ID_HERE/0.jpg)](https://www.youtube.com/watch?v=VIDEO_ID_HERE)

> **Click the image above** to see the inverse kinematics algorithm in action.

## 🧠 Key Implementations

### 1. The Challenge
Controlling a robot arm is difficult because motors move in circles (rotational motion), but we want the hand to move in straight lines (linear motion).

### 2. The Solution
I implemented the fundamental geometric algorithms required for spatial navigation:

| Feature | Description |
| :--- | :--- |
| **Forward Kinematics (FK)** | Calculates the Cartesian position $(X, Y, Z)$ of the end-effector based on current joint angles $(\theta_1, \theta_2, \theta_3)$. |
| **Inverse Kinematics (IK)** | The reverse process: Calculates the required joint angles to reach a specific target coordinate $(X, Y)$. This allows for "Point-and-Click" control. |
| **Trajectory Planning** | Interpolates intermediate points to drive the end-effector in straight lines rather than natural arcs. |

## 💻 Tech Stack
* **Simulation:** MATLAB (Visualizing the DH-Parameters and workspace).
* **Hardware Control:** C++ / Arduino.
* **Actuators:** Dynamixel AX-12 Servos (or similar).

## 📊 Visual Results
**Inverse Kinematics Solver in MATLAB:**
![Matlab Simulation](media/matlab_sim.png)
*The figure above shows the calculated link positions required to reach the target coordinate $(4, 0, -2)$.*

## 📂 File Structure
* `ik_matlab.m`: MATLAB script for calculating Inverse Kinematics.
* `forward_kinematics.ino`: C++ code for FK implementation on the microcontroller.
* `jacobian.m`: Differential kinematics for velocity control.

---
*Created by [Abdullakim](https://github.com/Abdullakim1)*

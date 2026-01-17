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


### Manipulator
<img width="936" height="535" alt="image" src="https://github.com/user-attachments/assets/0a2d3b3f-6b05-4611-a40c-601d085fd13f" />

### DH Parameters
<img width="936" height="448" alt="image" src="https://github.com/user-attachments/assets/149ff85b-1426-4415-b6ea-4d4670cde4c7" />

### Inverse Kinematics solutions
<img width="454" height="598" alt="image" src="https://github.com/user-attachments/assets/b5988689-4ddc-4a96-81ba-77353b8a6b3d" />
<img width="435" height="591" alt="image" src="https://github.com/user-attachments/assets/ad82785e-3bee-4546-b91a-62e89439522a" />
<img width="311" height="929" alt="image" src="https://github.com/user-attachments/assets/92c95989-112c-43ae-a8c7-fc549a1729a2" />
<img width="271" height="309" alt="image" src="https://github.com/user-attachments/assets/8dbed6d3-230b-4dba-bdc0-cd4d26cfdbc4" />

### Jacobian of Manipulator
<img width="936" height="288" alt="image" src="https://github.com/user-attachments/assets/a643732e-a6ed-4ab1-b70c-58621f404537" />

### Singularities
<img width="951" height="168" alt="image" src="https://github.com/user-attachments/assets/deb87be3-f9f8-491d-b974-ee035643966f" />
<img width="975" height="405" alt="image" src="https://github.com/user-attachments/assets/b1359125-94c1-40a7-908d-0f25bd2fc73c" />
<img width="936" height="355" alt="image" src="https://github.com/user-attachments/assets/2266eed3-2587-497e-984d-e289f9b7eb3c" />

### Conclusion
In this project, a complete kinematic analysis of a serial robotic manipulator was carried out through the study of forward kinematics, inverse kinematics, and the Jacobian matrix. 
The work provided a clear understanding of how joint variables relate to end-effector position, orientation, and velocity, and how these relationships can be modeled mathematically using DH - parameters. 
By deriving analytical expressions and implementing them in MATLAB, the project strengthened our ability to translate theoretical concepts into practical computational tools. 
In addition, the analysis of singularities enhanced our awareness of the limitations and critical configurations of robotic systems. Overall, this project improved our problem-solving skills, 
reinforced key robotics fundamentals, and built a strong foundation for advanced topics in robot control, motion planning, and automation.

## Hardware Implementation

### Inverse Kinematics

https://github.com/user-attachments/assets/4f44adf4-170b-4017-bc2c-e87fc16e66a6

### Forward Kinematics



https://github.com/user-attachments/assets/ac73ccbc-c3ee-4970-a6a1-5054a1c244bb



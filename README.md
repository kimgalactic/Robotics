# Implementation of Forward and Inverse Kinematics for a 3-DOF Robotic Manipulator

OverviewThis project focuses on the design and programming of a multi-degree-of-freedom (DOF) robotic arm using an Arduino microcontroller and Dynamixel AX-12 smart servos. 
The primary objective was to transition from simple motor control to intelligent spatial navigation, allowing the robot to perform precise tasks such as drawing geometric shapes in 3D space.2. 
The Challenge: KinematicsRobotic arms naturally move in arcs because they are driven by rotational joints. This creates a fundamental control challenge:Forward Kinematics (FK): 
Calculating where the hand is located ($X, Y, Z$) based on known motor angles. This acts as a monitoring system, similar to a GPS, but does not allow for direct coordinate control.Inverse Kinematics (IK): 
The more complex process of calculating the necessary motor angles to reach a specific target coordinate ($X, Y$). This is essential for straight-line motion, as it requires the robot to coordinate multiple 
joints simultaneously to fight its natural rotational arc.3. Implementation JourneyThe project began by establishing Forward Kinematics to visualize the robot's position in real-time. By applying trigonometric
principles (Law of Cosines), we translated raw motor data into Cartesian coordinates.The core of the project was the implementation of Inverse Kinematics. This involved deriving geometric formulas to control the 
Shoulder and Elbow joints dynamically. A critical step was the calibration of the physical robot (correcting "L-shape" hardware offsets) to match the mathematical model.
4. ResultsThe final system successfully demonstrated precise control capabilities. Unlike basic servo movements which result in curved paths, this robot is capable of:Linear Interpolation: 
Moving the end-effector in perfectly straight horizontal and vertical lines.Coordinate Navigation: Accepting precise $(X, Y)$ commands to reach specific points in space.Complex Trajectories: 
autonomously drawing shapes, such as a 5cm x 5cm square, by synchronizing multiple motors in real-time.This project demonstrates the practical application of trigonometry and control theory in robotics, 
bridging the gap between abstract math and physical motion.

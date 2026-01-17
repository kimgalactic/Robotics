clear all
close all force
L(1) = Link('d', 2, 'alpha',0, 'a', 2);
L(2) = Link('d', 0, 'alpha',0, 'a', 2);
L(3) = Link('theta', 0, 'alpha', -pi, 'a', 0); 
L(4) = Link('d', 2, 'alpha', pi/2, 'a', 0); 
L(5) = Link('d', 0, 'alpha', -pi/2, 'a', 0);
L(6) = Link('d', 2, 'alpha', 0, 'a', 0); 
 
L(3).sigma=1;
L(3).qlim = [-2 2];
     
 
L(4).offset = pi/2;
L(6).offset=-pi/2;
robot = SerialLink(L, 'name', 'two link')
robot.plotopt = {'workspace' [-2,2,-2,2,-2,2]};
% to plot the robot
robot.plot([0 0 0 0 0 0]) 
robot.teach('rpy')

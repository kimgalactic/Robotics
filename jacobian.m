clear all
close all force
clc

%% 1. Define Robot
L(1) = Link('d', 2, 'alpha',0, 'a', 2);
L(2) = Link('d', 0, 'alpha',0, 'a', 2);
% Link 3 is Prismatic
L(3) = Link('theta', 0, 'alpha', -pi, 'a', 0);
L(3).sigma = 1;
L(3).qlim = [-2 2];

L(4) = Link('d', 2, 'alpha', pi/2, 'a', 0);
L(5) = Link('d', 0, 'alpha', -pi/2, 'a', 0);
L(6) = Link('d', 2, 'alpha', 0, 'a', 0);

% Apply offsets
L(4).offset = pi/2;
L(6).offset = -pi/2;

robot = SerialLink(L, 'name', 'two link');

%% 2. Jacobian Analysis

% Define the joint angles 'q' for the calculation.
% use the home position:
q = [0 0 0 0 0 0];

% Calculate Jacobian in World Frame 
J0 = robot.jacob0(q);

% Calculate Jacobian in End-Effector Frame 
Ji = robot.jacobe(q);

% Calculate Determinant 
det_J = det(J0);

% Calculate Rank (Check for singularity. 6 = full rank)
rank_J = rank(J0);

%% 3. Display Results
disp('Jacobian in World Frame (J0)');
disp(J0);

disp('Jacobian in End-Effector Frame (Ji)');
disp(Ji);

disp('Determinant of Jacobian');
disp(det_J);

disp('Rank of Jacobian');
disp(rank_J);

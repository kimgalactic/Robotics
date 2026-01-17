clc; clear;

%% Given desired pose T06
T06 = [1 0 0 3;
       0 1 0 0;
       0 0 1 6;
       0 0 0 1];

R06 = T06(1:3,1:3);
o = T06(1:3,4);

%% Robot constants
a1 = 2;
a2 = 2;
d1 = 2;
d4 = 2; 
d6 = 2; 

%% Step 1: Wrist center
% We move backwards from the end-effector along the Z-axis by length d6
oc = o - d6 * R06 * [0;0;1];

xc = oc(1);
yc = oc(2);
zc = oc(3);

%% Step 2: Position IK
r = sqrt(xc^2 + yc^2);

% Original: d3 = zc - d1;
d3 = zc - d1 - d4;

% Law of Cosines for the 2-link planar arm
cos_t2 = (r^2 - a1^2 - a2^2) / (2 * a1 * a2);
sin_t2 = sqrt(1 - cos_t2^2); % Assuming 'elbow up' or positive configuration

theta2_1 = atan2(sin_t2, cos_t2);
theta2_2 = atan2(-sin_t2, cos_t2);

theta1_1 = atan2(yc, xc) - atan2(a2*sin_t2, a1 + a2*cos_t2);
theta1_2 = atan2(yc, xc) - atan2(-a2*sin_t2, a1 + a2*cos_t2);

%% Step 3: Rotation R03
% Calculating the rotation of the first 3 links to isolate the wrist
R03_1 = rotz(theta1_1 + theta2_1);
R03_2 = rotz(theta1_2 + theta2_2);

% We use the transpose (inverse) to remove R03 from R06
R36_1 = R03_1.' * R06;
R36_2 = R03_2.' * R06;

%% Step 4: Wrist IK (Calculating for solution 1 branch)
r31 = R36_1(3,1);
r32 = R36_1(3,2);
r33 = R36_1(3,3);
r13 = R36_1(1,3);
r23 = R36_1(2,3);

% Calculate Wrist Angles (Euler ZYZ logic)
theta5 = atan2(sqrt(r31^2 + r32^2), r33);

q4 = atan2(r23, r13);
% L(4).offset is pi/2. Formula: theta = q - offset
theta4 = q4 - pi/2;

q6 = atan2(-r32, r31);
% FIXED: L(6).offset is -pi/2.
% Formula: theta = q - offset => theta = q - (-pi/2) => q + pi/2
theta6 = q6 + pi/2;

%% Display results
disp('--- IK Solution (one branch) ---')
fprintf('theta1 = %.3f rad\n', theta1_1)
fprintf('theta2 = %.3f rad\n', theta2_1)
fprintf('d3     = %.3f m\n', d3)
fprintf('theta4 = %.3f rad\n', theta4)
fprintf('theta5 = %.3f rad\n', theta5)
fprintf('theta6 = %.3f rad\n', theta6)

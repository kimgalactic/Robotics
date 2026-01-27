clear all;
close all;
clc;

% Base and Shoulder
L(1) = Link('d', 2, 'alpha', 0, 'a', 2);
L(2) = Link('d', 0, 'alpha', 0, 'a', 2);

% Prismatic Arm (The extending part)
L(3) = Link('theta', 0, 'alpha', -pi, 'a', 0);
L(3).sigma = 1;       
L(3).qlim = [0 2];    

% Spherical Wrist
L(4) = Link('d', 2, 'alpha', pi/2, 'a', 0);
L(5) = Link('d', 0, 'alpha', -pi/2, 'a', 0);
L(6) = Link('d', 2, 'alpha', 0, 'a', 0);

% Offsets
L(4).offset = pi/2;
L(6).offset = -pi/2;

% Create Robot Object
robot = SerialLink(L, 'name', '3-DOF Manipulator');

%% 2. Define Key Positions (Waypoints)

% 1. Home Position (folded)
q_home = [0 0 0 0 0 0];

% 2. Reach Forward & Down (Extend prismatic L3)
q_pick = [0, -pi/6, 1.5, 0, pi/4, 0];

% 3. Rotate Base (Move object to the side)
q_move = [pi/2, -pi/6, 1.5, 0, pi/4, 0];

% 4. Retract (Drop off)
q_place = [pi/2, 0, 0, 0, 0, 0];

%% 3. Generate Trajectories (Smooth Interpolation)
steps = 50; 

% Create smooth paths between points using Quintic Polynomials
path1 = jtraj(q_home, q_pick, steps);
path2 = jtraj(q_pick, q_move, steps);
path3 = jtraj(q_move, q_place, steps);
path4 = jtraj(q_place, q_home, steps);

% Combine all paths into one long movie
full_path = [path1; path2; path3; path4];

%% 4. Run Animation and Save Video
figure('Name', 'Robotic Arm Simulation', 'Color', 'w');
robot.plotopt = {'workspace', [-4, 4, -4, 4, -1, 5], 'noarrow', 'nowrist', 'shadow'};

% Setup Video Writer
v = VideoWriter('robot_simulation.avi'); 
v.FrameRate = 30;
open(v);

disp('Initializing Plot...');
robot.plot(full_path(1, :)); 
hold on;

disp('Starting Recording...');

for i = 2:size(full_path, 1)
    robot.animate(full_path(i, :)); 
    drawnow;
    
    frame = getframe(gcf);
    writeVideo(v, frame);
end

close(v);
disp('Success! Video saved as robot_simulation.avi');

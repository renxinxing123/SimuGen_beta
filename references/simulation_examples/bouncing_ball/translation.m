% MATLAB script to construct a bouncing ball simulation in Simulink

% Model name
modelName = 'bouncing_ball_GT_sim';

% Close and delete model if exists
if bdIsLoaded(modelName)
    close_system(modelName,0);
end
if exist([modelName '.slx'],'file')
    delete([modelName '.slx']);
end

% Create new system
new_system(modelName);
open_system(modelName);

% Parameters as per C code
g = -9.81;                             % Gravitational acceleration
initial_pos = 25.0;                    % Initial height
initial_vel = 0.0;                     % Initial velocity
cor = -0.8;                            % Coefficient of restitution (negative for direction)
lower_limit = 0.0;                     % Ground (floor)
upper_limit = Inf;                     % No ceiling
simTime = 25.0;                        % Simulation end time
stepSize = 0.5;                        % Sample time

% Add Second Order Integrator block (2 outputs: position, velocity)
soiBlk = [modelName '/Second-Order Integrator'];
add_block('simulink/Continuous/Second-Order Integrator', soiBlk, 'Position', [100 100 180 180]);
set_param(soiBlk, 'InitialCondition', mat2str([initial_pos initial_vel]));
set_param(soiBlk, 'UpperSaturationLimit', num2str(upper_limit));
set_param(soiBlk, 'LowerSaturationLimit', num2str(lower_limit));

% Add Ground for signal routing (to use as G)
gBlk = [modelName '/Gravitational acceleration'];
add_block('simulink/Commonly Used Blocks/Constant', gBlk, 'Position', [40 160 70 190]);
set_param(gBlk, 'Value', num2str(g));

% Add Gain block for coefficient of restitution
corBlk = [modelName '/Coefficient of Restitution'];
add_block('simulink/Commonly Used Blocks/Gain', corBlk, 'Position', [510 145 560 175]);
set_param(corBlk, 'Gain', num2str(cor));

% Add MinMax block for velocity reset (if needed)
absBlk = [modelName '/Abs'];
add_block('simulink/Math Operations/Abs', absBlk, 'Position', [800 145 850 175]);

% Add Memory block for previous state
memBlk = [modelName '/Memory'];
add_block('simulink/Discrete/Memory', memBlk, 'Position', [410 150 440 180]);
set_param(memBlk, 'InitialCondition', num2str(0));

% Create Detector for impact (when pos <= 0)
detectBlk = [modelName '/HitFloor'];
add_block('simulink/Logic and Bit Operations/Compare To Constant', detectBlk, 'Position', [330 130 390 160]);
set_param(detectBlk, 'const', num2str(0));
set_param(detectBlk, 'relop', '==');

% Add Switch to reset velocity on impact
switchBlk = [modelName '/Switch'];
add_block('simulink/Signal Routing/Switch', switchBlk, 'Position', [600 120 650 180]);
set_param(switchBlk,'Threshold','0.5','Criteria','u2 ~= 0');

% Add Demux to split outputs from integrator [position, velocity]
demuxBlk = [modelName '/Demux'];
add_block('simulink/Signal Routing/Demux', demuxBlk, 'Position', [210 110 230 170]);
set_param(demuxBlk, 'Outputs', '2');

% Add Mux to create [position; new velocity] vector to feed back
muxBlk = [modelName '/Mux'];
add_block('simulink/Signal Routing/Mux', muxBlk, 'Position', [710 110 740 180]);
set_param(muxBlk, 'Inputs','2'); % position, velocity

% Add Out blocks for position and velocity monitoring
outPosBlk = [modelName '/Position'];
add_block('simulink/Sinks/Out1', outPosBlk, 'Position', [850 100 900 120]);
outVelBlk = [modelName '/Velocity'];
add_block('simulink/Sinks/Out1', outVelBlk, 'Position', [850 180 900 200]);

% Add Scope for visualization
scopeBlk = [modelName '/Scope'];
add_block('simulink/Sinks/Scope', scopeBlk, 'Position', [950 95 1000 205]);

% --- Wiring ---

% Gravity to SOI
add_line(modelName, 'Gravitational acceleration/1', 'Second-Order Integrator/2','autorouting','on');

% SOI output to Demux
add_line(modelName, 'Second-Order Integrator/1', 'Demux/1','autorouting','on');

% Demux outputs: 1=position, 2=velocity
add_line(modelName, 'Demux/1', 'Position/1','autorouting','on');
add_line(modelName, 'Demux/1', 'HitFloor/1','autorouting','on');

% Velocity to Memory (feedback for continuous velocity)
add_line(modelName, 'Demux/2', 'Memory/1','autorouting','on');

% Memory output to Gain (cor)
add_line(modelName, 'Memory/1', 'Coefficient of Restitution/1','autorouting','on');

% Gain output to Switch (new velocity if bounce)
add_line(modelName, 'Coefficient of Restitution/1', 'Switch/1','autorouting','on');

% Demux velocity to Switch (use normal velocity if not bounce)
add_line(modelName, 'Demux/2', 'Switch/3','autorouting','on');

% HitFloor output to Switch (condition)
add_line(modelName, 'HitFloor/1', 'Switch/2','autorouting','on');

% Switch output (selected velocity, either bounced or normal) to Mux (2nd in vector)
add_line(modelName, 'Switch/1', 'Mux/2','autorouting','on');

% Position (from Demux) to Mux (1st input)
add_line(modelName, 'Demux/1', 'Mux/1','autorouting','on');

% Mux output to Second-Order Integrator IC port (for modeling, this would require a reset via block variant or masked subsystem)
% Due to basic Simulink's library block limitations, here it's a simplification: continuous overrides are not permitted
% For accurate event-based IC update, one would custom-code a masked S-function.
% For this script, we'll use the resettable integrator pattern (license permitting), otherwise clarify for S-Function need.

% Connect velocity to Out2 and Scope
add_line(modelName, 'Demux/2', 'Velocity/1','autorouting','on');

% Connect Position and Velocity both to Scope
add_line(modelName, 'Position/1', 'Scope/1','autorouting','on');
add_line(modelName, 'Velocity/1', 'Scope/2','autorouting','on');

% Save the model
save_system(modelName);

% Set simulation parameters
set_param(modelName, 'Solver', 'ode3', 'StopTime', num2str(simTime), 'FixedStep', num2str(stepSize));

% Done - open the system for user inspection
open_system(modelName);
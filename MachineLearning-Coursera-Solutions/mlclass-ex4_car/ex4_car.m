clear ; close all; clc

%% =========== Part 1: Loading and Visualizing Data =============

fprintf('Loading Data ...\n')


fileTrain = 'car_data/car_numeric.data';
data = load(fileTrain);

numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

input_layer_size = numElemsRow - 1  % 6
hidden_layer_size = 20  % 25 hidden units
num_labels = length(unique(y))  % 4 labels


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% TRAIN

%% ================ Part 6: Initializing Pameters ================

fprintf('\nInitializing Neural Network Parameters ...\n')

initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);

% Unroll parameters - pesos aleatorios
initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];


%% =================== Part 8: Training NN ===================


fprintf('\nTraining Neural Network... \n')

% cost = 0.627255
% max_iterations = 400
% training accuracy = 91.76

options = optimset('MaxIter', 400);
lambda = 1;
costFunction = @(p) nnCostFunction(p, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, X, y, lambda);



[nn_params, cost] = fmincg(costFunction, initial_nn_params, options);


% Obtain Theta1 and Theta2 back from nn_params
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

fprintf('Program paused. Press enter to continue.\n');
pause;



%% ================= Part 10: Implement Predict =================
pred = predict(Theta1, Theta2, X);

fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);
fprintf('\ncost: %f\n', cost(end));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% TEST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fileTest = 'car_data/car-prueba_numeric.data';
data = load(fileTest);
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

pred = predict(Theta1, Theta2, X);

fprintf('\nTest Set Accuracy: %f\n', mean(double(pred == y)) * 100);


% Multiclass Regularized Logistic Regression - ONE VS ALL

clear ; close all; clc

%% ============ Part 1: Loading & visualizing data ============

fprintf('Loading and Visualizing Data ...\n')


fileTrain = 'car_data/car_numeric.data';
data = load(fileTrain);

numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

input_layer_size  = numElemsRow - 1;
num_labels = length(unique(y));


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ============ Part 2: Vectorize Logistic Regression ============

fprintf('\nTraining One-vs-All Logistic Regression...\n')

lambda = 1.0;
[all_theta] = oneVsAll(X, y, num_labels, lambda);

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ================ Part 3: Predict for One-Vs-All ================

pred = predictOneVsAll(all_theta, X);

fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);

%% # MAX ITERACIONES = 50
%% ACCURACY = 71.345708
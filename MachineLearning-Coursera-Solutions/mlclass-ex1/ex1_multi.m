
%% ================ Part 1: Feature Normalization ================

clear ; close all; clc

fprintf('Loading data ...\n');

% X1 = size of the house
% X2 = # bedrooms
% Y = price of the house

%% Load Data
data = load('ex1data2.txt');
X = data(:, 1:2);
y = data(:, 3);
m = length(y);

fprintf('First 10 examples from the dataset: \n');
fprintf(' x = [%.0f %.0f], y = %.0f \n', [X(1:10,:) y(1:10,:)]');
fprintf('Program paused. Press enter to continue.\n');
pause;

% Scale features and set them to zero mean
fprintf('Normalizing Features ...\n');

[X mu sigma] = featureNormalize(X);

% Add intercept term to X
X = [ones(m, 1) X];


%% ================ Part 2: Gradient Descent - Multivariable ================

fprintf('Running gradient descent ...\n');

max_num_iters = 500;  % limite de iteraciones
max_cost = 2.0433e+09;

% Run Gradient Descent 
alpha = [0.01, 0.7, 0.8, 0.9, 1.0, 1.1];
color = [{'-b'}, {'-y'}, {'-k'}, {'-r'}, {'-g'}, {'-m'}];

n_learningrates = length(alpha);
J_history_array = zeros(max_num_iters, n_learningrates);

iterations_array = zeros(1,n_learningrates);

for i = 1:n_learningrates
	fprintf('computing gradient descent with learning rate %f ...\n', alpha(i));
	theta = zeros(3, 1);
	[theta, J_history] = gradientDescentMulti(X, y, theta, alpha(i), max_num_iters);
	J_history_array(:,i) = J_history;
end

% Plot the CONVERGENCE GRAPH
figure;

for i = 1:n_learningrates
	plot(1:numel(J_history_array(:,i)), J_history_array(:,i), color(i));
	hold on;
end

title('Convergence Graph')
xlabel('Number of iterations');
ylabel('Cost J');

legend_names = strtrim(cellstr(num2str(alpha'))');
legend(legend_names);
hold off;

for i=1:n_learningrates
	fprintf('Para "learning rate" = %f, "iteraciones requeridas" = %i \n', alpha(i), iterations_array(i));
end



% Display gradient descent's result
fprintf('Theta computed from gradient descent: \n');
fprintf(' %f \n', theta);
fprintf('\n');

% Estimate the price of a 1650 sq-ft, 3 br house
inputData = [1650, 3];

inputData(1) = (inputData(1)-mu(1)) / sigma(1);
inputData(2) = (inputData(2)-mu(2)) / sigma(2);

price = theta(1) + inputData(1)*theta(2) + inputData(2)*theta(3); 

% ============================================================

fprintf(['Predicted price of a 1650 sq-ft, 3 br house ' ...
         '(using gradient descent):\n $%f\n'], price);

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ================ Part 3: Normal Equations ================

fprintf('Solving with normal equations...\n');

%% Load Data
data = csvread('ex1data2.txt');
X = data(:, 1:2);
y = data(:, 3);
m = length(y);

% Add intercept term to X
X = [ones(m, 1) X];

% Calculate the parameters from the normal equation
theta = normalEqn(X, y);

% Display normal equation's result
fprintf('Theta computed from the normal equations: \n');
fprintf(' %f \n', theta);
fprintf('\n');


% Estimate the price of a 1650 sq-ft, 3 br house
% ====================== YOUR CODE HERE ======================

inputData = [1650, 3];

price = theta(1) + inputData(1)*theta(2) + inputData(2)*theta(3); 

% ============================================================

fprintf(['Predicted price of a 1650 sq-ft, 3 br house ' ...
         '(using normal equations):\n $%f\n'], price);


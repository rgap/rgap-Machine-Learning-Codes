function [J, grad] = lrCostFunction(theta, X, y, lambda)
	
% vectorized logistic regression cost function

%LRCOSTFUNCTION Compute cost and gradient for logistic regression with 
%regularization
%   J = LRCOSTFUNCTION(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================

theta1 = [0; theta(2:end)];

h = sigmoid(X * theta);

J = (1/m) * sum(-y .* log(h) - (1 - y) .* log(1 - h)) + ...
    lambda / (2*m) * theta1' * theta1;

grad = (1/m) * (X' * (h - y) + lambda * theta1);

end
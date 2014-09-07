function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

hX = sigmoid((theta' * X')');
J = 1 / m * sum((-y' * log(hX)) - ((1 - y') * log(1 - hX)));
J = J + lambda / (2 * m) * sum(theta(2:end) .^ 2);
grad = 1 / m * ((hX - y)' * X);
grad(2:end) = grad(2:end)' + lambda / m * theta(2:end);

% =============================================================

end

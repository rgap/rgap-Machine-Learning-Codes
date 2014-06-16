function [J, grad] = costFunction(theta, X, y)
%COSTFUNCTION Compute cost and gradient for logistic regression
%   J = COSTFUNCTION(theta, X, y) computes the cost of using theta as the
%   parameter for logistic regression and the gradient of the cost
%   w.r.t. to the parameters.

m = length(y);
J = 0;
grad = zeros(size(theta));

h_theta = sigmoid(X * theta);

J = 1./m * (-y' * log(h_theta) - (1 - y') * log (1 - h_theta));
J;
grad = 1./m * (X' * (h_theta - y));

end


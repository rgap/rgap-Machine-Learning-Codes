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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

h_theta = sigmoid(X * theta);

fungrad = (-y)' * log(h_theta) - (1 - y)' * log(1 - h_theta);

regularization = (lambda / (2*m)) .* sum(theta.^2);

J = ((1/m) .* sum(fungrad)) + regularization;

%%%%%%%%%%%%%%%%%%%%%%%% gradient

n = length(theta);


grad(1) = 1./m * (X'(1,:) * (h_theta - y));

for j=2:n
	regularization = 1./m .* lambda .* theta(j,1);
	grad(j) = 1./m * (X'(j,:) * (h_theta - y))   +   regularization;
end

% =============================================================

end

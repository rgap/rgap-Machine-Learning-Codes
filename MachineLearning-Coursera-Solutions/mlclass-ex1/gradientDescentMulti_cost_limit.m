function [theta, J_history, iterations] = gradientDescentMulti(X, y, theta, alpha, num_iters, limit_cost)
%GRADIENTDESCENTMULTI Performs gradient descent to learn theta
%   theta = GRADIENTDESCENTMULTI(x, y, theta, alpha, num_iters) updates theta by
%   taking num_iters gradient steps with learning rate alpha

% Initialize some useful values
m = length(y); % number of training examples
J_history = zeros(num_iters, 1);
iterations = 0;

for iter = 1:num_iters

    t = repmat((X*theta - y), 1, size(X,2));
    theta = theta - (alpha * (sum(t .* X )/m)');

    % ============================================================

    % Save the cost J in every iteration    
    J_history(iter) = computeCostMulti(X, y, theta);

    if(J_history(iter) < limit_cost)
        J_history(iter:num_iters, 1) = J_history(iter);
        iterations = iter;
        return;
end

end

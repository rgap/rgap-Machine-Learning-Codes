function [theta, cost] = trainLogisticRegClassifier(X, y)

%% ============ Compute Cost and Gradient ============
[m, n] = size(X);
X = [ones(m, 1) X];
initial_theta = zeros(n + 1, 1);

%% ============= Gradient Descent  =============
options = optimset('GradObj', 'on', 'MaxIter', 400);

[theta, cost] = ...
	fminunc(@(t)(costFunction(t, X, y)), initial_theta, options);
end
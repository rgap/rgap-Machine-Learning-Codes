function [theta, J, exit_flag] = train_regLogisticRClassifier(X, y, lambda)

%% ============ Compute Cost and Gradient ============
[m, n] = size(X);
X = [ones(m, 1) X];
initial_theta = zeros(n + 1, 1);

%% ============= Gradient Descent  =============
options = optimset('GradObj', 'on', 'MaxIter', 400);

[theta, J, exit_flag] = ...
		fminunc(@(t)(costFunctionReg(t, X, y, lambda)), initial_theta, options);
end
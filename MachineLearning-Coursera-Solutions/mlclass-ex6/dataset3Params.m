function [C, sigma] = dataset3Params(X, y, Xval, yval)
%EX6PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = EX6PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

param = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];

error_min = inf;

for i = 1:length(param)
	for j = 1:length(param)
		c = param(i);
		s = param(j);
		model = svmTrain(X, y, c, @(x1, x2) gaussianKernel(x1, x2, s));
		predictions = svmPredict(model, Xval);
		error = mean(double(predictions ~= yval))
		if (error < error_min)
			C = c;
			sigma = s;
			error_min = error;
		end
	end
end 


end

function [predicted_class] = test_noregLogisticRClassifier(X, y, thetaArray, nclasses)

X = [ones(size(X,1), 1), X];
nsamples = size(X,1);
probArray = zeros(1, nclasses);
predicted_class = zeros(1, nsamples);

for i=1:nsamples
	fprintf('Test # %i\n', i);
	for j=1:nclasses
		probArray(j) = sigmoid(X(i,:) * thetaArray(:,j));
		fprintf('Class %i with probability %f\n', j-1, probArray(j));
	end
	[val idx] = max(probArray);
	predicted_class(i) = idx-1;
	fprintf('Predicted class = %i, with probability %f\n', predicted_class(i), val);
end

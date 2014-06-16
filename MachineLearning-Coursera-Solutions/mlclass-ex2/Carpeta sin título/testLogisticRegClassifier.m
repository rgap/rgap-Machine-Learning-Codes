function = testLogisticRegClassifier(X, y)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data = load();
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);
X = [ones(size(X,1), 1), X];
nsamples = size(X,1);
probArray = zeros(1, nclasses);


for i=1:nsamples
	fprintf('Test # %i\n', i);
	for j=1:nclasses

		probArray(j) = sigmoid(X(i,:) * thetaArray(:,j));
		fprintf('Class %i with probability %f\n', j-1, probArray(j));
	end
	[val idx] = max(probArray);
	fprintf('Predicted class = %i, with probability %f\n', idx-1, val);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
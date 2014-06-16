onevsall

data = load(file);
numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

nclasses = length(unique(y));
thetaArray = zeros(numElemsRow, nclasses);
nsamples = length(y);
yOneClass = zeros(nsamples, 1);


fprintf('numero de clases = %i\n\n', nclasses);

for i=1:nclasses
	for j=1:nsamples
		if y(j) == (i - 1)
			yOneClass(j) = 1;
		else
			yOneClass(j) = 0;
		end
	end
	[thetaArray(:,i), cost] = trainLogisticRegClassifier(X, yOneClass);
end




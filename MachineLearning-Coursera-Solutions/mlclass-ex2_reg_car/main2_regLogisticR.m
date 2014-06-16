clear ; close all; clc

fprintf('_______________ ONE VS ALL\n');

fileTrain = 'car_data/car_numeric.data';
data = load(fileTrain);

numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);
nclasses = length(unique(y));

X = mapFeature(X(:,1), X(:,2)); % Feature mapping function to polynomial features

lambda = 1;
thetaArray = oneVsAll(X, y, lambda);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('_______________ TEST CAR-PRUEBA\n');

fileTest = 'car_data/car-prueba_numeric.data';
data = load(fileTest);
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

X = mapFeature(X(:,1), X(:,2)); % Feature mapping function to polynomial features

predicted_class = test_regLogisticRClassifier(X, y, thetaArray, nclasses);

nsamples = length(y);
nhits = 0;
for i=1:nsamples
	if predicted_class(i) == y(i)
		nhits += 1;
	end
end

accuracy = nhits ./ nsamples;
fprintf('\n');
fprintf('Accuracy %f\n', accuracy);
fprintf('Error %f\n', 1 - accuracy);
fprintf('\n');

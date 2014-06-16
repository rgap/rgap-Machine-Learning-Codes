clear ; close all; clc

fprintf('_______________ ONE VS ALL\n');

fileTrain = 'car_data/car_numeric.data';
data = load(fileTrain);

numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);
nclasses = length(unique(y));

thetaArray = oneVsAll(X, y);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('_______________ TEST CAR-PRUEBA\n');

fileTest = 'car_data/car-prueba_numeric.data';
data = load(fileTest);
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);

predicted_class = test_noregLogisticRClassifier(X, y, thetaArray, nclasses);

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

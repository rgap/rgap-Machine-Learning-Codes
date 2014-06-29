clear ; close all; clc

fprintf('_______________ ONE VS ALL - TRAIN\n');

fileTrain = 'car_data/car_numeric.data';
data = load(fileTrain);

numElemsRow = length(data(1,:));
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);
nclasses = length(unique(y));


C = 10.0;
sigma = 0.5;
fprintf('C = %f\n', C);
fprintf('sigma = %f\n', sigma);


model = oneVsAll(X, y, C, sigma);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf('_______________ TEST CAR-PRUEBA\n');

fileTest = 'car_data/car-prueba_numeric.data';
data = load(fileTest);
X = data(:, [1:numElemsRow-1]); y = data(:, numElemsRow);
nsamples = size(X,1);
predicted_OneClass = zeros(nsamples, nclasses);
predicted_class = zeros(nsamples, 1);

for i=1:nclasses
	predicted_OneClass(:, i) = svmPredict(model(i), X);
end

for i=1:nsamples
	fprintf('Test # %i\n', i);
	for j=1:nclasses
		predicted_OneClass(i, j);
		fprintf('Class %i with probability %f\n', j-1, predicted_OneClass(i, j));
	end

	[val idx] = max(predicted_OneClass(i,:));
	predicted_class(i) = idx-1;
	fprintf('Predicted class = %i, with probability %f\n', predicted_class(i), val);
end


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

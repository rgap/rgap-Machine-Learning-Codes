function model = oneVsAll(X, y, C, sigma)

nclasses = length(unique(y));
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
	fprintf('Train with class %i', i - 1);
	model(i) = svmTrain(X, yOneClass, C, @(x1, x2) gaussianKernel(x1, x2, sigma));
end

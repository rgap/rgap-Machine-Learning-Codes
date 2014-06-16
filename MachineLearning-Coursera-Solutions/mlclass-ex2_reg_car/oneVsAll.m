function thetaArray = oneVsAll(X, y, lambda)

nclasses = length(unique(y));
thetaArray = zeros(size(X,2)+1, nclasses);
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
	[thetaArray(:,i), J, exit_flag] = train_regLogisticRClassifier(X, yOneClass, lambda);
end

thetaArray
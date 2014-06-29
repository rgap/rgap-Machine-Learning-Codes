clear ; close all; clc

%% ==================== Part 1: Email Preprocessing ====================
fprintf('\nPreprocessing sample email (emailSample1.txt)\n');

file_contents = readFile('emailSample1.txt');
word_indices  = processEmail(file_contents);

fprintf('Word Indices: \n');
fprintf(' %d', word_indices);
fprintf('\n\n');

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ==================== Part 2: Feature Extraction ====================
fprintf('\nExtracting features from sample email (emailSample1.txt)\n');

file_contents = readFile('emailSample1.txt');
word_indices  = processEmail(file_contents);
features      = emailFeatures(word_indices);

fprintf('Length of feature vector: %d\n', length(features));
fprintf('Number of non-zero entries: %d\n', sum(features > 0));

fprintf('Program paused. Press enter to continue.\n');
pause;

%% =========== Part 3: Train Linear SVM for Spam Classification ========
load('spamTrain.mat'); % -> X, y

fprintf('\nTraining Linear SVM (Spam Classification)\n')
fprintf('(this may take 1 to 2 minutes) ...\n')

C = 0.1;
model = svmTrain(X, y, C, @linearKernel);

p = svmPredict(model, X); % predicted class per feature vector

fprintf('Training Accuracy: %f\n', mean(double(p == y)) * 100);

%% =================== Part 4: Test Spam Classification ================
load('spamTest.mat'); % Xtest, ytest

fprintf('\nEvaluating the trained Linear SVM on a test set ...\n')
p = svmPredict(model, Xtest);

fprintf('Test Accuracy: %f\n', mean(double(p == ytest)) * 100);
pause;


%% ================= Part 5: Top Predictors of Spam ====================

[weight, idx] = sort(model.w, 'descend');
vocabList = getVocabList();

fprintf('\nTop predictors of spam: \n');
for i = 1:15
    fprintf(' %-15s (%f) \n', vocabList{idx(i)}, weight(i));
end

fprintf('\n\n');
fprintf('\nProgram paused. Press enter to continue.\n');
pause;

%% =================== Part 6: Try Your Own Emails =====================

filename = 'spamSample1.txt';
classify_mail(filename, model);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
filename = 'spamSample2.txt';
classify_mail(filename, model);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
filename = 'emailSample1.txt';
classify_mail(filename, model);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
filename = 'emailSample2.txt';
classify_mail(filename, model);
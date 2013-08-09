#include "hmm.h"

#include <string>

HMM::HMM(int n = 0, int m = 0) {
	N = n;
	M = m;
	current = new Data(n, m);
	reestimated = new Data(n, m);
}

double HMM::alpha(const string s) {
	string out;
	double P = 0.0;
	out = s;
	int T1 = out.length();

	double* previous_alpha = new double[N + 1];
	double* current_alpha = new double[N + 1];

	for (int i = 1; (i <= N); i++) {
		previous_alpha[i] = pi(i) * b(i, 1, out);
	}

	for (int t = 1; (t < T1); t++) {
		for (int j = 1; (j <= N); j++) {
			double sum = 0.0;
			for (int i = 1; (i <= N); i++) {
				sum += previous_alpha[i] * a(i, j);
			}
			current_alpha[j] = sum * b(j, t + 1, out);
		}
	}
	for (int c = 1; (c <= N); c++) {
		previous_alpha[c] = current_alpha[c];
	}

	for (int i = 1; (i <= N); i++) {
		P += previous_alpha[i];
	}

	return P;
}

double HMM::beta(const string s) {
	double P = 0.0;
	o = s;
	int T = o.length();

	double* next_beta = new double[N + 1];
	double* current_beta = new double[N + 1];

	for (int i = 1; (i <= N); i++) {
		next_beta[i] = 1.0;
	}

	double sum;

	for (int t = T - 1; (t >= 1); t--) {
		for (int i = 1; (i <= N); i++) {

			sum = 0.0;
			for (int j = 1; (j <= N); j++) {
				sum += a(i, j) * b(j, t + 1) * next_beta[j];
			}
			current_beta[i] = sum;
		}
	}

	for (int c = 1; (c <= N); c++) {
		next_beta[c] = current_beta[c];
	}

	for (int i = 1; (i <= N); i++) {
		P += next_beta[i] * pi(i) * b(i, 1);
	}
	return P;
}

double HMM::gamma(int t, int i) {
	return ((alpha_table[t][i] * beta_table[t][i]) / alpha_beta_table[t]);
}

int HMM::index(const char c) {
	switch (c) {
	case 'H':
		return 0;
	case 'T':
		return 1;

	default:
		error("No legal input symbol");
		return 0;
	}
}

double HMM::viterbi(const string s, int best_path[]) {
	double P_star = 0.0;
	string o = s;
	//int *help = new int;
	int T = o.length();
	double* previous_delta = new double[N + 1];
	double* current_delta = new double[N + 1];
	int** psi = new int*[T + 1];

	for (int i = 0; i <= T; i++)
		psi[i] = new int[N + 1];
	// Initializitaion:
	for (int i = 1; i <= N; i++) {
		previous_delta[i] = pi(i) * b(i, 1);
		psi[1][i] = 0;
	}

	double tmp, max;
	// Recursion:
	for (int t = 2; (t <= T); t++) {
		for (int j = 1; (j < N); j++) {
			max = 0.0;
			for (int i = 1; (i <= N); i++) {
				tmp = previous_delta[i] * a(i, j);
				if (tmp >= max) {
					max = tmp;
					psi[t][j] = i;
				}
			}
			current_delta[j] = max * b(j, t);
		}
		for (int c = 1; (c <= N); c++) {
			previous_delta[c] = current_delta[c];
		}
	}

	// Termination:
	for (int i = 1; i <= N; i++) {
		if (previous_delta[i] >= P_star) {
			P_star = previous_delta[i];
			best_path[T] = i;
		}
	}
	// Extract best sequence:
	for (int t = T - 1; t >= 1; t--)
		best_path[t] = psi[t + 1][best_path[t + 1]];

	best_path[T + 1] = -1;

	return P_star;
}

double** HMM::construct_alpha_table() {
	double** alpha_table = new double*[T + 1];
	for (int i = 0; (i < T + 1); i++) {
		alpha_table[i] = new double[N + 1];
	}

	for (int i = 0; (i <= N); i++) {
		alpha_table[1][i] = pi(i) * b(i, 1);
	}

	for (int t = T - 1; (t < T); t++) {
		for (int j = 1; (j <= N); j++) {
			double sum = 0.0;
			for (int i = 1; (i <= N); i++) {
				sum += alpha_table[t][i] * a(i, j);
			}
			alpha_table[t + 1][j] = sum * b(j, t + 1);
		}
	}
	return alpha_table;
}

double** HMM::construct_beta_table() {
	double **beta_table;

	beta_table = new double*[T + 1];

	for (int i = 0; (i <= T + 1); i++) {
		beta_table[i] = new double[N + 1];
	}

	for (int i = 1; (i <= N); i++) {
		beta_table[T][i] = 1.0;
	}

	double sum;

	for (int t = T - 1; (t >= 1); t--) {
		for (int i = 1; (i <= N); i++) {
			sum = 0.0;
			for (int j = 1; (j < N); j++) {
				sum += a(i, j) * b(j, t + 1) * beta_table[t + 1][j];
			}
			beta_table[t][i] = sum;
		}
	}

	for (int i = 1; (i <= N); i++) {
		beta_table[1][i] = beta_table[1][i] * pi(i) * b(i, 1);
	}

	return beta_table;
}

double* HMM::construct_alpha_beta_table() {
	double* alpha_beta_table = new double[T + 1];
	for (int t = 1; (t <= T); t++) {
		alpha_beta_table[t] = 0;
		for (int i = 1; (i <= N); i++) {
			alpha_beta_table[t] += (alpha_table[t][i] * beta_table[t][i]);
		}
	}
	return alpha_beta_table;
}

double* HMM::construct_xi_divisor() {
	xi_divisor = new double[T + 1];
	double sum_j;
	for (int t = 1; (t < T); t++) {
		xi_divisor[t] = 0.0;
		for (int i = 1; (i <= N); i++) {
			sum_j = 0.0;
			for (int j = 1; (j <= N); j++) {
				sum_j += (alpha_table[t][i] * a(i, j) * b(j, t + 1)
						* beta_table[t + 1][j]);
			}
			xi_divisor[t] += sum_j;
		}
	}
	return xi_divisor;
}

double HMM::xi(int t, int i, int j) {
	return ((alpha_table[t][i] * a(i, j) * b(j, t + 1) * beta_table[t + 1][j])
			/ (xi_divisor[t]));
}

void HMM::reestimate_pi() {
	for (int i = 0; (i <= N); i++) {
		reestimated->set_pi_transition(i, gamma(1, i));
	}
}

void HMM::reestimate_a() {
	double sum_xi, sum_gamma;

	for (int i = 1; (i <= N); i++) {
		for (int j = 1; (j <= N); j++) {
			sum_xi = 0.0;
			sum_gamma = 0.0;

			for (int t = 1; (t < T); t++) {
				sum_xi += xi(t, i, j);
			}
			for (int t = 1; (t < T); t++) {
				sum_gamma += gamma(t, i);
			}

			reestimated->set_transition(i, j, (sum_xi / sum_gamma));
		}
	}

}

void HMM::reestimate_b() {

	double sum_gamma;
	double tmp_gamma;
	double sum_gamma_output;

	for (int j = 1; (j <= N); j++) {
		for (int k = 0; (k < M); k++) {
			sum_gamma = 0.0;
			sum_gamma_output = 0.0;
			for (int t = 1; (t <= T); t++) {
				tmp_gamma = gamma(t, j);
				if (index(o[t - 1]) == k) {
					sum_gamma_output += tmp_gamma;
				}
				sum_gamma += tmp_gamma;
			}
			reestimated->set_emission(j, k, (sum_gamma_output / sum_gamma));
		}
	}
}

void HMM::forward_backward(string o) {
	T = o.length();
	alpha_table = construct_alpha_table();
	beta_table = construct_beta_table();

	alpha_beta_table = construct_alpha_beta_table();
	xi_divisor = construct_xi_divisor();

	reestimate_pi();
	reestimate_a();
	reestimate_b();

	for (int t = 1; (t <= T); t++) {
		delete[] alpha_table[t];
		//delete[] alpha_table[t];
		//delete[] alpha_table;
	}

	for (int t = 1; (t <= T); t++) {
		delete[] beta_table[t];
		//delete[] beta_table;
		//delete[] alpha_beta_table;
		//delete[] xi_divisor;

		Data* tmp_value = current;
		current = reestimated;
		reestimated = tmp_value;
	}
}

void HMM::maximize(string o, string test) {
	double diff_entropy, old_cross_entropy, new_cross_entropy;
	int c = 1;
	int t = test.length();
	old_cross_entropy = -((log10(alpha(test)) / log10(2)) / t);
	cout << "Re-estimation:\n";
	cout << " initial cross_entropy: " << old_cross_entropy << "\n";
	do {
		forward_backward(o);
		new_cross_entropy = -(log10(alpha(test)) / log10(2)) / t;
		diff_entropy = (old_cross_entropy - new_cross_entropy);
		old_cross_entropy = new_cross_entropy;
		c++;
	} while (diff_entropy > 0.0);
	cout << " No of iterations: " << c << "\n";
	cout << " resulting cross_entropy: " << old_cross_entropy << "\n";
}

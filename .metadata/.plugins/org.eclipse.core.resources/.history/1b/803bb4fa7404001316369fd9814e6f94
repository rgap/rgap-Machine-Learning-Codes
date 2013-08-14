#ifndef HMM_H
#define HMM_H

#include "hmm_data.h"

#include <string>

class HMM {

	private:

		int N;
		int M;
		int T;
		string o;

		double **alpha_table;
		double **beta_table;
		double *alpha_beta_table;
		double *xi_divisor;

		Data *current;
		Data *reestimated;

	public:

		HMM(int n, int m);

		void error(const string s)
		{
			cerr << "Error: " << s << "\n";
		}

		void init(int s1, int s2, double value)
		{
			current->set_transition(s1, s2, value);
		}

		void pi_init(int s, double value)
		{
			current->set_pi_transition(s, value);
		}

		void o_init(int s, const char c, double value)
		{
			current->set_emission(s, index(c), value);
		}

		double a(int s1, int s2)
		{
			return current->get_transitions(s1, s2);
		}

		double b(int state, int pos)
		{
			return current->get_emission(state, index(o[pos-1]));
		}

		double b(int state, int pos, string o)
		{
			return current->get_emission(state, index(o[pos-1]));
		}

		double pi(int state)
		{
			return current->get_pi_transitions(state);
		}

		double alpha(const string s);
		double beta(const string s);
		double gamma(int t, int i);
		int index(const char c);
		double viterbi(const string s, int *best_sequence);
		double** construct_alpha_table();
		double** construct_beta_table();
		double* construct_alpha_beta_table();
		double xi(int t, int i, int j);
		void reestimate_pi();
		void reestimate_a();
		void reestimate_b();
		double* construct_xi_divisor();
		void maximize(string training, string test);
		void forward_backward(string s);
};

#endif /* HMM_H */

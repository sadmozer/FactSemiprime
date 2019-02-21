#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int isSquare(mpf_t n) {
	mpf_t sqrt_n;
	mpf_t floor_sqrtn;
	int x;

	x = 0;
	mpf_init(sqrt_n);
	mpf_init(floor_sqrtn);

	mpf_sqrt(sqrt_n, n);
	mpf_floor(floor_sqrtn, sqrt_n);
	x = mpf_cmp(sqrt_n, floor_sqrtn);

	mpf_clear(sqrt_n);
	mpf_clear(floor_sqrtn);

	return x == 0;
}

int main(int argc, char** argv) {
	mpf_t n;
	mpf_t n_plusone;
	mpf_t sqrt_n;
	mpf_t num;
	mpf_t p;
	mpf_t q;
	mpf_t sqrt_delta;
	mpf_t offset;
	mpf_t max_num;
	mpf_t delta;

	FILE* file_o;
	FILE* file_i;
	int i;
	int trovato;
	int opt;

	mpf_set_default_prec(1200);
	mpf_init(n);
	mpf_init(n_plusone);
	mpf_init(sqrt_n);
	mpf_init(num);
	mpf_init(max_num);
	mpf_init(delta);
	mpf_init(p);
	mpf_init(q);
	mpf_init(sqrt_delta);
	mpf_init(offset);
	
	// Parser Input
	file_o = stdout;
	file_i = stdin;

	while (optind < argc) {
		if ((opt = getopt(argc, argv, "i:o:")) != -1) {
			switch (opt) {
			case 'i': {
				if ((file_i = fopen(optarg, "r")) == NULL) {
					perror("test: input path");
					return -1;
				}
			} break;
			case 'o': {
				if ((file_o = fopen(optarg, "rw")) == NULL) {
					perror("test: output path");
					return -1;
				}
			} break;
			default: {
				printf("test: usare ./test [-i <path_inputfile>] [-o <path_outputfile>]\n");
				return -1;
			} break;
			}
		}
		else {
			printf("test: usare ./test [-i <path_inputfile>] [-o <path_outputfile>]\n");
			return -1;
		}
	}
	
	// Prendo N in input
	fprintf(file_o, "N: ");

	mpf_inp_str(n, file_i, 10);
	if (file_i != stdin) {
		mpf_out_str(file_o, 10, 1200, n);
		fprintf(file_o, "\n");
	}

	// Calcolo limite minimo: n^(1/2)
	mpf_sqrt(sqrt_n, n);
	mpf_ceil(num, sqrt_n);
	
	// Calcolo limite massimo: (n + 1)/2
	mpf_add_ui(n_plusone, n, 1);
	mpf_div_ui(max_num, n_plusone, 2);

	// Calcolo delta iniziale: num^2 - n
	mpf_pow_ui(delta, num, 2);
	mpf_sub(delta, delta, n);

	// Calcolo offset tra quadrati iniziale: num * 2 + 1
	mpf_mul_ui(offset, num, 2);
	mpf_add_ui(offset, offset, 1);

	i = 0;
	trovato = 0;

	while (mpf_cmp(max_num, num) >= 0 && !trovato) {
		fprintf(file_o, "Iterazione (%d). num: ", i);
		mpf_out_str(file_o, 10, 1200, num);
		fprintf(file_o, ", delta: ");
		mpf_out_str(file_o, 10, 1200, delta);
		fprintf(file_o, "\n");

		if (isSquare(delta)) {
			trovato = 1;
			mpf_sqrt(sqrt_delta, delta);
			mpf_add(p, num, sqrt_delta);
			mpf_div(q, n, p);
		}
		else {
			mpf_add_ui(num, num, 1);
			mpf_add(delta, delta, offset);
			mpf_add_ui(offset, offset, 2);
			i++;
		}
	}

	if (trovato) {
		fprintf(file_o, "p: ");
		mpf_out_str(file_o, 10, 1200, p);
		fprintf(file_o, "\nq: ");
		mpf_out_str(file_o, 10, 1200, q);
		fprintf(file_o, "\n");
	}
	else {
		fprintf(file_o, "Non trovato\n");
	}
	mpf_clear(n);
	mpf_clear(sqrt_n);
	mpf_clear(num);
	mpf_clear(max_num);
	mpf_clear(delta);
	mpf_clear(n_plusone);
	mpf_clear(p);
	mpf_clear(q);
	mpf_clear(sqrt_delta);
	mpf_clear(offset);
	return 0;
}

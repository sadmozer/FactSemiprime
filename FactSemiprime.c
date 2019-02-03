#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <errno.h>

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
	mpf_t n_minusone;
	mpf_t n_x4;
	mpf_t sqrt_n;
	mpf_t num;
	mpf_t num_x2;
	mpf_t num_x2_pow2;
	mpf_t p;
	mpf_t q;
	mpf_t sqrt_delta;
	mpf_t aux;
	FILE* file;
	FILE* file2;

	mpf_t max_num;
	mpf_t delta;
	int i;
	int trovato;

	mpf_set_default_prec(1200);
	
	mpf_init(n);
	mpf_init(n_minusone);
	mpf_init(sqrt_n);
	mpf_init(num);
	mpf_init(max_num);
	mpf_init(delta);
	mpf_init(n_x4);
	mpf_init(num_x2);
	mpf_init(num_x2_pow2);
	mpf_init(p);
	mpf_init(q);
	mpf_init(sqrt_delta);
	mpf_init(aux);
	
	if (argc == 5) {
		if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0){
			if ((file2 = fopen(argv[2], "r")) == NULL || (file = fopen(argv[4], "w+")) == NULL) {
				perror("fopen");
				return -1;
			}
		}
		else if (strcmp(argv[3], "-i") == 0 && strcmp(argv[1], "-o") == 0) {
			if ((file2 = fopen(argv[4], "r")) == NULL || (file = fopen(argv[2], "w+")) == NULL) {
				perror("fopen");
				return -1;
			}
		}
		else {
			printf("errore: usare ./test -i path_inputfile -o path_outputfile\n");
			return -1;
		}
	}
	else {
		printf("errore: usare ./test -i path_inputfile -o path_outputfile\n");
		return -1;
	}

	i = 0;
	trovato = 0;


	fprintf(file, "N: ");
	mpf_inp_str(n, file2, 10);
	mpf_out_str(file, 10, 1200, n);
	fprintf(file, "\n");


	printf("N: ");
	mpf_out_str(stdout, 10, 1200, n);
	printf("\n");
	
	mpf_sqrt(sqrt_n, n);
	mpf_ceil(num, sqrt_n);
	
	mpf_sub_ui(n_minusone, n, 1);
	mpf_div_ui(max_num, n_minusone, 2);

	while (mpf_cmp(max_num, num) >= 0 && !trovato) {
		mpf_mul_ui(num_x2, num, 2);
		mpf_pow_ui(num_x2_pow2, num_x2, 2);
		mpf_mul_ui(n_x4, n, 4);
		mpf_sub(delta, num_x2_pow2, n_x4);

		fprintf(file, "Iterazione (%d). num: ", i);
		mpf_out_str(file, 10, 1200, num);
		fprintf(file, ", delta: ");
		mpf_out_str(file, 10, 1200, delta);
		fprintf(file, "\n");

		if (isSquare(delta)) {
			trovato = 1;
			mpf_sqrt(sqrt_delta, delta);
			mpf_add(aux, num_x2, sqrt_delta);
			mpf_div_ui(p, aux, 2);
			mpf_div(q, n, p);
		}

		i++;
		mpf_add_ui(num, num, 1);

	}

	if (trovato) {
		fprintf(file, "p: ");
		mpf_out_str(file, 10, 1200, p);
		fprintf(file, "\nq: ");
		mpf_out_str(file, 10, 1200, q);
		fprintf(file, "\n");
		printf("p: ");
		mpf_out_str(stdout, 10, 1200, p);
		printf("\nq: ");
		mpf_out_str(stdout, 10, 1200, q);
		printf("\nIterazioni: %d\n", i);
	}
	else {
		fprintf(file, "Non trovato\n");
		printf("Non trovato\n");
	}
	mpf_clear(n);
	mpf_clear(sqrt_n);
	mpf_clear(num);
	mpf_clear(max_num);
	mpf_clear(delta);
	mpf_clear(n_minusone);
	mpf_clear(n_x4);
	mpf_clear(num_x2);
	mpf_clear(num_x2_pow2);
	mpf_clear(p);
	mpf_clear(q);
	mpf_clear(sqrt_delta);
	mpf_clear(aux);
	return 0;
}

#include"fantasy.h"

bool my_choice(int* vcurr, double* p_squadre) {

	if (vcurr[0] != 0 || vcurr[1] != 8) {
		return false;
	}

	if (vcurr[2] > 6) {
		return false;
	}

	return true;
}

void stampa(FILE* f, int nsol, int* v, double budget) {
	char* s1[] = { {"McLaren"},{"Ferrari"},{"Red_Bull"},{"Mercedes"},{"Williams"},{"Alpine"},{"Aston_Martin"},{"Racing_Bull"} ,{"Haas"},{"Sauber"} };
	char* s2[] = { "Norris", "Piastri", "Leclerc", "Hamilton", "Verstappen", "Lawson", "Russel", "Kimi", "Sainz", "Albon", "Gasly", "Dohan", "Alonso", "Stroll", "Tsunoda", "Hadjar", "Ocon", "Bearman", "Hulkenberg", "Bortoleto" };
	fprintf(f, "%.5d) ", nsol);

	for (int i = 0; i < n_piloti + n_squadre; i++) {
		if (i < 2) {
			fprintf(f, "%s ", s1[v[i]]);
		}
		else {
			fprintf(f, "%s ", s2[v[i]]);
		}
	}

	fprintf(f," inoltre sono avanzati %lf crediti\n", budget);

	printf("loading...\n");

	return;
}

void fantasy_rec(FILE *f, int*nsol, int* vcurr, int i_piloti, int i_squadre, int c_piloti, int c_squadre, double* p_piloti, double* p_squadre, double budget) {
	
	if (c_piloti > n_piloti || c_squadre > n_squadre || budget < 0) {
		return;
	}

	if (c_piloti == n_piloti && c_squadre == n_squadre) {
		if (budget <= 5 && my_choice(vcurr,p_squadre)) {
			*(nsol) += 1;
			stampa(f, *nsol, vcurr, budget);
		}

		return;
	}
	
	if (c_squadre < n_squadre) {

		for (i_squadre; i_squadre < dim_squadre; i_squadre++) {
			vcurr[c_squadre] = i_squadre;

			fantasy_rec(f, nsol, vcurr, i_piloti, i_squadre + 1, c_piloti, c_squadre + 1, p_piloti, p_squadre, budget - p_squadre[i_squadre]);
		
			vcurr[c_squadre] = -1;
		}
		
	} else { //c_piloti < n_piloti

		for (i_piloti; i_piloti < dim_piloti; i_piloti++) {
			vcurr[n_squadre + c_piloti] = i_piloti;
			
			fantasy_rec(f, nsol, vcurr, i_piloti + 1, i_squadre, c_piloti + 1, c_squadre, p_piloti, p_squadre, budget - p_piloti[i_piloti]);
			
			vcurr[n_squadre + c_piloti] = -1;

		}

	}

	return;
}

void fantasy(double* p_piloti, double* p_squadre) {
	FILE* f = fopen("output.txt", "w");
	if (f == NULL) {
		printf("Errore nell'apertura del file!\n");
		return;
	}

	int* vcurr = calloc(n_piloti + n_squadre, sizeof(int));
	int nsol = 0;

	fantasy_rec(f, &nsol, vcurr, 0, 0, 0, 0, p_piloti, p_squadre, 100);

	fclose(f);
	free(vcurr);

	return;
}

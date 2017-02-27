#include <stdio.h>
#include "chessboard.h"
#include "optimizer.h"


int main(int argc, char const *argv[])
{
	int i;
	// Tamaño de la población y número máximo
	// de iteraciones
	int pop_size, maxIter;

	// porcentaje de mutación
	float pmutation;

	printf("Population size: ");
	scanf("%d", &pop_size);

	printf("Iteration: ");
	scanf("%d", &maxIter);

	printf("Mutation rate (0, 1): ");
	scanf("%f", &pmutation);

	// Iniciando población
	Chessboard* population = (Chessboard *) malloc(sizeof(Chessboard) * pop_size);

	// Colocando en memoria
	initPopulation(pop_size, population, 1);


	// Itera aplicando Cruza y mutación
	Chessboard minn, tmp = population[0];
	for (i = 0; i < maxIter; ++i) {
		minn = crossing(pop_size, population, pmutation);
		
		if (minn.val == 0) {
			printf("=============================\n");
			printf("\t Solution\n");
			printf("\t iter: %d\n", i);
			printf("=============================\n");
			showChessboard(minn);
			break;
		}

		if (tmp.val != minn.val) {
			showChessboard(minn);
		}

		tmp = minn;
	}

	free(population);

	return 0;
}
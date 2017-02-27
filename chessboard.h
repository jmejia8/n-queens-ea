#include <stdlib.h>
#include <time.h>

// Tamaño del tablero
#ifndef N
	#define N 8
#endif

typedef struct _chessboard
{
	short matrix[N][N];
	int val;
} Chessboard;

int seed = 7; 
float randm() {
	srand(time(NULL) + seed );
	seed = rand();
    return (float) seed / (float)RAND_MAX ;
}
// Cuanta atques de la reyna en la posición x,y
int queenAtacks(Chessboard solution, int x, int y){
	int i, s = 0, val, k, j;
	short flag1 = 0,  flag2 = 0;

	// Cuando encuentra una reyna en la diagonal
	// suma el ataque directo
	for (i = 1; i < N; ++i){
		k = x + i;
		j = y + i;

		if (k >= N || j >= N){
			flag1 = 1;
			val = 0;
		}else
			val = solution.matrix[k][j];
		
		if (!flag1 && val){
			s += 1;
			flag1 = 1;
		}

		k = x - i;
		j = y - i;

		if (k < 0  ||  j < 0 ){
			flag2 = 1;
			val = 0;
		}else
			val = solution.matrix[k][j];
		
		if (!flag2 && val){
			s += 1;
			flag2 = 1;
		}

		if (flag1 && flag2) break;
	}

	flag1 = 0; flag2 = 0;

	// Cuando encuentra una reyna en la diagonal
	// suma el ataque directo
	for (i = 1; i < N; ++i){
		k = x + i;
		j = y - i;

		if (k >= N || j < 0){
			flag1 = 1;
			val = 0;
		}else
			val = solution.matrix[k][j];
		
		if (!flag1 && val){
			s += 1;
			flag1 = 1;
		}

		k = x - i;
		j = y + i;

		if (k < 0  ||  j >= N ){
			flag2 = 1;
			val = 0;
		}else
			val = solution.matrix[k][j];
		
		if (!flag2 && val){
			s += 1;
			flag2 = 1;
		}

		if (flag1 && flag2) break;
	}

	flag1 = 0; flag2 = 0;

	// Cuando encuentra una reyna en vertical
	// suma el ataque directo
	for (i = 1; i < N; ++i){
		k = x - i;

		if (k < 0) {
			flag1 = 1;
			val = 0;
		}else
			val = solution.matrix[k][y];
		
		if (!flag1 && val){
			s += 1;
			flag1 = 1;
		}

		k = x + i;

		if (k >= N) {
			flag2 = 1;
			val = 0;
		}else
			val = solution.matrix[k][y];
		
		if (!flag2 && val){
			s += 1;
			flag2 = 1;
		}

		if (flag1 && flag2) break;
	}


	flag1 = 0; flag2 = 0;

	// Cuando encuentra una reyna en horizontal
	// suma el ataque directo
	for (i = 1; i < N; ++i){
		k = y - i;

		if (k < 0) {
			flag1 = 1;
			val = 0;
		}else
			val = solution.matrix[x][k];
		
		if (!flag1 && val){
			s += 1;
			flag1 = 1;
		}

		k = y + i;

		if (k >= N) {
			flag2 = 1;
			val = 0;
		}else
			val = solution.matrix[x][k];
		
		if (!flag2 && val){
			s += 1;
			flag2 = 1;
		}

		if (flag1 && flag2) break;
	}

	return s;
}

void setQueens(Chessboard* solution, short values){
	int i, j;

	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			solution->matrix[i][j] = 0;

	if (!values)
		return;

	int counter = 0;
	while (counter < N){
		i = (int) (randm() * N);
		j = (int) (randm() * N);

		// printf("%d %d\n",  i, j);

		if (!solution->matrix[i][j]) {
			solution->matrix[i][j] = 1;
			++counter;
		}
	}

}

void showChessboard (Chessboard solution){
	printf("=========================\n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (solution.matrix[i][j])
				printf(" Q");
			else 
				printf(" -");
		}
		printf("\n");
	}

	printf(">>>>> %d\n", solution.val);
}
int fitnessFunction(Chessboard solution){
	int val = 0, i, j;
	for ( i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j){
			if (solution.matrix[i][j] == 0)
				continue;

			val += queenAtacks(solution, i, j);
		}
	}
	return val;

}

void initPopulation(int pop_size, Chessboard solutions[], short values){
	int i;

	for (i = 0; i < pop_size; ++i){
		setQueens(&solutions[i], values);
		solutions[i].val = fitnessFunction(solutions[i]);
	}
}

float crossingFactor(float v, float minn, float maxx){
	return (v - minn) / (maxx - minn);
}

void mixer(Chessboard* parent1, Chessboard* parent2, Chessboard* son){
	int i, j, bits[N][2], k = 0, flag1 = 0;

	for (i = 0;  i < N; ++i) {
		for (j = 0; j < N; ++j) {
			if (!parent1->matrix[i][j])
				continue;
			bits[k][0] = i;
			bits[k++][1] = j;
		}
	}

	k = 0;
	for (i= 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			if (!parent2->matrix[i][j])
				continue;

			// Si el padre1 pierde el volado
			// el padre2 hereda el bit
			if (!son->matrix[bits[k][0]][bits[k][1]] && randm() < 0.5 && k < N){
				son->matrix[bits[k][0]][bits[k][1]] = 1;
				flag1 = 1;
				k++;
			}else if (!son->matrix[i][j]){
				son->matrix[i][j] = 1;
				flag1 = 0;
				k++;
			}
			

		}
	}


	while (k < N){
			i = (int) (randm()*N);
			j = (int) (randm()*N);
			if (!son->matrix[i][j]) {
				son->matrix[i][j] = 1;
				k++;
			}
	}	
}

void mutation(Chessboard* solution){
	int i, j;
	i = (int) (randm() * N);
	j = (int) (randm() * N);

	short v = solution->matrix[i][j];
	solution->matrix[i][j] = !v; 

	while(1) {
		i = (int) (randm() * N);
		j = (int) (randm() * N);

		if (solution->matrix[i][j] != v){
			solution->matrix[i][j] = v;
			return;
		}

	}

}

Chessboard crossing(int pop_size, Chessboard solutions[], float pmutation){
	int i,j, minn = 0, maxx = 0, tmp;
	int order[pop_size];
	int parent[pop_size], parent_len = 0;
	float cf;

	// Ordenamiento para remplazo de padres por hijos 
	for (int i = 0; i < pop_size; ++i)
		order[i] = i;

	for (i = 0; i < pop_size - 1; ++i) {
		for (j = pop_size - 1; j > i; --j) {
			if (solutions[order[j - 1]].val < solutions[order[j]].val){
				int tmp = order[j];
				order[j] = order[j - 1];
				order[j-1] = tmp;
			}
		}
	}


	// Ruleta para elegir a los padres
	for (i = 0; i < pop_size; ++i) {
		cf = (float) (order[i]) / (float) (pop_size);

		if (randm() <= cf){
			parent[parent_len++] = order[i];
		}
		else
			tmp = order[i];
	}

	// Si la cantidad de padres es impar
	// se agrega el último padre que perdió
	// la ruleta
	if (parent_len == 0 || parent_len % 2 != 0)
		if (parent_len < 1){
			parent[parent_len++] = tmp;
			parent[parent_len++] = order[pop_size - 1];
		}
		else if (parent_len >= pop_size)
			parent_len = pop_size;
		else
			parent[parent_len++] = tmp;


	Chessboard* children = (Chessboard *) malloc(sizeof(Chessboard) * parent_len / 2 );
	// printf("------>   %d\n", parent_len);
	initPopulation(parent_len / 2, children, 0);

	for (i = 0; i < parent_len / 2; ++i) {
		mixer(&solutions[parent[2*i]],
			  &solutions[parent[2*i+1]],
			  &children[i]);


		// printf("========== padres   =====\n");
		// showChessboard(solutions[parent[2*i]]);
		// showChessboard(solutions[parent[2*i + 1]]);
		// printf("========== hijo   =====\n");
		// showChessboard(children[i]);

		if (randm() <= pmutation) {
			// printf("mutation\n");
			mutation(&children[i]);
		}


		children[i].val = fitnessFunction(children[i]);
	}

	j = 0;
	for (i = 0; i < parent_len / 2; ++i){
		if (solutions[order[j]].val >= children[i].val) {
			solutions[order[j++]] = children[i];
		}
	}

	for (i = 0; i < pop_size ; ++i) {
		if (solutions[minn].val > solutions[i].val)
			minn = i;
	}

	free(children);

	return solutions[minn];


}
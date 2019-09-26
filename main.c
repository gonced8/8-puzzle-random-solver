#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum dimensions {X=3, Y=3};
typedef enum {True='t', False='f'} Bool;
typedef enum {Left, Up, Right, Down} Move;
int Total = X*Y;
int NMoves = 4;

Bool Print = True;
Bool Clear = True;


int *shuffled_array(int dim);
void print_board(int *board);
int solve_randomly(int *board);
Bool check_solution(int *board);
int find_zero(int *board);
Bool check_valid_move(int i, Move move);
Move random_move();
int do_move(int *board, int i, Move move);
void switch_two(int *a, int *b);


int main (void){
	int *board;

	srand(time(NULL));

	board = shuffled_array(Total);
	solve_randomly(board);

	return 0;
}


int *shuffled_array(int dim){
	int i, temp, randomIndex;
	int *array = (int *) malloc(dim*sizeof(int));
	
	for(i = 0; i<dim; i++)		// fill array
		array[i] = i;
	
	for(i = 0; i<dim; i++){		// shuffle array
		temp = array[i];
		randomIndex = rand() % dim;

		array[i] = array[randomIndex];
		array[randomIndex] = temp;
	}

	return array;
}


void print_board(int *board){
	int i;

	for(i=0; i<Total; i++){
		printf("%d\t", board[i]);

		if((i+1)%X == 0){
			printf("\n\n");
		}
	}

	putchar('\n');

	return;
}


int solve_randomly(int *board){
	int i;
	unsigned long nsteps = 0;
	Move move;

	i = find_zero(board);

	print_board(board);

	while (check_solution(board) != True){
		do{
			move = random_move();
		}while(check_valid_move(i, move) != True);

		i = do_move(board, i, move);
		nsteps++;

		if(Print == True){
			if(Clear == True)
				system("clear");
			printf("Iteration %lu:\n", nsteps);
			print_board(board);
		}
	}

	printf("Solution found. Took %lu random moves.\n", nsteps);
	
	return nsteps;
}


Bool check_solution(int *board){
	int i;
	Bool solved = True;

	for(i=0; i<Total; i++){
		if(board[i] != i){
			solved = False;
			break;
		}
	}

	return solved;
}


int find_zero(int *board){
	int i;
	
	for(i=0; i<Total; i++){
		if(board[i] == 0)
			break;
	}

	return i;
}


Bool check_valid_move(int i, Move move){
	Bool valid = True;

	switch (move){
		case Left:
			if(i%X == 0)
				valid = False;
			break;

		case Up:
			if(i<X)
				valid = False;
			break;

		case Right:
			if((i+1)%X == 0)
				valid = False;
			break;

		case Down:
			if(i >= X*(Y-1))
				valid = False;
			break;
	}

	return valid;
}


Move random_move(){
	Move move = rand()%NMoves;
	
	return move;
}


int do_move(int *board, int i, Move move){
	int *a, *b;

	a = &(board[i]);

	switch (move){
		case Left:
			i = i-1;
			break;

		case Up:
			i = i-X;
			break;

		case Right:
			i = i+1;
			break;

		case Down:
			i = i+X;
			break;
	}

	b = &(board[i]);
	switch_two(a, b);

	return i;
}


void switch_two(int *a, int *b){
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;

	return;
}

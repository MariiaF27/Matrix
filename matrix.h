
#ifndef MATRIX
#define MATRIX

typedef struct Line{
    int len;
    int *numArray;
} Line;

typedef struct Matrix{
    int linesNum;
    Line *lineArray;
} Matrix;

typedef enum Err{
	ERR_CORRECT=1,
	ERR_OK=0,
	ERR_MEM=-1,
} Err;


Err read_input(int *input);
Err get_positive_num(int *input);
Err matrix_input(Matrix *matrix, int *linesNum, int *len);
int findSum(Line line);
void matrix_print(Matrix *matrix, int linesNum);
void vector_print(int *line, int linesNum);
Err matrix_init(Matrix **matrix);
void matrix_free(Matrix *matrix);
Err calculate_result(Matrix *matrix, int linesNum, int **result);

#endif

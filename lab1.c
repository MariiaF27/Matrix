#include <stdio.h>
#include<stdlib.h>
#include "matrix.h"

int main(){
    Matrix *matrix;
    int linesNum = 0, len = 0;

    if (matrix_init(&matrix) != ERR_OK){
        return ERR_MEM;
    }

    if(matrix_input(matrix, &linesNum, &len)==ERR_MEM){
    	matrix_free(matrix);
    	return ERR_MEM;
    }

    int *result = NULL;
    Err err = calculate_result(matrix, linesNum, &result);
    if(err!=ERR_OK){
    	matrix_free(matrix);
    	return err;
    }
    
    matrix_print(matrix, linesNum);
    vector_print(result, linesNum);

    free(result);
    matrix_free(matrix);
    return 0;
}


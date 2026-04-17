
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Err get_positive_num(int *input){
    int check = read_input(input);
    while (*input < 0 && check != ERR_MEM){
        printf("You can't input negative values.\n");
        scanf("%*[^\n]");
        check = read_input(input);
    }
    if (check == ERR_MEM){
        return ERR_MEM;
    }
    return ERR_OK;
}

Err read_input(int *input) {
    int check;

    while (1) {
        check = scanf("%d", input);

        if (check == ERR_CORRECT) { // Успешный ввод
            return ERR_OK;
        } else if (check == ERR_MEM) { // Ошибка или конец ввода
            printf("Program has been stopped\n");
            return ERR_MEM;
        } else { // Ошибочный ввод
            printf("You can't input such symbols.\n");
            scanf("%*[^\n]"); // Очистка буфера
            scanf("%*c");     // Удаление оставшегося символа новой строки
        }
    }
}

void matrix_partial_free(Matrix *matrix, int filledLines){
	if(matrix->lineArray==NULL) return;

	for(int i=0; i<filledLines; i++){
		free(matrix->lineArray[i].numArray);
	}

	free(matrix->lineArray);;
	matrix->lineArray=NULL;
}

Err matrix_input(Matrix *matrix, int *linesNum, int *len){
    printf("Enter the number of lines in the matrix:\n");
    if (get_positive_num(linesNum) == ERR_MEM){
        return ERR_MEM;
    }

    matrix->linesNum = *linesNum;
    matrix->lineArray = (Line*) malloc(*linesNum * sizeof(Line));

	if(matrix->lineArray==NULL){
		printf("Memory allocation failed for matrix lines array/\n");
		return ERR_MEM;
	}
	
    printf("Enter the number of elements in each line:\n");
    for (int i = 0; i < *linesNum; i++){
        printf("Number of elements in line %d:\n", i + 1);
        if (get_positive_num(len) == ERR_MEM){
        	matrix_partial_free(matrix, i);
            return ERR_MEM;
        }

        Line *currentLine = &(matrix->lineArray[i]);
        currentLine->len = *len;
        currentLine->numArray = (int*) malloc(*len * sizeof(int));

		if(currentLine ->numArray==NULL){
			printf("Memory allocation failed for line %d/\n", i+1);
			matrix_partial_free(matrix, i);
			return ERR_MEM;
		}
		
        printf("Enter the elements in line %d:\n", i + 1);
        for (int j = 0; j < *len; j++){
            if (read_input(&currentLine->numArray[j]) == ERR_MEM){
            	matrix_partial_free(matrix, i);
                return ERR_MEM;
            }
        }
    }
    return ERR_OK;
}

int findSum(Line line) {
    int sum = 0;
    for (int i = 0; i < line.len; i++) {
        sum += line.numArray[i]; 
    }
    return sum;
}

void matrix_print(Matrix *matrix, int linesNum){
    printf("The matrix is:\n[\n");
    for (int i = 0; i < linesNum; i++) {
        for (int j = 0; j < matrix->lineArray[i].len; j++){
            printf("%d ", matrix->lineArray[i].numArray[j]);
        }
        printf("\n");
    }
    printf("]\n");
}

void vector_print(int *line, int linesNum){
    printf("The resulting vector is:\n[");
    for (int i = 0; i < linesNum; i++){
        printf("%d ", line[i]);
    }
    printf("]\n");
}

Err matrix_init(Matrix **matrix){
	*matrix=(Matrix*)malloc(sizeof(Matrix));
	if(*matrix==NULL){
		printf("Memory allocation failed for matrix structure/\n");
		return ERR_MEM;
	}
	(*matrix)->lineArray=NULL;
	(*matrix)->linesNum=0;
	return ERR_OK;
}

void matrix_free(Matrix *matrix){
	if(matrix==NULL){
		return;
	}
	if(matrix->lineArray != NULL){
		for(int i=0; i<matrix->linesNum; i++){
			free(matrix->lineArray[i].numArray);
		}
		free(matrix->lineArray);
	}
	free(matrix);
}

Err calculate_result(Matrix *matrix, int linesNum, int **result){
	*result=(int*)malloc(linesNum*sizeof(int));

	if(*result ==NULL){
		printf("Memory allocation failed for result vector.\n");
		return ERR_MEM;
	}
	
	for(int i=0; i<linesNum; i++){
		(*result)[i]=findSum(matrix->lineArray[i]);
	}
	return ERR_OK;
}

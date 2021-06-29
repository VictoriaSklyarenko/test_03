/*
 ============================================================================
 Name        : listCalculator.c
 Author      : Victoria Sklyarenko
 Version     :4
 Copyright   : VSU
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// использование списков для хранения массива данных с произвольным количеством элементов
// выполнила Скляренко Виктория, ивт

#include <stdio.h>
#include <stdlib.h>

// список для входных данных
struct inputList {
    char operation, vbor;
    int size;
    float *x, *y;
    struct inputList *next;
};

// список для выходных данных
struct outputList {
    float *result;
    struct outputList *res_next;
};

// операции с числами
float* func_numb(char operation, float *first_number, float *second_number) {
    float fuctorial, stepen, *result_numb;
    result_numb = malloc(sizeof(float));
    switch (operation) {
// сложение
    case '+':
            result_numb[0] = first_number[0] + second_number[0];
            return result_numb;
// вычитание
    case '-':
            result_numb[0] = first_number[0] - second_number[0];
            return result_numb;
// умножение
    case '*':
            result_numb[0] = first_number[0] * second_number[0];
            return result_numb;
// деление
    case '/':
            if (second_number != 0) {
                result_numb[0] = first_number[0] / second_number[0];
                return result_numb;
            } else {
                return 0;
            }
// факториал
    case '!':
            fuctorial = 1;
            for (int i = 1; i <= first_number[0]; i++) {
                fuctorial *= i;
            }
            result_numb[0] = fuctorial;
            return result_numb;
// возведение в степень
    case '^':
            fuctorial = 1;
            stepen = 1;
            for (int i = 1; i <= second_number[0]; i++) {
                stepen *= first_number[0];
            }
            result_numb[0] = stepen;
            return result_numb;
    }
    return first_number;
    return second_number;
    free(first_number);
    free(second_number);
    free(result_numb);
}

// операции с векторами
float* func_vect(char operation, int size, float *firstvector, float *secondvector) {
    float *res_vect;
    switch (operation) {
// сложение
    case '+':
            res_vect = malloc(size * sizeof(float));
            for (int i = 0; i < size; i++) {
                res_vect[i] = firstvector[i] + secondvector[i];
            }
            return res_vect;
// вычитание
    case '-':
            res_vect = malloc(size * sizeof(float));
            for (int i = 0; i < size; i++) {
                res_vect[i] = firstvector[i] - secondvector[i];
            }
            return res_vect;
// умножение
    case '*':
            res_vect = malloc(sizeof(float));
            res_vect[0] = 0;
            for (int i = 0; i < size; i++) {
                res_vect[0] += firstvector[i] * secondvector[i];
            }
            return res_vect;
    }
    return firstvector;
    return secondvector;
    free(firstvector);
    free(secondvector);
    free(res_vect);
}

// считывание указателей, добавление чисел
float* add_numb(FILE *input, int size) {
    float *numb;
    numb = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        fscanf(input, "%f", &numb[i]);
    }
    return numb;
}

// добавление одного элемента списка для входных данных
void add_element(struct inputList *current, FILE *input) {
    struct inputList *current_elem = malloc(sizeof(struct inputList));
    fscanf(input, " %c", &current_elem->vbor);
    fscanf(input, " %c", &current_elem->operation);
    if (current_elem->vbor == 'v') {
        fscanf(input, " %i", &current_elem->size);
    } else {
        current_elem->size = 1;
    }
    if (current_elem->operation != '!') {
        current_elem->x = add_numb(input, current_elem->size);
        current_elem->y = add_numb(input, current_elem->size);
    } else {
        current_elem->x = add_numb(input, current_elem->size);
        current_elem->y = NULL;
    }
// последний элемент списка
    current_elem->next = NULL;
// переустановка указателя
    current->next = current_elem;
}

// добавление элемента списка для выходных данных
void result_add_element(struct outputList *res_current, struct inputList *current) {
    struct outputList *z_res = malloc(sizeof(struct inputList));
    if (current->vbor == 'v') {
        z_res->result = func_vect(current->operation, current->size, current->x, current->y);
    } else {
        z_res->result = func_numb(current->operation, current->x, current->y);
    }
    z_res->res_next = NULL;
    res_current->res_next = z_res;
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char in[100], out[100];
    char n = 'y';
    FILE *inFile, *outFile;
//указатели на начало inputList списка и текущий элемент
    struct inputList *head, *current;
//указатели на начало outputList списка и текущий элемент
    struct outputList *head_result, *current_result;
    while (n == 'y') {
// просит ввести файл, откуда брать данные
    	printf("Input file name: ");
        scanf("%s", in);
        inFile = fopen(in,"r");
// проверка на существование файла ввода
        if (inFile == NULL){
            printf("Error, enter again\n");
            while (inFile == NULL){
                printf("Input file name: ");
                scanf("%s", in);
                inFile = fopen(in,"r");
            }
        }
// просит ввести файл, куда записывать данные
        printf("\nOutput file name: ");
        scanf("%s", out);
        outFile = fopen(out,"w");
        if (feof(inFile) == 0) {
// head - указатель на структуру,на его начало
        	head = malloc(sizeof(struct inputList));
            fscanf(inFile, " %c", &head->vbor);
            fscanf(inFile, " %c", &head->operation);
            if (head->vbor == 'v') {
                fscanf(inFile, " %i", &head->size);
            } else {
                head->size = 1;
            }
            if (head->operation != '!') {
                head->x = add_numb(inFile, head->size);
                head->y = add_numb(inFile, head->size);
            } else {
                head->x = add_numb(inFile, head->size);
                head->y = NULL;
            }
// current указатель на структуру, а именно на текущее положение
            current = head;
// заполнение односвязанного списка вхожными данными из файла
            while (feof(inFile) == 0) {
                add_element(current, inFile);
                current = current->next;
            }
// head - указатель на структуру,на его начало
            head_result = malloc(sizeof(struct outputList));
            current = head;
            if (current->vbor == 'v') {
                head_result->result = func_vect(current->operation, current->size, current->x,
                                     current->y);
            } else {
                head_result->result = func_numb(current->operation, current->x, current->y);
            }
            head_result->res_next = NULL;
            current = current->next;
            current_result = head_result;
// пока элемент списка не последниий
            while (current != NULL) {
                result_add_element(current_result, current);
// переустановка указателей на следующий элемент
                current = current->next;
                current_result = current_result->res_next;
            }
            current = head;
            current_result = head_result;
            fclose(inFile);
            outFile = fopen(out, "w");
//запись результата в output
            while (current != NULL)
            {
// тут мы выбираем с чем работать: с числами или с векторами
            	fprintf(outFile,"That you will work with numbers or vectors?  (s - numbers, v-vectors)\n");
                fprintf(outFile,"%c\n",current->vbor);
                if (current->vbor == 'v') {
                    fprintf(outFile,"Enter the size of the vector:\n");
                    fprintf(outFile,"%i\n",current->size);
                    fprintf(outFile,"Enter vector one:\n");
// заполняем первый вектор
                    for(int i = 0; i < current->size ;i++){fprintf(outFile,"%f\n",current->x[i]);}
                    fprintf(outFile,"Enter vector two:\n");
// заполняем второй вектор
                    for(int i = 0; i < current->size ;i++){fprintf(outFile,"%f\n",current->y[i]);}
                    fprintf(outFile,"Select an operation (+ - *):\n");
                    fprintf(outFile,"%c\n",current->operation);
                    fprintf(outFile, "(");
                    for (int i = 0; i < current->size; i++) {
                        fprintf(outFile, " %.2f", current->x[i]);
                    }
                    fprintf(outFile, ") %c (", current->operation);
                    for (int i = 0; i < current->size; i++) {
                        fprintf(outFile, " %.2f", current->y[i]);
                    }
                    fprintf(outFile, " ) = ");
                    if (current->operation != '*') {
                        fprintf(outFile, "( ");
                        for (int i = 0; i < current->size; i++) {
                            fprintf(outFile, "%.2f ", current_result->result[i]);
                        }
                        fprintf(outFile, ")\n\n");
                    } else {
                        fprintf(outFile, "%.2f\n\n", current_result->result[0]);
                    }
                } else if (current->vbor == 's') {
                    fprintf(outFile, "%.2f %c %.2f = %.2f\n\n", current->x[0], current->operation,current->y[0], current_result->result[0]);
                }
                current = current->next;
                current_result = current_result->res_next;
            }
            fclose(outFile);
        }
        printf("\nWant to work with new files(input and output)?\n");
        scanf( "%s", &n);
    }
    return 0;
}

/*
 ============================================================================
 Name        : fileCalculator.c
 Author      : Sklyarenko Victoria
 Version     : 3
 Copyright   : VSU
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// файловый калькулятор
// выполнила Скляренко Виктория, ивт
// калькулятор может работать с входными файлами и также выводить результат в файл

#include <stdio.h>
#include <stdlib.h>

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char in[100],out[100],vbor,operation,next;
    FILE *inFile,*outFile;
    float *firstvector,*secondvector;
    float a, b, res, exponentiation;
    int size;
// операции с векторами
    	printf("My operation: +, -, *, /, ^, ! \n");
    do{
// откуда берётся файл
    	printf("Input file name: ");
        scanf("%s", in);
        inFile = fopen(in,"r");
// проверка на существование файла ввода
        if (inFile == NULL){
            printf("Error\n");
            while (inFile == NULL){
                printf("Input file name: ");
                scanf("%s", in);
                inFile = fopen(in,"r");
            }
        }
// куда будут записываться данные
        printf("\n Output file name: ");
        scanf("%s", out);
        outFile = fopen(out,"w");
        do {
// тут мы выбираем с чем работать: с числами или с векторами
        	fprintf(outFile," That you will work with numbers or vectors  (s - numbers, v-vectors)\n");
            fscanf(inFile," %c",&vbor);
            fprintf(outFile,"%c\n",vbor);
            if(vbor == 'v'){
// читает с файла операцию
            	fscanf(inFile," %c",&operation);
                fprintf(outFile," Input the size of the vector:\n");
// читает с файла размер вектора
                fscanf(inFile,"%i",&size);
                fprintf(outFile,"%i\n",size);
                firstvector = malloc(size*sizeof(int));
                secondvector = malloc(size*sizeof(int));
                fprintf(outFile,"Enter vector one:\n");
// заполняем первый вектор
                for(int i = 0; i < size ;i++){fscanf(inFile," %f",&firstvector[i]);fprintf(outFile,"%f\n",firstvector[i]);}
                fprintf(outFile,"Enter vector two:\n");
// заполняем второй вектор
                for(int i = 0; i < size ;i++){fscanf(inFile," %f",&secondvector[i]);fprintf(outFile,"%f\n",secondvector[i]);}
                fprintf(outFile," Select an operation (+ - *):\n");
                fprintf(outFile,"%c\n",operation);
// операции с векторами
                switch(operation){
// сложение
                    case('+'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", firstvector[i]);
                        fprintf(outFile, ") + ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", secondvector[i]);
                        fprintf(outFile, ") = ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", firstvector[i] + secondvector[i]);
                        fprintf(outFile, ")");
                        fprintf(outFile,"\n\n");
                        break;
// вычитание
                    case('-'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", firstvector[i]);
                        fprintf(outFile, ") + ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", secondvector[i]);
                        fprintf(outFile, ") = ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", firstvector[i] - secondvector[i]);
                        fprintf(outFile, ")");
                        fprintf(outFile,"\n\n");
                        break;
// умножение
                    case('*'):
                        fprintf(outFile, "( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", firstvector[i]);
                        fprintf(outFile, ") * ( ");
                        for (int i = 0; i < size; i++)
                            fprintf(outFile, "%.2f ", secondvector[i]);
                        fprintf(outFile, ") = ");
                        for (int i = 0; i < size; ++i) {
                            if (i != size - 1 ){fprintf(outFile, "%.2f ", firstvector[i]*secondvector[i]);
                                fprintf(outFile,"+ ");
                            }
                            else{
                                fprintf(outFile, "%.2f ", firstvector[i]*secondvector[i]);
                            }
                        }
                        fprintf(outFile, " = ");
                        for (int i = 0; i < size; i++)
                            res += firstvector[i] * secondvector[i];
                        fprintf(outFile, "%.2f ", res);
                        fprintf(outFile,"\n\n");
                        break;
                    default:
                        printf("Error\n");
// если ввести какой-то другой символ - будет ошибка
                }
//очистка памяти
                free(firstvector);
                free(secondvector);
            }else{
                fscanf(inFile," %c",&operation);
                if (operation != '!') {
// для факториала нужно только ввести число и операцию
                    fscanf(inFile," %f %f",&a,&b);
                    switch (operation) {
// операции: сложение, вычитание, деление, умножение, возведение в степень и факториал через цикл for соответственно
                        case ('+'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a + b);
                            fprintf(outFile,"\n");
                            break;
                        case ('-'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a - b);
                            fprintf(outFile,"\n");
                            break;
                        case ('/'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a / b);
                            fprintf(outFile,"\n");
                            break;
                        case ('*'):
                            fprintf(outFile,"%f %c %f = %f\n", a, operation, b, a * b);
                            fprintf(outFile,"\n");
                            break;
                        case ('^'):
		                  exponentiation = 1;
                            if (b >= 0) {
                                for (int i = 1; i <= b; i++) {
                                	exponentiation *= a;
                                }
                                fprintf(outFile,"%f %c %f = %f\n", a, operation, b, exponentiation);
                            } else if (b < 0) {
                                for (int i = 0; i > b; i--) {
                                	exponentiation *= a;
                                }
                                fprintf(outFile,"%f %c %f = %f\n", a, operation, b, 1 / exponentiation);

                            }
                            fprintf(outFile,"\n");
                            break;
                        default:
// ошибка, если операция не будет определена
                            fprintf(outFile,"Error\n");
                    }
                } else {
                    fscanf(inFile," %f",&a);
                    res = 1;
                    if (a >= 0 && (a <= (int)a)) {
                        for (int i = 1; i <= a; i++) {
                            res *= i;
                        }
                        fprintf(outFile,"%f %c = %f\n", a, operation, res);
                        fprintf(outFile,"\n");
                    } else {
// обработка ошибки
                        fprintf(outFile,"Error\n");
                    }
                }
            }
        } while (feof(inFile) == 0);
// закрывает файл при завершении работы с файлом ввода
        fclose(outFile);
// очистка
        clearerr(outFile);
// тут у нас спрашивают: "хотим ли мы продолжить?"
// если переменная равна y, то калькулятор продолжает свою работу, если переменная равна n, то на этом все завершается
        printf("\n Continue (y/n)?\n");
        scanf(" %c", &next);
    }while (next == 'y');
    return 0;
}

/*
 ============================================================================
 Name        : vectorCalculator.c
 Author      : Vika
 Version     :
 Copyright   : VSU
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
// векторный калькулятор
// выполнила Скляренко Виктория, ивт

#include <stdio.h>
#include <stdlib.h>

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	float *firstvector,*secondvector;
	int size;
	float a, b, res, exponentiation;
	int vbor;
	float result = 0.0;
	char operation;
	char next;
// операции с векторами
	printf("My operation: +, -, *, /, ^ \n");
	do {
		printf(" That you will work with numbers or vectors (0 - numbers, 1- vectors)\n");
// тут мы выбираем с чем работать: с числами или с векторами
		scanf("%i",&vbor);
		if(vbor == 1){
// вводим размер вектора
			printf(" Input the size of the vector:\n");
			scanf("%i",&size);
			firstvector = malloc(size*sizeof(int));
			secondvector = malloc(size*sizeof(int));
			printf("Input the first vector:\n");
			for(int i = 0; i < size ;i++){scanf("%f",&firstvector[i]);}
// первый вектор
			printf("Input the second vector:\n");
			for(int i = 0; i < size ;i++){scanf("%f",&secondvector[i]);}
// второй вектор
			printf(" Select an operation (+ - *):\n");

			scanf(" %c", &operation);
			switch(operation){
// операция "сложение"
			case('+'):
				for(int i = 0; i < size ;i++)printf("%f ",firstvector[i] + secondvector[i]);
				break;
// вычитание
			case('-'):
				for(int i = 0; i < size ;i++)printf("%f ",firstvector[i] - secondvector[i] );
				break;
// умножение
			case('*'):
				for(int i = 0; i < size ;i++){
					result += firstvector[i] * secondvector[i];
				}
				printf("%f \n",result);
				result = 0;
				break;
			default:
// если ввести какой-то другой символ - будет ошибка
					printf("Error\n");
			}
			free(firstvector);
			free(secondvector);
			printf("Continue (y/n)? \n");
// тут у нас спрашивают: "хотим ли мы продолжить?"
// если переменная равна y, то калькулятор продолжает свою работу, если переменная равна n, то на этом все завершается
			scanf(" %c", &next);
		}else{

			scanf("%f %c", &a, &operation);
			if (operation != '!') {
// для факториала нужно только ввести число и операцию
				scanf("%f", &b);
				switch (operation) {
// опять сложение
				case ('+'):
					printf("%f %c %f = %f\n", a, operation, b, a + b);
					break;
// опять вычитание
				case ('-'):
					printf("%f %c %f = %f\n", a, operation, b, a - b);
					break;
// деление
				case ('/'):
					printf("%f %c %f = %f\n", a, operation, b, a / b);
					break;
// умножение
				case ('*'):
					printf("%f %c %f = %f\n", a, operation, b, a * b);
					break;
// возведение в степень
				case ('^'):
		exponentiation = 1;
				if (b >= 0) {
					for (int i = 1; i <= b; i++) {
							exponentiation *= a;
						}
						printf("%f %c %f = %f\n", a, operation, b, exponentiation);
					} else if (b < 0) {
						for (int i = 0; i > b; i--) {
							exponentiation *= a;
						}
						printf("%f %c %f = %f\n", a, operation, b, 1 / exponentiation);
					}
					break;
				default:
					printf("Error\n");
// ошибка, если операция не будет определена
				}
			} else {
				res = 1;
				if (a >= 0 && (a * 3 < (int)a)) {
					for (int i = 1; i <= a; i++) {
// факториал, как и степень, реализован через цикл for
						res *= i;
					}
					printf("%f %c = %f\n", a, operation, res);
				} else {
					printf("Error\n");
// ошибка, если операция не будет определена
				}
			}
			printf("Continue (y/n)? \n");
// тут у нас спрашивают: "хотим ли мы продолжить?"
// если переменная равна y, то калькулятор продолжает свою работу, если переменная равна n, то на этом все завершается
			scanf(" %c", &next);
		}
	} while (next == 'y');
	return 0;

}

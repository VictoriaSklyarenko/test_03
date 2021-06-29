/*
 ============================================================================
 Name        : stackCalculator.c
 Author      : Vika
 Version     :
 Copyright   : VSU
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    float data;
    struct element *next;
} stack;
stack *headStack = NULL;

float numberFunction(char operation, float number1, float number2){     //  function for working with numbers
    float factorial = 1, stepen = 1, resultNumber;
    switch (operation){  //  operation fetch block
        case '+':
            resultNumber = number1 + number2;
            return resultNumber;  //  результат сложение
        case '-':
            resultNumber = number1 - number2;
            return resultNumber;  //  результат вычитание
        case '*':
            resultNumber = number1 * number2;
            return resultNumber;  // результат умножение
        case '/':
            if (number2 != 0){
                resultNumber = number1 / number2;
                return resultNumber;  //  результат деления
            }
            else{
                return 0;
            }
        case '!':
            for (int i=1; i <= number1; i++){
                factorial = factorial*i;
            }
            resultNumber = factorial;
            return resultNumber;  //  результат факториала
        case '^':
            for (int i=1; i <= number2; i++){
                stepen = stepen*number1;
            }
            resultNumber = stepen;
            return resultNumber;  //  результат степени
    }
    return number1;
}

void pushElement(stack **head, float data){         //добавить элемент в стек структуру
    stack *pushLocal = malloc(sizeof(stack));
    pushLocal->next = *head;
    pushLocal->data = data;
    *head = pushLocal;
}

float popElement(stack **head){             //  remove element from stack`s struct
    stack *popLocal;
    float data;
    popLocal = *head;
    *head = (*head)->next;
    data = popLocal->data;
    return data;
}

int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char n, stringLine[255], line = '0';
    char input[255], output[255];
    int i = 0;
    float localNum, onenumber, twonumber;
    FILE *inFile, *outFile;
    do{
        printf("Enter input file name:\n");
        scanf("%s", input);
        inFile = fopen(input,"r");  //   открыть входной файл
        if (inFile == NULL){
            printf("File is empty. Try again.\n");
            while (inFile == NULL){
                printf("Enter input file name:\n");
                scanf(" %s", input);
                inFile = fopen(input,"r");
            }
        }
        printf("Enter output file name:\n");
        scanf(" %s", output);
        outFile = fopen(output, "w");  //  открыть выходной файл
        while (feof(inFile) == 0){
            fscanf(inFile, "%c", &stringLine[i]);
            if (stringLine[i] == ' '){
                if (line == '0'){
                    localNum = strtof(stringLine, NULL); //  разделите выражение на символы
                    pushElement(&headStack, localNum);
                    i = 0;
                }
            }
            else if (stringLine[i] == '*' || stringLine[i] == '+' || stringLine[i] == '-'	|| stringLine[i] == '/' || stringLine[i] == '^'){
                onenumber = popElement(&headStack);
                twonumber = popElement(&headStack);
                pushElement(&headStack, numberFunction(stringLine[i], onenumber, twonumber));
                fprintf(outFile, "%.3f %c %.3f = %.3f \n", onenumber, stringLine[i], twonumber, numberFunction(stringLine[i], onenumber, twonumber));
                line = '1';
            }
            else if (stringLine[i] == 'n'){
                while (headStack != NULL){
                    popElement(&headStack);
                }
                fprintf(outFile, "\n");
            }
            else{
                line = '0';
                i = i + 1;
            }
        }
        fclose(inFile);
        fclose(outFile);
        printf("Want to work with new files(input and output)?\n");
        scanf(" %c", &n);
    }
    while (n == 'y');
    return 0;
}

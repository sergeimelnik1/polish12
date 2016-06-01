#include "stdlib.h"
#include "string.h"
#include "iostream"

using namespace std;

#define SIZE 50
int *tos, stack[SIZE];
void push(int i);
int pop(void);
int top();
int isEmpty(void);
int prior(char ch);
char * polish(char * strIn, char * strOut);
int polishScore(char * strIn);

int main(void)
{
    tos = stack; /* tos ссылаетс€ на основание стека */
    char* stringIn = "21*(34-7)*5";
    char* stringOut = new char[strlen(stringIn) * 2 + 1];
    stringOut = polish(stringIn, stringOut);
    cout << stringIn << "\nPolish write=" << stringOut;
    cout << "=" << polishScore(stringOut);
    delete[]stringOut;
    cout << endl;
    system("pause");
    return 0;
}
void push(int i) {
    tos++;
    if (tos == (stack + SIZE - 1)) {
        printf("Stack Overflow!\n");
        exit(1);
    }
    *tos = i;
}
int pop(void) {
    if (isEmpty()) {
        printf("stack is empty\n");
        
    }
    tos--;
    return *(tos + 1);
}
int top() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        
    }
    return *tos;
}
int isEmpty(void) {
    if (tos == stack)
        return 1;
    else
        return 0;
}
char  *polish(char * strIn, char * strOut) {
    int i = 0;
    int j = 0;
    while (strIn[i] != '\0') {
        
        if (isalnum(strIn[i])) {
            while (isalnum(strIn[i])) {
                strOut[j] = strIn[i];
                ++i;
                ++j;
            }
            strOut[j] = ' ';
            j++;
            if (strIn[i] == '\0')
                break;
        }
        
        if (prior(strIn[i]) == 0)
            push(strIn[i]);
        else {
            if (isEmpty() || prior(strIn[i]) > prior(top()))
                push(strIn[i]);
            
            else {
                while (prior(strIn[i]) <= prior(top()))
                    if (!isEmpty()) {
                        strOut[j] = top();
                        pop();
                        strOut[j + 1] = ' ';
                        j = j + 2;
                    }
                push(strIn[i]);
            }
        }
        
        if (strIn[i] == ')') {
            pop();
            while (top() != '(') {
                strOut[j] = top();
                pop();
                strOut[j + 1] = ' ';
                j = j + 2;
            }
            pop();
        }
        ++i;
    }
    while (!isEmpty()) {
        strOut[j] = top();
        pop();
    }
    strOut[j + 1] = '\0';
    return strOut;
}

int prior(char  charIn) {
    if (charIn == '(')return 0;
    if (charIn == '+' || charIn == '-')return 1;
    if (charIn == '*' || charIn == '/')return 2;
    else return 3;
}

int polishScore(char * strIn) {//подсчет значения
    int i = 0;
    int j = 0;
    while (strIn[i] != '\0') {//пока считываетс€ файл провер€ем все символы
        char*bofer = new char[strlen(strIn) * 2 + 1];//создание буфера в котором мы будем все вычисл€ть
        if (strIn[i] == ' ')
            i++;
        if (isalnum(strIn[i])){
            while (isalnum(strIn[i])) {//проверка наличи€ цифр записываем в буфер и увеличиваем его размер
                bofer[j] = strIn[i];
                ++i;
                ++j;
            }
            push(atoi(bofer));
            j = 0;
        }
        
        if (strIn[i] == '+') {
            int a = top();
            pop();
            int b = a + top();//выполение операций относительно того, какой знак найден
            pop();
            push(b);
        }
        if (strIn[i] == '-') {
            int a = top();
            pop();
            int b = top() - a;
            pop();
            push(b);
        }
        if (strIn[i] == '*') {
            int a = top();
            pop();
            int b = top() * a;
            pop();
            push(b);
        }
        if (strIn[i] == '/') {
            int a = top();
            pop();
            int b = top() / a;
            pop();
            push(b);
        }
        i++;
    }
    return top();
}




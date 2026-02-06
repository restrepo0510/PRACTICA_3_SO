#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100

// Estructura de la pila
typedef struct {
    double items[MAX_STACK];
    int top;
} Stack;

// Inicializar la pila
void initStack(Stack *s) {
    s->top = -1;
}

// Verificar si la pila está vacía
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Verificar si la pila está llena
int isFull(Stack *s) {
    return s->top == MAX_STACK - 1;
}

// Agregar elemento a la pila 
void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Error: Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
    printf("Pushed: %.2f\n", value);
}

// Sacar elemento de la pila
double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack underflow\n");
        return 0;
    }
    return s->items[(s->top)--];
}

// Ver el elemento superior sin sacarlo
double peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack is empty\n");
        return 0;
    }
    return s->items[s->top];
}

// Mostrar el contenido de la pila
void displayStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack: [vacía]\n");
        return;
    }
    printf("Stack: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%.2f ", s->items[i]);
    }
    printf("\n");
}

// Realizar operación
void performOperation(Stack *s, char op) {
    if (s->top < 1) {
        printf("Error: Operandos insuficientes\n");
        return;
    }
    
    double b = pop(s);
    double a = pop(s);
    double result;
    
    switch(op) {
        case '+':
            result = a + b;
            printf("%.2f + %.2f = %.2f\n", a, b, result);
            break;
        case '-':
            result = a - b;
            printf("%.2f - %.2f = %.2f\n", a, b, result);
            break;
        case '*':
            result = a * b;
            printf("%.2f * %.2f = %.2f\n", a, b, result);
            break;
        case '/':
            if (b == 0) {
                printf("Error: División por cero\n");
                push(s, a);
                push(s, b);
                return;
            }
            result = a / b;
            printf("%.2f / %.2f = %.2f\n", a, b, result);
            break;
        default:
            printf("Error: Operador no válido\n");
            push(s, a);
            push(s, b);
            return;
    }
    
    push(s, result);
}

// Función para verificar si es un número
int isNumber(const char *str) {
    char *endptr;
    strtod(str, &endptr);
    return *endptr == '\0' && endptr != str;
}

int main() {
    Stack stack;
    initStack(&stack);
    
    char input[100];
    
    printf("========================================\n");
    printf("  CALCULADORA \n");
    printf("========================================\n");
    printf("Instrucciones:\n");
    printf("  - Ingrese números para apilar\n");
    printf("  - Operadores: + - * /\n");
    printf("  - 'show' para ver la pila\n");
    printf("  - 'clear' para limpiar la pila\n");
    printf("  - 'exit' para salir\n");
    printf("========================================\n\n");
    
    while (1) {
        printf("RPN> ");
        if (scanf("%99s", input) != 1) {
            break;
        }
        
        // Salir
        if (strcmp(input, "exit") == 0) {
            printf("¡Hasta luego!\n");
            break;
        }
        
        // Mostrar pila
        if (strcmp(input, "show") == 0) {
            displayStack(&stack);
            continue;
        }
        
        // Limpiar pila
        if (strcmp(input, "clear") == 0) {
            initStack(&stack);
            printf("Pila limpiada\n");
            continue;
        }
        
        // Si es un número, hacer push
        if (isNumber(input)) {
            double num = atof(input);
            push(&stack, num);
            continue;
        }
        
        // Si es un operador, realizar operación
        if (strlen(input) == 1 && strchr("+-*/", input[0])) {
            performOperation(&stack, input[0]);
            continue;
        }
        
        printf("Error: Entrada no válida '%s'\n", input);
    }
    
    return 0;
}
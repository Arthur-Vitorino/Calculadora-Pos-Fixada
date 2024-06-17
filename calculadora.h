#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define M_PI 3.14159265358979323846

// Definição da estrutura da pilha para números
typedef struct No
{
    double dado;
    struct No *proximo;
} No;

typedef struct
{
    No *topo;
} Pilha;

void inicializar(Pilha *pilha);
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);

// Definição da estrutura da pilha para strings
typedef struct NoStr
{
    char *dado;
    struct NoStr *proximo;
} NoStr;

typedef struct
{
    NoStr *topo;
} PilhaStr;

void inicializarStr(PilhaStr *pilha);
void empilharStr(PilhaStr *pilha, char *valor);
char *desempilharStr(PilhaStr *pilha);

double avaliarExpressaoPosfixada(const char *expressao);

char *converterParaInfixa(const char *expressao);

#endif

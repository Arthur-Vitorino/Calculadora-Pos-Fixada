#include "calculadora.h"

void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

void inicializarStr(PilhaStr *pilha)
{
    pilha->topo = NULL;
}

void empilharStr(PilhaStr *pilha, char *valor)
{
    NoStr *novoNo = (NoStr *)malloc(sizeof(NoStr));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

char *desempilharStr(PilhaStr *pilha)
{
    if (pilha->topo != NULL)
    {
        NoStr *temp = pilha->topo;
        char *valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double avaliarExpressaoPosfixada(const char *expressao)
{
    Pilha pilha;
    inicializar(&pilha);
    char *token;
    char expressaoCopy[100];
    strcpy(expressaoCopy, expressao);

    token = strtok(expressaoCopy, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            empilhar(&pilha, atof(token));
        }
        else if (strcmp(token, "log") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, log10(operando));
        }
        else if (strcmp(token, "sen") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, sin(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "cos") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, cos(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "tg") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, tan(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "sqrt") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, sqrt(operando));
        }
        else if (strcmp(token, "^") == 0)
        {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            empilhar(&pilha, pow(operando1, operando2));
        }
        else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                 strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
        {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);

            switch (token[0])
            {
            case '+':
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0)
                    empilhar(&pilha, operando1 / operando2);
                else
                {
                    printf("Erro: Divisão por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                printf("Erro: Operador inválido\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Erro: Token inválido na expressão\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

char *converterParaInfixa(const char *expressao)
{
    PilhaStr pilha;
    inicializarStr(&pilha);
    char *token;
    char expressaoCopy[100];
    strcpy(expressaoCopy, expressao);

    token = strtok(expressaoCopy, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            char *numero = (char *)malloc(strlen(token) + 1);
            strcpy(numero, token);
            empilharStr(&pilha, numero);
        }
        else if (strcmp(token, "log") == 0 || strcmp(token, "sen") == 0 ||
                 strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                 strcmp(token, "sqrt") == 0)
        {
            char *operando = desempilharStr(&pilha);
            char *resultado = (char *)malloc(strlen(token) + strlen(operando) + 3);
            sprintf(resultado, "%s(%s)", token, operando);
            empilharStr(&pilha, resultado);
            free(operando);
        }
        else
        {
            char *operando2 = desempilharStr(&pilha);
            char *operando1 = desempilharStr(&pilha);
            char *resultado = (char *)malloc(strlen(operando1) + strlen(token) + strlen(operando2) + 5);
            sprintf(resultado, "(%s %s %s)", operando1, token, operando2);
            empilharStr(&pilha, resultado);
            free(operando1);
            free(operando2);
        }

        token = strtok(NULL, " ");
    }

    return desempilharStr(&pilha);
}

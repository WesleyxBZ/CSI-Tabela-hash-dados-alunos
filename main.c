#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "struct.h"
#include "alunos.h"

const int tam=50;

int main(){
    setlocale(LC_ALL,"Portuguese");

    TabHash *tab[tam]; // Criando ponteiro para tabela de N posições
    int opc=0;

    iniciaTab(tab, tam); // Inicializando tabela de N posições

    do{
        printf("\t\t==============\n");
        printf("\t\t| Trabalho 1 |\n");
        printf("\t\t==============\n\n");

        printf("<1> - Inserir novo aluno\n");
        printf("<2> - Remover aluno\n");
        printf("<3> - Visualizar aluno pelo nº de matrícula\n");
        printf("<4> - Visualizar todos os alunos\n\n");
        printf("<0> - Sair do programa\n\n:");
        scanf("%d", &opc);

        switch(opc){
            case 1:
                inserir(tab, tam);
                break;
            case 2:
                remover(tab, tam);
                break;
            case 3:
                visualizarPorMat(tab, tam);
            break;
            case 4:
                visualizarTodos(tab, tam);
                break;
            default:
                system("cls");
                break;
        }
    }while(opc != 0);

    freeAll(tab, tam); // Limpa todos os elementos ao final do programa
    return 0;
}

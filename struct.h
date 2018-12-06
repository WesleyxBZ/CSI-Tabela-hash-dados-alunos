#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct tabHash{
    int matricula;
    char nome[10];
    char sobrenome[20];
    char email[30];
    struct tabHash *prox;
};
typedef struct tabHash TabHash;

#endif // STRUCT_H_INCLUDED

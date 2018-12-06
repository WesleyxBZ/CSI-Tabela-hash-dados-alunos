/* Inicializa a tabela hash com N posições nulas */
void iniciaTab(TabHash* tab[], int tam){
    /* Percorre todas as N posições da tabela */
    for(int i=0; i<tam; i++){
        tab[i] = NULL; // A posição [i] recebe nulo
    }
}

/* Efetua o calculo Hash */
int hashNum(int mat, int tam){
    return (mat%tam)+1;
}

/* Verifica se matrícula inserida já existe na tabela */
int verificaMat(TabHash *tab[], TabHash *novoElem, int matricula, int tam){

    TabHash *aux=NULL;

    /* Roda um laço em toda a tabela */
    for(int i=0; i<tam; i++){
        aux = tab[i]; // 'aux' recebe nova posição de tabela toda vez que o laço gira

        /* Enquanto 'aux' for diferente de nulo percorrerá a lista encadeada */
        while(aux != NULL){

            /* Compara a matrícula da tabela com matrícula inserida agora */
            if(aux->matricula == matricula){
                printf("\nAluno já cadastrado...\n");
                printf("Deseja substituir informações?\n\n<0> - SIM\n<1> - NÃO\n\n: ");
                int opc=0;
                scanf("%d", &opc);

                if(opc == 0){
                    system("cls");
                    insereInfo(aux, matricula);
                    free(novoElem);
                    system("cls");
                    printf("Informações atualizadas!\n\n");
                }else{
                    system("cls");
                    printf("Informações mantidas!\n\n");
                }
                return 0;
            }
            aux = aux->prox;
        }
    }

    return 1;
}

/* Verifição de posição livre */
void verificaPos(TabHash *tab[], TabHash *novoElem, int posicao, int mat, int tam){

    /* Se a determinada posição estiver vazia, insere o elemento na posição da tabela*/
    if(tab[posicao] == NULL){
        novoElem->prox = NULL/*tab[posicao]*/; // Próximo do elemento aponta para nulo
        tab[posicao] = novoElem; // Posição N da tabela recebe elemento
        insereInfo(novoElem, mat); // Insere informações no elemento
        system("cls");
        printf("Aluno inserido!\n\n");
    }else{ /* Se estiver ocupada terá que encadear o elemento em outro da tabela */
        system("cls");
        printf("\nPosição hash ocupada...\n\n");

        TabHash *aux = tab[posicao];
        int op=0, op2=0;

        while(aux->prox != NULL){
            aux = aux->prox;
        }

        printf("Inserir novo aluno...\n\n");
        insereInfo(novoElem, mat);
        aux->prox = novoElem;
        novoElem->prox = NULL;
        system("cls");
        printf("Aluno inserido!\n\n");

    }
}

/* Insere informações, a serem digitadas, no novo elemento criado */
void insereInfo(TabHash *novoElem, int matricula){

    char nome[10], sobrenome[20], email[30];

    printf("Nome: ");
    fflush(stdin);
    gets(nome);
    printf("Sobrenome: ");
    fflush(stdin);
    gets(sobrenome);
    printf("E-mail: ");
    fflush(stdin);
    gets(email);

    novoElem->matricula = matricula;
    strcpy(novoElem->nome, nome);
    strcpy(novoElem->sobrenome, sobrenome);
    strcpy(novoElem->email, email);
}

/* Chama funções para inserir elemento na tabela */
void inserir(TabHash *tab[], int tam){
    system("cls");

    int matricula;
    TabHash *novoElem = (TabHash*)malloc(sizeof(TabHash)); // Criando e alocando memória para um novo elemento
    novoElem->prox = NULL;

    printf("Inserir aluno...\n\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);

    int posicao = hashNum(matricula, tam); // Faz o calculo hash e recebe o resultado do calculo
    int contr = verificaMat(tab, novoElem, matricula, tam); // Verifica se matrícula inserida já existe na tabela
    if(contr == 1)verificaPos(tab, novoElem, posicao, matricula, tam); // Verifica a posiçao na tablela para saber se está livre
}

/* Remove elementos da tabela */
void remover(TabHash *tab[], int tam){
    system("cls");

    int num, posicao, enc=0;
    TabHash *aux=NULL; // Cria ponteiro auxuliar

    /* Verifica se não existe elementos na tabela */
    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("Não existe alunos cadastrados!\n\n");
    }else{
        printf("\nDigite a matrícula que deseja remover: ");
        scanf("%d", &num);

        posicao = hashNum(num, tam); // posição recebe calculo hash da matricula inserida

        system("cls");

        /* Verifica se a posição contém elemento */
        if(tab[posicao] != NULL){
            if(tab[posicao]->matricula == num){ // Se a matrícula inserida for igual a digitada
                aux = tab[posicao];                 // 'aux' recebe o elemento
                tab[posicao] = tab[posicao]->prox;  // Elemento recebe o seu próximo
                free(aux);                          // 'aux' é liberada da memória
                printf("Aluno removido!\n\n");
            } else { // Se a posição não contém o elemento
                aux = tab[posicao]->prox; // 'aux' recebe o próximo elemento na lista encadeada
                TabHash *ant = tab[posicao]; // Criado ponteiro 'ant' que recebe elemento da tabela

                /* Enquanto aux != de nulo e matrícula digitada != de matrícula na lista encadeada */
                while(aux != NULL && aux->matricula != num){
                    ant = aux;       // 'ant' recebe próxima posição na lista encadeada
                    aux = aux->prox; // 'aux' recebe próxima posição na lista encadeada (uma posição a frente de 'ant')
                }

                /* Se aux != de nulo */
                if(aux != NULL){
                    ant->prox = aux->prox; // O próximo de 'ant' aponta para o próxima de 'aux' (que pode ser nulo ou conter elemento encadeado)
                    free(aux); // Libera memória de 'aux'
                    printf("Aluno removido!\n\n");
                } else { // Se a 'aux' for nulo, não foi encontrada a matrícula digitada
                    printf("Matrícula não encontrada!\n\n");
                }
            }
        }else{ // Se a posição calculada em hash não contém elemento, matricula está incorreta ou não existe
            printf("Matrícula não encontrada!\n\n");
        }
    }
}

/* Visualizar aluno pelo número de matrícula */
void visualizarPorMat(TabHash *tab[], int tam){
    system("cls");

    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("Não existe alunos cadastrados!\n\n");
    }else{
        int mat, cont=0;

        printf("Digite o número de matrícula: ");
        scanf("%d", &mat);

        int posicao = hashNum(mat, tam);
        cont++;

        TabHash *aux=NULL; // Craiando ponteiro aux

        /* Se a posição calculada por hash for diferente de nulo */
        if(tab[posicao] != NULL){
            aux = tab[posicao]; // Ponteiro aux recebe a posição da tabela
            cont++; // Incrementa contador de passos

            /* Enquando aux for diferente de nulo, o laço gira */
            while(aux != NULL){
                /* Se a matrícula digitada for igual ao que está na tabela, imprime
                   as informações e incrementa 'cont'*/
                if(aux->matricula == mat){
                    cont++;
                    system("cls");
                    printf("\nID \t%-10s\t%-20s\tEmail\n", "Nome", "Sobrenome");
                    printf("%d\t%-10s\t%-20s\t%s\n", aux->matricula, aux->nome, aux->sobrenome, aux->email);
                    printf("\nQtd passos até ser encontrada: %d\n\n", cont);
                    system("pause");
                    system("cls");
                }
                aux = aux->prox; // 'aux' recebe o próximo elemento
            }
        } else {
            system("cls");
            printf("Matrícula não encontrada!\n\n");
        }
    }
}

/* Visualizar todos os alinos */
void visualizarTodos(TabHash *tab[], int tam){
    system("cls");

    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("Não existe alunos cadastrados!\n\n");
    }else{

        TabHash *aux=NULL; // ponteiro 'aux' recebe nulo

        printf("\nID \t%-10s\t%-20s\tEmail\n", "Nome", "Sobrenome");

        /* Laço girará até 'i' ser menor que tamanho da tabela */
        for(int i=0; i<tam; i++){
            aux = tab[i]; // 'aux' recebe posição da tabela

            /* Enquanto aux for diferente de nulo, laço gira e aponta para o próximo encadeado */
            while(aux != NULL){
                printf("%d\t%-10s\t%-20s\t%s\n", aux->matricula, aux->nome, aux->sobrenome, aux->email);
                aux = aux->prox; // 'aux' recebe, se existir, o próximo encadeado
            }
        }

        printf("\n");
        system("pause");
        system("cls");
    }
}

/* Verifica se contém elementos na tabela */
int verifTab(TabHash *tab[], int tam){
    TabHash *aux=NULL;
    for(int i=0; i<tam; i++){
        aux = tab[i];
        while(aux != NULL){
            return 0;
            aux=aux->prox;
        }
    }
    return 1;
}

/* Limpa todos os elementos ao final do programa */
void freeAll(TabHash *tab[], int tam){
    TabHash *aux=NULL;
    for(int i=0; i<tam; i++){
        aux = tab[i];

        if(aux != NULL){
            if(aux->prox == NULL){
                free(aux);
            }else{
                TabHash *p=NULL;
                while(aux != NULL){
                    p=aux;
                    aux = aux->prox;
                    free(p);
                }
            }
        }
    }
}

/* Inicializa a tabela hash com N posi��es nulas */
void iniciaTab(TabHash* tab[], int tam){
    /* Percorre todas as N posi��es da tabela */
    for(int i=0; i<tam; i++){
        tab[i] = NULL; // A posi��o [i] recebe nulo
    }
}

/* Efetua o calculo Hash */
int hashNum(int mat, int tam){
    return (mat%tam)+1;
}

/* Verifica se matr�cula inserida j� existe na tabela */
int verificaMat(TabHash *tab[], TabHash *novoElem, int matricula, int tam){

    TabHash *aux=NULL;

    /* Roda um la�o em toda a tabela */
    for(int i=0; i<tam; i++){
        aux = tab[i]; // 'aux' recebe nova posi��o de tabela toda vez que o la�o gira

        /* Enquanto 'aux' for diferente de nulo percorrer� a lista encadeada */
        while(aux != NULL){

            /* Compara a matr�cula da tabela com matr�cula inserida agora */
            if(aux->matricula == matricula){
                printf("\nAluno j� cadastrado...\n");
                printf("Deseja substituir informa��es?\n\n<0> - SIM\n<1> - N�O\n\n: ");
                int opc=0;
                scanf("%d", &opc);

                if(opc == 0){
                    system("cls");
                    insereInfo(aux, matricula);
                    free(novoElem);
                    system("cls");
                    printf("Informa��es atualizadas!\n\n");
                }else{
                    system("cls");
                    printf("Informa��es mantidas!\n\n");
                }
                return 0;
            }
            aux = aux->prox;
        }
    }

    return 1;
}

/* Verifi��o de posi��o livre */
void verificaPos(TabHash *tab[], TabHash *novoElem, int posicao, int mat, int tam){

    /* Se a determinada posi��o estiver vazia, insere o elemento na posi��o da tabela*/
    if(tab[posicao] == NULL){
        novoElem->prox = NULL/*tab[posicao]*/; // Pr�ximo do elemento aponta para nulo
        tab[posicao] = novoElem; // Posi��o N da tabela recebe elemento
        insereInfo(novoElem, mat); // Insere informa��es no elemento
        system("cls");
        printf("Aluno inserido!\n\n");
    }else{ /* Se estiver ocupada ter� que encadear o elemento em outro da tabela */
        system("cls");
        printf("\nPosi��o hash ocupada...\n\n");

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

/* Insere informa��es, a serem digitadas, no novo elemento criado */
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

/* Chama fun��es para inserir elemento na tabela */
void inserir(TabHash *tab[], int tam){
    system("cls");

    int matricula;
    TabHash *novoElem = (TabHash*)malloc(sizeof(TabHash)); // Criando e alocando mem�ria para um novo elemento
    novoElem->prox = NULL;

    printf("Inserir aluno...\n\n");
    printf("Matr�cula: ");
    scanf("%d", &matricula);

    int posicao = hashNum(matricula, tam); // Faz o calculo hash e recebe o resultado do calculo
    int contr = verificaMat(tab, novoElem, matricula, tam); // Verifica se matr�cula inserida j� existe na tabela
    if(contr == 1)verificaPos(tab, novoElem, posicao, matricula, tam); // Verifica a posi�ao na tablela para saber se est� livre
}

/* Remove elementos da tabela */
void remover(TabHash *tab[], int tam){
    system("cls");

    int num, posicao, enc=0;
    TabHash *aux=NULL; // Cria ponteiro auxuliar

    /* Verifica se n�o existe elementos na tabela */
    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("N�o existe alunos cadastrados!\n\n");
    }else{
        printf("\nDigite a matr�cula que deseja remover: ");
        scanf("%d", &num);

        posicao = hashNum(num, tam); // posi��o recebe calculo hash da matricula inserida

        system("cls");

        /* Verifica se a posi��o cont�m elemento */
        if(tab[posicao] != NULL){
            if(tab[posicao]->matricula == num){ // Se a matr�cula inserida for igual a digitada
                aux = tab[posicao];                 // 'aux' recebe o elemento
                tab[posicao] = tab[posicao]->prox;  // Elemento recebe o seu pr�ximo
                free(aux);                          // 'aux' � liberada da mem�ria
                printf("Aluno removido!\n\n");
            } else { // Se a posi��o n�o cont�m o elemento
                aux = tab[posicao]->prox; // 'aux' recebe o pr�ximo elemento na lista encadeada
                TabHash *ant = tab[posicao]; // Criado ponteiro 'ant' que recebe elemento da tabela

                /* Enquanto aux != de nulo e matr�cula digitada != de matr�cula na lista encadeada */
                while(aux != NULL && aux->matricula != num){
                    ant = aux;       // 'ant' recebe pr�xima posi��o na lista encadeada
                    aux = aux->prox; // 'aux' recebe pr�xima posi��o na lista encadeada (uma posi��o a frente de 'ant')
                }

                /* Se aux != de nulo */
                if(aux != NULL){
                    ant->prox = aux->prox; // O pr�ximo de 'ant' aponta para o pr�xima de 'aux' (que pode ser nulo ou conter elemento encadeado)
                    free(aux); // Libera mem�ria de 'aux'
                    printf("Aluno removido!\n\n");
                } else { // Se a 'aux' for nulo, n�o foi encontrada a matr�cula digitada
                    printf("Matr�cula n�o encontrada!\n\n");
                }
            }
        }else{ // Se a posi��o calculada em hash n�o cont�m elemento, matricula est� incorreta ou n�o existe
            printf("Matr�cula n�o encontrada!\n\n");
        }
    }
}

/* Visualizar aluno pelo n�mero de matr�cula */
void visualizarPorMat(TabHash *tab[], int tam){
    system("cls");

    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("N�o existe alunos cadastrados!\n\n");
    }else{
        int mat, cont=0;

        printf("Digite o n�mero de matr�cula: ");
        scanf("%d", &mat);

        int posicao = hashNum(mat, tam);
        cont++;

        TabHash *aux=NULL; // Craiando ponteiro aux

        /* Se a posi��o calculada por hash for diferente de nulo */
        if(tab[posicao] != NULL){
            aux = tab[posicao]; // Ponteiro aux recebe a posi��o da tabela
            cont++; // Incrementa contador de passos

            /* Enquando aux for diferente de nulo, o la�o gira */
            while(aux != NULL){
                /* Se a matr�cula digitada for igual ao que est� na tabela, imprime
                   as informa��es e incrementa 'cont'*/
                if(aux->matricula == mat){
                    cont++;
                    system("cls");
                    printf("\nID \t%-10s\t%-20s\tEmail\n", "Nome", "Sobrenome");
                    printf("%d\t%-10s\t%-20s\t%s\n", aux->matricula, aux->nome, aux->sobrenome, aux->email);
                    printf("\nQtd passos at� ser encontrada: %d\n\n", cont);
                    system("pause");
                    system("cls");
                }
                aux = aux->prox; // 'aux' recebe o pr�ximo elemento
            }
        } else {
            system("cls");
            printf("Matr�cula n�o encontrada!\n\n");
        }
    }
}

/* Visualizar todos os alinos */
void visualizarTodos(TabHash *tab[], int tam){
    system("cls");

    if(verifTab(tab, tam) == 1){
        system("cls");
        printf("N�o existe alunos cadastrados!\n\n");
    }else{

        TabHash *aux=NULL; // ponteiro 'aux' recebe nulo

        printf("\nID \t%-10s\t%-20s\tEmail\n", "Nome", "Sobrenome");

        /* La�o girar� at� 'i' ser menor que tamanho da tabela */
        for(int i=0; i<tam; i++){
            aux = tab[i]; // 'aux' recebe posi��o da tabela

            /* Enquanto aux for diferente de nulo, la�o gira e aponta para o pr�ximo encadeado */
            while(aux != NULL){
                printf("%d\t%-10s\t%-20s\t%s\n", aux->matricula, aux->nome, aux->sobrenome, aux->email);
                aux = aux->prox; // 'aux' recebe, se existir, o pr�ximo encadeado
            }
        }

        printf("\n");
        system("pause");
        system("cls");
    }
}

/* Verifica se cont�m elementos na tabela */
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

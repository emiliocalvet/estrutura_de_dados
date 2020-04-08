#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 32//O endereco base possui 5bits.

typedef struct no
{
    int chave;
    int info;
    struct no *prox;
} No;

typedef No *Hash[M];
int buffer_bin[8];

int *dec_to_bin(int dec);
int bin_to_dec(int *bin);
int hash(int chave, int tam);
int inserir(Hash tabela, int chave, int info);
No *buscar(Hash tabela, int chave);
int remover(Hash tabela, int chave);

int main()
{
    int info = 0;
    int chave = 0;
    int escolha_menu = 0;

    Hash tabela;
    No *aux = NULL;

    //Inicializando vetor de ponteiros para No com endereços vazios.
    for (int i = 0; i < M; i++)
        tabela[i] = NULL;

    while (escolha_menu != -1)
    {
        system("clear");

        printf(" ________________________________ \n");
        printf("|######### HASH-EXTERNA #########|\n");
        printf("|                                |\n");
        printf("|          [1] INSERIR           |\n");
        printf("|          [2] BUSCAR            |\n");
        printf("|          [3] REMOVER           |\n");
        printf("|          [4] SAIR              |\n");
        printf("|________________________________|\n");
        printf("\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:;
            int pos;
            printf("\nDigite o numero deseja guardar: ");
            scanf("%d", &info);
            setbuf(stdin, NULL);
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            setbuf(stdin, NULL);
            pos = inserir(tabela, chave, info);
            if (pos != -1)
                printf("\nInserido na posicao %d!", pos);
            else
                printf("\nErro. Tente uma chave diferente!");
            printf("\nPressione [ENTER] para retornar ao menu.");
            setbuf(stdin, NULL);
            getchar();
            break;

        case 2:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            aux = buscar(tabela, chave);
            if (aux != NULL)
            {
                printf("\nNumero guardado: %d", aux->info);
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 3:
            printf("\nDigite o numero da chave de acesso: ");
            scanf("%d", &chave);
            if (remover(tabela, chave))
            {
                printf("Removido com sucesso!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            else
            {
                printf("Nao encontrado!");
                printf("\nPressione [ENTER] para retornar ao menu.");
                setbuf(stdin, NULL);
                getchar();
            }
            break;

        case 4:
            escolha_menu = -1;
            printf("Bye!\n\n");
            break;

        default:
            printf("\nOpção incorreta, pressione [ENTER] e tente novamente!");
            escolha_menu = 0;
            setbuf(stdin, NULL);
            getchar();
            break;
        }
    }
    return 0;
}

//Transforma de decimal para binário.
int *dec_to_bin(int dec)
{
    for (int i = 9; i >= 0; i--)
    {
        if (dec % 2 == 0)
            buffer_bin[i] = 0;
        else
            buffer_bin[i] = 1;
        dec = dec / 2;
    }
    return buffer_bin;
}

//Transforma de binário para decimal.
int bin_to_dec(int *bin)
{
    int dec = 0;

    for (int i = 4; i >= 0; i--)
    {
        dec = dec + (bin[i] * pow(2, (4 - i)));
    }

    return dec;
}

//Método da dobra.
int hash(int chave, int tam)
{
    int *chave_bin = dec_to_bin(chave);
    int pos_bin[4];

    for (int i = 0; i < 5; i++)
    {
        //Operação OUEX.
        pos_bin[i] = chave_bin[i] ^ chave_bin[i + 5];
        //Operação OU
        //pos_bin[i] = chave_bin[i] | chave_bin[i + 5];
        //Operação E.
        //pos_bin[i] = chave_bin[i] & chave_bin[i + 5];
    }
    int posicao = bin_to_dec(pos_bin);
    return posicao;
}

int inserir(Hash tabela, int chave, int info)
{
    No *aux = buscar(tabela, chave);
    int h = hash(chave, M);

    //Verifica chave repetida.
    if (aux == NULL)
    {
        //Insere nó no inicio da lista de colisão externa.
        aux = (No *)malloc(sizeof(No));
        aux->chave = chave;
        aux->info = info;
        aux->prox = tabela[h];
        tabela[h] = aux;
        return h;
    }
    return -1;
}

No *buscar(Hash tabela, int chave)
{
    int h = hash(chave, M);
    No *aux = tabela[h];

    //Em caso de colisão, procura nó que corresponde a chave na lista encadeada.
    while (aux != NULL)
    {
        if (aux->chave == chave)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

int remover(Hash tabela, int chave)
{
    No *aux = buscar(tabela, chave);
    if (aux != NULL)
    {
        free(aux);
        aux = NULL;
        return 1;
    }
    return 0;
}
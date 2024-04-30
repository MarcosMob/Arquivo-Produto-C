#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto
{
    char nome[200];
    char descricao[500];
    float preco;
    int id;
    char removido;
    struct produto *prox;//struct para mostrar o proximo item
} contato;

int recuperar();
int cadastroProduto();
int listar();
int consultar();
int excluir();
int salvar();

contato *inicio, *lista, *aux;

int main()
{
    int opcao;

    recuperar();

    do
    {
        printf("\n");
        printf("-------------------- Opcoes --------------------\n");
        printf("1-) Cadastrar novo produto \n\n");
        printf("2-) Exibir todos os produtos \n\n");
        printf("3-) Consultar produto \n\n");
        printf("4-) Deletar produto \n\n");
        printf("5-) Sair \n\n");
        printf("------------------------------------------------\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // cadastrar
            cadastroProduto();
            break;

        case 2:
            // exibir todos os produtos
            listar();
            break;

        case 3:
            // consultar produto pelo nome
            consultar();
            break;

        case 4:
            // deletar produto
            excluir();
            break;

        case 5:
            //sair do programa
            printf("Obrigado por sua visita!\n");
            break;

        default:
            printf("Essa opcao nao existe!\n");
            break;
        }
    } while (opcao != 5);
    return 0;
}

// recuperar informacoes do arquivo e salvar na lista global
int recuperar()
{
    FILE *arquivo;
    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL)
    {
        // printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    while (!feof(arquivo))
    {   //ORDENANDO OS NOMES
        
        contato *novo;
        novo = (contato *)malloc(sizeof(contato));

        fscanf(arquivo, "%s %s %f %d %c", novo->nome, novo->descricao, &novo->preco, &novo->id, &novo->removido);

        if (inicio == NULL)
        {
            inicio = novo;
            novo->prox = NULL;
        }
        else
        {
            if (strcmp(novo->nome, inicio->nome) < 0)
            {   //comparando os nomes e ordena por ordem alfabética
                novo->prox = inicio;
                inicio = novo;
            }
            else
            {   //comparando os nomes e ordenando o restante da lista
                lista = inicio;
                while (lista->prox != NULL && strcmp(novo->nome, lista->prox->nome) > 0)
                {
                    lista = lista->prox;
                }
                novo->prox = lista->prox;
                lista->prox = novo;
            }
        }
    }
    fclose(arquivo);
    // remover primeiro item
    inicio = inicio->prox;
    listar();
}

// cadastro na lista global em ordem alfabetica pelo nome
int cadastroProduto()
{
    contato *novo;
    novo = (contato *)malloc(sizeof(contato));

    printf("Digite o nome do produto: ");
    scanf("%s", novo->nome);

    printf("Digite a descricao do produto: ");
    scanf("%s", novo->descricao);

    printf("Digite o preco do produto: ");
    scanf("%f", &novo->preco);

    printf("Digite o id do produto: ");
    scanf("%d", &novo->id);

    novo->removido = '0';
    //ordena e incrementa na lista
    if (inicio == NULL)
    {
        inicio = novo;
        novo->prox = NULL;
    }
    else
    {
        if (strcmp(novo->nome, inicio->nome) < 0)
        {
            novo->prox = inicio;
            inicio = novo;
        }
        else
        {
            lista = inicio;
            while (lista->prox != NULL && strcmp(novo->nome, lista->prox->nome) > 0)
            {
                lista = lista->prox;
            }
            novo->prox = lista->prox;
            lista->prox = novo;
        }
    }
    salvar();
    return 0;
}

// salvar lista global no arquivo
int salvar()
{
    FILE *arquivo;
    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    aux = inicio;
    while (aux != NULL)
    {
        fprintf(arquivo, "%s %s %f %d %c\n", aux->nome, aux->descricao, aux->preco, aux->id, aux->removido);
        aux = aux->prox;
    }
    fclose(arquivo);
}

// listar lista global
int listar()
{
    aux = inicio;
    while (aux != NULL)
    {
        if (aux->removido == '0')
        {
            printf("Nome: %s\n", aux->nome);
            printf("Descricao: %s\n", aux->descricao);
            printf("Preco: %.2fR$\n", aux->preco);
            printf("Id: %d\n", aux->id);
            printf("Removido: %c\n", aux->removido);
            printf("\n");
        }
        aux = aux->prox;
    }
}

// consultar pelo nome
int consultar()
{
    char nome[30];
    printf("Digite o nome do produto: ");
    scanf("%s", nome);

    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome) == 0)
        {
            printf("Nome: %s\n", aux->nome);
            printf("Descricao: %s\n", aux->descricao);
            printf("Preco: %.2fR$\n", aux->preco);
            printf("Id: %d\n", aux->id);
            printf("Removido: %c\n", aux->removido);
            printf("\n");
        }
        aux = aux->prox;
    }
}

int excluir()
{
    char nome[30];
    printf("Digite o nome do produto: ");
    scanf("%s", nome);

    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome) == 0)
        {
            aux->removido = '1';
        }
        aux = aux->prox;
    }
    salvar();
    printf("Produto removido com sucesso!\n");
}
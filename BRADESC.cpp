#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_MAX_DE_SENHA 6
#define TAMANH0_MAX_DE_LISTA 100

// Responsavel pelos dados cadastrados na fila
typedef struct senhaCliente
{
    char nome_cliente_da_fila[TAMANHO_MAX_DE_SENHA][50];
    int idade_cliente_da_fila[TAMANHO_MAX_DE_SENHA];
    char cpf_cliente_da_fila[TAMANHO_MAX_DE_SENHA][50];
    int tras, frente, senha_numero;
    char senha_gerada[TAMANHO_MAX_DE_SENHA][20];

} senhaDocliente;

// Responsavel por guardar os dados das contas registradas
typedef struct Dadosbancarios
{
    char cpf_clinete[TAMANH0_MAX_DE_LISTA][50];
    char nome_cliente[TAMANH0_MAX_DE_LISTA][50];
    int idade_cliente[TAMANH0_MAX_DE_LISTA];
    float saldo_cliente[TAMANH0_MAX_DE_LISTA];
    int tamanho;

} Dados_do_cliente;

// funcoes responsaveis pelos menus
int menu();
int menu_de_controle_de_senhas();
int menu_de_atendimento();
int adicionar_encerrar();
int adicionar_transferir();
int gerar_outra_senha();

// funcoes responsaveis pelo geranciamento da fila
void inicializar(senhaDocliente *senhaC, Dados_do_cliente *dadosC);
bool filaCheia(senhaDocliente *senhaC);
bool filaVazia(senhaDocliente *senhaC);

void gerar_senha_para_cliente(senhaDocliente *senha, char nomeIndicado[50], char cpfIndicado[50], int idadeIndicada);
void consultar_primeiro_cliente(senhaDocliente senha);
void retirar_primeiro_cliente(senhaDocliente *senha);
void listar_clientes(senhaDocliente senha);
bool verificar_senha(senhaDocliente senha);
void controle_de_senha(senhaDocliente *senhaC);

// funcoes responsaveis pelos atendimentos: criacao de conta, encerramento de conta, transferencias, saldo.
bool lista_cheia(Dados_do_cliente dadosC);
bool lista_vazia(Dados_do_cliente dadosC);
void abertura_de_contas(Dados_do_cliente *dadosC, char nome_indicado[50], int idade_indicada, char cpf_indicado[50]);
void encerrar_conta(Dados_do_cliente *dadosC, char cpfIndicado[50]);
void registro_e_encerramento(Dados_do_cliente *dadosC);
void adicionar_saldo(Dados_do_cliente *dadosC, char cpfIndicado[50]);
void realizar_transferencia(Dados_do_cliente *dadosC);
void transferir_e_adicionar(Dados_do_cliente *dadosC);
void mostrar_saldo(char cpfIndicado[50]);
void atendimento_dos_clientes(senhaDocliente senha, Dados_do_cliente dadosC);

// funcoes responsaveis pelo gerenciamento do arquivo
void salvar_em_arquivo(Dados_do_cliente *dadosC);
void apagar_do_arquivo(Dados_do_cliente *dadosC, char cpfIndicado[50]);
void carregar_de_arquivo(Dados_do_cliente *dadosC);

int main()
{
    senhaCliente senhaC;
    Dados_do_cliente dadosC;
    int escolha, adicionar = 0, idade;
    char cpf[50], nome[50];

    inicializar(&senhaC, &dadosC);
    carregar_de_arquivo(&dadosC);

    do
    {
        system("cls");
        escolha = menu();

        switch (escolha)
        {
        case 1:
            system("cls");
            if (filaCheia(&senhaC))
            {
                printf("ERROR! \n");
                printf("Sem senhas disponiveis \n");
                system("pause");
            }
            else
            {
                adicionar = 1;
                while (adicionar == 1)
                {
                    system("cls");
                    if (filaCheia(&senhaC))
                    {
                        adicionar = 0;
                        printf("ERROR! \n");
                        printf("Sem senhas disponiveis \n");
                        system("pause");
                        break;
                    }

                    printf("Digite o nome do cliente: \n");
                    fflush(stdin);
                    gets(nome);

                    printf("Digite o CPF do cliente: \n ");
                    fflush(stdin);
                    gets(cpf);

                    printf("Digite a idade do cliente \n");
                    fflush(stdin);
                    scanf("%d", &idade);

                    gerar_senha_para_cliente(&senhaC, nome, cpf, idade);

                    system("cls");

                    adicionar = gerar_outra_senha();
                }
            }

            break;
        case 2:
            system("cls");
            if (filaVazia(&senhaC))
            {
                printf("Nao ha clientes na fila...\n");
                system("pause");
            }
            else
            {
                atendimento_dos_clientes(senhaC, dadosC);
            }

            break;
        case 3:
            system("cls");
            controle_de_senha(&senhaC);
            break;
        case 4:
            system("cls");
            printf("Saindo...\n");
            break;

        default:
            system("cls");
            printf("Opcao invalida, por favor selecione uma das opcoes apresentadas...\n");
            system("pause");
            break;
        }

    } while (escolha != 4);

    return 0;
}

//-----------------------------------------------------------------------------
// funcoes responsaveis pelos menus
int menu()
{
    int opcao;
    printf("|-----SISTEMA DE BANCO-----|\n");
    printf("\n");
    printf("[1] - Gerar senha \n");
    printf("[2] - Atendimento \n");
    printf("[3] - Controle de senha \n");
    printf("[4] - Sair \n");
    scanf("%i", &opcao);

    return opcao;
}

int menu_de_controle_de_senhas()
{
    int op;

    printf("|-----CONTROLE DE SENHA-----|\n");
    printf("\n");
    printf("\n [1] - Consultar primeiro da fila \n");
    printf("\n [2] - Retirar primeiro cliente da fila \n");
    printf("\n [3] - Listar todos os clientes da fila \n");
    printf("\n [4] - Retornar para o menu principal \n");
    scanf("%i", &op);

    return op;
}

int menu_de_atendimento()
{
    int op;
    printf("|-----MENU DE ATENDIMENTO-----|\n");
    printf("\n");
    printf("[1] - Abertura / Encerramento de conta \n");
    printf("[2] - Transferencias \n");
    printf("[3] - Saldo \n");
    printf("[4] - Retornar para o menu principal \n");
    printf("Escolha uma opcao: \n");
    scanf("%i", &op);

    return op;
}

int adicionar_transferir()
{
    int escolha;
    printf(" [1] - Transferir \n [2] - Adicionar saldo \n [3] - Voltar \n");
    scanf("%i", &escolha);

    return escolha;
}

int adicionar_encerrar()
{
    int escolha;
    printf(" [1] - Abertura de contas \n [2] - Encerramento de contas \n [3] - Voltar \n");
    scanf("%i", &escolha);

    return escolha;
}

int gerar_outra_senha()
{
    int adicionar;
    printf("Deseja adicionar outro cliente na fila? [1] = sim [0] = nao \n");
    scanf("%i", &adicionar);

    if (adicionar != 1 && adicionar != 0)
    {
        system("cls");
        printf("OPÇÃO INVALIDA! Tente novamente.\n");
        return gerar_outra_senha();
    }

    return adicionar;
}

//-----------------------------------------------------------------------------
// funcoes responsaveis pelo geranciamento da fila

void inicializar(senhaDocliente *senhaC, Dados_do_cliente *dadosC)
{
    senhaC->tras = -1;
    senhaC->frente = -1;
    senhaC->senha_numero = 0;
    dadosC->tamanho = 0;
}

bool filaCheia(senhaDocliente *senha)
{
    bool fila_cheia = false;
    if (senha->tras == TAMANHO_MAX_DE_SENHA - 1)
    {
        fila_cheia = true;
    }
    return fila_cheia;
}
bool filaVazia(senhaDocliente *senha)
{
    bool fila_vazia = false;
    if (senha->frente == -1 && senha->tras == -1)
    {
        fila_vazia = true;
    }

    return fila_vazia;
}

void gerar_senha_para_cliente(senhaDocliente *senha, char nomeIndicado[50], char cpfIndicado[50], int idadeIndicada)
{
    char string_numero[20];

    if (filaVazia(senha))
    {
        senha->frente = 0;
    }
    senha->tras++;
    strcpy(senha->nome_cliente_da_fila[senha->tras], nomeIndicado);
    strcpy(senha->cpf_cliente_da_fila[senha->tras], cpfIndicado);
    senha->idade_cliente_da_fila[senha->tras] = idadeIndicada;

    senha->senha_numero++;
    sprintf(string_numero, "%d", senha->senha_numero);
    strcpy(senha->senha_gerada[senha->tras], "N0");
    strcat(senha->senha_gerada[senha->tras], string_numero);

    system("cls");
    printf("DADOS DO CLIENTE SALVOS NA FILA: \n");
    printf("NOME: %s \n", nomeIndicado);
    printf("CPF: %s \n", cpfIndicado);
    printf("IDADE: %i \n", idadeIndicada);
    printf("SENHA DO CLIENTE: %s \n", senha->senha_gerada[senha->tras]);
    printf("\n");
    system("pause");
}

void consultar_primeiro_cliente(senhaDocliente senha)
{
    system("cls");
    if (filaVazia(&senha))
    {
        printf("Nao ha clientes na fila! \n");
        system("pause");
        return;
    }
    else
    {
        printf("Primeiro cliente da fila:\n");
        printf("Nome: %s\n", senha.nome_cliente_da_fila[senha.frente]);
        printf("CPF: %s\n", senha.cpf_cliente_da_fila[senha.frente]);
        printf("Idade: %d\n", senha.idade_cliente_da_fila[senha.frente]);
        printf("Senha do cliente: %s \n", senha.senha_gerada[senha.frente]);
        printf("\n");
        system("pause");
    }
}

void retirar_primeiro_cliente(senhaDocliente *senha)
{
    system("cls");
    if (filaVazia(senha))
    {
        printf("Nao ha clientes na fila! \n");
        system("pause");
        return;
    }
    if (senha->frente == senha->tras)
    {
        senha->frente = -1;
        senha->tras = -1;
        senha->senha_numero = 0;
    }
    else
    {
        for (int i = senha->frente; i < senha->tras; i++)
        {
            strcpy(senha->nome_cliente_da_fila[i], senha->nome_cliente_da_fila[i + 1]);
            strcpy(senha->cpf_cliente_da_fila[i], senha->cpf_cliente_da_fila[i + 1]);
            strcpy(senha->senha_gerada[i], senha->senha_gerada[i + 1]);
            senha->idade_cliente_da_fila[i] = senha->idade_cliente_da_fila[i + 1];
        }
        senha->tras--;
        printf("Primeiro cliente da fila foi removido...\n");
        system("pause");
    }
}

void listar_clientes(senhaDocliente senha)
{
    if (filaVazia(&senha))
    {
        printf("Nao ha clientes na fila! \n");
        system("pause");
        return;
    }
    else
    {
        printf("Lista de clientes na fila: \n");
        printf("\n");
        for (int i = senha.frente; i <= senha.tras; i++)
        {
            printf("Nome: %s \n", senha.nome_cliente_da_fila[i]);
            printf("CPF: %s \n", senha.cpf_cliente_da_fila[i]);
            printf("idade: %i \n", senha.idade_cliente_da_fila[i]);
            printf("Senha do cliente : %s \n", senha.senha_gerada[i]);
            printf("\n");
            printf("---------- \n");
        }
    }
    system("pause");
}

bool verificar_senha(senhaDocliente senha)
{
    bool senha_igual;
    char senhaIndicada[50];
    senha_igual = false;

    printf("Informe a senha do cliente para seguir com o atendimento: \n");
    fflush(stdin);
    gets(senhaIndicada);

    if (strcmp(senha.senha_gerada[senha.frente], senhaIndicada) == 0)
    {
        senha_igual = true;
    }
    else
    {
        senha_igual = false;
    }
    return senha_igual;
}

void controle_de_senha(senhaDocliente *senhaC)
{
    int op;

    do
    {
        system("cls");
        op = menu_de_controle_de_senhas();
        switch (op)
        {
        case 1:
            system("cls");
            consultar_primeiro_cliente(*senhaC);

            break;
        case 2:
            system("cls");
            retirar_primeiro_cliente(senhaC);

            break;
        case 3:
            system("cls");
            listar_clientes(*senhaC);
            break;
        case 4:
            system("cls");
            printf("retornado...\n");
            system("pause");
            return;
            break;

        default:
            system("cls");
            printf("Opcao invalida, por favor selecione uma das opcoes apresentadas...\n");
            system("pause");
            break;
        }

    } while (op != 4);
}

//-----------------------------------------------------------------------------
// funcoes responsaveis pelos atendimentos: criacao de conta, encerramento de conta, transferencias, saldo.

bool lista_cheia(Dados_do_cliente dadosC)
{
    return dadosC.tamanho == TAMANH0_MAX_DE_LISTA;
}

bool lista_vazia(Dados_do_cliente dadosC)
{
    return dadosC.tamanho == 0;
}

void abertura_de_contas(Dados_do_cliente *dadosC, char nome_indicado[50], int idade_indicada, char cpf_indicado[50])
{
    int i;
    if (!lista_cheia(*dadosC))
    {
        for (i = 0; i < dadosC->tamanho; i++)
        {
            if (strcmp(cpf_indicado, dadosC->cpf_clinete[i]) == 0)
            {
                printf("Ja existe uma conta cadastrada com este cpf...\n");
                system("pause");
                return;
            }
        }
        strcpy(dadosC->cpf_clinete[dadosC->tamanho], cpf_indicado);
        strcpy(dadosC->nome_cliente[dadosC->tamanho], nome_indicado);
        dadosC->idade_cliente[dadosC->tamanho] = idade_indicada;
        dadosC->saldo_cliente[dadosC->tamanho] = 0;
        dadosC->tamanho++;
        salvar_em_arquivo(dadosC);

        printf("Conta cadastrada com sucesso! \n");
        system("pause");
    }
    else
    {
        printf("Nao e possivel registrar novas contas. ");
    }
}

void encerrar_conta(Dados_do_cliente *dadosC, char cpfIndicado[50])
{
    int i, j;
    bool conta_encontrada = false;

    for (i = 0; i < dadosC->tamanho; i++)
    {
        if (strcmp(dadosC->cpf_clinete[i], cpfIndicado) == 0)
        {
            conta_encontrada = true;
            for (j = i; j < dadosC->tamanho - 1; j++)
            {
                strcpy(dadosC->cpf_clinete[j], dadosC->cpf_clinete[j + 1]);
                strcpy(dadosC->nome_cliente[j], dadosC->nome_cliente[j + 1]);
                dadosC->idade_cliente[j] = dadosC->idade_cliente[j + 1];
                dadosC->saldo_cliente[j] = dadosC->saldo_cliente[j + 1];
            }
            dadosC->tamanho--;
            printf("A conta registrada no CPF: %s foi encerrada.\n", cpfIndicado);
            apagar_do_arquivo(dadosC, cpfIndicado);
            break; 
        }
    }

    if (!conta_encontrada)
    {
        printf("Conta nao encontrada.\n");
    }
    system("pause");
}

bool conta_existente(Dados_do_cliente dadosC, char cpfIndicado[50])
{
    bool conta_ja_existente = false;

    for (int i = 0; i < dadosC.tamanho; i++)
    {
        if (strcmp(dadosC.cpf_clinete[i], cpfIndicado) == 0)
            conta_ja_existente = true;
        break;
    }
    return conta_ja_existente;
}

void registro_e_encerramento(Dados_do_cliente *dadosC)
{
    char cpf[50], nome[50];
    int op, idade;

    do
    {
        system("cls");
        op = adicionar_encerrar();

        switch (op)
        {
        case 1:
            system("cls");
            printf("|-----ABERTURA DE CONTA-----| \n");

            printf("Informe o CPF do cliente: \n");
            fflush(stdin);
            gets(cpf);

            printf("Informe o nome do cliente: \n");
            fflush(stdin);
            gets(nome);

            printf("informe a idade do cliente: \n");
            scanf("%i", &idade);

            if (conta_existente(*dadosC, cpf))
            {
                printf("Ja existe uma conta cadastrada neste cpf...\n");
                system("pause");
            }
            else
            {
                abertura_de_contas(dadosC, nome, idade, cpf);
            }

            break;
        case 2:
            system("cls");
            if (!lista_vazia(*dadosC))
            {

                printf("Digite o CPF no qual deseja encerrar a conta: \n");
                fflush(stdin);
                gets(cpf);

                encerrar_conta(dadosC, cpf);
            }
            else
            {
                printf("Sem contas cadastradas atualmente! \n");
                system("pause");
            }
            break;
        case 3:
            printf("retornado...\n");
            system("pause");
            break;

        default:
            system("cls");
            printf("Opcao invalida, por favor selecione uma das opcoes apresentadas... \n");
            system("pause");
            break;
        }

    } while (op != 3);
}

void adicionar_saldo(Dados_do_cliente *dadosC, char cpfIndicado[50])
{
    int i;
    float valor;
    bool conta_encontrada = false;

    if (lista_vazia(*dadosC))
    {
        printf("Atualmente nao ha contas registradas...\n");
        system("pause");
    }
    else
    {

        for (i = 0; i < dadosC->tamanho; i++)
        {
            if (strcmp(dadosC->cpf_clinete[i], cpfIndicado) == 0)
            {
                conta_encontrada = true;
                printf("Digite o valor que deseja adicionar: \n");
                scanf("%f", &valor);
                dadosC->saldo_cliente[i] = dadosC->saldo_cliente[i] + valor;

                printf("Saldo de %s foi atualizado! \n", dadosC->nome_cliente[i]);
                printf("Saldo atual: %.2f \n", dadosC->saldo_cliente[i]);
                salvar_em_arquivo(dadosC);
                break;
            }
        }
        if (!conta_encontrada)
        {
            printf("Conta nao encontrada!");
        }
        system("pause");
    }
}

void realizar_transferencia(Dados_do_cliente *dadosC)
{
    char cpf_origem[50], cpf_destino[50];
    int i;
    float valor;
    bool conta_de_origem = false;
    bool conta_de_destino = false;

    if (lista_vazia(*dadosC))
    {
        printf("Atualmente nao ha contas registradas...\n");
    }
    else
    {
        printf("Digite o CPF de origem: \n");
        fflush(stdin);
        gets(cpf_origem);

        printf("Digite o CPF do destinatario: \n");
        fflush(stdin);
        gets(cpf_destino);

        for (i = 0; i < dadosC->tamanho; i++)
        {
            if (strcmp(dadosC->cpf_clinete[i], cpf_origem) == 0)
            {
                conta_de_origem = true;

                printf("Informe o valor que deseja transferir: \n");
                scanf("%f", &valor);

                if (dadosC->saldo_cliente[i] < valor)
                {
                    printf("Saldo insuficiente para realizar a transferencia \n");
                    system("pause");
                    return; 
                }

                dadosC->saldo_cliente[i] = dadosC->saldo_cliente[i] - valor;
                break;
            }
        }

        for (i = 0; i < dadosC->tamanho; i++)
        {
            if (strcmp(dadosC->cpf_clinete[i], cpf_destino) == 0)
            {
                conta_de_destino = true;
                dadosC->saldo_cliente[i] = dadosC->saldo_cliente[i] + valor;
                break;
            }
        }

        if (!conta_de_origem || !conta_de_destino)
        {
            printf("CPF de origem ou de destino não encontrado...\n");

            for (i = 0; i < dadosC->tamanho; i++)
            {
                if (strcmp(dadosC->cpf_clinete[i], cpf_origem) == 0)
                {
                    dadosC->saldo_cliente[i] = dadosC->saldo_cliente[i] + valor;
                    break;
                }
            }
        }
        else
        {
            printf("Transferencia realizada com sucesso! \n");
            salvar_em_arquivo(dadosC);
        }
    }
    system("pause");
}

void mostrar_saldo(char cpfIndicado[50])
{

    FILE *arquivo;
    arquivo = fopen("Contas_clientes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    bool conta_encontrada = false;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, cpfIndicado) != NULL)
        {
            conta_encontrada = true;
            printf("%s", linha); 

            
            for (int i = 0; i < 3; i++)
            {
                fgets(linha, sizeof(linha), arquivo);
                printf("%s", linha);
            }

            break;
        }
    }

    if (!conta_encontrada)
    {
        printf("Nao foi encontrada uma conta registrada com esse CPF.\n");
    }

    fclose(arquivo); 
    system("pause");
}

void transferir_e_adicionar(Dados_do_cliente *dadosC)
{
    int op;
    char cpf[50];
    do
    {
        system("cls");
        op = adicionar_transferir();
        switch (op)
        {
        case 1:
            system("cls");
            realizar_transferencia(dadosC);
            break;
        case 2:
            system("cls");
            printf("Digite o CPF do cliente que deseja adicionar saldo: \n");
            fflush(stdin);
            gets(cpf);
            adicionar_saldo(dadosC, cpf);
            break;
        case 3:
            system("cls");
            printf("retornado...\n");
            system("pause");
            break;

        default:
            system("cls");
            printf("Opcao invalida, por favor selecione uma das opcoes apresentadas...\n");
            system("pause");
            break;
        }
    } while (op != 3);
}

void atendimento_dos_clientes(senhaDocliente senha, Dados_do_cliente dadosC)
{
    int op;
    char cpf[50];

    if (!verificar_senha(senha))
    {
        printf("Senha incorreta ou nao e a primeira da fila...\n");
        system("pause");
    }
    else
    {
        do
        {
            system("cls");
            op = menu_de_atendimento();

            switch (op)
            {
            case 1:
                system("cls");
                registro_e_encerramento(&dadosC);
                break;
            case 2:
                system("cls");
                transferir_e_adicionar(&dadosC);
                break;
            case 3:
                system("cls");
                if (!lista_vazia(dadosC))
                {
                    printf("Digite o CPF do cliente que deseja saber o saldo: \n");
                    fflush(stdin);
                    gets(cpf);
                    system("cls");

                    mostrar_saldo(cpf);
                }
                else
                {
                    printf("Sem contas cadastradas atualmente! \n");
                    system("pause");
                }
                break;
            case 4:
                system("cls");
                printf("retornado...\n");
                system("pause");
                break;

            default:
                system("cls");
                printf("Opcao invalida, por favor selecione uma das opcoes apresentadas... \n");
                system("pause");
                break;
            }
        } while (op != 4);
    }
}

//-----------------------------------------------------------------------------
// funcoes responsaveis pelo gerenciamento do arquivo

void salvar_em_arquivo(Dados_do_cliente *dadosC)
{
    FILE *arquivo;
    arquivo = fopen("Contas_clientes.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < dadosC->tamanho; i++)
    {
        fprintf(arquivo, "CPF: %s \n", dadosC->cpf_clinete[i]);
        fprintf(arquivo, "NOME: %s \n", dadosC->nome_cliente[i]);
        fprintf(arquivo, "IDADE: %i \n", dadosC->idade_cliente[i]);
        fprintf(arquivo, "SALDO: %.2f \n", dadosC->saldo_cliente[i]);
    }

    fclose(arquivo); 
}

void apagar_do_arquivo(Dados_do_cliente *dadosC, char cpfIndicado[50])
{

    FILE *arquivoOriginal;
    arquivoOriginal = fopen("Contas_clientes.txt", "r+");

    if (arquivoOriginal == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *arquivoTemporario;
    arquivoTemporario = fopen("temp.txt", "w");

    if (arquivoTemporario == NULL)
    {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivoOriginal);
        return;
    }

    char linha[100];
    int linhasParaPular = 0;
    bool contaEncontrada = false;

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        if (linhasParaPular > 0)
        {
            linhasParaPular--;
            continue;
        }

        if (strstr(linha, cpfIndicado) == NULL)
        {
            fprintf(arquivoTemporario, "%s", linha);
        }
        else
        {
            linhasParaPular = 3; 
            contaEncontrada = true;
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    remove("Contas_clientes.txt");
    rename("temp.txt", "Contas_clientes.txt");
}

void carregar_de_arquivo(Dados_do_cliente *dadosC)
{

    FILE *arquivo;
    arquivo = fopen("Contas_clientes.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    int contador = 0; 

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
       
        linha[strcspn(linha, "\n")] = 0;

       
        if (strncmp(linha, "CPF:", 4) == 0)
        {
            sscanf(linha, "CPF: %[^\n]", dadosC->cpf_clinete[contador]);
        }
        else if (strncmp(linha, "NOME:", 5) == 0)
        {
            sscanf(linha, "NOME: %[^\n]", dadosC->nome_cliente[contador]);
        }
        else if (strncmp(linha, "IDADE:", 6) == 0)
        {
            sscanf(linha, "IDADE: %d", &dadosC->idade_cliente[contador]);
        }
        else if (strncmp(linha, "SALDO:", 6) == 0)
        {
            sscanf(linha, "SALDO: %f", &dadosC->saldo_cliente[contador]);
            contador++; 
        }
    }

    dadosC->tamanho = contador; 

    fclose(arquivo); 
}

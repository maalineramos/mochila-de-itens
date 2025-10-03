#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Struct Item:
typedef struct {
    char nome[20];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 (mais alta) a 5 (mais baixa)
} Item;
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO,
    ORDENAR_POR_PRIORIDADE
} CriterioOrdenacao;
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).


// --- Protótipo do programa ---
void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio, int *comparacoes);
void buscaBinariaPorNome();



int main() {

    int opcao;
    do {
        setbuf(stdin, NULL); // evita problemas de buffer no scanf
        exibirMenu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            inserirItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            menuDeOrdenacao();  
            break;
        case 5:
            buscaBinariaPorNome();
            break;
        case 0:
            printf("Saindo do programa. Ate a proxima!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    } while (opcao != 0);

    return 0;
}



// Vetor mochila:
// Armazena até 10 itens coletados.
Item mochila[10];
int numItens = 0;
bool ordenadaPorNome = false;
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
void limparTela(){
    for(int i = 0; i < 50; i++) printf("\n");
}
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
void exibirMenu(){
    printf("=================================\n");
    printf("      Gerenciamento de Mochila    \n");
    printf("=================================\n");
    printf("Itens na mochila: %d/10\n\n", numItens);
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens por critério (nome, tipo, prioridade)\n");
    printf("5. Realizar busca binária por nome\n");
    printf("0. Sair\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
}
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
void inserirItem(){
    if(numItens >= 10){
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    Item novoItem;
    printf("Digite o nome do item: ");
    scanf(" %19[^\n]", novoItem.nome);
    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);
    printf("Digite a prioridade do item (1-5): ");
    scanf("%d", &novoItem.prioridade);
    
    mochila[numItens++] = novoItem;
    ordenadaPorNome = false;
    printf("Item %s adicionado com sucesso!\n", novoItem.nome);
}
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
void removerItem(){
    if(numItens == 0){
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    for(int i = 0; i < numItens; i++){
        if(strcmp(mochila[i].nome, nomeRemover) == 0){
            for(int j = i; j < numItens - 1; j++){
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado na mochila.\n");
}
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
void listarItens(){
    if(numItens == 0){
        printf("Mochila vazia! Nenhum item para listar.\n");
        return;
    }
    printf("\nItens na mochila:\n");
    printf("-------------------------------------------------\n");
    printf("| %-20s | %-10s | %-8s | %-9s |\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("-------------------------------------------------\n");
    for(int i = 0; i < numItens; i++){
        printf("| %-20s | %-10s | %-8d | %-9d |\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------\n");
}
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void menuDeOrdenacao() {
    int opcao;
    printf("\n=== Menu de Ordenação ===\n");
    printf("1. Ordenar por Nome\n");
    printf("2. Ordenar por Tipo\n");
    printf("3. Ordenar por Prioridade\n");
    printf("0. Cancelar\n");
    printf("Escolha o critério de ordenação: ");
    scanf("%d", &opcao);
    if (opcao == 0) {
        printf("Operação cancelada.\n");
        return;
    }
    int comparacoes = 0;
    switch (opcao) {
        case ORDENAR_POR_NOME:
            insertionSort(ORDENAR_POR_NOME, &comparacoes);
            ordenadaPorNome = true;
            printf("Itens ordenados por nome.\n");
            break;
        case ORDENAR_POR_TIPO:
            insertionSort(ORDENAR_POR_TIPO, &comparacoes);
            ordenadaPorNome = false;
            printf("Itens ordenados por tipo.\n");
            break;
        case ORDENAR_POR_PRIORIDADE:
            insertionSort(ORDENAR_POR_PRIORIDADE, &comparacoes);
            ordenadaPorNome = false;
            printf("Itens ordenados por prioridade.\n");
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }
    printf("Comparações realizadas: %d\n", comparacoes);
}

// insertionSort():
void insertionSort(CriterioOrdenacao criterio, int *comparacoes) {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;
            if (criterio == ORDENAR_POR_NOME) {
                cmp = strcmp(mochila[j].nome, chave.nome);
            } else if (criterio == ORDENAR_POR_TIPO) {
                cmp = strcmp(mochila[j].tipo, chave.tipo);
            } else if (criterio == ORDENAR_POR_PRIORIDADE) {
                cmp = mochila[j].prioridade - chave.prioridade;
            }
            if (cmp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila nao esta ordenada por nome. Por favor, ordene antes de buscar.\n");
        return;
    }
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBusca);
    
    int esquerda = 0, direita = numItens - 1;
    int comparacoes = 0;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Item nao encontrado.\n");
    printf("Comparações realizadas: %d\n", comparacoes);
}
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

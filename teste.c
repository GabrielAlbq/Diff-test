#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura que representa um usuario
struct Usuario{
    char nome[20];
    int idade;
};

// quantidade de posicoes do vetor de usuarios
// esta variavel e
#define TAMANHO_VETOR 10

// quantidade de usuarios cadastrados no vetor
// este valor sera sempre menor do que TAMANHO_VETOR
// esta variavel e incrementada quando um usuario e inserido
// e decrementada quando um usuario e removido
int quantidades_usuarios;

// vetor de usuários
struct Usuario usuarios[TAMANHO_VETOR];

// esta variavel indica se informacoes de debug devem ser impressas
// se valor for 1 as informacoes de debug sao impressas
// se for igual a 0 as informacoes nao sao impressas
int DEBUG_MODE = 0;

// imprime informacoes de debug
void imprimeInformacoesDebug(){
    if(DEBUG_MODE){
        printf("\n*********************\n");
        printf("TAMANHO_VETOR = %d\n", TAMANHO_VETOR);
        printf("quantidade_usuarios = %d\n", quantidades_usuarios);
        printf("usuarios = %p\n", usuarios);
        printf("***********************\n");
    }
}

// procedimento auxiliar que imprime mensagem de erro
void mensagemErro(char *nome_arquivo){
    printf("Erro: nao foi possivel abrir arquivo %s", nome_arquivo);
}

// lista os usuarios do vetor
void imprimeVetorUsuarios(){
    int c;
    printf("\nListando %d usuarios cadastrados\n", quantidades_usuarios);
    for(c=0; c < quantidades_usuarios; c++){
        printf("-----------------------------------\n");
        printf("(%d)\n", c+1);
        printf("Nome  = %s\n", usuarios[c].nome);
        printf("Idade = %d\n", usuarios[c].idade);
    }
}

// remove a quebra de linha no fim da string
void removeQuebraLinha(char *string){
    if(string != NULL && strlen(string) > 0){
        short tamanho = strlen(string);
        if(string[tamanho-1] == '\n'){
            string[tamanho-1] = '\0';
        }
    }
}

// le do teclado uma string com ate quantidade_caracteres de tamanho
// e guarda na variavel string_destino
// se houver uma quebra de linha no fim da string esta quebra e removida
void leStringTeclado(char *string_destino, int quantidade_caracteres){
    
    // fgets e mais seguro do que gets
    // gets le do teclado uma string que pode ser maior do que a
    // variavel que vai armazenar a string (neste exemplo string_destino)
    fgets(string_destino, quantidade_caracteres, stdin);
    
    removeQuebraLinha(string_destino);
}


// le do teclado nome e idade e retorna uma variavel Usuario
struct Usuario leInformacoesUsuario(){
    
    struct Usuario u;
    
    printf("\nNome: ");
    leStringTeclado(u.nome, 20);
    
    // nao precisa de \n depois da leitura do nome
    // \n digitado pelo teclado e aproveitado como quebra
    printf("Idade: ");
    scanf("%d", &u.idade);
    
    return u;
}

// insere novo usuario no vetor enquanto existe uma posicao livre
void insereNovoUsuario(struct Usuario u){
    
    // se o vetor esta cheio
    if(quantidades_usuarios == TAMANHO_VETOR){
        
        printf("Nao e possivel inserir mais usuarios, capacidade maxima atingida");
        return;
    }
    
    // guarda o usuario na ultima posicao livre
    usuarios[quantidades_usuarios] = u;
    
    // atualiza quantidade de usuarios no vetor
    quantidades_usuarios++;
    
}

// procura por um usuario no vetor cujo nome é passado como
// argumento e retorna o ponteiro para o usuario
// o valor do ponteiro retornado e NULL quando nenhum usuario com
// o nome fornecido foi encontrado
struct Usuario *recuperaUsuario(char nome[20]){
    struct Usuario *u = NULL;
    int i;
    for (i=0; i < quantidades_usuarios; i++) {
        if(strcmp(usuarios[i].nome, nome) == 0){
            u = &usuarios[i];
            // quebra o laco logo que encontra o usuario
            // isto economiza tempo evitando percorrer o restante do vetor
            break;
        }
    }
    return u;
}

// recua os elementos do vetor de usuarios em uma posicao
// iniciando de indice_elemento_removido
void reorganizaVetor(int indice_elemento_removido){
    int j = indice_elemento_removido;
    while(j < quantidades_usuarios-1){
        usuarios[j] = usuarios[j+1];
        j++;
    }
}

// remove do vetor o usuario cujo nome foi passado como argumento
int removeUsuarioVetor(char *nome_usuario){
    int i, encontrou = 0;
    for (i=0; i < quantidades_usuarios; i++) {
        if(strcmp(usuarios[i].nome, nome_usuario) == 0){
            reorganizaVetor(i);
            quantidades_usuarios--;
            encontrou = 1;
            // quebra o laco, isto economiza tempo evitando
            // percorrer o restante do vetor
            break;
        }
    }
    return encontrou;
}

void atualizaUsuario(){
    
    printf("Digite o nome do usuario a ser atualizado: ");
    
    char nome_usuario[20];
    leStringTeclado(nome_usuario, 20);
    
    struct Usuario *u = recuperaUsuario(nome_usuario);
    
    if(u != NULL){
        printf("Digite os novos dados para o usuario\n");
        
        struct Usuario u2 = leInformacoesUsuario();
        
        // atualiza o usuario atraves do ponteiro
        strcpy(u->nome, u2.nome);//tem que usar strcpy, nao funciona u->nome = u2.nome!!!
        u->idade = u2.idade;
    }else{
        printf("Usuario nao encontrado!\n");
    }
}

void removeUsuario(){
    
    printf("Digite o nome do usuario a ser removido: ");
    
    char nome_usuario[20];
    leStringTeclado(nome_usuario, 20);
    
    int sucesso = removeUsuarioVetor(nome_usuario);
    
    if(!sucesso){
        printf("Usuario nao encontrado!\n");
    }else{
        printf("Usuario removido com sucesso!\n");
    }
}

// menu do sistema
void menu(){
    
    int sair = 0;
    
    while(!sair){
        
        printf("\nDigite uma das opcoes a seguir\n\n");
        printf("1 - Listar usuarios\n");
        printf("2 - Insere novo usuario\n");
        printf("3 - Atualiza usuario\n");
        printf("4 - Remove usuario\n");
        printf("5 - Sair\n\n");
        printf("Opcao = ");
        
        int opcao;
        scanf("%d", &opcao);
        
        // consome a quebra de linha que sobrou da leitura da opcao do menu
        // se este comando for comentado a proxima leitura vai ler um \n
        getchar();
        
        switch (opcao) {
            case 1:
                imprimeVetorUsuarios();
                break;
                
            case 2:
                printf("Digite o nome do usuario a ser inserido: ");
                insereNovoUsuario(leInformacoesUsuario());
                imprimeInformacoesDebug();
                break;
                
            case 3:
                atualizaUsuario();
                break;
                
            case 4:
                removeUsuario();
                imprimeInformacoesDebug();
                break;
                
            case 5:
                imprimeInformacoesDebug();
                sair = 1;
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
        
    }
    
}


int main(){
    
    printf("#########################################################\n");
    printf("Bem vindo ao sistema de cadastro de usuarios v0.1\n");
    printf("#########################################################\n");
    
    imprimeInformacoesDebug();
    
    insereUsuariosVetor();
    
    imprimeInformacoesDebug();
    
    menu();
    
    printf("\n#########################################################\n");
    printf("Obrigado por ter usado o nosso sistema. Ate breve!\n");
    printf("#########################################################\n");
    
    return 0;
    
}

//Aluno: Daniel Welter da Silva

#include <stdio.h>
#include <stdlib.h>

//Define o valor informado pelo usuário, e ja define o bit de sinal
float defineValorSinal(int *sinal){
    int verificador, resposta = 0;
    float valor;

    //apenas aceita numeros decimais
    while (resposta == 0){
        printf("Digite um valor decimal\nValor: ");
        scanf("%f", &valor);

        verificador = (int)valor;

        if (verificador == valor)
            printf("Número inteiro digitado, favor digitar um valor decimal\n\n");
        else
            resposta = 1;
    }

    //Define o bit de sinal
    if (valor < 0){
        (valor) = ((valor) * (-1));
        *sinal = 1;
    }else{
        *sinal = 0;
    }

    return valor;
}

//Converte valores inteiros para binario
int *converterBinarioInteiro(int valor, int tamanho_vet){
    int i, *vet;

    vet = malloc(tamanho_vet * sizeof(int));

    for (i = (tamanho_vet - 1); (valor > 0 && i >= 0); i--){
            vet[i] = (valor % 2);
            valor = ((valor - vet[i]) / 2);
    }

    return vet;
}

//Converte os valores decimais para binario
int *converterBinario(int *posicao_virg, int *contagem, float valor){
    int *binario, binario_temp[32];
    int i, j, ant_virgula, cont;
    float pos_virgula;

    cont = 0;
    binario = malloc(32 * sizeof(int));

    //Separa a parte inteira da parte decimal
    ant_virgula = (int)valor;
    pos_virgula = (valor - ant_virgula);

    //Converte a parte inteira para binario
    if (ant_virgula == 0){
        binario_temp[0] = 0;
        cont++;
    }else{
        for (i = 0; ant_virgula > 0; i++){
            binario_temp[i] = (ant_virgula % 2);
            ant_virgula = ((ant_virgula - binario_temp[i]) / 2);
            cont++;
        }
    }

    //Reorganiza o vetor principal
    for (i = (cont - 1), j = 0; i >= 0; i--, j++){
        binario[j] = binario_temp[i];
    }

    *posicao_virg = cont;

    //Converte a parte decimal em binario
    if ((*posicao_virg) > 0){
        for (i = cont; pos_virgula > 0; i++, cont++){
            pos_virgula *= 2;
            ant_virgula = (int)pos_virgula;
            pos_virgula = (pos_virgula - ant_virgula);
            binario[i] = ant_virgula;
        }
    }

    //Tamanho do vetor
    *contagem = cont;

    return binario;
}

void imprimirBinario(int *vet, int pos_virg, int contagem){
    int i;

    printf("Binario: ");

    for (i = 0; i < contagem; i++){
        if (i == pos_virg){
            printf(",");
        }
        printf("%d", vet[i]);
    }

    printf("\n");
}

//Transforma o binario em notação normalizada e retorna o valor do expoente
int notacaoNormalizada(int *vet, int *pos_virgula, int tamanho_vet){
    int i, pos_virg_ant = *pos_virgula, expoente;

    for (i = 0; i < tamanho_vet; i++){
        if (vet[i] == 1){
            *pos_virgula = (i + 1);
            break;
        }
    }

    expoente = (pos_virg_ant - (*pos_virgula));

    return expoente;
}

//Reorganiza o vetor
void reoganizaVetor(int *vet, int *pos_virgula, int *tamanho_vet){
    int i, cont = 0;

    while (vet[0] != 1){
        for (i = 0; vet[i] != 1; i++){
            if (vet[i] == 0){
                if (vet[i + 1] == 0 || vet[i + 1] == 1){
                    vet[i] = vet[i + 1];
                }
            }
        }
        cont++;
    }

    *tamanho_vet = ((*tamanho_vet) - cont);
    *pos_virgula = 1;
}

//Imprime a notação Normalizada
void imprimeNotacaoNormalizada(int * vet, int expoente, int pos_virgula, int tamanho_vet){
    int i;

    printf("Notacao Normalizada: ");

    for (i = 0; i < tamanho_vet; i++){
        if (i == pos_virgula){
            printf(",");
        }

        printf("%d", vet[i]);
    }

    printf(" * 2^%d\n", expoente);
}

//Transforma em padrão IEEE754
void converterIEEE(int sinal, int expoente, int *vet, int pos_virgula, int *vet_final, int tam_vet){
    int *exp, exp_conv, posicao_atual = 0, i, j;

    vet_final[posicao_atual] = sinal;

    exp_conv = (expoente + 127);

    exp = converterBinarioInteiro(exp_conv, 8);

    for (posicao_atual = 1, j = 0; posicao_atual < 9; posicao_atual++, j++){
        vet_final[posicao_atual] = exp[j];
    }

    for (i = pos_virgula, j = posicao_atual; i < tam_vet; i++, j++, posicao_atual++){
        vet_final[j] = vet[i];
    }

    for (i = posicao_atual, j = 1; i < 32; i++, posicao_atual++, j++){
        vet_final[i] = 0;
    }

    printf("Padrao IEEE754: ");

    for (i = 0; i < posicao_atual; i++){
        if (i == 1 || i == 9){
            printf("|");
        }
            printf("%d", vet_final[i]);
    }

    printf("\n");
}

int main(){
    int posicao_virgula, contagem, *vet, expoente, sinal, *vet_final;
    float valor;

    vet_final = malloc(32 * sizeof(int));


    valor = defineValorSinal(&sinal);

    printf("\n");

    vet = converterBinario(&posicao_virgula, &contagem, valor);

    imprimirBinario(vet, posicao_virgula, contagem);

    expoente = notacaoNormalizada(vet, &posicao_virgula, contagem);

    reoganizaVetor(vet, &posicao_virgula, &contagem);

    imprimeNotacaoNormalizada(vet, expoente, posicao_virgula, contagem);

    converterIEEE(sinal, expoente, vet, posicao_virgula, vet_final, contagem);

    printf("\n");

    return 0;
}

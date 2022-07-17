#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TAMANHO 16

int limiteNumeros(int num){
    while(num > 32767 || num < -32768){
        printf("\nHouve overflow!!!\nImposs�vel fazer a convers�o deste n�mero para bin�rio com apenas 16 bits!!!\n\nDigite outro n�mero: ");
        scanf("%i",&num);
    }
    return num;
}

int adicao(int *binario1,int *binario2,int *resultado){
    int vaiUM = 0,vaiUmBitSinal = 0,vaiUmForaNumero = 0;
    for(int i = 15;i>= 0;i--){
        switch(binario1[i]){
            case 0:
                switch(binario2[i]){
                    case 0:
                        if(vaiUM == 1){
                            resultado[i] = 1;   //realizando a opera��o entre bin�rios
                            vaiUM = 0;
                        }
                        else{
                            resultado[i] = 0;
                        }
                        break;

                    case 1:
                        if(vaiUM == 1){
                            resultado[i] = 0;
                            vaiUM = 1;
                            if(i == 1){
                                vaiUmBitSinal = 1;
                            }
                            else
                                if(i == 0){
                                    vaiUmForaNumero = 1;
                                }
                        }
                        else{
                            resultado[i] = 1;
                        }
                        break;
                }
                break;

            case 1:
                switch(binario2[i]){
                    case 0:
                        if(vaiUM == 1){
                            resultado[i] = 0;
                            vaiUM = 1;
                            if(i == 1){
                                vaiUmBitSinal = 1;
                            }
                            else
                                if(i == 0){
                                    vaiUmForaNumero = 1;
                                }
                        }
                        else{
                            resultado[i] = 1;
                        }
                        break;

                    case 1:
                        if(vaiUM == 1){
                            resultado[i] = 1;
                            vaiUM = 1;
                            if(i == 1){
                                vaiUmBitSinal = 1;
                            }
                            else
                                if(i == 0){
                                    vaiUmForaNumero = 1;
                                }
                        }
                        else{
                            resultado[i] = 0;
                            vaiUM = 1;
                            if(i == 1){
                                vaiUmBitSinal = 1;
                            }
                            else
                                if(i == 0){
                                    vaiUmForaNumero = 1;
                                }
                        }
                        break;
                }
                break;
        }
        if((vaiUmBitSinal == 0 && vaiUmForaNumero == 1 && i == 0) || (vaiUmBitSinal == 1 && vaiUmForaNumero == 0 && i == 0))//Condi��o para ter overflow
            return -1;  //retorno -1 para fun��o main que indica overflow
    }

    return 0;
}

int verificaDados(int min,int max){
    int num;
    scanf("%i",&num);
    while(num < min || num > max){
        printf("\nValor inv�lido!!!\n\nPor favor digite um valor v�lido: ");
        scanf("%i",&num);
    }
    return num;

}

void inverteAdiciona(int *numero){
    int i,vaiUm = 1;
    for(i = 0; i < TAMANHO;i++){    //invertendo os bits do numero
        if(numero[i] == 1)
            numero[i] = 0;
        else
            if(numero[i] == 0)
                numero[i] = 1;
    }
    for(i = 15;i>=0;i--){
        switch(numero[i]){  //somando 1 ao n�mero
            case 0:
                if(vaiUm == 1){
                    numero[i] = 1;
                    vaiUm = 0;
                }
                else
                    numero[i] = 0;

                break;

            case 1:
                if(vaiUm == 1){
                    numero[i] = 0;
                    vaiUm = 1;
                }
                else
                    numero[i] = 1;
            break;
        }
    }
}

void complementoDeDois(int num, int *numero){
    int i=15,resto=0;

    for(int s = 0;s <= 15;s++){ //inicializando vetor numero com 0
        numero[s] = 0;
    }

    while(abs(num) != 0){  //convertendo numero de decimal para bin�rio
        if(abs(num) == 1){
            numero[i] = 1;
            break;
        }
        resto = abs(num)%2;
        numero[i] = resto;
        num /= 2;
        i--;
    }

    if(num < 0){ //caso o n�mero seja negativo, chamada da fun��o que realiza o complemento de 2(inverte todos os bits e soma 1)
        inverteAdiciona(numero);
    }

}

int main(){
    int num1,num2,operacao,resultado[TAMANHO]={0},binario1[TAMANHO]={0},binario2[TAMANHO]={0},i;
    setlocale(LC_ALL,"");

    do{
        printf("Digite um valor inteiro:\n");

        scanf("%i",&num1);
        num1 = limiteNumeros(num1);     //Chamada da fun��o limiteNumeros que verifica se o n�mero inserido � possivel representar com 16 bits

        printf("\n\nDigite outro valor inteiro:\n");

        scanf("%i",&num2);
        num2 = limiteNumeros(num2);

        complementoDeDois(num1,binario1);
        complementoDeDois(num2,binario2);

        system("CLS || Clear");

       for(i = 0;i < TAMANHO;i++){      //printando os n�meros em bin�rio e decimal para o usu�rio ter uma no��o do valor em bin�rio do numero que digitou
            printf("%i ",binario1[i]);
        }
        printf(" ----> %i",num1);

        printf("\n\n");

        for(i = 0;i < TAMANHO;i++){
            printf("%i ",binario2[i]);
        }
        printf(" ----> %i",num2);

        printf("\n\nEscolha uma opera��o para realizar com os dois n�meros: \n\n1 - Adi��o\n2 - Subtra��o\n0 - Sair do programa\n");
        operacao = verificaDados(0,2);  //verificando se os n�meros digitados s�o v�lidos

        switch(operacao){
            case 1: //caso for adi��o

                if(adicao(binario1,binario2,resultado)== 0){    //chamada da fun��o juntamente com verifica��o de valor
                    system("CLS || Clear");                     //retorno 0 = valor v�lido e ser� printado ao usu�rio a opera��o
                                                                //retorno -1 = houve overflow na soma
                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",binario1[i]);
                    }
                    printf(" ----> %i",num1);

                    printf("\n\n");

                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",binario2[i]);
                    }
                    printf(" ----> %i",num2);

                    printf("\n-------------------------------\n");

                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",resultado[i]);
                    }
                    printf(" ----> %i\n\n",num1+num2);
                }
                else{
                    printf("\nHouve overflow na adi��o dos n�meros!!!\n\n");

                }

                system("Pause");
                system("CLS || Clear");

                break;


            case 2:
                inverteAdiciona(binario2);  //invertendo o subtraendo e adicionando 1 para poder realizar a soma entre os dois bin�rios

                if(adicao(binario1,binario2,resultado)== 0){  //chamada da fun��o adicao com teste de retorno

                    system("CLS || Clear");

                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",binario1[i]);
                    }
                    printf(" ----> %i",num1);

                    printf("\n\n");

                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",binario2[i]);
                    }
                    printf(" ----> %i",num2*-1);    //printando o subtraendo invertido para o usu�rio

                    printf("\n-------------------------------\n");

                    for(i = 0;i < TAMANHO;i++){
                        printf("%i ",resultado[i]);
                    }
                    printf(" ----> %i\n\n",num1-num2);
                }
                else{
                    printf("\nHouve overflow na adi��o dos n�meros!!!\n\n");
                }

                system("Pause");
                system("CLS || Clear");

                break;
        }
    }while(operacao != 0);  //condi��o de sa�da � opera��o == 0

    return 0;
}

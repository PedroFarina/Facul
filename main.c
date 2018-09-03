#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int precos[10] = {2, 4, 7, 9, 10, 13, 15, 17, 19, 22};

int main(int argc, char *argv[]) {
	int tamPeca = 11;
	
	int descePreco = tamPeca;
	
	int precoFinal;
	int precoTemporario;
	int descePrecoMaior=0;
	
	while(descePreco != 0){
		precoTemporario = 0;
		int restantePeca = tamPeca;
		int descePrecoPeca = descePreco;
		
		while(restantePeca != 0){
			int resto = restantePeca%descePrecoPeca;
			int quantVezes = ((restantePeca-resto)/descePrecoPeca);
			precoTemporario += quantVezes * precos[descePrecoPeca -1];
			restantePeca = resto;
			descePrecoPeca = resto;
		}
		if(precoTemporario > precoFinal){
			precoFinal = precoTemporario;
			descePrecoMaior = descePreco;
		}
		descePreco--;
	}
	printf("O melhor preco e: %d dividindo em pedacos de %dcm e vendendo o restante.", precoFinal, descePrecoMaior);
	return 0;
}

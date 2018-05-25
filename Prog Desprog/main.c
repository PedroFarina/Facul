#include <stdio.h>
#include <stdlib.h>

#ifndef __MAIN__
#define __MAIN__
typedef int bool;
#define true 1
#define false 0

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void Codifica(char *, int);
void CodificaPadrao(char *, int);
void Descodifica(char *, int);
void Reverter(char *, int);
double Elevar(int, int);
bool TodosSao(char*, int, char);

int main(int argc, char *argv[]) {
	char str[200];
	printf("Entre com uma sigla : ");
	scanf("%s", str);
	CodificaPadrao(str, 200);
	printf("%s\n", str);
	//Descodifica(str, 200);
	printf("%s\n", str);
	return 0;
}

void Codifica(char *str, int len){
	int i, i2, quant = 1;
	i2 = 0;
	char str2[len], c;
	c = str[0];
	for(i = 1; i < len && str[i] != '\0'; i++){			//Rodando enquanto não estamos no fim do length, nem no fim do array('\0')
		if(c == str[i]){								//Se o anterior é o mesmo caractere que o atual, soma no contador.
			quant++;
		}
		else{
			str2[i2] = c;								//Seta o caractere no lugar.
			i2++;
			i2 += sprintf(&str2[i2], "%d", quant);		//Converte o contador de quantidade pra "string".
			str2[i2] = '-';								//Separador.
			i2++;
			quant = 1;		
		}
		c = str[i];
	}
	str2[i2] = c;						//Faz o mesmo processo pro ultimo caractere que não tem um "próximo a ser comparado.
	i2++;
	sprintf(&str2[i2], "%d", quant);
	
	for(i = 0; i<len; i++){				//Alterando a array original para igualar a nova gerada.
		*(str + i) = str2[i];
	}
}

void CodificaPadrao(char *str, int len){
	char padrao[len], str2[len], c;
	int i=1, lenPadrao=1, i2=0, i2Anterior=0, i3;
	int nTeste = 0, acumulaPadrao = 0;
	bool achouPadrao = false;
	padrao[0] = str[0];
	
	while(i < len){
		c = str[i];
		
		if(achouPadrao){
			if(c==padrao[nTeste]){
				nTeste++;
				if(nTeste==lenPadrao){
					acumulaPadrao++;
					nTeste = 0;
				}
			}
			else{
				achouPadrao = false;
				for(i3=0; i3<lenPadrao; i3++){
					str2[i2 + i3] = padrao[i3];
				}
				i2 += lenPadrao;
				i2 += sprintf(&str2[i2], "%d", acumulaPadrao);
				str2[i2] = '-';
				i2++;
				i2Anterior = i2;
				i -= nTeste + 1;
				lenPadrao = 0;
			}
		}
		else if(c == padrao[0] && !TodosSao(padrao, lenPadrao, c)){
			achouPadrao = true;
			nTeste = 1;
			acumulaPadrao = 1;
		}
		else{
			padrao[lenPadrao] = c;
			lenPadrao++;
		}
		
		if(str[i] == '\0'){
			if(lenPadrao > 1){
				if(TodosSao(padrao, lenPadrao, padrao[0])){
					str2[i2] = padrao[0];
					i2++;
					i2 += sprintf(&str2[i2], "%d", lenPadrao-1);
					str2[i2] = '\0';
				}
				else{
					for(i2=i2; i2<i2Anterior+lenPadrao - 1; i2+= lenPadrao-1){
						for(i3=0; i3<lenPadrao-1; i3++){
							str2[i2 + i3] = padrao[i3];
						}
					}
					str2[i2] = '1';
					i2++;
					str2[i2] = '\0';
					i2++;	
				}
			}
			else{
				str2[i2-1] = '\0';
			}
			int k;
			printf("%s\n", str2);
			break;
		}
		i++;
	}
	
	for(i = 0; i<len; i++){				//Alterando a array original para igualar a nova gerada.
		*(str + i) = str2[i];
	}
}

void Descodifica(char *str, int len){
	int i, i2 = 0, i3 = 0, i4 = 0, i2Anterior = 0;
	char str2[len], str3[len], str4[len], contador;
	
	
	for(i = 0; i < len; i++){
		if(isdigit(str[i])){
			str3[i3] = str[i];
			i3++;
		}
		else if(str[i] == '-' || str[i] == '\0'){
			int total = 0, i5;
			Reverter(str3, i3);
			for(i5=0; i5 < i3; i5++){
				total += Elevar(10, i5) * (str3[i5] - '0');
			}
			//printf("O total e %d.\n", total);
			
			for(i2 = i2; i2 < i2Anterior + total;i2 += i4){
				for(i5 = 0; i5 < i4; i5++){
					str2[i2 + i5] = str4[i5];
				}
			}
			if(str[i] == '\0'){
				str2[i2] = '\0';
				break;	
			}
			i2Anterior = i2;
			i3 = 0;
			i4 = 0;
		}
		else{
			str4[i4] = str[i];
			i4++;
		}
	}
	
	for(i = 0; i<len; i++){				//Alterando a array original para igualar a nova gerada.
		*(str + i) = str2[i];
	}
}

void Reverter(char *str, int len){
	int i, i2 = 0;
	char str2[len];
	
	for(i=len - 1; i >= 0; i--){				//Revertendo.
		str2[i2] = str[i];
		i2++;
	}
	
	for(i = 0; i<len; i++){				//Alterando a array original para igualar a nova gerada.
		*(str + i) = str2[i];
	}
}

double Elevar(int base, int expoente){
	if(expoente==0 || base==1) return 1;
	return base * Elevar(base, expoente -1);
}

bool TodosSao(char *str,int len,char c){
	bool retorno = true;
	int i;
	for(i=0;i<len && str[i] != '\0';i++){
		retorno = retorno & str[i] == c;
	}
	return retorno;
}
#endif

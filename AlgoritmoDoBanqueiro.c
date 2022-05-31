#include <stdio.h>

#define X 5
#define Y 4

#define false 0
#define true 1

//matrizes
int recursos_disponiveis[Y] = {9,0,0,1}; 
int recursos_atribuidos[X][Y] = {{3,0,1,1},{0,1,0,0},{1,1,1,0},{1,1,0,1},{0,0,0,0}};	 
int recursos_necessarios[X][Y] = {{1,1,0,0},{0,1,1,2},{3,1,0,0},{0,0,1,0},{2,1,1,0}}; 

//variáveis globais
int i, j, k, pode_Ser_Atendido;
int verf_atendimento[X]; //vetor que armazena se o processo foi atendido ou nao
int deadlock = false;
int ord_atend[X]; //vetor que armazena a ordem que os processos foram atendidos
int num_atend = 0;

void proc_nao_atendidos(int num_processo) {
	pode_Ser_Atendido = 0;
		for(j = 0; j < Y; j++) {
			if(recursos_necessarios[num_processo][j] <= recursos_disponiveis[j]) {
				pode_Ser_Atendido++;
		}
	}

	if(pode_Ser_Atendido == Y) { // se todos os elementos da linha podem ser atendidos
		//o processo pode ser atendido então atualiza  o vetor A
		int z;
		for(z = 0; z < Y; z++) {
			recursos_disponiveis[z] = recursos_disponiveis[z] + recursos_atribuidos[num_processo][z];
			recursos_atribuidos[num_processo][z] = 0;
		}
		verf_atendimento[num_processo] = true;
		ord_atend[num_atend] = num_processo;
		num_atend++;
	}
}
int main()
{
	for(i = 0 ; i < X; i++)
		verf_atendimento[i] = true;

	for(i = 0; i < X; i++) {
		pode_Ser_Atendido = 0;
		for(j = 0; j < Y; j++) {
			if(recursos_necessarios[i][j] <= recursos_disponiveis[j]) { //verifica se o pedido é igual ou menor que os recursos disponiveis
				pode_Ser_Atendido++;
			}
		}
		//se a condicao for verdadeira, significa que o processo pode ser atendido com os recursos que ele deseja
		if(pode_Ser_Atendido == Y) {
			//se o processo pode ser atendido, atualiza  o array A 
			for(k = 0; k < Y; k++) {
				recursos_disponiveis[k] = recursos_disponiveis[k] + recursos_atribuidos[i][k];
				recursos_atribuidos[i][k] = 0;
			}
			verf_atendimento[i] = true;
			ord_atend[num_atend] = i;
			num_atend++;
			//varrer a lista de nao atendidos, para ver se um novo processo pode ser atendido agora
			for(k = 0; k < X; k++) {
				if(verf_atendimento[k] == false)
					proc_nao_atendidos(k);				
			}
		}
		else {
			verf_atendimento[i] = false;
		}	
	}
	for(i = 0; i < X; i++)
		if(!verf_atendimento[i])
			deadlock = true;

	if(deadlock) { 
		printf("Houve deadlock com os seguintes processos:\n");
		for(i = 0; i < X; i++)
			if(verf_atendimento[i] == false)
				printf("p%d, ", i);
	}
	else {
		printf("Nao houve deadlock. Os processos podem ser atendidos na seguinte ordem:\n");
		for(i = 0; i < X; i++)
			printf("p%d, ", ord_atend[i]);
	}
	printf("\n");	
	return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>	


float * summaryMean(float **dataset, int class)
{
	int i;
	
	float * means = malloc(FEATURES * sizeof(float));

	
	for(i = 0; i<FEATURES;i++)
	{
		means[i] = calculateMean(dataset,i, class);

	}

	return means;
}

int main()
{

	//carrega dados pra memória
	float **dataset = loadCSV(FILENAME);


	
	/*É preciso 2 vetores, 1 para guardar as médias e 1 para guardar a stdv
	*O tamanho do vetor é o número de atributos (FEATURES) * o número de classes(CLASS_NUMBER)
	*Supondo que o número de classes é 2,  então a gente vai usar duas linhas 
	*1 linha para as entradas da classe 0 e uma linha para os da classe 1
	* As entradas são as médias de cada atributo, então o primeiro elemento do vetor vai guardar a média dos dados da primeira
	* coluna do dataset, mas somente os dados que são da classe 0 e assim sucessivamente
	*/
	float **means = malloc(CLASS_NUMBER * sizeof(float *));
	for(j=0;j<CLASS_NUMBER;j++)
		means[j] = malloc((FEATURES)*sizeof(float));


	float **stdevs = malloc(CLASS_NUMBER * sizeof(float *));
	for(j=0;j<CLASS_NUMBER;j++)
		stdevs[j] = malloc((FEATURES)*sizeof(float));


	for(j = 0; j<CLASS_NUMBER;j++)
	{
		means[j] = summaryMean(dataset,j);
		stdevs[j] = summaryStdv(dataset,j);
	}
}
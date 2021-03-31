#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void remove_spaces(char* restrict str_trimmed, const char* restrict str_untrimmed){
	while(*str_untrimmed!='\0'){
		if(!isspace(*str_untrimmed)){
			*str_trimmed = *str_untrimmed;
			str_trimmed++;
		}
		str_untrimmed++;
	}
	*str_trimmed='\0';
}

int main(int argc, char*argv[]){
	/*Validar que el archivo a leer fue ingresado como parametro*/
	if(argc < 2){
		printf("You must specify a filepath\n");
		return EXIT_FAILURE;
	}

	FILE* fp = fopen(argv[1], "r");

	/*Validar si hubo un error al ingresar a leer el archivo*/
	if(!fp){
		printf("Error while opening the file %s\n", argv[1]);
	}

	char line[1024];
	int line_count = 0;
	int arguments[4];
	int num_ingredients_per_plate = 0;
	int total_ingredients = 0;
	int total_plates = 0;
	int p2, p3, p4 = 0;
	char ingredients[20][10];
	bool flag;
	int op3, op4 = 0;

	/*Comenzamos a leer el archivo*/
	while(fgets(line, 1024, fp)){
		char *word;
		char *rest =line;
		/*Ingresamos a la primera linea del archivo y la leemos*/
		if(line_count == 0){

			int terms_count = 0;
			/*Llenamos los valores del vector arguments en las posiciones
			correspondientes*/
			while(word = strtok_r(rest, " ", &rest)){
				/*En el vector en la posicion dada guardamos el valor leido
				haciendo un casting a entero*/
				arguments[terms_count] = atoi(word);
				terms_count++;
			}
			p2 = arguments[1];
			p3 = arguments[2];
			p4 = arguments[3];
			/*Incrementamos variable de control para la entrada de este procedimiento*/
			line_count++;

		/*Lectura de platos y sus ingredientes*/
		}else{
			/*Lectura de numero de ingredientes por plato*/
			word = strtok_r(rest, " ", &rest);
			num_ingredients_per_plate = atoi(word);
			total_plates++;

			/*Lectura de cada ingrediente por plato*/
			for(int i = 0; i<num_ingredients_per_plate; i++){

				word  = strtok_r(rest, " ", &rest);
				flag = false;
				char *aux = (char*)malloc(sizeof(char*));
				remove_spaces(aux,word);
				for(int j = 0; j < total_ingredients; j++){
					int cmp = strcmp(ingredients[j], aux);
					if(cmp == 0){
						flag = true;
					}
				}
				if(flag == false){
					strcpy(ingredients[total_ingredients], aux);
					total_ingredients++;
				}
			}
		}

	}
	fclose(fp);
	printf("Cantidad de pedidos de 2 platos: %d \n", p2);
	printf("Cantidad de pedidos de 3 platos: %d \n", p3);
	printf("Cantidad de pedidos de 4 platos: %d \n", p4);
	printf("Cantidad total de platos: %d \n", total_plates);
	printf("Cantidad total de ingredientes: %d \n", total_ingredients);
	if(arguments[0] == total_plates){
		printf("Puede continuar\n");
			/*Asignacion de valores offset*/
			op3 = 2*p2;
			op4 = 2*p2 + 3*p3;
			/*Llenado de la matriz de P con valores 0*/
			int p[total_plates][total_ingredients];
			for(int i = 0; i < total_plates; i++){
				for(int j=0; j < total_ingredients; j++){
					p[i][j] = 0;
				}

			}
			/*Debemos leer nuevamente el archivo*/
			char line2[1024];
			fp = fopen(argv[1], "r");
			//rewind(fp);
			line_count = 0;
			num_ingredients_per_plate = 0;
			while(fgets(line2, 1024,fp)){
				char *word;
				char *rest=line2;
				/*Omitir primera linea del archivo*/
				if(line_count==0){
					line_count++;
				/*Lectura de los archivos*/
				}else{
					word = strtok_r(rest, " ", &rest);
					num_ingredients_per_plate = atoi(word);
					/*Recorrido de ingredientes*/
					for(int i=0; i<num_ingredients_per_plate; i++){
						word = strtok_r(rest, " ", &rest);
						char *aux = (char*)malloc(sizeof(char*));
						remove_spaces(aux, word);
						for(int j=0;j<total_ingredients;j++){
							int cmp = strcmp(ingredients[j],aux);
							if(cmp == 0){
								/*Platos van de la linea 1 a n*/
								p[line_count-1][j] = 1;
								j=total_ingredients;
							}
						}
					}
					line_count++;
				}
			}
			/*Se imprime la matriz P*/
			for(int i=0; i< total_plates; i++){
				for(int j=0; j<total_ingredients; j++){
					printf(" %d ", p[i][j]);
				}
				printf("\n");
			}
			/*Inicialmente llenamos el vector AP*/
			int ap[total_plates];
			for(int i=0; i < total_plates; i++){
				ap[i] = i;
				printf(" %d ", ap[i]);
			}
			printf("\n");
	}else{
		printf("La cantidad de platos ingresada no corresponde a la encontrada");
	}
}

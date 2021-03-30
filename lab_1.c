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

	printf("Cantidad total de platos: %d \n", total_plates);
	printf("Cantidad total de ingredientes: %d \n", total_ingredients);
	if(arguments[0] == total_plates){
		printf("Puede continuar\n");
	}else{
		printf("La cantidad de platos ingresada no corresponde a la encontrada");
	}
	fclose(fp);
}

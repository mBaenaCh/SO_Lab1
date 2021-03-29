#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int linecount = 0;
	int arguments[4];
	int numingredients = 0;
	int pp = 0;
	int I = 0;
	int p2, p3, p4 = 0;

	/*Comenzamos a leer el archivo*/
	while(fgets(line, 1024, fp)){
		char *word;
		char *rest =line;
		/*Ingresamos a la primera linea del archivo y la leemos*/
		if(linecount == 0){

			int termscount = 0;
			/*Llenamos los valores del vector arguments en las posiciones 
			correspondientes*/
			while(word = strtok_r(rest, " ", &rest)){
				/*En el vector en la posicion dada guardamos el valor leido
				haciendo un casting a entero*/
				arguments[termscount] = atoi(word);
				termscount++;
			}
			/*Incrementamos variable de control para la entrada de este procedimiento*/
			linecount++;
		}else{
			/*Lectura de platos y sus ingredientes*/
			word = strtok_r(rest, " ", &rest);
			numingredients = atoi(word); /*Ingredientes por plato*/

			for(int i = 0; i<numingredients; i++){
				word  = strtok_r(rest, " ", &rest);
				printf("Ingredient: %s\n", word);

			}
		}
	}
	printf("Cantidad pedidos:%d \n",arguments[0]);
 	printf("Pedidos de 2 platos:%d \n", arguments[1]);
	printf("Pedidos de 3 platos:%d \n", arguments[2]);
	printf("Pedidos de 4 platos: %d \n",arguments[3]);

	fclose(fp);
}

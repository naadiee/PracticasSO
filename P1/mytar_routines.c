#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;

/** Copy nBytes bytes from the origin file to the destination file.
 *
 * origin: pointer to the FILE descriptor associated with the origin file
 * destination:  pointer to the FILE descriptor associated with the destination file
 * nBytes: number of bytes to copy
 *
 * Returns the number of bytes actually copied or -1 if an error occured.
 */
int copynFile(FILE * origin, FILE * destination, int nBytes)
{
	int caracter; 
	int bytesCopied = 0; 

	if((origin == NULL) || (destination == NULL)){
		return -1; 
	}

	do{
		caracter = getc(origin); // Lee un carcater del fichero origen (el cual se pasa la direccion como argumento) 
		/*
		Esta funcion LEE solo 1 BYTE -> que es lo que tenemos que ir comprobando en todo momento con la varianle bytesCopied, 

		1) En caso de EXITO devuelve el caracter leido en formato de unsigned char. 
		2) En caso de ERROR devuelve EOF 
		*/

		if(caracter != EOF){ // comprobamos que lo leido es correcto en caso que no sea EOF continuamos con la copia 
			putc(caracter, destination); // Dado que no hay error procedemos a realizar la copia. Le pasamos el caracter como primer argumetno y como segundo la direccion del archivo destino 
			bytesCopied++; // se ha realizado la copia por lo tanto aumentamos en 1 los bytes copiados. 
		}

	}while((caracter != EOF) || (bytesCopied <= nBytes)); // comprobamos que no nos pasemos de los bytes que tenemos que copiar y tambien que lo que hemos copiado es correcto



	return bytesCopied; // devolvemos los bytes copiados

}

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor 
 * 
 * The loadstr() function must allocate memory from the heap to store 
 * the contents of the string read from the FILE. 
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc()) 
 * 
 * Returns: !=NULL if success, NULL if error
 */
char* loadstr(FILE * file){
	int caracter; // Vatiable que almacena el caracter leido del fichero pasado por argumento 
	int tam = 0; // contador que nos permite clacular el tamaño del array para reservar espacio.
	
	char * contenido = NULL; // puntero de la direccion que hemos leido 

	if(file == NULL){
		return -1; 
	}
	caracter = getc(file); // leemos el primer byte
	while((caracter != EOF )&& (caracter != '\0')){// comprobamos que lo leido NO nos devuleve EOF(lee un caracter valido) o NO estamos en el final(\0)
		tam++; // aumentamos el tamño. TODO ha ido bien 
		caracter = getc(file);// para que siga metiendo en el bucle. 
	}

	if(caracter == EOF){ // este if nos sirve a distinguir si lo ultimo leido ha sido un \0 en caso contrario nos quiere decir que el fichero no tiene el fomato adecuado
		return -1; // asi que se meteria en este if y nos diria que algo ha ido mal 
	}
	else{
		fseek(file, -(tam), SEEK_CUR); // volvemos al inicio del fichero, para poder volver a leer. 

		contenido = malloc(sizeof(char) * tam); // reservamos memoria de acuerdo con lo que hemos leido previamente 

		for(int i = 0; i < tam; i++){
			contenido[i] = getc(file); //copiamos byte a byte  en el array lellendo del fichero 
		}

	}
	

	// Complete the function
	return contenido;
}

/** Read tarball header and store it in memory.
 *
 * tarFile: pointer to the tarball's FILE descriptor 
 * nFiles: output parameter. Used to return the number 
 * of files stored in the tarball archive (first 4 bytes of the header).
 *
 * On success it returns the starting memory address of an array that stores 
 * the (name,size) pairs read from the tar file. Upon failure, the function returns NULL.
 */
stHeaderEntry* readHeader(FILE * tarFile, int *nFiles){

	int tam; 

	if(tarFile == NULL){ //en caso de que la direccion del mtar sea mala
		return NULL; 
	}

	fread(nFiles, sizeof(int), 1, tarFile); // leemos la cabecera del archivo mtar que nos da el numero de archivos que contiene
	if(*nFiles == 0){
		return NULL; // es que lo leido de la cabecera no esta bien
	}

	stHeaderEntry t = malloc(sizeof(stHeaderEntry)* *nFiles) // reservaos memoria para los pares de stHeaderEntry para el numero de archivos que tiene el mtar


	for(int i = 0; i < *nFiles; i++){
		t[i].name = loadstr(tarFile); // leemos la cabezera con la funcion que carga en un buffer lo que haya leido de un archivo 

		if(t[i].name == NULL){
			return NULL; // al leer una de las cabeceras algo ha ido mal asi que terminamos. 
		}

		fread(&t[i].size,sizeof(int), 1, tarFile);

	}

	// Complete the function
	return NULL;
}

/** Creates a tarball archive 
 *
 * nfiles: number of files to be stored in the tarball
 * filenames: array with the path names of the files to be included in the tarball
 * tarname: name of the tarball archive
 * 
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First reserve room in the file to store the tarball header.
 * Move the file's position indicator to the data section (skip the header)
 * and dump the contents of the source files (one by one) in the tarball archive. 
 * At the same time, build the representation of the tarball header in memory.
 * Finally, rewind the file's position indicator, write the number of files as well as 
 * the (file name,file size) pairs in the tar archive.
 *
 * Important reminder: to calculate the room needed for the header, a simple sizeof 
 * of stHeaderEntry will not work. Bear in mind that, on disk, file names found in (name,size) 
 * pairs occupy strlen(name)+1 bytes.
 *
 */
int
createTar(int nFiles, char *fileNames[], char tarName[])
{
	// Complete the function
	return EXIT_FAILURE;
}

/** Extract files stored in a tarball archive
 *
 * tarName: tarball's pathname
 *
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First load the tarball's header into memory.
 * After reading the header, the file position indicator will be located at the 
 * tarball's data section. By using information from the 
 * header --number of files and (file name, file size) pairs--, extract files 
 * stored in the data section of the tarball.
 *
 */
int
extractTar(char tarName[])
{
	// Complete the function
	return EXIT_FAILURE;
}

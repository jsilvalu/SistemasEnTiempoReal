/*
 * p1.c
 *
 *  Created on: 2 oct. 2019
 *      Author: JUAN ANTONIO SILVA LUJAN
 */
#include "buffer_acotado.h"
#include <stdio.h>

#define REPETICIONES 50
#define NUM_HILOS 5

void hilo_productor(limited_buffer_t *b) {
	//Llamar REPETICIONES veces a limited_buffer_put mostrando un mensaje con el n�mero que se introducir�
	int i;
	for (i = 0; i < 50; i++) {
		limited_buffer_put(b, i);
		printf("Ejecutado limited_buffer_get...........Añadiendo elemento: %d\n", i);
	}
}

void hilo_consumidor(limited_buffer_t *b) {
	//Llamar REPETICIONES veces a limited_buffer_get mostrando un mensaje con el n�mero le�do
	int i, elem;
	for (i = 0; i < 50; i++) {
		limited_buffer_get(b, &elem);
		printf("Ejecutado limited_buffer_get...........Obtengo elemento: %d\n", elem);
	}
}


int main (void) {

	printf("INICIO DE EJECUCION DE PRACTICA01 - JUAN ANTONIO SILVA LUJAN\n");


	//Definir una variable limited_buffer_t
		limited_buffer_t buffer ;

	//Inicializar el buffer
		limited_buffer_create(&buffer,1);

	//Crear dos vectores idP e idC de tipo pthread_t y de tama�o NUM_HILOS para almacenar los identificadores de los productores y de los consumidores
		pthread_t idP[NUM_HILOS], idC[NUM_HILOS];

	//Lanzar los NUM_HILOS productores y consumidores
	int i;
	for (i = 0; i < 5; i++) {
		pthread_create(&idC[i],NULL,(void *)hilo_consumidor,(void *)&buffer);  //Creo 5 consumidores
		pthread_create(&idP[i],NULL,(void *)hilo_productor,(void *)&buffer);   //Creo 5 productores
	}
	//Esperar a que terminen todos los productores y los consumidores
		//JOIN ?
	for (i = 0; i < 5; i++) {
		pthread_join(idC[i],NULL);
		pthread_join(idP[i],NULL);
	}	
	
	//Destruir el buffer
	limited_buffer_destroy(&buffer);
	return 0;
}


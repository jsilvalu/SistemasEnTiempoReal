/*
 * buffer_acotado.c
 *
 *  Created on: 2 oct. 2019
 *      Author: JUAN ANTONIO SILVA LUJAN
 */
#include "buffer_acotado.h"

void limited_buffer_create  (limited_buffer_t *buffer, int buff_size) {
	//Reservar la memoria para el campo buf del par�metro buffer usando el par�metro buff_size
	buffer->buf = (int *)malloc(sizeof(int)*buff_size);
	//Inicializar los contadores y el tama�o del buffer
	buffer->cuenta = 0;
	buffer->primero = 0;
	buffer->ultimo = 0;
	buffer->tam_buff = buff_size;
	//Inicializar el mutex
	pthread_mutex_init(&buffer->mutex, NULL);
	//Inicializar las variables de condici�n
	pthread_cond_init(&buffer->buffer_no_lleno, NULL);
	pthread_cond_init(&buffer->buffer_no_vacio, NULL);
}

void limited_buffer_destroy (limited_buffer_t  *buffer) {
	//Destruir el mutex
    pthread_mutex_destroy(&buffer->mutex);
	//Destruir las variables de condici�n
	pthread_cond_destroy(&buffer->buffer_no_lleno);
	pthread_cond_destroy(&buffer->buffer_no_vacio);
}

void limited_buffer_put (limited_buffer_t  *buffer, int  elem) {
	//Acceder a la regi�n cr�tica a trav�s del mutex
	pthread_mutex_lock(&buffer->mutex);
	//Mientras el buffer est� lleno, bloquearse en la variable de condici�n lleno
	while (buffer->cuenta == buffer->tam_buff){
		pthread_cond_wait(&buffer->buffer_no_lleno, &buffer->mutex);
	}

	//A�adir elem en el buffer y actualizar cuenta y �ltimo
	 buffer->buf[buffer->ultimo] = elem;
	 buffer->ultimo++;
	 buffer->cuenta++;

	if (buffer->ultimo == buffer->tam_buff) {
		buffer->ultimo = 0;
	}
	

	//Liberar el mutex
	 pthread_mutex_unlock(&buffer->mutex);
	//Hacer un signal en la variable de condici�n vacio
	 pthread_cond_signal(&buffer->buffer_no_vacio);
}

void limited_buffer_get (limited_buffer_t  *buffer, int *elem) {
	//Acceder a la regi�n cr�tica a trav�s del mutex
	pthread_mutex_lock(&buffer->mutex);
	//Mientras el buffer est� vac�o, bloquearse en la variable de condici�n vacio
	while (buffer->cuenta == 0)
		pthread_cond_wait(&buffer->buffer_no_vacio, &buffer->mutex);

	//Guardar en *elem el primer elemento del buffer y actualizar cuenta y primero
	*elem = buffer->buf[buffer->primero];
	buffer->primero++;
	buffer->cuenta--;

	if (buffer->primero == buffer->tam_buff) {
		buffer->primero = 0;
	}
	//Liberar el mutex
	 pthread_mutex_unlock(&buffer->mutex);
	//Hacer un signal en la variable de condici�n lleno
	 pthread_cond_signal(&buffer->buffer_no_lleno);
}




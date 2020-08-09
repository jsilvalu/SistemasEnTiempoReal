/*
 * buffer_acotado.h
 *
 *  Created on: 2 oct. 2019
 *      Author: JUAN ANTONIO SILVA LUJAN
 */
#ifndef BUFFER_ACOTADO_H_
#define BUFFER_ACOTADO_H_

//incluir la librer�a para usar threads
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

typedef struct {
	int *buf;
	int cuenta, primero, ultimo, tam_buff;
	//Definir el mutex
	 pthread_mutex_t mutex;
	//Definir las variables de condici�n lleno y vacio
	 pthread_cond_t buffer_no_lleno;
	 pthread_cond_t buffer_no_vacio;

} limited_buffer_t;

void limited_buffer_create  (limited_buffer_t *buffer, int buff_size);
void limited_buffer_destroy (limited_buffer_t  *buffer);
void limited_buffer_put (limited_buffer_t  *buffer, int  elem);
void limited_buffer_get (limited_buffer_t  *buffer, int *elem);



#endif /* BUFFER_ACOTADO_H_ */

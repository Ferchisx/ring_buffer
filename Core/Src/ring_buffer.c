/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Felipe Fernández
 */


#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *rb, uint8_t * mem_add, uint8_t cap){
	rb->buffer = mem_add;
	rb->capacity = cap;

	ring_buffer_reset(rb);
}

void ring_buffer_write(ring_buffer_t *rb, uint8_t data){
		rb->buffer[rb->head] = data;
		rb->head = rb->head + 1; //los espacios van a ir moviendose

		if(rb->head >= rb->capacity){ //indica el final del recorrido de la cabeza
			rb->head = 0;
		}

		if(rb->is_full != 0){ //si se pierden datos viejos, para que la cola avance
			rb->tail = rb->tail + 1;
		}

		if(rb->tail >= rb->capacity){ //si la cola llega al final de la memoria
			rb->tail = 0; //se reinicia la bandera
		}

		if(rb->head == rb->tail){ //si la cabeza alcanza la cola
			rb->is_full = 1;
		}
}

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *data){
	if((rb->is_full != 0) || (rb->head != rb->tail)){
		*data = rb->buffer[rb->tail];
		rb->tail = rb->tail + 1;
		if(rb->tail >= rb->capacity){
			rb->tail = 0;
		}
		rb->is_full = 0;
		return 1; //buffer con datos
	}
	return 0; //buffer vacío
}

void ring_buffer_reset(ring_buffer_t *rb){
	//Queremos que el valor de la cabeza, cola y que la bandera de llenado queden en 0
	rb->head = 0;
	rb->tail = 0;
	rb->is_full = 0;
}

uint8_t ring_buffer_size(ring_buffer_t *rb){
	uint8_t size = 0;

    if (rb->is_full != 0) {
    	size = rb->capacity; //Si el buffer se encuentra lleno, devuelve esa misma capacidad como tamaño
    }

    if (rb->head >= rb->tail) {
    	size = rb->head - rb->tail;	 //Si la cabeza es mayor o igual a la cola, el tamaño es la diferencia entre ambos,
        							 //ya que no se ha dado la vuelta al buffer
    } else {
    	size = rb->capacity + (rb->head - rb->tail); //Si la cabeza ha dado la vuelta y alcanza la cola, el tamaño será la
        										 	 //capacidad del buffer más la diferencia entre cabeza y cola
    }
    return size;
}

uint8_t ring_buffer_is_full(ring_buffer_t *rb){
	return rb->is_full;
}

uint8_t ring_buffer_is_empty(ring_buffer_t *rb){
	return ((rb->head == rb->tail) && (rb->is_full == 0)) ?1:0;
}

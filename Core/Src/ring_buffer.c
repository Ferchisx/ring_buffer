/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Felipe Fernández
 */


#include "ring_buffer.h"

//para crear la memoria en buffer
#define capacity (10)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full; //bandera que indica cuando el buffer está lleno

void ring_buffer_write(uint8_t data){
		ring_buffer[head_ptr] = data;
		head_ptr = head_ptr + 1; //los espacios van a ir moviendose

		if(head_ptr >= capacity){ //indica el final del recorrido de la cabeza
			head_ptr = 0;
		}

		if(is_full != 0){ //si se pierden datos viejos, para que la cola avance
			tail_ptr = tail_ptr + 1;
		}

		if(tail_ptr >= capacity){ //si la cola llega al final de la memoria
			tail_ptr = 0; //se reinicia la bandera
		}

		if(head_ptr == tail_ptr){ //si la cabeza alcanza la cola
			is_full = 1;
		}
}

uint8_t ring_buffer_read(uint8_t *data){
	if((is_full != 0) || (head_ptr != tail_ptr)){
		*data = ring_buffer[tail_ptr];
		tail_ptr = tail_ptr + 1;
		if(tail_ptr >= capacity){
			tail_ptr = 0;
		}
		is_full = 0;
		return 1; //buffer con datos
	}
	return 0; //buffer vacío
}

void ring_buffer_reset(){
	//Queremos que el valor de la cabeza, cola y que la bandera de llenado queden en 0
	head_ptr = 0;
	tail_ptr = 0;
	is_full = 0;
}

uint8_t ring_buffer_size(void){
	uint8_t size = 0;

    if (is_full != 0) {
    	size = capacity; //Si el buffer se encuentra lleno, devuelve esa misma capacidad como tamaño
    }

    if (head_ptr >= tail_ptr) {
    	size = head_ptr - tail_ptr;	 //Si la cabeza es mayor o igual a la cola, el tamaño es la diferencia entre ambos,
        							 //ya que no se ha dado la vuelta al buffer
    } else {
    	size = capacity + (head_ptr - tail_ptr); //Si la cabeza ha dado la vuelta y alcanza la cola, el tamaño será la
        										 //capacidad del buffer más la diferencia entre cabeza y cola
    }
    return size;
}

uint8_t ring_buffer_is_full(void){
	return is_full;
}

uint8_t ring_buffer_is_empty(void){
	return ((head_ptr == tail_ptr) && (is_full == 0)) ?1:0;
}

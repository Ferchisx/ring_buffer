/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Felipe Fernández
 */


#include "ring_buffer.h"

//para crear la memoria en buffer
#define capacity (8)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full; //bandera que indica cuando el buffer está lleno

uint8_t ring_buffer_size(void){
	uint8_t size = 0;
	if(head_ptr > tail_ptr){
		size = head_ptr - tail_ptr;
	}else{

	}
}
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

uint8_t ring_buffer_read(uint8_t * data){
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

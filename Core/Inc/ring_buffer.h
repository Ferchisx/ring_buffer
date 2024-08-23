/*
 * ring_buffer.h
 *
 *  Created on: Aug 15, 2024
 *      Author: Felipe Fernández
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
uint8_t ring_buffer_size(void);
uint8_t ring_buffer_is_full(void);
uint8_t ring_buffer_is_empty(void);
uint8_t ring_buffer_read(uint8_t * byte);
void ring_buffer_reset();
void ring_buffer_write(uint8_t data);


#endif /* INC_RING_BUFFER_H_ */

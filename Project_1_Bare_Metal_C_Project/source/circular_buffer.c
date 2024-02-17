/**
 * @file: circular_buff.c
 * @brief: functions have been implemented for working with circular buffer
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 * @tools: MCUXpresso IDE and FRDM-KL25Z Development Board
 */

#include "common.h"

/**
 * @brief: initialization function that sets front and rear pointers to 0,
 * items to 0 and sets capacity to the maximum capacity of the buffer
 *
 * @param: pointer to the buffer
 * @return: void
 */
void cbuff_init(cbuff_t *c)
{
	for(int i=0; i < MAX_CAPACITY; i++)
	{
		c->data[i] = '_'; // set all the items as '_' for easy debugging
	}
	c->front = 0; // front is used to read and remove items from the buffer
	c->rear = 0; // rear is used to write items into the buffer
	c->items = 0; // tracks the number of items in the buffer
	c->capacity = MAX_CAPACITY;
}

/**
 * @brief: computes whether the buffer is full or not.
 *
 * @param: pointer to the buffer
 * @return: returns 1 if full and 0 if not
 */
uint8_t ifFull(cbuff_t *c)
{
	if(c->items == MAX_CAPACITY)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

/**
 * @brief: computes whether the buffer is empty or not
 *
 * @param: pointer to the buffer
 * @return: returns 1 if empty and 0 if not
 */
uint8_t ifEmpty(cbuff_t *c)
{
	if(c->items == 0)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

/**
 * @brief: function to return the capacity of the buffer
 *
 * @param: pointer to the buffer
 * @return: returns the capacity of the buffer
 */
size_t cbuff_capacity(cbuff_t *c)
{
	return (c->capacity);
}

size_t cbuff_length(cbuff_t *c)
{
	return (c->items);
}

/**
 * @brief: function to enqueue the elements into the buffer,
 * interrupts are enabled and disabled accordingly to handle the critical sections
 * for the operations to be performed correctly.
 *
 * @param: pointer to the buffer, pointer to the source from where the items are to be
 * enqueued and the number of bytes to be enqueued
 * @return: returns the number of items/elements enqueued
 */
size_t cbuff_enqueue(cbuff_t *c, void *buffer, size_t nbyte)
{
	size_t flag = 0;
	__disable_irq();
	if(ifFull(c))
	{
		__enable_irq();
		return 0;
	}
	else
	{
		while((c->items != c->capacity) && flag < nbyte)
		{
			(c->data[c->rear]) = *(uint8_t *)(buffer++);
			c->items++;
			c->rear = (c->rear + 1) % c->capacity;
			flag++;
		}
	}
	__enable_irq();
	return flag;
}

/**
 * @brief: function to dequeue the elements into the buffer,
 * interrupts are enabled and disabled accordingly to handle the critical sections
 * for the operations to be performed correctly.
 *
 * @param: pointer to the source buffer, destination pointer where the dequeued
 * elements are stored and the number of bytes to be dequeued
 * @return: returns the number of items/elements dequeued
 */
size_t cbuff_dequeue(cbuff_t *c, void *buffer, size_t nbyte)
{
	size_t flag = 0;

	__disable_irq();
	if(ifEmpty(c))
	{
		__enable_irq();
		return 0;
	}
	else
	{
		while((c->items != 0) && flag < nbyte)
		{
			*(uint8_t *)(buffer++) = c->data[c->front];
			c->data[c->front] = '_'; // replacing the dequeued elements with '_' for easy debugging
			c->items--;
			c->front = (c->front + 1) % c->capacity;
			flag++;
		}
	}
	__enable_irq();
	return flag;
}
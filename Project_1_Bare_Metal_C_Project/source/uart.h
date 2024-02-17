/*
 * @file: uart.h
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 */

#ifndef UART_H_
#define UART_H_

#include "common.h"

extern cbuff_t Txbuf, Rxbuf;

// function declarations

void Init_UART0(uint32_t baud_rate);

#endif /* UART_H_ */

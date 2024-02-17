/*
 * @file: systick.h
 *
 * @author: Harshwardhan Singh
 * @date: 13th December 2022
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "common.h"

typedef uint32_t ticktime_t;

// function declarations

void Init_Systick(void);
ticktime_t Now(void);
void Reset_Timer(void);
ticktime_t Get_Timer(void);

#endif /* SYSTICK_H_ */

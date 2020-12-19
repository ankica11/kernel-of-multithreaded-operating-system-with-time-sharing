/*
 * Timer.h
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_TIMER_H_
#define ANAVANOS_TIMER_H_

#include "idle.h"
#include "thread.h"

typedef void interrupt (*pInterrupt)(...); //adresa neke prekidne rutine

class Timer {
public:
	static void inic();
	static void restore();
	static void interrupt timer(...); //nasa nova prekidna rutina
	static volatile int change_context_in_demand;
	static volatile int counter;
	static pInterrupt oldInterruptRoutine;

	static Thread* main;
	static Idle* idle;

};

#endif /* ANAVANOS_TIMER_H_ */

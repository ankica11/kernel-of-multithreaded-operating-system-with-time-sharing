/*
 * Idle.h
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_IDLE_H_
#define ANAVANOS_IDLE_H_

#include "thread.h"

class Idle: public Thread {
public:
	Idle();
	void run();
	void start();
};

#endif /* ANAVANOS_IDLE_H_ */

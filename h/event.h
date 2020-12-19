/*
 * Event.h
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_EVENT_H_
#define ANAVANOS_EVENT_H_

#include "IVTEntry.h"


#define PREPAREENTRY(ivtNo, tocallold) \
void interrupt routine##ivtNo(...); \
IVTEntry entry##ivtNo(ivtNo,routine##ivtNo); \
void interrupt routine##ivtNo(...){ \
if(tocallold) entry##ivtNo.oldInterruptRoutine(); \
entry##ivtNo.signal(); \
}

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo ivtNo);
	virtual ~Event();
	void wait();

protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};

#endif /* ANAVANOS_EVENT_H_ */

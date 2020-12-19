/*
 * Semaphor.cpp
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#include "semaphor.h"
#include "kernSem.h"
#include "thread.h"
#include <iostream.h>

Semaphore::Semaphore(int init) {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	myImpl=new KernelSem(init);

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}

Semaphore::~Semaphore() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	delete myImpl;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}


int  Semaphore::wait(Time maxTimeToWait){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
    //cout<<"semaphore wait\t";
	int ret=myImpl->wait(maxTimeToWait);

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

	return ret;
}



int Semaphore::signal(int n){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	int ret=myImpl->signal(n);

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

	return ret;
}

int Semaphore::val() const{
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	int ret=myImpl->val;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

	return ret;
}





















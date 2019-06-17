/*
 * ace_task_thread_pool.cpp
 *
 *  Created on: 2019年6月17日
 *      Author: bingcod
 */

#include <ace/Task.h>
#include <iostream>
using namespace std;

class MyThreadPools: public ACE_Task<ACE_MT_SYNCH> {
public:
	int open(void*) {
		ACE_DEBUG((LM_DEBUG,"(%t) MyThreadPools task opened. \n"));
		activate(THR_NEW_LWP, 3);
		return 0;
	}
	int svc(void) {
		char buf[512];
		while (true) {
			memset(buf, 0x00, sizeof(buf));
			cin.getline(buf, sizeof(buf));
			cout << "(%t)buf=" << buf << endl;
			if (strcmp(buf, "quit") == 0) {
				break;
			}
		}
		ACE_DEBUG((LM_DEBUG,"(%t) thread do something end. \n"));
		return 0;
	}
	int close(u_long) {
		ACE_DEBUG((LM_DEBUG,"(%t) thread closes down.\n"));
		return 0;
	}
};

int main() {
	ACE_DEBUG((LM_DEBUG,"starting..."));
	MyThreadPools* pools = new MyThreadPools;
	pools->open(NULL);
	ACE_DEBUG((LM_DEBUG,"open..."));
	ACE_Thread_Manager::instance()->wait();
	ACE_DEBUG((LM_DEBUG,"waiting..."));
	return 0;
}


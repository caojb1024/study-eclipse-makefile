/*
 * ace_task_threadmanager.cpp
 *
 *  Created on: 2019年6月15日
 *      Author: bingcod
 */

#include <ace/Thread_Manager.h>

ACE_Thread_Mutex nm, iom;
int n = 0;

static ACE_THR_FUNC_RETURN func(void* arg) {
	while (n < 100) {
		{
			ACE_Guard<ACE_Thread_Mutex> guard(nm);
			++n;
		}
		ACE_OS: sleep(1);
		ACE_Guard<ACE_Thread_Mutex> guard2(iom);
		ACE_DEBUG((LM_DEBUG, "(%t) %d\n", n));

	}
	return 0;
}

int main() {
	ACE_Thread_Manager::instance()->spawn_n(3, func, 0,
	THR_SCOPE_SYSTEM | THR_NEW_LWP);

	ACE_Thread_Manager::instance()->wait();
	return 0;
}


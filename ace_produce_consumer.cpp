/*
 * ace_produce_consumer.cpp
 *
 *  Created on: 2019年6月15日
 *      Author: bingcod
 */

#include <ace/Task.h>
#include <ace/Message_Block.h>
#include <iostream>

const int N = 10;

class Consumer: public ACE_Task<ACE_MT_SYNCH> {
public:
	int open(void*) {
		ACE_DEBUG((LM_DEBUG,"(%t) Consumer task opend.\n"));
		activate(THR_NEW_LWP, 6);
		return 0;
	}
	int svc(void) {
		ACE_Message_Block* mb = 0;
		while (true) {
			mb = 0;
			getq(mb);
			if (*mb->rd_ptr() < N) {
				ACE_DEBUG(
						(LM_DEBUG, "(%t)Got message: %d from remote task\n", *mb->rd_ptr()));
			} else if (*mb->rd_ptr() == N) {
				ACE_DEBUG(
						(LM_DEBUG, "(%t)Got message: %d from remote task\n",*mb->rd_ptr()));
				++*mb->rd_ptr();
				ungetq(mb);
				break;
			} else {
				ungetq(mb);
				break;
			}
		}
		return 0;
	}

	int close(u_long) {
		ACE_DEBUG((LM_DEBUG, "(%t)Consumer closes down.\n"));
		return 0;
	}
};

class Producer: public ACE_Task_Base {
public:
	Producer(Consumer * consumer) :
			data_(0), consumer_(consumer) {
		mb_ = new ACE_Message_Block((char*) &data_, sizeof(data_));
	}
	int open(void*) {
		ACE_DEBUG((LM_DEBUG,"(%t) Producer task opened. \n"));
		activate(THR_NEW_LWP, 2);
		return 0;
	}
	int svc(void) {
		while (data_ <= N) {
			ACE_DEBUG(
					(LM_DEBUG,"(%t) Sending message: %d to remote task \n",data_));
			consumer_->putq(mb_);
			ACE_OS: sleep(1);
			++data_;
		}
		return 0;
	}
	int close(u_long) {
		ACE_DEBUG((LM_DEBUG,"(%t) Producer closes down.\n"));
		return 0;
	}
private:
	char data_;
	Consumer* consumer_;
	ACE_Message_Block* mb_;

};

int main() {
	Consumer* consumer = new Consumer;
	Producer* producer = new Producer(consumer);
	producer->open(NULL);
	consumer->open(NULL);
	ACE_Thread_Manager::instance()->wait();
	return 0;
}


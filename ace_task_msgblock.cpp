/*
 * ace_task_msgblock.cpp
 *
 *  Created on: 2019年6月15日
 *      Author: bingcod
 */

#include <iostream>
#include <ace/Message_Block.h>
#include <ace/ACE.h>
#include <ace/Log_Msg.h>

int main() {

	ACE_Message_Block* head = new ACE_Message_Block(8);
	ACE_Message_Block* input = head;

	int exe_num = 0;
	while (true) {
		ssize_t nbytes = ACE::read_n(ACE_STDIN, input->wr_ptr(), input->size());
		if (nbytes <= 0) {
			break;
		}
		input->wr_ptr(nbytes);
		input->cont(new ACE_Message_Block(8));
		input->cont();
		if (++exe_num > 3) {
			break;
		}
	}
	std::cout << "execute outputing ..." << std::endl;
	int i = 1;
	for (input = head; input != 0; input = input->cont()) {
		ACE_DEBUG((LM_DEBUG,"\n%dth message:",i++));
		ACE::write_n(ACE_STDOUT, input->rd_ptr(), input->length());
	}
	head->release();
	return 0;

}


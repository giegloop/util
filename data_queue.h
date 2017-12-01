//
// Created by hujianzhe on 16-5-2.
//

#ifndef UTIL_DATA_QUEUE_H
#define UTIL_DATA_QUEUE_H

#include "syslib/error.h"
#include "syslib/ipc.h"
#include "datastruct/list.h"

namespace Util {
class DataQueue {
public:
	DataQueue(void(*deleter)(list_node_t*) = NULL);
	virtual ~DataQueue(void);

	void push(list_node_t* data);
	list_node_t* pop(int msec, size_t expect_cnt = ~0);

	void weakup(void);

private:
	CSLOCK m_cslock;
	CONDITION m_condition;
	list_node_t *m_head, *m_tail;
	bool m_forcewakeup;
	void(*m_deleter)(list_node_t*);
};
}

#endif

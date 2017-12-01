//
// Created by hujianzhe on 16-8-17.
//

#ifndef	UTIL_NIO_NIO_OBJECT_MANAGER_H
#define	UTIL_NIO_NIO_OBJECT_MANAGER_H

#include "../syslib/io.h"
#include "../syslib/ipc.h"
#include "../datastruct/list.h"
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Util {
class NioObject;
class NioObjectManager {
public:
	NioObjectManager(void);
	~NioObjectManager(void);

	REACTOR* getReactor(void);

	size_t count(void);
	void get(std::list<std::shared_ptr<NioObject> >& l);
	void get(std::vector<std::shared_ptr<NioObject> >& v);
	bool add(const std::shared_ptr<NioObject>& object);
	bool del(const std::shared_ptr<NioObject>& object);

	size_t checkObjectValid(void);

public:
	struct NioEvent {
		list_node_t list_node;
		std::shared_ptr<NioObject> obj;
		int event;
		void* ol;

		NioEvent(const std::shared_ptr<NioObject>& obj_, int event_, void* ol_) :
			obj(obj_),
			event(event_),
			ol(ol_)
		{
			list_node_init(&list_node);
		}
	};

	int wait(NIO_EVENT* e, int n, int msec);
	list_node_t* result(NIO_EVENT* e, int n);
	void exec(struct NioEvent* objev);

private:
	NioObjectManager(const NioObjectManager& o);
	NioObjectManager& operator=(const NioObjectManager& o);

private:
	REACTOR m_reactor;
	//
	RWLOCK m_validLock;
	std::unordered_map<FD_HANDLE, std::shared_ptr<NioObject> > m_validObjects;
};
}

#endif //UTIL_NIO_OBJECT_MANAGER_H

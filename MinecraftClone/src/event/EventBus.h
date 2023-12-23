#pragma once

#include <map>
#include <typeindex>
#include <list>

#include "HandlerFunctionBase.h"
#include "MemberFunctionHandler.h"

using HandlerList = std::list<HandlerFunctionBase*>;

class EventBus {
public:
	template<class EventT>
	void publish(EventT* event) {
		HandlerList* handlers = subscribers[typeid(EventT)];
		if (handlers == nullptr)
			return;
		
		for (auto& handler: *handlers) {
			if (handler != nullptr) {
				handler->exec(event);
			}
		}

		delete event;
	}

	template<class T, class EventT>
	void subscribe(T* instance, void (T::* memberFunction)(EventT*)) {
		HandlerList* handlers = subscribers[typeid(EventT)];

		if (handlers == nullptr) {
			handlers = new HandlerList();
			subscribers[typeid(EventT)] = handlers;
		}

		handlers->push_back(new MemberFunctionHandler<T, EventT>(instance, memberFunction));
	}



private:
	std::map<std::type_index, HandlerList*> subscribers;
};
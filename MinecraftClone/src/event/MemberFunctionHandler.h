#pragma once

#include "HandlerFunctionBase.h"

template<class T, class EventT>
class MemberFunctionHandler : public HandlerFunctionBase {
public:
	typedef void (T::* MemberFunction)(EventT*);

	MemberFunctionHandler(T* instance, MemberFunction mFunc) : instance(instance), function(mFunc) {}
	
	void call(Event* event) {
		(instance->*function)(static_cast<EventT*>(event));
	}

private:
	T* instance;
	MemberFunction function;
};
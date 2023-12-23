#include "Entity.h"

Entity::~Entity() {
	for (const auto& kv: components) {
		delete kv.second;
	}
}

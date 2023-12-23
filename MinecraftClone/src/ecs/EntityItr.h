#pragma once

#include <vector>

#include "Entity.h"

#include <game/Game.h>



template <class... Args>
class EntityItr {
public:
    EntityItr(std::vector<Entity*> entities = Game::instance().getCurrentScene().entities,
        int i = 0) : entities(entities), i(i) {
    }

    ~EntityItr() {}

    /*std::vector<Entity&> makeEntityArray() {
        std::vector<Entity&> entityArray;
        for (Entity& entity : this) {
            entityArray.push_back(entity);
        }

        return entityArray;
    }*/

    bool operator!=(EntityItr rhs) {
        return i != rhs.i;
    }

    Entity& operator*() {
        return *entities[i];
    }

    void operator++() {
        ++i;
        incrementIf();
    }

    EntityItr operator+(int rhs) {
        EntityItr itr = EntityItr(entities, i + 1);
        itr.incrementIf();
        return itr;
    }

    void incrementIf() {
        while (i < entities.size() && !entities[i]->hasComponent<Args...>()) {
            ++i;
        }
    }

    EntityItr begin() {
        incrementIf();
        return EntityItr(entities, i);
    }
    EntityItr end() {
        return EntityItr(entities, entities.size());
    }

private:
    int i;
	std::vector<Entity*> entities;
};
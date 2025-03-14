

#include "scene.h"

void Scene::addObject(std::unique_ptr<Renderable> object) {
    objects.push_back(std::move(object));
}

void Scene::render() const {
    for (const auto& object : objects) {
        if (object) {
            object->render();
        }
    }
}
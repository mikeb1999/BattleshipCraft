

#pragma once
#include <memory>
#include <vector>

class Renderable {
public:
    virtual void render() const = 0;
    virtual ~Renderable() = default;
};

class Scene {
public:
    void addObject(std::unique_ptr<Renderable> object);
    void render() const;

private:
    std::vector<std::unique_ptr<Renderable>> objects;
};
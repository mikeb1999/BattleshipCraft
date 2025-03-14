

#pragma once
#include <GL/glew.h>

class GameObject {
public:
    virtual void render() const = 0;
    virtual void update() {}
    virtual ~GameObject() = default;
};

class Ground : public GameObject {
public:
    Ground();
    void render() const override;
    void update() override {}
};

class Skybox : public GameObject {
public:
    Skybox();
    void render() const override;
    void update() override {}
};


#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "Camera.h"

class CoordinateSystem {
public:
    static void globalToLocal(const Camera& camera, float globalX, float globalY, float globalZ,
        float& localX, float& localY, float& localZ);

    static void localToGlobal(const Camera& camera, float localX, float localY, float localZ,
        float& globalX, float& globalY, float& globalZ);
};

#endif
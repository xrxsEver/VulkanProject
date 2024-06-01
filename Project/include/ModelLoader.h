#pragma once

#include "Vertex.h"
#include <vector>
#include <string>

class ModelLoader {
public:
    static bool loadOBJ(const std::string& filename, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};


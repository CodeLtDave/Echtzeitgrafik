#include <filesystem>
#include "helper/RootDir.h"

const std::filesystem::path root = std::filesystem::path(ROOT_DIR);
static const std::filesystem::path VERTEX_SHADER_PATH = root / "res" / "shader.vert";
static const std::filesystem::path FRAGMENT_SHADER_PATH = root / "res" / "shader.frag";

GLfloat triangle[] =
{
    /*   Positions            Colors */
         0.9f, -0.9f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,
         0.0f,  0.9f, 0.0f,   0.0f, 0.0f, 1.0f
};
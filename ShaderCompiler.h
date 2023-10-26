#pragma once
#include "GLFW/glfw3.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int CreateShaderProgram(GLenum type1, std::filesystem::path path1, GLenum type2 = NULL, std::filesystem::path path2 = "");
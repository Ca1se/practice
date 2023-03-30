#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace tputil
{

GLFWwindow* initGl(const std::string& title, int32_t width, int32_t height);

}  // namespace tputil
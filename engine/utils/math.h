#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

const glm::vec3 vec3_zero = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 vec3_one = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 vec3_left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 vec3_right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 vec3_up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 vec3_down = glm::vec3(0.0f, -1.0f, 0.0f);
const glm::vec3 vec3_back = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 vec3_forward = glm::vec3(0.0f, 0.0f, 1.0f);
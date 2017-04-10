#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <algorithm>

const glm::vec3 vec3_zero = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 vec3_one = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 vec3_left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 vec3_right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 vec3_up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 vec3_down = glm::vec3(0.0f, -1.0f, 0.0f);
const glm::vec3 vec3_back = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 vec3_forward = glm::vec3(0.0f, 0.0f, 1.0f);

namespace math {
	inline float Lerp(float a, float b, float t) {
		return (1.0f - t) * a + b * t;
	}

	inline glm::vec3 Lerp(glm::vec3& a, glm::vec3& b, float t) {
		glm::vec3 result;
		for (int i = 0; i < 3; i++) {
			result[i] = Lerp(a[i], b[i], t);
		}
		return result;
	}

	template <typename T>
	inline T Clamp(const T& val, const T& min, const T& max) {
		return std::max(min, std::min(val, max));
	}

	template <typename T>
	inline T Clamp01(const T& val) {
		return Clamp<T>(val, 0.0f, 1.0f);
	}
}
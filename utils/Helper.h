#pragma once

# include <iostream>	
# include <string>
# include <glm/gtc/quaternion.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/constants.hpp>
namespace Helper
{
	void log_error(const char* msg);
	void log_error(const std::string msg);
	glm::quat computeOrienQuatFromOrienVec(const glm::vec3 &orien);
	glm::vec3 computeOrienVecFromOrienQuat(const glm::quat &qorien);
	glm::quat computeRotationFromTwoVectors(const glm::vec3 &start, const glm::vec3 &end);
	glm::vec3 computeRotationAppliedOrienVec(const glm::vec3 &orientation);
	glm::quat computeRotationBetweenVectors(glm::vec3 start, glm::vec3 end);

}
# include "Helper.h"


namespace Helper
{
	void log_error(const char* msg)
	{
		fprintf(stderr, "Error : %s\n", msg);
		exit(-1);
	}
	void log_error(const std::string msg)
	{
		fprintf(stderr, "Error : %s\n", msg);
		exit(-1);
	}

	glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 end)
	{
		start = glm::normalize(start);
		end = glm::normalize(end);
		float cosTheta = glm::dot(start, end);
		glm::vec3 rotationAxis;
		// if 
		if (cosTheta < -1 + 0.001f) {
			rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
			if (glm::length(rotationAxis) < 0.01)
				rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
			rotationAxis = normalize(rotationAxis);
			return glm::angleAxis(180.0f, rotationAxis);
		}
		rotationAxis = cross(start, end);
		float angle = glm::acos(cosTheta);
		return angleAxis(angle, rotationAxis);
	}

	// Assume rotation angle is radian.
	glm::quat computeRotationQuat(float rotationAngle, glm::vec3 rotaxis)
	{
		return glm::angleAxis(glm::degrees(rotationAngle), rotaxis);
	}

	// cumulate rotation, combine rotation.
	glm::quat cumulateRotation(const glm::quat &rot_first, const glm::quat &rot_second)
	{
		return rot_second * rot_first;
	}

	// glm mix call slerp
	glm::quat interpolateTwoQuat(const glm::quat &q1, const glm::quat &q2, float mixratio)
	{
		return glm::mix(q1, q2, mixratio);
	}


	/*
	This function return rotation quaternion between two vector from start to end orientation.
	*/
	glm::quat computeRotationFromTwoVectors(const glm::vec3 &start, const glm::vec3 &end)
	{
		glm::vec3 w = glm::cross(glm::normalize(start), glm::normalize(end));
		glm::quat q = glm::quat(glm::dot(start, end), w.x, w.y, w.z);
		q.w += glm::sqrt(q.x*q.x + q.w*q.w + q.y*q.y + q.z*q.z);
		return glm::normalize(q); // Project to unit 4-dimension sphere.
	}

	/*
	This function return orientation that applied rotation for given orientation.
	*/

	
}
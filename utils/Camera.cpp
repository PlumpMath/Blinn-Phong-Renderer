# include "Camera.h"

void Camera::printInfo()
{
	std::cout << "Camera info" << std::endl;
	std::cout << "position : " << position.x <<","<< position.y << ","<< position.z <<std::endl;
	std::cout << "lookat_position : " << lookat_position.x << "," << lookat_position.y << "," << lookat_position.z << std::endl;
	std::cout << "orientation : " << head_orientation.x << "," << head_orientation.y << "," << head_orientation.z << std::endl;
	std::cout << "upvector : " << upvector.x << "," << upvector.y << "," << upvector.z << std::endl;
	std::cout << "rightvector : " << rightvector.x << "," << rightvector.y << "," << rightvector.z << std::endl;
	std::cout << "move_speed : " << move_speed << std::endl;
	std::cout << "rot_speed : " << rot_speed << std::endl;
	std::cout << "SCREEN_WIDTH : " << SCREEN_WIDTH << std::endl;
	std::cout << "SCREEN_HIEHT : " << SCREEN_HIEHT << std::endl;
	std::cout << "near_plane : " << near_plane << std::endl;
	std::cout << "far_plane : " << far_plane << std::endl;
	std::cout << "aspect_ratio : " << aspect_ratio << std::endl;
	std::cout << "FOV : " << FOV << std::endl;
	std::cout << "zoom : " << zoom << std::endl;
}

/*Zoom in/Zoom out*/
void Camera::zoomIn()
{
	FOV -= 1;
	zoom = 1.0 / glm::tan(FOV / 2.0);
}

void Camera::zoomOut()
{
	FOV += 1;
	zoom = 1.0 / glm::tan(FOV / 2.0);
}

void Camera::move(CameraMoveDirection dir)
{
	switch (dir)
	{
	case CameraMoveDirection::UP:
		position += dt * move_speed * upvector;
		break;
	case CameraMoveDirection::DOWN:
		position -= dt * move_speed * upvector;
		break;
	case CameraMoveDirection::LEFT:
		position -= dt * move_speed * rightvector;
		break;
	case CameraMoveDirection::RIGHT:
		position += dt * move_speed * rightvector;
		break;
	case CameraMoveDirection::FORWARD:
		position += dt * move_speed * head_orientation;
		break;
	case CameraMoveDirection::BACK:
		position -= dt * move_speed * head_orientation;
		break;
	default:
		break;
	}
}
glm::quat Camera::computeHead2TargetRotation(const glm::vec3 &target)
{
	glm::vec3 start = glm::normalize(head_orientation);
	glm::vec3 end = glm::normalize(target);

	float cosTheta = glm::dot(start, end);
	glm::vec3 rotationAxis;
	// if start and end vector is parallel
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

void Camera::rotate(const glm::vec3 &target_orien)
{
	glm::quat rotation_quat = computeHead2TargetRotation(target_orien);
	glm::vec3 local_lookat_position = lookat_position - position;
	local_lookat_position = dt * rot_speed * rotation_quat * local_lookat_position;
	lookat_position = local_lookat_position + position;
	head_orientation = glm::normalize(lookat_position - position);
	upvector = rotation_quat * upvector;
	rightvector = rotation_quat * rightvector;
}

void Camera::update(const GLfloat delta_time)
{
	dt = delta_time;
	if (ptype == CameraProjectionType::ORTHO)
		projection = glm::ortho(-1.5f * float(aspect_ratio), 1.5f * float(aspect_ratio), -1.5f, 1.5f, -10.0f, 10.f);
	else if (ptype == CameraProjectionType::PROJECT)
		projection = glm::perspective(FOV, aspect_ratio, near_plane, far_plane);

	view = glm::lookAt(position, lookat_position, upvector);
	model = glm::mat4(1.0f);
	MVP = projection * view * model;
}
# include "Camera.h"
void Camera::rotate(const glm::vec3 &target_orien)
{
	
}

void Camera::printInfo()
{
	std::cout << "Camera info" << std::endl;
	std::cout << "position : " << position.x <<","<< position.y << ","<< position.z <<std::endl;
	std::cout << "lookat_position : " << lookat_position.x << "," << lookat_position.y << "," << lookat_position.z << std::endl;
	std::cout << "orientation : " << orientation.x << "," << orientation.y << "," << orientation.z << std::endl;
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

// simple translations
void Camera::move(const glm::vec3 delta)
{
	position = position + delta;
	lookat_position = lookat_position + delta;
}
void Camera::moveDown(const GLfloat dt)
{
	glm::vec3 delta = - dt * move_speed * upvector;
	move(delta);
}

void Camera::moveUp(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * upvector;
	move(delta);
}

void Camera::moveForward(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * orientation;
	move(delta);
}

void Camera::moveBackward(const GLfloat dt)
{
	glm::vec3 delta = -dt * move_speed * orientation;
	move(delta);
}

void Camera::moveRight(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * rightvector;
	move(delta);
}

void Camera::moveLeft(const GLfloat dt)
{
	glm::vec3 delta = - dt * move_speed * rightvector;
	move(delta);
}
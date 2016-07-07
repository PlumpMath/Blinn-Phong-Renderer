# include "Camera.h"
void Camera::rotate(const glm::vec3 &target_orien)
{
	
}

void Camera::moveDown(const GLfloat dt)
{
	glm::vec3 delta = - dt * move_speed * upvector;
	position = position + delta;

}

void Camera::moveUp(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * upvector;
	position = position + delta;

}

void Camera::moveForward(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * orientation;
	position = position + delta;

}

void Camera::moveBackward(const GLfloat dt)
{
	glm::vec3 delta = -dt * move_speed * orientation;
	position = position + delta;

}

void Camera::moveRight(const GLfloat dt)
{
	glm::vec3 delta = dt * move_speed * rightvector;
	position = position + delta;
}

void Camera::moveLeft(const GLfloat dt)
{
	glm::vec3 delta = - dt * move_speed * rightvector;
	position = position + delta;
}
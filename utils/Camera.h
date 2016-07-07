#pragma once
#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Camera
{
public:
	Camera() {}
	~Camera() {}
	
	void moveDown(const GLfloat dt);
	void moveUp(const GLfloat dt);
	void moveForward(const GLfloat dt);									/*Dolly in*/
	void moveBackward(const GLfloat dt);									/*Dolly out*/
	void moveRight(const GLfloat dt);									/*panning*/
	void moveLeft(const GLfloat dt);										/*panning*/
	void zoomIn();														/*Camera FOV*/
	void zoomOut();														/*Camera FOV*/
	void rotate(const glm::vec3 &target_orien);


private:
	/*Physical parameters*/
	glm::vec3 position = glm::vec3(0,0,-5);
	glm::vec3 lookat_position = glm::vec3(0,0,0);
	glm::vec3 orientation = glm::normalize(lookat_position - position); // forward vector
	glm::vec3 upvector = glm::vec3(0,1,0);
	glm::vec3 rightvector = glm::normalize(glm::cross(orientation, upvector));
	GLfloat move_speed = 10.0;
	GLfloat rot_speed = 5.0;


	/*Image plane parameters*/
	GLuint SCREEN_WIDTH = 1280;
	GLuint SCREEN_HIEHT = 720;
	GLfloat near_plane = 0.2f;
	GLfloat far_plane = 120.0f;
	GLfloat aspect_ratio = SCREEN_WIDTH/SCREEN_HIEHT;
	GLfloat FOV = 45.0f;
};
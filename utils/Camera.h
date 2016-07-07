#pragma once
#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Camera
{
public:
	Camera() {}
	~Camera() {}
	
	void moveForward(const GLfloat dt);									/*Dolly in*/
	void moveBackward(const GLfloat dt);												/*Dolly out*/
	void moveRight(const GLfloat dt);													/*panning*/
	void moveLeft(const GLfloat dt);													/*panning*/
	void zoomIn();														/*Camera FOV*/
	void zoomOut();														/*Camera FOV*/
	void rotation(glm::vec3 &orien_start, glm::vec3 &orien_end);


private:
	/*Physical parameters*/
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 upvector;
	GLfloat move_speed;
	GLfloat rot_speed;


	/*Image plane parameters*/
	GLuint SCREEN_WIDTH = 1280;
	GLuint SCREEN_HIEHT = 720;
	GLfloat near_plane = 0.2f;
	GLfloat far_plane = 120.0f;
	GLfloat aspect_ratio = SCREEN_WIDTH/SCREEN_HIEHT;
	GLfloat FOV = 45.0f;


};
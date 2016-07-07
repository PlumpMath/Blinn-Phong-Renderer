#pragma once
#include <iostream>
#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>




class Camera
{
public:
	Camera() {}
	~Camera() {}
	
	/*Basic translation, rotation and zoom in zoom out*/
	void move(const glm::vec3 delta);
	void moveDown(const GLfloat dt);
	void moveUp(const GLfloat dt);
	void moveForward(const GLfloat dt);									/*Dolly in*/
	void moveBackward(const GLfloat dt);									/*Dolly out*/
	void moveRight(const GLfloat dt);									/*panning*/
	void moveLeft(const GLfloat dt);										/*panning*/
	void rotate(const glm::vec3 &target_orien);
	void zoomIn();														/*Camera FOV*/
	void zoomOut();														/*Camera FOV*/
	
	/*Update OpenGL*/

	/*Calc matricies*/

	/*Camera info*/
	void printInfo();
private:
	/*Physical parameters*/
	glm::vec3 position = glm::vec3(0,0,-5);
	glm::vec3 lookat_position = glm::vec3(0,0,0);
	glm::vec3 orientation = glm::normalize(lookat_position - position); // forward vector
	glm::vec3 upvector = glm::vec3(0,1,0);
	glm::vec3 rightvector = glm::normalize(glm::cross(orientation, upvector));

	GLfloat move_speed = 0.01;
	GLfloat rot_speed = 0.01;

	/*Image plane parameters*/
	GLuint SCREEN_WIDTH = 1280;
	GLuint SCREEN_HIEHT = 720;
	GLfloat near_plane = 0.2f;
	GLfloat far_plane = 120.0f;
	GLfloat aspect_ratio = SCREEN_WIDTH/SCREEN_HIEHT;
	GLfloat FOV = 90.0f; //unit is degree, 90 degree fov means zoom = 1
	GLfloat zoom = 1.0 / glm::tan(FOV / 2.0);

	/*Set of matrix*/
};
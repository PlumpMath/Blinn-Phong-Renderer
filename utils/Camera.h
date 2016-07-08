#pragma once
#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

extern enum class CameraProjectionType	{ORTHO, PROJECT};
extern enum class CameraMoveDirection	{UP, DOWN, LEFT, RIGHT, FORWARD, BACK};

/*First Person Camera (FPS camera)*/
class Camera
{
public:
	Camera() {}
	~Camera() {}
	
	/*Basic translation, rotation and zoom in zoom out*/
	void move(CameraMoveDirection dir);						
	void rotate(const glm::vec3 &target_orien);
	void zoomIn();														/*Change Camera FOV*/
	void zoomOut();														/*Change Camera FOV*/
	
	/*Update OpenGL*/
	void update(const GLfloat delta_time);

	/*Camera info*/
	void printInfo();
private:
	/*Private methods*/
	glm::quat computeHead2TargetRotation(const glm::vec3 &target);


	glm::vec3 position = glm::vec3(0,0,-5);
	glm::vec3 lookat_position = glm::vec3(0,0,0);
	glm::vec3 head_orientation = glm::normalize(lookat_position - position); // forward vector
	glm::vec3 upvector = glm::vec3(0,1,0);
	glm::vec3 rightvector = glm::normalize(glm::cross(head_orientation, upvector));

	GLfloat dt;
	GLfloat move_speed = 0.01;
	GLfloat rot_speed = 0.01;
	GLuint SCREEN_WIDTH = 1280;
	GLuint SCREEN_HIEHT = 720;
	GLfloat near_plane = 0.2f;
	GLfloat far_plane = 120.0f;
	GLfloat aspect_ratio = SCREEN_WIDTH/SCREEN_HIEHT;
	GLfloat FOV = 90.0f; //unit is degree, 90 degree fov means zoom = 1
	GLfloat zoom = 1.0 / glm::tan(FOV / 2.0);

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;

	CameraProjectionType ptype = CameraProjectionType::PROJECT;
};
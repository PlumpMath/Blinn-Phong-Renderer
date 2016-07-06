#pragma once
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <iostream>
#include <GL/gl3w.h>
#include <TOBJ/tiny_obj_loader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Helper.h"


class Obj
{
	/*Constructors*/
	Obj() {};
	Obj(const std::string &_p);
	void draw(GLuint vao);
	
private:
	std::vector<GLuint> position_buffers;
	std::vector<GLuint> normal_buffers;
	std::vector<GLuint> texcoord_buffers;
	std::vector<GLuint> indicies_buffers;
	std::vector<GLuint> material_buffers;

	std::string path;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	void upload2GPU();
};




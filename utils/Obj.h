#pragma once
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <iostream>
#include <TOBJ/tiny_obj_loader.h>
#include <GLFW/glfw3.h>

class Obj
{
	Obj() {};
	Obj(const std::string &_p)
		:path(_p)
	{
		std::string err;
		bool ret = tinyobj::LoadObj(shapes, materials, err, path.c_str());
		if (!err.empty()) { // `err` may contain warning message.
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}
		std::cout << "Load Obj : " << path << std::endl;
		std::cout << "# of shapes    : " << shapes.size() << std::endl;
		std::cout << "# of materials : " << materials.size() << std::endl;
	}
private:
	GLuint id;
	std::string path;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
};


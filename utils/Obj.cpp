# include "Obj.h"

Obj::Obj(const std::string &_p)
	:path(_p)
{
	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, path.c_str());
	if (!err.empty()) { // `err` may contain warning message.
		Helper::log_error(err);
	}

	if (!ret) {
		exit(1);
	}
	std::cout << "Load Obj : " << path << std::endl;
	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;
}

void Obj::upload2GPU()
{
	const int numbBuffer = shapes.size();
	/* Upload position data */
	for (size_t i = 0; i < numbBuffer; i++)
	{
		GLuint temp;
		size_t numb = shapes[i].mesh.positions.size();
		glGenVertexArrays(1, &temp);
		glBindBuffer(GL_ARRAY_BUFFER, temp);
		glBufferData(GL_ARRAY_BUFFER, numb * sizeof(float), &shapes[i].mesh.positions[0], GL_STATIC_DRAW);
		position_buffers.push_back(temp);
	}

	/* Upload normal data */
	for (size_t i = 0; i < numbBuffer; i++)
	{
		GLuint temp;
		size_t numb = shapes[i].mesh.normals.size();
		glGenVertexArrays(1, &temp);
		glBindBuffer(GL_ARRAY_BUFFER, temp);
		glBufferData(GL_ARRAY_BUFFER, numb * sizeof(float), &shapes[i].mesh.normals[0], GL_STATIC_DRAW);
		normal_buffers.push_back(temp);
	}
	/* Upload texcoord data */
	for (size_t i = 0; i < numbBuffer; i++)
	{
		GLuint temp;
		size_t numb = shapes[i].mesh.texcoords.size();
		glGenVertexArrays(1, &temp);
		glBindBuffer(GL_ARRAY_BUFFER, temp);
		glBufferData(GL_ARRAY_BUFFER, numb * sizeof(float), &shapes[i].mesh.texcoords[0], GL_STATIC_DRAW);
		texcoord_buffers.push_back(temp);
	}

	/* Upload indicies data */
	for (size_t i = 0; i < numbBuffer; i++)
	{
		GLuint temp;
		size_t numb = shapes[i].mesh.indices.size();
		glGenVertexArrays(1, &temp);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numb * sizeof(unsigned int), &shapes[i].mesh.indices[0], GL_STATIC_DRAW);
		indicies_buffers.push_back(temp);
	}
}
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
	upload2GPU();
	
}

void Obj::createVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	const int pos_attrib = 0;
	const int nor_attrib = 1;
	const int tex_attrib = 2;

	// Enable my attributes
	glEnableVertexAttribArray(pos_attrib);
	glEnableVertexAttribArray(nor_attrib);
	glEnableVertexAttribArray(tex_attrib);

	// Set up the formats for my attributes
	glVertexAttribFormat(pos_attrib, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribFormat(nor_attrib, 3, GL_FLOAT, GL_FALSE, 12);
	glVertexAttribFormat(tex_attrib, 2, GL_FLOAT, GL_FALSE, 24);
	glBindVertexArray(0);
}

void Obj::draw(GLuint program)
{
	glBindVertexArray(vao);
	const int pos_attrib = 0;
	const int nor_attrib = 1;
	const int tex_attrib = 2;
	// Set up binding points for all attrib
	// Binding index = The index of the vertex buffer binding with which to associate the generic vertex attribute.
	for (size_t i = 0; i < shapes.size(); i++)
	{
		glVertexAttribBinding(pos_attrib, position_buffers[i]);
		glVertexAttribBinding(nor_attrib, normal_buffers[i]);
		glVertexAttribBinding(tex_attrib, texcoord_buffers[i]);
		glUseProgram(program);
	}

	glBindVertexArray(0);
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
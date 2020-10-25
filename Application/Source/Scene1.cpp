#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// generate buffers for triangle 1
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	// an array of 3 vectors which represents 3	vertices
	static const GLfloat vertex_buffer_data[] = {
		-0.25f, 1.0f, 0.0f,
		0.25f, 1.0f, 0.0f,
		-0.75f, 0.5f, 0.0f,
		0.75f, 0.5f, 0.0f,
		-0.75f, -0.25f, 0.0f,
		0.75f, -0.25f, 0.0f,
		-0.25f, -0.75f, 0.0f,
		0.25f, -0.75f, 0.0f,
	};
	// an array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	static const GLfloat vertex_buffer_data1[] = {
		0.0f, 1.0f, -0.1f,
		-0.25f, -0.75f, -0.1f,
		0.1f, -0.1f, -0.1f,
	};
	static const GLfloat color_buffer_data1[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	static const GLfloat vertex_buffer_data2[] = {
		0.0f, 1.0f, -0.1f,
		0.25f, -0.75f, -0.1f,
		-0.1f, -0.1f, -0.1f,
	};
	static const GLfloat color_buffer_data2[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	static const GLfloat vertex_buffer_data3[] = {
		-0.75f, 0.25f, -0.1f,
		0.75f, 0.25f, -0.1f,
		0.0f, -0.1f, -0.1f,
	};
	static const GLfloat color_buffer_data3[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	static const GLfloat vertex_buffer_data4[] = {
		-0.15f, -0.1f, -0.2f,
		0.15f, 0.2f, -0.2f,
		0.05f, -0.1f, -0.2f,
	};
	static const GLfloat color_buffer_data4[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	static const GLfloat vertex_buffer_data5[] = {
		0.15f, -0.1f, -0.2f,
		-0.15f, 0.25f, -0.2f,
		-0.05f, -0.1f, -0.2f,
	};
	static const GLfloat color_buffer_data5[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//static const GLfloat vertex_buffer_data1[] = {
	//	0.0f, 0.0f, 0.0f, // vertex 0 of triangle
	//	1.0f, 1.0f, 0.0f, // vertex 1 of triangle
	//	1.0f, -1.0f, 0.0f, // vertex 2 of triangle
	//};

	//static const GLfloat color_buffer_data1[] = {
	//	1.0f, 1.0f, 0.0f, // color of vertex 0
	//	1.0f, 1.0f, 0.0f, // color of vertex 1
	//	1.0f, 1.0f, 0.0f, // color of vertex 2
	//};
	
	//OCTAGON
	// set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_OCTAGON]);
	// transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	// set buffer for colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_OCTAGON]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//STAR
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);
	}

	// MYSHAPE
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MYSHAPE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MYSHAPE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MYSHAPE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5), vertex_buffer_data5, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MYSHAPE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5), color_buffer_data5, GL_STATIC_DRAW);


	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);

	//// set buffer for colors
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);

	// load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
	);
	// use our shader
	glUseProgram(m_programID);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here

	// clear color buffer every frame
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_OCTAGON]);
	glVertexAttribPointer(
		0, // attribute 0. must match the layout in the shader. usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		0 // array buffer
	);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_OCTAGON]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); // starting from vertex 0; 3 vertices = 1 triangle

	{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MYSHAPE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MYSHAPE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MYSHAPE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MYSHAPE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(0);


}

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

}

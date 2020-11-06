#include "Scene3.h"
#include "GL\glew.h"
#include "GLFW/glfw3native.h"
#include "Mtx44.h"
#include "Application.h"

#include "shader.hpp"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	rotateAngle = 0;
	translateY = 0;
	translateX = 6;
	randomY = 0;
	randomX = 0;
	scaleAll = 0;

	// Init VBO here

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// generate buffers for triangle 1
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//Right angled triangle
	static const GLfloat vertex_buffer_data[] = {
		-1.0f, 0.0f, 0.0f,
		-1.0f, 2.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	static const GLfloat color_buffer_data[] = {
		0.6f, 0.9f, 1.0f,
		0.1f, 0.1f, 1.0f,
		0.6f, 0.9f, 1.0f,
	};
	//equilateral
	static const GLfloat vertex_buffer_data1[] = {
		0.0f, 2.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	static const GLfloat color_buffer_data1[] = {
		1.0f, 1.0f, 0.6f,
		0.5f, 0.5f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	//isoceles
	static const GLfloat vertex_buffer_data2[] = {
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	static const GLfloat color_buffer_data2[] = {
		0.0f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//square
	static const GLfloat vertex_buffer_data3[] = {
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,

	};
	static const GLfloat color_buffer_data3[] = {
		0.2f, 0.05f, 0.03f,
		0.2f, 0.05f, 0.03f,
		0.54f, 0.27f, 0.0745f,
		0.54f, 0.27f, 0.0745f,
	};

	//circle
	static GLfloat vertex_buffer_data4[360] = { 0.0f, };
	static GLfloat color_buffer_data4[360] = { 0.0f, };

	int num = 0;
	int radius = 2;
	for (GLfloat i = 0; i < 2 * 3.14159265359; i += 2 * 3.14159265359 / 64) {
		int currentx = num++;
		int currenty = num++;
		int currentz = num++;

		vertex_buffer_data4[currentx] = cos(i) * radius;
		vertex_buffer_data4[currenty] = sin(i) * radius;
		vertex_buffer_data4[currentz] = 0.0f;

		color_buffer_data4[currentx] = 1.0f;
		color_buffer_data4[currenty] = 1.0f;
		color_buffer_data4[currentz] = 1.0f;
	}


	// set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RIGHT_TRIANGLE]);
	// transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	// set buffer for colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RIGHT_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_EQUILATERAL_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_EQUILATERAL_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ISOCELES_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_ISOCELES_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2), color_buffer_data2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3), vertex_buffer_data3, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3), color_buffer_data3, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4), vertex_buffer_data4, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4), color_buffer_data4, GL_STATIC_DRAW);


	// load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");


	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// use our shader
	glUseProgram(m_programID);
}

void Scene3::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		randomX = -9 + rand() % (9 - (-9) + 1);
		randomY = rand() % 5 + 1;

		if ((rotateDirection != -1) && (rotateAngle < 1))
			rotateDirection = 1;
		else if ((rotateDirection == -1) && (rotateAngle <= -1))
			rotateDirection = 1;
		else
			rotateDirection = -1;

		rotateAngle += (float)(rotateDirection * 25 * dt);

		if (translateY <= -10)
			translateY = 10;
		else
			translateY -= (float)(75 * dt);

		if (translateX >= 10)
			translateX = -10;
		else
			translateX += (float)(10 * dt);

		if (scaleAll >= 3)
			scaleAll = 1;
		else
			scaleAll += (float)(2 * dt);
	}
}

void Scene3::Render()
{
	// Render VBO here

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	projection.SetToOrtho(-10, 10, -10, 10, -10, 10); //Our world is a cube defined by these boundaries

	// clear color buffer every frame
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors

	//moon
	scale.SetToScale(0.5, 0.5, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 6.5, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 64);

	//snow
	for (int i = 0; i < 10; i++)
	{
		scale.SetToScale(0.05, 0.05, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(randomX, randomY + translateY, 3);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 64);
	}



	{
		scale.SetToScale(10, 4, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-5, -10, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RIGHT_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RIGHT_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//right angled triangle
		scale.SetToScale(6, 13, 1);
		rotate.SetToRotation(90, 0, 0, 1);
		translate.SetToTranslation(10, -6, 2);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RIGHT_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RIGHT_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices = 1 triangle
	}

	{ //tree
		scale.SetToScale(2, 6, 1);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(-4, -1, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ISOCELES_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_ISOCELES_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		scale.SetToScale(2, 6, 1);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(-4, -4, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ISOCELES_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_ISOCELES_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		scale.SetToScale(0.5, 2, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-4, -5, 1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SQUARE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	{ //star
		scale.SetToScale(0.5, 0.5, 1);
		rotate.SetToRotation(rotateAngle, 0, 0, 1);
		translate.SetToTranslation(-4, 4.8, 2);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_EQUILATERAL_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_EQUILATERAL_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		scale.SetToScale(0.5, 0.5, 1);
		rotate.SetToRotation(180 + rotateAngle, 0, 0, 1);
		translate.SetToTranslation(-4, 5.5, 2);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_EQUILATERAL_TRIANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_EQUILATERAL_TRIANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	/*{ //square
		scale.SetToScale(1, 1, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(5, 7, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_SQUARE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_SQUARE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}*/

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);

}

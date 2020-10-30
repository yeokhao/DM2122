#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"

class Scene2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		//GEO_TRIANGLE_2,
		//GEO_TRIANGLE_3,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexBuffer[U_TOTAL];
	unsigned m_colorBuffer[U_TOTAL];
	unsigned m_programID;

	float rotateAngle;
	float translateX;
	float scaleAll;

public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif
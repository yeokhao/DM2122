#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_RIGHT_TRIANGLE = 0,
		GEO_ISOCELES_TRIANGLE,
		GEO_EQUILATERAL_TRIANGLE,
		GEO_SQUARE,
		GEO_CIRCLE,
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
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;

	float rotateAngle;
	int rotateDirection;
	float translateY;
	float translateX;
	float randomY;
	float randomX;
	float scaleAll;

public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif
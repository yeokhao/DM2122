#ifndef SCENE_1_H
#define SCENE_1_H

#include "Scene.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif
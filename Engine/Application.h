#pragma once
#include "Game.h"
#include "Light.h"

class Application :
	public Game
{
public:
	Application();
	virtual ~Application();

	virtual void Init() override final;
	virtual void Update() override final;
	virtual void Render() override final;

	static Light* light;
};


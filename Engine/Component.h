#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
	class Composite* parent;
private:
protected:

public:

	Component();
	~Component();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void SetParent(Composite* parent);
	Composite* GetParent();
};

#endif
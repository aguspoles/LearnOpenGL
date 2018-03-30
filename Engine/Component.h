#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
private:
	class Composite* parent;
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
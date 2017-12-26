#pragma once
#include "Composite.h"
#include "shader.h"
#include "Model.h"
#include <map>

class MeshRenderer :
	public Composite
{
public:
	MeshRenderer();
	~MeshRenderer();

	virtual void InitComposite() override;
	virtual void UpdateComposite() override;
	virtual void RenderComposite(glm::mat4 modelMatrix) override;
	virtual void SetShaderProperties() = 0;

	void SetShader(Shader* shader);
	void SetModel(Model* model);

	Shader* GetShader();

protected:
	Model* m_model;
	Shader* m_shader;
};


#include "MeshRenderer.h"
#include "Game.h"


MeshRenderer::MeshRenderer() : m_shader(NULL)
{
}


MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::InitComposite()
{
}

void MeshRenderer::UpdateComposite()
{
}

void MeshRenderer::RenderComposite(glm::mat4 modelMatrix)
{
	m_shader->use();

	SetShaderProperties();

	m_shader->setMat4("model", transform->GetModelMatrix());
	m_shader->setMat4("view", Game::camera->GetViewMatrix());
	m_shader->setMat4("projection", Game::camera->GetProjectionMatrix());

	m_model->Draw(*m_shader);
}

void MeshRenderer::SetShader(Shader* shader)
{
	m_shader = shader;
}

void MeshRenderer::SetModel(Model* model)
{
	m_model = model;
}

Shader * MeshRenderer::GetShader()
{
	return m_shader;
}

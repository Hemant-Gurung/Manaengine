#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
using namespace dae;

unsigned int Scene::m_IdCounter = 0;

std::string& Scene::GetName()
{
	 return m_Name; 
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Initialize()
{

}

void Scene::Update(float dt)
{
	for(auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void Scene::FixedUpdate()
{

}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}


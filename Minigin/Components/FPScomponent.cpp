#include "MiniginPCH.h"
#include "FPScomponent.h"

#include "Scenegraph/GameObject.h"

dae::FPScomponent::FPScomponent(std::shared_ptr<GameObject>& pGameObj,std::shared_ptr<TextComponent> text)
	:BaseComponent(pGameObj),
	m_TextComponent(text),
	 m_fpsTimer{},
     m_SecondsPerBound{1.f/(float)SDL_GetPerformanceFrequency()},
	 m_CurrentTime{},
     m_PreviousTime{},	
     m_FPScount{},
	 m_FPS{},
     m_ElapsedTime{}
{
	uint64_t startTime{ SDL_GetPerformanceCounter() };
	m_PreviousTime = startTime;
}



void dae::FPScomponent::update(float)
{
		
	/*
	 fps =1/dt;
	 
	 */

	//m_pGameObject->GetComponent<TransformComponent>()->SetPosition(2,2,0);

	uint64_t currentTime = SDL_GetPerformanceCounter();
	m_CurrentTime = currentTime;

	m_ElapsedTime = (float)((m_CurrentTime - m_PreviousTime) * m_SecondsPerBound);

	if(m_ElapsedTime<0)
	{
		m_ElapsedTime = 0;
	}
	m_PreviousTime = m_CurrentTime;

	//Fps logic
	m_fpsTimer += m_ElapsedTime;
	++m_FPScount;
	if(m_fpsTimer>=1.0f)
	{
		m_FPS = int(m_FPScount);
		m_FPScount = 0;
		m_fpsTimer -= 1.0f;
	}
	
	SetText();
}

void dae::FPScomponent::Render() const
{
	m_TextComponent->Render();
}

void dae::FPScomponent::SetPosition(float x, float y , float z)
{
	m_TextComponent->SetPosition(x, y, z);
}

void dae::FPScomponent::SetText()
{
	//m_fpsString = std::to_string(m_FPS);
	if(m_FPS!=0)
	m_TextComponent->SetText(std::to_string(m_FPS)+" FPS");
}

void dae::FPScomponent::SetCurrentTime(uint64_t currTime)
{
	m_CurrentTime = currTime;
}

void dae::FPScomponent::SetPreviousTime(uint64_t prevTime)
{
	m_PreviousTime = prevTime;
}



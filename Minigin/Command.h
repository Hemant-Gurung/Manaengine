#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "PlayerComponent.h"
#include <iostream>



class Command
{
public:
	Command(std::shared_ptr<dae::GameObject> pGameObject)
		:m_pGameObject(pGameObject)
	{};
	virtual ~Command() = default;
	virtual void Execute() = 0;
	std::weak_ptr<dae::GameObject> m_pGameObject;
};

//jump

class JumpCommand: public Command
{
public:
	JumpCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{};
	void  Execute() override
	{
		//jump call player
		std::cout << "Jumping\n"; 
	};
};

class DeathCommand : public Command
{
public:
	DeathCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{};
	void  Execute() override
	{
		m_pGameObject.lock()->GetComponent<dae::PlayerComponent>()->DeathCall();
		
	};
};

class ScoreCommand : public Command
{
public:
	ScoreCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{};
	void  Execute() override
	{
		m_pGameObject.lock()->GetComponent<dae::PlayerComponent>()->ScoreCall();

	};
};


//FireGun 

class FireGunCommand : public Command
{
public:
	FireGunCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{}
	void  Execute() override { std::cout << "Firing Gun\n"; }
};

//Duck

class DuckCommand : public Command
{  
public:
	DuckCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{

	}
	void  Execute() override { std::cout << "Ducking\n"; }
};

//Fart

class FartCommand : public Command
{
public:
	FartCommand(std::shared_ptr<dae::GameObject> pGameobject)
		:Command(pGameobject)
	{

	}
	void  Execute() override { std::cout << "Farting \n"; }
};

//MOVEMENT COMMANDS
class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(std::shared_ptr<dae::GameObject> pGameobject) :
		Command(pGameobject)
	{

	}

	void Execute() override
	{
		auto playerObj = m_pGameObject.lock()->GetComponent<dae::PlayerComponent>();
		playerObj->MoveLeft();
		dae::PlayerState state = dae::PlayerState::running;
		playerObj->ChangeState(state);
		//m_pGameObject.lock()->GetComponent<dae::PlayerComponent>()->SetVelocity();
		bool checkTexture = playerObj->GetIsFlipped();
		if (checkTexture)
		{
			playerObj->FLipTexture(false);
		}
	}
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(std::shared_ptr<dae::GameObject> pGameobject) :
		Command(pGameobject)
	{

	}

	void Execute() override
	{
		auto playerObj = m_pGameObject.lock()->GetComponent<dae::PlayerComponent>();
		dae::PlayerState state = dae::PlayerState::running;
		playerObj->ChangeState(state);
		playerObj->MoveRight();
		bool checkTexture = playerObj->GetIsFlipped();
		if (!checkTexture)
		{
			playerObj->FLipTexture(true);
		}

	}
};
class MoveUpCommand : public Command
{
public:
	MoveUpCommand(std::shared_ptr<dae::GameObject> pGameobject) :
		Command(pGameobject)
	{

	}

	void Execute() override
	{
		auto playerObj = m_pGameObject.lock()->GetComponent<dae::PlayerComponent>();
		playerObj->MoveUp();
		dae::PlayerState state = dae::PlayerState::climbing;
		playerObj->ChangeState(state);
	}
};

class MoveDownCommand : public Command
{
public:
	MoveDownCommand(std::shared_ptr<dae::GameObject> pGameobject) :
		Command(pGameobject)
	{

	}

	void Execute() override
	{
		auto playerObj =  m_pGameObject.lock()->GetComponent<dae::PlayerComponent>();
		playerObj->MoveDown();
		dae::PlayerState state = dae::PlayerState::climbing;
		playerObj->ChangeState(state);
	}
};



struct InputAction
{
	InputAction() :
		playerIndex(GamePadIndex::playerOne)
		, command(nullptr) {}

	InputAction(std::unique_ptr<Command> command = nullptr, GamePadIndex playerIndex = GamePadIndex::playerOne) :
		command(std::move(command)),
		playerIndex(playerIndex)

	{}
	std::unique_ptr<Command> command;
	GamePadIndex playerIndex;
};
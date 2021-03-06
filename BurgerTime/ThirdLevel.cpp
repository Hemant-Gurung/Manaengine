#include "pch.h"
#include "ThirdLevel.h"
#include "SecondLevel.h"
#include "BurgerComponent.h"
#include "EnemyComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Utils.h"

ThirdLevel::ThirdLevel()
	:GameScene("ThirdLevel")
	, m_PlayerPos()
	, m_Player(nullptr)
	, m_lives(nullptr)
	, m_Score(nullptr),
	m_accumulatedDeathTime(0)
{
	m_hasOverlapped = false;
}

ThirdLevel::~ThirdLevel()
{
	//delete m_pLevel;
}

void ThirdLevel::Initialize()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	m_hasOverlapped = false;
	//dae::SceneManager::GetInstance().AddGameScene("Demo");
	dae::ResourceManager::GetInstance().Init("../Data/");

	auto gameObjectLevel = std::make_shared<dae::GameObject>();
	////make render component
	auto Renderlevel = std::make_shared<dae::RenderComponent>(gameObjectLevel);
	auto transformLevel_1 = std::make_shared<dae::TransformComponent>(gameObjectLevel);
	gameObjectLevel->AddComponent(transformLevel_1);

	//auto texture = dae::ResourceManager::GetInstance().LoadTexture(LEVELS[0]);
	Renderlevel->SetTexture(LEVELS[2]);
	gameObjectLevel->AddComponent(Renderlevel);
	////ADD LEVEL SKELETON
	auto levelVertices = std::make_shared<LevelComponent>(gameObjectLevel);
	levelVertices.get()->Initialize(LEVEL_COLLISIONS[2]);
	gameObjectLevel->AddComponent(levelVertices);

	//scene.Add(gameObjectLevel);



	auto level = gameObjectLevel->GetComponent<LevelComponent>();
	m_sLevel = std::shared_ptr <LevelComponent>(level);
	//m_pLevel = Level;
	AddChild(gameObjectLevel);
	//===PLAYER ONE ===========================================================>>>>>>>>>>>>>>>
	PlayerOne(m_sLevel);

	AddBurger(m_sLevel);


	// Enemy Red
	EnemyType enemy = EnemyType::Red;
	Enemy(enemy, m_sLevel);


	//Enemy Egg
	enemy = EnemyType::Egg;
	Enemy(enemy, m_sLevel);


}

void ThirdLevel::Update(float dt)
{
	if (m_sceneObjects.size() > 0)
	{
		for (const auto& object : m_sceneObjects)
		{
			// get enemy0 pos
			auto enemy0 = object->GetComponent<dae::EnemyComponent>();
			if (enemy0 != nullptr)
			{
				m_enemyPos = enemy0->GetEnemyPos();
			}

			//if (m_PlayerPos.width <= 0)
			//{
			//	auto player1 = object->GetComponent<dae::PlayerComponent>();
			//	
			//	if (player1 != nullptr)
			//	{
			//		m_Player = player1;
			//	}
			//}

			if (m_Player != nullptr)
			{
				if (object->GetTag() == L"Player1")
				{
					m_PlayerPos = m_Player->GetPlayerPos();
				}
				CheckIfPlayerIsDead(*m_Player);

			}

			// check for game win
			if (object->GetTag() == L"Burger")
			{
				int count = 0;
				for (auto burger : object.get()->GetAllcomponents())
				{
					const int burgerLastPosCheck = 212;
					if (burger->GetPosition().bottom > burgerLastPosCheck)
					{
						count++;
					}
				}
				if (count >= 6)
				{
					//Game won
					std::cout << "Game Won";
					ClearScene();
					//dae::InputManager::GetInstance().ResetInput();
					dae::SceneManager::GetInstance().setActive("startScreen");
					break;
				}
			}

			//if(player)

			object->Update(dt);
		}
	}


	if (m_hasOverlapped)
	{
		m_accumulatedDeathTime += 10 * dt;
		if (m_accumulatedDeathTime >= 50.f)
		{
			m_accumulatedDeathTime = 0;
			ResetScene();
			m_hasOverlapped = false;
		}
	}
}

void ThirdLevel::FixedUpdate()
{
}

void ThirdLevel::Render()
{
	for (const auto& object : m_sceneObjects)
	{
		object->Render();
	}
}

void ThirdLevel::Enemy(EnemyType& enemytype, std::shared_ptr<LevelComponent> level)
{
	auto gameObjectEnemy = std::make_shared<dae::GameObject>();



	auto enemy = std::make_shared<dae::EnemyComponent>(gameObjectEnemy, enemytype, level);
	gameObjectEnemy->SetTag(L"Enemy");
	gameObjectEnemy->AddComponent(enemy);

	//scene.Add(gameObjectEnemy);
	AddChild(gameObjectEnemy);
}

void ThirdLevel::AddBurger(std::shared_ptr<LevelComponent> level)
{
	auto gameobjectBurger = std::make_shared<dae::GameObject>();
	float4 burgerPos;
	//Bottom
	burgerPos.one = 31.461f;
	burgerPos.two = 125.84f;
	burgerPos.three = 173.03f;
	burgerPos.four = 298.876f;

	Point2f leftPos = Point2f(55.180f, 298.876f);
	//float lastpos = 590.f;

	auto burger = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos, burgerPos);
	burger->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger);

	//float4 burgerPos;
	//Bottom
	burgerPos.one = 31.461f;
	burgerPos.two = 78.65f;
	burgerPos.three = 228.09f;
	burgerPos.four = 275.28f;

	Point2f leftPos2 = Point2f(202.2f, 448.31f);
	auto burger2 = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos2, burgerPos);
	burger2->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger2);

	burgerPos.one = 31.461f;
	burgerPos.two = 78.65f;
	burgerPos.three = 228.09f;
	burgerPos.four = 275.28f;

	Point2f leftPos3 = Point2f(359.f, 448.31f);
	auto burger3 = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos3, burgerPos);
	burger3->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger3);


	burgerPos.one = 31.461f;
	burgerPos.two = 125.843f;
	burgerPos.three = 173.2f;
	burgerPos.four = 298.876f;

	Point2f leftPos4 = Point2f(505.6f, 298.876f);
	auto burger4 = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos4, burgerPos);
	burger4->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger4);


	burgerPos.one = 369.7F;
	burgerPos.two = 424.719F;
	burgerPos.three = 471.9f;
	burgerPos.four = 590.f;

	Point2f leftPos5 = Point2f(55.180f, 590.f);
	auto burger5 = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos5, burgerPos);
	burger5->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger5);

	burgerPos.one = 369.7F;
	burgerPos.two = 424.719F;
	burgerPos.three = 471.9f;
	burgerPos.four = 590.f;

	Point2f leftPos6 = Point2f(505.6f, 590.f);
	auto burger6 = std::make_shared<BurgerComponent>(gameobjectBurger, level, leftPos6, burgerPos);
	burger6->AddObserver(m_Score);
	gameobjectBurger->AddComponent(burger6);


	gameobjectBurger->SetTag(L"Burger");
	//scene.Add(gameobjectBurger);
	AddChild(gameobjectBurger);
}

void ThirdLevel::PlayerOne(std::shared_ptr<LevelComponent> slevel)
{
	auto gameObjectPlayer = std::make_shared<dae::GameObject>();

	//Do this inside player class
	//player commands
	//if (dae::Input::GetInstance().m_ConsoleCommands.size() <= 0)
	{
		//InputAction a = InputAction(std::make_unique<DeathCommand>(gameObjectPlayer), GamePadIndex::playerOne);
		dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::down, dae::XBOX360Controller::ControllerButton::ButtonA), InputAction(std::make_unique<ThrowPepperCommand>(gameObjectPlayer), 'O', GamePadIndex::playerOne));
		//dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::down, dae::XBOX360Controller::ControllerButton::ButtonB), InputAction(std::make_unique<ScoreCommand>(gameObjectPlayer), 'P', GamePadIndex::playerOne));
		//RIGHT
		dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::held, dae::XBOX360Controller::ControllerButton::DpadRight), InputAction(std::make_unique<MoveRightCommand>(gameObjectPlayer), 'D', GamePadIndex::playerOne));
		//LEFT
		dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::held, dae::XBOX360Controller::ControllerButton::DpadLeft), InputAction(std::make_unique<MoveLeftCommand>(gameObjectPlayer), 'A', GamePadIndex::playerOne));
		//UP
		dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::held, dae::XBOX360Controller::ControllerButton::DpadUp), InputAction(std::make_unique<MoveUpCommand>(gameObjectPlayer), 'W', GamePadIndex::playerOne));
		//DOWN
		dae::Input::GetInstance().MapEvent(std::make_pair(dae::XBOX360Controller::ButtonState::held, dae::XBOX360Controller::ControllerButton::DpadDown), InputAction(std::make_unique<MoveDownCommand>(gameObjectPlayer), 'S', GamePadIndex::playerOne));
	}


	auto transformPlayer1 = std::make_shared<dae::TransformComponent>(gameObjectPlayer);
	//transformPlayer1->SetPosition(216, 180, 0);

	//player observer

	gameObjectPlayer->AddComponent(transformPlayer1);
	//player one
	auto player = std::make_shared<dae::PlayerComponent>(gameObjectPlayer, slevel);
	m_Player = player;

	//add gameobject to scene
	//scene.Add(gameObjectPlayer);
	player->SetPlayerStartPosition(Point2f{ 303.f,558.f });

	gameObjectPlayer->AddComponent(player);
	//gameObjectPlayer->GetComponent<TransformComponent>()->SetPosition(200.f, 10.f, 0.f);
	//score
	// gameObjLivesCounter = std::make_shared<GameObject>();

	//make transform component for the game object
	auto transformLives = std::make_shared<dae::TransformComponent>(gameObjectPlayer);

	//make text component
	auto fontLives = dae::ResourceManager::GetInstance().LoadFont("VPPixel-Simplified.otf", 20);
	auto textLives = std::make_shared<dae::TextComponent>(gameObjectPlayer, " ", fontLives, SDL_Color{ 255,255,255,1 });
	auto fontScore = dae::ResourceManager::GetInstance().LoadFont("VPPixel-Simplified.otf", 16);
	auto textScore = std::make_shared<dae::TextComponent>(gameObjectPlayer, " ", fontScore, SDL_Color{ 255,255,255,1 });

	// score achievement 
	//auto scoreAchievement = std::make_shared<Achievements>(g_Achievements, 4, gameObjectPlayer);

	//make livescounter component/ observer
	if (m_lives == nullptr)
	{
		auto lives = std::make_shared<dae::LivesCounterComponent>(gameObjectPlayer, textLives);
		m_lives = lives;
	}
	//score counter
	if (m_Score == nullptr)
	{
		auto score = std::make_shared<dae::ScoreComponent>(gameObjectPlayer, textScore);
		m_Score = score;
	}
	//score achievement observer
	//player->AddObserver(scoreAchievement);

	//add observers
	player->AddObserver(m_lives);

	//add score observer
	player->AddObserver(m_Score);

	//add gameobject scoreAchievement to gameobject
	//gameObjectPlayer->AddComponent(scoreAchievement);
	//add transform component to gameobject
	gameObjectPlayer->AddComponent(transformLives);

	//add counter to gameobject
	gameObjectPlayer->AddComponent(m_lives);

	//add score component to gameobject
	gameObjectPlayer->AddComponent(m_Score);

	//add text component for lives
	gameObjectPlayer->AddComponent(textLives);


	//add textComponent for score
	gameObjectPlayer->AddComponent(textScore);

	//set score position
	textScore->SetPosition(350, 5, 0);

	//set lives position
	textLives->SetPosition(570, 5, 0);

	gameObjectPlayer->SetTag(L"Player1");
	//add to scent
	//scene.Add(gameObjectPlayer);
	AddChild(gameObjectPlayer);
}

bool ThirdLevel::CheckIfPlayerIsDead(dae::PlayerComponent& player)
{
	if (m_Player->GetLives() <= 0)
	{
		//ClearScene();
		//dae::SceneManager::GetInstance().setActive("startScreen");

	}

	else if (!m_hasOverlapped && m_enemyPos.left != 0 && utils::IsOverlapping(m_PlayerPos, m_enemyPos))
	{

		m_hasOverlapped = true;
		player.CallPlayerIsDead();
		//m_Player = nullptr;
		//m_PlayerPos = Rectf(0, 0, 0, 0);
		return true;
	}
	return false;
}

void ThirdLevel::ResetScene()
{
	//ClearScene();
	m_Player->SetPlayerStartPosition(Point2f{ 303.f,459.f });
	m_PlayerPos = m_Player->GetPlayerPos();

	auto playerState = dae::PlayerState::standing;
	m_Player->ChangeState(playerState);

	for (auto obj : m_sceneObjects)
	{
		if (obj->GetTag() == L"Enemy")
		{
			obj->GetComponent<dae::EnemyComponent>()->ResetEnemyPos();
		}
	}
}

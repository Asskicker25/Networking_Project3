#include "GameWindow.h"
#include "EntityManager/EntityManager.h"
#include "Utilities/RendererInstance.h"
#include "NetworkManager/NetworkManager.h"
#include "GameManager/GameManager.h"
#include "Player/PlayerManager.h"
#include <thread>

void GameWindow::SetUp()
{
	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = 0;
	moveSpeed = 10;


	RendererInstance::GetInstance().SetRenderer(&renderer);


	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 1000.0f, 65.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 3));
	camera->transform.SetRotation(glm::vec3(0, 0, 0));

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);

#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(lightModel, Directional);
	dirLight->intensity = 1.5f;
	lightManager.AddLight(dirLight);

#pragma endregion

	GameManager* gameManager = new GameManager();
	NetworkManager* networkManager = new NetworkManager();
	PlayerManager::GetInstance().Print();

	networkManager->gameManager = gameManager;
	networkManager->Initialize();
	
	//gameManager->AddPlayer(0);

	EntityManager::GetInstance().Start();
}

void GameWindow::PreRender()
{
	EntityManager::GetInstance().Update(Timer::GetInstance().deltaTime);
	physicsEngine.Update(Timer::GetInstance().deltaTime);
}

void GameWindow::PostRender()
{
}

void GameWindow::ProcessInput(GLFWwindow* window)
{
	std::stringstream ssTitle;
	ssTitle << " ***Server*** "
		<<"Camera Pos : "
		<< camera->transform.position.x << " , "
		<< camera->transform.position.y << " , "
		<< camera->transform.position.z
		<< "  Camera Pitch : "
		<< camera->transform.rotation.x
		<< "  Camera Yaw : "
		<< camera->transform.rotation.y;

	std::string theTitle = ssTitle.str();

	glfwSetWindowTitle(window, theTitle.c_str());
}

void GameWindow::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_SPACE)
		{
			physicsEngine.gravity.y = (-9.8f / 5.0f);
		}
	}
}

void GameWindow::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}

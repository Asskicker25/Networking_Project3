#include "ClientWindow.h"
#include "EntityManager/EntityManager.h"
#include "Utilities/RendererInstance.h"
#include <thread>
#include "NetworkManager/NetworkManager.h"
#include "Player/PlayerManager.h"

void ClientWindow::SetClientId(const int& id)
{
	this->clientId = id;
}

void ClientWindow::SetUp()
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

	NetworkManager* networkManager = new NetworkManager();
	PlayerManager::GetInstance().Print();

	networkManager->Initialize(clientId);

	EntityManager::GetInstance().Start();
}

void ClientWindow::PreRender()
{
	physicsEngine.Update(Timer::GetInstance().deltaTime);
	EntityManager::GetInstance().Update(Timer::GetInstance().deltaTime);
}

void ClientWindow::PostRender()
{
}

void ClientWindow::ProcessInput(GLFWwindow* window)
{
	std::stringstream ssTitle;
	ssTitle << " ***Client*** "
		<< "Camera Pos : "
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

void ClientWindow::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void ClientWindow::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}

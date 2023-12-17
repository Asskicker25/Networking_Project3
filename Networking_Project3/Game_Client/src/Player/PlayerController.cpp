#include "PlayerController.h"

PlayerController::PlayerController()
{
	InitializeEntity(this);

	InputManager::GetInstance().AddListener(this);
}

void PlayerController::SetPlayer(GameObject* player)
{
	this->player = player;
}

GameObject* PlayerController::GetPlayer()
{
	return player;
}

void PlayerController::Start()
{
}

void PlayerController::Update(float deltaTime)
{
}

void PlayerController::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void PlayerController::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void PlayerController::OnKeyPressed(const int& key)
{

	Multiplayer::UserInput input;

	if (key == GLFW_KEY_W)
	{
		input.set_input((int)FORWARD);
	}
	else if (key == GLFW_KEY_S)
	{
		input.set_input((int)BACKWARD);
	}
	else if (key == GLFW_KEY_A)
	{
		input.set_input((int)TURN_LEFT);
	}
	else if (key == GLFW_KEY_D)
	{
		input.set_input((int)TURN_RIGHT);
	}
	else if (key == GLFW_KEY_J)
	{
		input.set_input((int)FIRE);
	}

	client->SendCommand(USER_INPUT, input);
}

void PlayerController::OnKeyReleased(const int& key)
{
}

void PlayerController::OnKeyHeld(const int& key)
{
}

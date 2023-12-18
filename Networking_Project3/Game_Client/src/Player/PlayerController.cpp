#include "PlayerController.h"
#include <Graphics/Timer.h>

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

void PlayerController::PositionPredictor()
{

	glm::vec3 pos;
	glm::vec3 targetPos;
	glm::vec3 forward = player->GetTransform()->GetForward();
	pos = player->GetTransform()->position;

	if (wPressed)
	{
		targetPos = pos - forward * speed * Timer::GetInstance().deltaTime;
		player->GetTransform()->SetPosition(targetPos);
	}
	else if(sPressed)
	{
		targetPos = pos + forward * speed * Timer::GetInstance().deltaTime;
		player->GetTransform()->SetPosition(targetPos);
	}
}

void PlayerController::Start()
{
}

void PlayerController::Update(float deltaTime)
{
	if (player == nullptr) return;
	PositionPredictor();
}

void PlayerController::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void PlayerController::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void PlayerController::OnKeyPressed(const int& key)
{

	if (key == GLFW_KEY_W)
	{
		Multiplayer::UserInput input;
		input.set_action((int)PRESSED);
		input.set_input((int)FORWARD);
		client->SendCommand(USER_INPUT, input);

		wPressed = true;
	}
	else if (key == GLFW_KEY_S)
	{
		Multiplayer::UserInput input;
		input.set_action((int)PRESSED);
		input.set_input((int)BACKWARD);
		client->SendCommand(USER_INPUT, input);

		sPressed = true;
	}
	else if (key == GLFW_KEY_A)
	{
		Multiplayer::UserInput input;
		input.set_action((int)PRESSED);
		input.set_input((int)TURN_LEFT);
		client->SendCommand(USER_INPUT, input);
	}
	else if (key == GLFW_KEY_D)
	{
		Multiplayer::UserInput input;
		input.set_action((int)PRESSED);
		input.set_input((int)TURN_RIGHT);
		client->SendCommand(USER_INPUT, input);
	}
	else if (key == GLFW_KEY_SPACE)
	{
		Multiplayer::UserInput input;
		input.set_action((int)PRESSED);
		input.set_input((int)FIRE);
		client->SendCommand(USER_INPUT, input);
	}

}

void PlayerController::OnKeyReleased(const int& key)
{

	if (key == GLFW_KEY_W)
	{
		Multiplayer::UserInput input;
		input.set_action((int)RELEASED);
		input.set_input((int)FORWARD);
		client->SendCommand(USER_INPUT, input);

		wPressed = false;

	}
	else if (key == GLFW_KEY_S)
	{
		Multiplayer::UserInput input;
		input.set_action((int)RELEASED);
		input.set_input((int)BACKWARD);
		client->SendCommand(USER_INPUT, input);

		sPressed = false;
	}
	else if (key == GLFW_KEY_A)
	{
		Multiplayer::UserInput input;
		input.set_action((int)RELEASED);
		input.set_input((int)TURN_LEFT);
		client->SendCommand(USER_INPUT, input);
	}
	else if (key == GLFW_KEY_D)
	{
		Multiplayer::UserInput input;
		input.set_action((int)RELEASED);
		input.set_input((int)TURN_RIGHT);
		client->SendCommand(USER_INPUT, input);
	}
	else if (key == GLFW_KEY_SPACE)
	{
		Multiplayer::UserInput input;
		input.set_action((int)RELEASED);
		input.set_input((int)FIRE);
		client->SendCommand(USER_INPUT, input);
	}
}

void PlayerController::OnKeyHeld(const int& key)
{
	
}

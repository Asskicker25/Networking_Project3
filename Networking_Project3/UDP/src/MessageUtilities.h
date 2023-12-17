#pragma once
#include <string>
#include "../../ProtocolFile/MultiplayerProtoBuf.pb.h"
#include <glm/glm.hpp>

static enum Command
{
	USER_INPUT = 0,
	GAME_SCENE = 1

};

static enum PlayerInput
{
	FORWARD = 0,
	BACKWARD = 1,
	TURN_RIGHT = 2,
	TURN_LEFT = 3,
	FIRE = 4
};

struct LengthPrefixedMessage
{
	std::string message;
};

static LengthPrefixedMessage SerializeWithCommandAndLengthPrefix(int id, const Command& command, const google::protobuf::Message& message)
{
	std::string serializedMessage;
	message.SerializeToString(&serializedMessage);

	Multiplayer::CommandAndData commnadData;

	commnadData.set_clientid(id);
	commnadData.set_command((int)command);
	commnadData.set_data(serializedMessage);

	std::string serializedMessageData;
	commnadData.SerializeToString(&serializedMessageData);

	Multiplayer::LengthPrefix lengthPrefix;
	lengthPrefix.set_messagelength(serializedMessageData.size());

	std::string serializedLengthPrefix;
	lengthPrefix.SerializeToString(&serializedLengthPrefix);

	std::string result;
	result.append(serializedLengthPrefix);
	result.append(serializedMessageData);

	return LengthPrefixedMessage{ serializedMessageData };
}

static Multiplayer::vector3* GetVector3(const glm::vec3& value)
{
	Multiplayer::vector3* returnValue = new Multiplayer::vector3();

	returnValue->set_x(value.x);
	returnValue->set_y(value.y);
	returnValue->set_z(value.z);

	return returnValue;
}

static glm::vec3 GetGlmVector3(const Multiplayer::vector3& value)
{
	glm::vec3 returnValue = glm::vec3(0);

	returnValue.x = value.x();
	returnValue.y = value.y();
	returnValue.z = value.z();

	return returnValue;
}
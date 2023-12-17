#include "ClientWindow.h"

int main(int argc, char* argv[])
{
	int clientId;

	std::cout << "Enter Player ID : ";
	std::cin >> clientId;

	ClientWindow window;

	window.SetClientId(clientId);

	window.InitializeWindow(800, 600);

	window.Render();

	return -1;
}
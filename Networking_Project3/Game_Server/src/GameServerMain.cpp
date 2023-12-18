#include "GameWindow.h"

int main(int argc, char* argv[])
{
	Debugger::print = true;

	GameWindow window;

	window.InitializeWindow(800, 600);

	window.Render();

	return -1;
}
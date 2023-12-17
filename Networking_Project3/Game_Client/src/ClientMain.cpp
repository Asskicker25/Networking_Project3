#include "ClientWindow.h"

int main(int argc, char* argv[])
{
	ClientWindow window;

	window.InitializeWindow(800, 600);

	window.Render();

	return -1;
}
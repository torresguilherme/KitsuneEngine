#include "display.h"
#include "input.h"

int main()
{
	Display display(800, 600, "test");
	while(!display.isClosed)
	{
		display.Clear(0.5f, 0.0f, 0.5f, 1.0f);
		display.Update();
	}

	return 0;
}

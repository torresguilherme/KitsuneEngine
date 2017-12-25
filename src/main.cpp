#include "display.h"
#include "input.h"

int main()
{
	Display display(800, 600, "test");
	display.Run();
	return 0;
}

#include<conio.h>
#include "keyInput.h"

keyInput::keyInput()
{
}


keyInput::~keyInput()
{
}

char keyInput::readKey()
{
	return _getch();
}
#pragma once

#include <OneWire.h>

class IButtonManager
{
public:
	IButtonManager();
	void init();
	bool update();

private:

	OneWire _btn;
	byte _addr[8];
};


#include "IButtonManager.h"

#include "Krakeenone_pinout.h"

IButtonManager::IButtonManager()
{

}

void IButtonManager::init()
{
	_btn = OneWire(IBUTTON);
}

bool IButtonManager::update()
{
	if (!_btn.search(_addr))
	{
		_btn.reset_search();
		return false;
	}

	_btn.reset();
	return true;
}

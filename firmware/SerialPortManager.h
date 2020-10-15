#pragma once
class SerialPortManager
{
public:

	enum Mode {normal, timeSet};

	SerialPortManager();
	void init(int baudRate);
	void update();

private:

	Mode _mode = normal;
};


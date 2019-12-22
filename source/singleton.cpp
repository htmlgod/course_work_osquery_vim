#include <singleton.h>

void VimConfig::init() {
	std::cout << "VimConfig singleton started!" << std::endl;
	_startupTime = 0;
}
int VimConfig::getStartupTime() {
    return _startupTime;
}
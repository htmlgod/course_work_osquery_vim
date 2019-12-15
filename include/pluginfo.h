#pragma once

#include <curl/curl.h>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>

class Plugin {
public:
	Plugin(std::string name) : _pluginName(name) {}
	
	int getPluginStarCount();
private:
	std::string _pluginName;
};


#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include <boost/filesystem.hpp>
#include <boost/process.hpp>


class VimConfig {

public:
    VimConfig(VimConfig const&) = delete;
    VimConfig& operator= (VimConfig const&) = delete;

	static VimConfig& Instance() {
		static VimConfig vimconfig;
		return vimconfig;
	}

	double getStartupTimeinMS();

	double getStartupTimeinSec();

	void init();
private:
    VimConfig() = default;
	//std::vector<Plugin> 	 _plugins;
	//std::vector<std::string> _settings;
	//std::vector<std::string> _modes;
	double						 _startupTime;
};

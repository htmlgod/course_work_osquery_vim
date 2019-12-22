#pragma once
#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>

using namespace boost::process;
class VimConfig {

public:
    VimConfig(VimConfig const&) = delete;
    VimConfig& operator= (VimConfig const&) = delete;
	static VimConfig& Instance() {
		static VimConfig vimconfig;
		return vimconfig;
	}
	double getStartupTime();
	void init();
private:
    VimConfig() = default;
	//std::vector<Plugin> 	 _plugins;
	//std::vector<std::string> _settings;
	//std::vector<std::string> _modes;
	double						 _startupTime;
};

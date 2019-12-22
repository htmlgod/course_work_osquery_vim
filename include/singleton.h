#pragma once
#include <iostream>

class VimConfig {

public:
    VimConfig(VimConfig const&) = delete;
    VimConfig& operator= (VimConfig const&) = delete;
	static VimConfig& Instance() {
		static VimConfig vimconfig;
		return vimconfig;
	}
	int getStartupTime();
	void init();
private:
    VimConfig() = default;
	//std::vector<Plugin> 	 _plugins;
	//std::vector<std::string> _settings;
	//std::vector<std::string> _modes;
	int						 _startupTime;
};
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <plugin.h>

class VimConfig {

public:
    VimConfig(VimConfig const&) = delete;

    VimConfig(const std::vector<std::string> &settings);

    VimConfig& operator= (VimConfig const&) = delete;

	static VimConfig& Instance() {
		static VimConfig vimconfig;
		return vimconfig;
	}

    void getPluginList();
	void parsePluginList();

    void getSettingList();
    void parseSettingList();

	void detectPluginManager();
	void detectVimConfigFile();
	
	void getStartupTime();
	double getStartupTimeMS();
    double getStartupTimeS();

    void exportJSONData();

	void init();
private:
    VimConfig() = default;
	std::vector<Plugin> 	    _plugins;
	std::string                 _manager;
	std::string                 _configFilePath;
	std::vector<std::string>    _settings;
	//std::vector<std::string>  _modes;
	double	_startupTime;
};

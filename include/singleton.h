#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <plugin.h>
#include <webutils.h>

class VimConfig {
public:
    VimConfig(VimConfig const&) = delete;
    VimConfig& operator= (VimConfig const&) = delete;

    // Singleton instance function
    static VimConfig& Instance();

    // Initialization functions
    void init();
    void start();

    // Parsing data
    void parsePluginList();
    void parseSettingList();
    void getStartupTime();
    void parseFromJSON();

    // Detection functions
    void detectPluginManager();
    void detectVimConfigFile();
    void detectExtensionSocket();

    // check function
    static bool isOsqueryInstalled();
    static bool isPythonInstalled();
    bool isForeignPlugin(std::string& name);

    // Getting data
    void getPluginList();
    void getSettingList();
    double getStartupTimeMS();
    double getStartupTimeS();
    unsigned long getPluginsAmount();
    Plugin& getPluginByName(std::string& name);

    // Osquery Integration functions
    void exportJSONData();
    void startExtension() noexcept;

    // other functions
	void findGitHubStarsPlugins();
    void clear();

private:
    VimConfig() = default;

    std::string                 _username = "none";
    std::string                 _password = "none";
    std::string                 _homePath;
    std::string                 _infoFilesDir;
	std::string                 _manager;
	std::string                 _configFilePath;
	std::string                 _extensionsSocket;
    std::vector<Plugin> 	    _plugins;
	std::vector<std::string>    _settings;
	double	                    _startupTime = 0;
    unsigned long               _pluginsAmount = 0;
};

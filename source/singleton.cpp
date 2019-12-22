#include <singleton.h>
#include <nlohmann/json.hpp>

namespace bp = boost::process;

void VimConfig::init() {
    std::cout << "VimConfig singleton started!" << std::endl;
    detectPluginManager();
    detectVimConfigFile();
    parsePluginList();
    parseSettingList();
    getStartupTime();
}
void VimConfig::getPluginList() {
    for(auto& plug : _plugins)
        std::cout << plug.getPluginName() << std::endl;
}

void VimConfig::parsePluginList() {
    std::ifstream config(_configFilePath);
    std::string keyWord;
    if (_manager == "bundle") {
        keyWord = "Plugin";
    } else {
        keyWord = "Plug";
    }
    if (config.is_open()) {
        while(!config.eof()) {
            std::string pluginName;
            std::getline(config, pluginName);
            if (pluginName.find(keyWord) != std::string::npos and pluginName[0] != '\"') {
                std::size_t foundFirstQuote = pluginName.find("\'");
                pluginName = pluginName.substr(foundFirstQuote + 1);
                std::size_t foundNextQuote = pluginName.find("\'");
                pluginName = pluginName.substr(0, foundNextQuote);
                _plugins.emplace_back(pluginName);
            }
        }
    }
}

void VimConfig::detectPluginManager() {
    std::string homePath = getenv("HOME");
    std::string vimFilesDir;
    if (boost::filesystem::exists(homePath + "/.vim")) {
        vimFilesDir = homePath + "/.vim";
    } else if (boost::filesystem::exists(homePath + "/.nvim")) {
        vimFilesDir = homePath + "/.nvim";
    }
    if (boost::filesystem::exists(vimFilesDir + "/plugged")) {
        _manager = "vim-plug";
    } else if (boost::filesystem::exists(vimFilesDir + "/bundle")) {
        _manager = "bundle";
    }
}

void VimConfig::detectVimConfigFile() {
    std::string homePath = getenv("HOME");
    if (boost::filesystem::exists(homePath + "/.vimrc")) {
        _configFilePath = homePath + "/.vimrc";
    } else if (boost::filesystem::exists(homePath + "/.config/nvim/init.vim")) {
        _configFilePath = homePath + "/.config/nvim/init.vim";
    }
}

void VimConfig::getSettingList() {
    for(int i = 0; i < _settings.size(); i++)
        std::cout << _settings[i] << std::endl;
}

void VimConfig::parseSettingList() {
    std::ifstream config(_configFilePath);
    std::string keyWord = "set";
    if (config.is_open()) {
        while(!config.eof()) {
            std::string setting;
            std::getline(config, setting);
            if (setting.find(keyWord) != std::string::npos and setting[0] != '\"') {
                std::string junk;
                std::string clearedSetting;
                std::stringstream ss(setting);
                ss >> junk;
                ss >> clearedSetting;
                _settings.push_back(clearedSetting);
            }
        }
    }
}

void VimConfig::getStartupTime() {
    std::string homePath = getenv("HOME");
    boost::process::child c("vim --startuptime "+homePath + "/runtime.txt");
    c.wait();
    std::ifstream config(homePath + "/runtime.txt");
    if (config.is_open()) {
        while(!config.eof()) {
            std::string lane;
            std::getline(config, lane);
            if (lane.find("VIM STARTED")!= std::string::npos) {
                std::stringstream ss(lane);
                ss >> _startupTime;
            }
        }
    }
}
double VimConfig::getStartupTimeMS() {
    return _startupTime;
}

double VimConfig::getStartupTimeS() {
    return _startupTime/1000;
}

void VimConfig::exportJSONData() {
    nlohmann::json plugins = nlohmann::json::array();
    for (auto& plug : _plugins) {
        nlohmann::json plugin = nlohmann::json::object({
            {"name", plug.getPluginName()},
            {"stars", plug.getStarsCount()},
            {"category", plug.getVimAwesomePluginClassification()},
            {"open", plug.getOpenedIssues()},
            {"closed", plug.getClosedIssues()}
        });
        plugins.push_back(plugin);
    }
    std::string homePath = getenv("HOME");
    std::ofstream out(homePath+"/.vimPlugins.json");
    if(out.is_open()) {
//        for (auto& item : plugins) {
//            out << std::setw(4) << item << std::endl;
//        }
        out << std::setw(4) << plugins << std::endl;
    }
    out.close();
}

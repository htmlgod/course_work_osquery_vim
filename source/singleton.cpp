#include <singleton.h>
#include <nlohmann/json.hpp>

namespace bp = boost::process;
namespace bf = boost::filesystem;

VimConfig &VimConfig::Instance() {
    static VimConfig vimconfig;
    return vimconfig;
}

void VimConfig::init() {
    std::string homePath = getenv("HOME");

    if (getenv("GITHUB_USERNAME") != nullptr and getenv("GITHUB_PASSWORD") != nullptr) {
        _username = getenv("GITHUB_USERNAME");
        _password = getenv("GITHUB_PASSWORD");
    }

    _homePath = homePath;
    _infoFilesDir = _homePath + "/.vim-info/";

}

void VimConfig::start() {
    if (bf::exists(_infoFilesDir + "vimInfo.json") and
        bf::exists(_infoFilesDir + "vimPlugins.json")) {
        parseFromJSON();
        std::cout << "Loaded!" << std::endl;
    } else {
        bf::create_directory(_infoFilesDir);
        detectPluginManager();
        detectVimConfigFile();
        parsePluginList();
        detectExtensionSocket();
    }
    parseSettingList();
    getStartupTime();
}

void VimConfig::detectPluginManager() {
    std::string vimFilesDir;
    if (bf::exists(_homePath + "/.vim")) {
        vimFilesDir = _homePath + "/.vim";
    } else if (bf::exists(_homePath + "/.nvim")) {
        vimFilesDir = _homePath + "/.nvim";
    }
    if (bf::exists(vimFilesDir + "/plugged")) {
        _manager = "vim-plug";
    } else if (bf::exists(vimFilesDir + "/bundle")) {
        _manager = "bundle";
    }
}

void VimConfig::detectVimConfigFile() {
    if (bf::exists(_homePath + "/.vimrc")) {
        _configFilePath = _homePath + "/.vimrc";
    } else if (bf::exists(_homePath + "/.config/nvim/init.vim")) {
        _configFilePath = _homePath + "/.config/nvim/init.vim";
    }
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
        while (!config.eof()) {
            std::string pluginStr;
            std::getline(config, pluginStr);
            std::stringstream ss(pluginStr);
            std::string pluginName;
            ss >> pluginName;
            if (pluginName == keyWord) {
                ss >> pluginName;
                std::size_t foundFirstQuote = pluginName.find('\'');
                pluginName = pluginName.substr(foundFirstQuote + 1);
                std::size_t foundNextQuote = pluginName.find('\'');
                pluginName = pluginName.substr(0, foundNextQuote);
                _plugins.emplace_back(pluginName);
            }
        }
    }
    _pluginsAmount = _plugins.size();
}

void VimConfig::parseSettingList() {
    std::ifstream config(_configFilePath);
    std::string keyWord = "set";
    if (config.is_open()) {
        while (!config.eof()) {
            std::string settingStr;
            std::getline(config, settingStr);
            std::stringstream ss(settingStr);
            std::string setting;
            ss >> setting;
            if (setting == keyWord) {
                ss >> setting;
                _settings.push_back(setting);
            }
        }
    }
}

// Get Info functions
void VimConfig::getStartupTime() {
    std::string homePath = getenv("HOME");
    boost::process::child c("vim --startuptime " + homePath + "/runtime.txt");
    c.wait();
    std::ifstream config(homePath + "/runtime.txt");
    if (config.is_open()) {
        while (!config.eof()) {
            std::string lane;
            std::getline(config, lane);
            if (lane.find("VIM STARTED") != std::string::npos) {
                std::stringstream ss(lane);
                ss >> _startupTime;
            }
        }
    }
    config.close();
    bf::remove(homePath + "/runtime.txt");
}

void VimConfig::getPluginList() {
    for (unsigned long i = 0; i < _pluginsAmount; i++) {
        std::cout << _plugins[i].getPluginName() << "  ";
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
}

void VimConfig::getSettingList() {
    for (const auto &_setting : _settings)
        std::cout << _setting << std::endl;
}

double VimConfig::getStartupTimeMS() {
    return _startupTime;
}

double VimConfig::getStartupTimeS() {
    return _startupTime / 1000;
}

unsigned long VimConfig::getPluginsAmount() {
    return _pluginsAmount;
}

bool VimConfig::isForeignPlugin(std::string &name) {
    for (auto &x : _plugins) {
        if (x.getPluginName() == name)
            return false;
    }
    return true;
}

Plugin &VimConfig::getPluginByName(std::string &name) {
    static Plugin plug;
    for (auto &x : _plugins) {
        if (x.getPluginName() == name)
            plug = x;
    }
    return plug;
}

// Find plugins from Github stars
void VimConfig::findGitHubStarsPlugins() {
    if (std::getenv("GITHUB_USERNAME") != nullptr) {
        std::string username = std::getenv("GITHUB_USERNAME");
        std::string paginationURL = "https://api.github.com/users/" + username + "/starred?per_page=1";
        std::string header = httpHeader(paginationURL);
        std::stringstream ss(header);
        std::string pages;
        while (pages != "rel=\"next\",")
            ss >> pages;
        ss >> pages;
        size_t pos = pages.find_last_of("page=");
        pages = pages.substr(pos + 1);
        size_t pos2 = pages.find(">;");
        pages = pages.substr(0, pos2);
        int userStarsNumber = stoi(pages);
        std::cout << username << " starred list: " << std::endl;
        for (int i = 1; i < userStarsNumber + 1; i++) {
            paginationURL += "&page=" + std::to_string(i);
            std::string query = httpQuery(paginationURL, _username, _password);
            auto json = nlohmann::json::parse(query);
            auto name = json[0]["full_name"].get<std::string>();
            Plugin plug(name);
            std::cout << name << "is ";
            if (plug.getVimAwesomePluginClassification() == "none") {
                std::cout << "is not a plugin" << std::endl;
            } else {
                std::cout << "is a plugin with class: " << plug.getVimAwesomePluginClassification() << std::endl;
            }
        }
    } else {
        std::cout << "Empty info about github user!" << std::endl;
    }
}

// Data import/export

void VimConfig::parseFromJSON() {
    // plugins
    nlohmann::json plugins = nlohmann::json::array();
    std::ifstream plugsIn(_infoFilesDir + "vimPlugins.json");
    if (plugsIn.is_open())
        plugsIn >> plugins;
    plugsIn.close();
    _plugins.reserve(plugins.size());
    for (auto &x : plugins) {
        _plugins.emplace_back(x["name"].get<std::string>(),
                              x["stars"].get<int>(),
                              x["open"].get<int>(),
                              x["closed"].get<int>(),
                              x["category"].get<std::string>());
    }
    // info
    nlohmann::json info = nlohmann::json::object();
    std::ifstream infoIn(_infoFilesDir + "vimInfo.json");
    if (infoIn.is_open())
        infoIn >> info;
    infoIn.close();
    _configFilePath = info["config_file"].get<std::string>();
    _manager = info["plugin_manager"].get<std::string>();
    _pluginsAmount = info["plugins_count"].get<int>();
    _extensionsSocket = info["socket"].get<std::string>();
}

void VimConfig::exportJSONData() {
    // Plugins
    nlohmann::json plugins = nlohmann::json::array();
    for (auto &plug : _plugins) {
        nlohmann::json plugin = nlohmann::json::object({
                                                               {"name",     plug.getPluginName()},
                                                               {"stars",    plug.getStarsCount()},
                                                               {"category", plug.getVimAwesomePluginClassification()},
                                                               {"open",     plug.getOpenedIssues()},
                                                               {"closed",   plug.getClosedIssues()}
                                                       });
        plugins.push_back(plugin);
    }
    std::ofstream plugOut(_infoFilesDir + "vimPlugins.json");
    if (plugOut.is_open()) {
        plugOut << std::setw(4) << plugins << std::endl;
    }
    plugOut.close();
    // Info
    nlohmann::json info = nlohmann::json::object({
                                                         {"plugin_manager", _manager},
                                                         {"config_file",    _configFilePath},
                                                         {"plugins_count",  getPluginsAmount()},
                                                         {"socket",         _extensionsSocket}
                                                 });
    std::ofstream infoOut(_infoFilesDir + "vimInfo.json");
    if (infoOut.is_open()) {
        infoOut << std::setw(4) << info << std::endl;
    }
    infoOut.close();
    // Runtime
    nlohmann::json runtime = nlohmann::json::object({
                                                            {"runtime_ms", getStartupTimeMS()},
                                                            {"runtime_s",  getStartupTimeS()}
                                                    });
    std::ofstream runtimeOut(_infoFilesDir + "vimRunTime.json");
    if (runtimeOut.is_open()) {
        runtimeOut << std::setw(4) << runtime << std::endl;
    }
    runtimeOut.close();
}

// Osquery integration functions
bool VimConfig::isOsqueryInstalled() {
    bf::path find = bp::search_path("osqueryi");
    return !find.empty();
}

bool VimConfig::isPythonInstalled() {
    bf::path find = bp::search_path("python3");
    return !find.empty();
}

void VimConfig::startExtension() noexcept {
    if (isOsqueryInstalled() and isPythonInstalled()) {
        //detectExtensionSocket();
        std::string cmd = "python3 " + _infoFilesDir + "extension.py --socket " + _extensionsSocket;
        std::cout << cmd << std::endl;
        bp::child c(cmd);
        c.wait();
    }
}

void VimConfig::detectExtensionSocket() {
    if (isOsqueryInstalled()) {
        bp::ipstream out;
        std::string socketString;
        bp::child c("osqueryi --line \"select value from osquery_flags where name = 'extensions_socket';\"",
                    bp::std_out > out);
        getline(out, socketString);
        c.wait();
        std::stringstream ss(socketString);
        ss >> _extensionsSocket;
        ss >> _extensionsSocket;
        ss >> _extensionsSocket;
    }
}

void VimConfig::clear() {
    bf::remove(_infoFilesDir + "vimPlugins.json");
    bf::remove(_infoFilesDir + "vimInfo.json");
}
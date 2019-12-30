#include <nlohmann/json.hpp>
#include <utility>
#include <plugin.h>

Plugin::Plugin(std::string name) {
    _pluginName = std::move(name);
    if (getenv("GITHUB_USERNAME") != nullptr and getenv("GITHUB_PASSWORD") != nullptr) {
        _username = getenv("GITHUB_USERNAME");
        _password = getenv("GITHUB_PASSWORD");
        parseStarsCount();
        parseOpenedIssues();
        parseClosedIssues();
        parseVimAwesomePluginClassification();
    }
}
Plugin::Plugin() {
    _pluginName = "none";
}
Plugin::Plugin(std::string name, int stars, int open, int closed, std::string category) {
    _pluginName = std::move(name);
    _starsCount = stars;
    _openIssues = open;
    _closedIssues = closed;
    _category = std::move(category);
    _openToCloseIssues = double(open)/double(closed);
}

void Plugin::setName(std::string& name) {
    _pluginName = name;
}
// Get info functions
int Plugin::getStarsCount() {
    return _starsCount;
}

int Plugin::getOpenedIssues() {
    return _openIssues;
}

int Plugin::getClosedIssues() {
    return _closedIssues;
}

double Plugin::getAmountOfOpenedIssuesToClosed() {
    return _openToCloseIssues;
}

std::string Plugin::getVimAwesomePluginClassification() {
    return _category;
}

std::string Plugin::getPluginName() {
    return _pluginName;
}
// Parse functions
void Plugin::parseStarsCount() {
    const std::string url = API::GITHUB_API_ENTRY + "repos/"
                            + _pluginName;

    std::string jsonHTTP = httpQuery(url,_username, _password);
    if (jsonHTTP != "empty") {
        auto json = nlohmann::json::parse(jsonHTTP);
        _starsCount = json["stargazers_count"].get<int>();
    } else {
        _starsCount = 0;
    }
}

void Plugin::parseOpenedIssues() {
    const std::string search_query = "+type:issue+state:open";
    const std::string url = API::GITHUB_API_ENTRY + "search/issues?q=repo:" + _pluginName + search_query;

    std::string jsonHTTP = httpQuery(url,_username, _password);
    if (jsonHTTP != "empty") {
        auto json = nlohmann::json::parse(jsonHTTP);
        _openIssues = json["total_count"].get<int>();
        _openToCloseIssues = double(_openIssues);
    } else {
        _openIssues = 0;
        _openToCloseIssues = 0;
    }
}

void Plugin::parseClosedIssues() {
    const std::string search_query = "+type:issue+state:closed";
    const std::string url = API::GITHUB_API_ENTRY + "search/issues?q=repo:" + _pluginName + search_query;

    std::string jsonHTTP = httpQuery(url,_username, _password);
    if (jsonHTTP != "empty") {
        auto json = nlohmann::json::parse(jsonHTTP);
        _closedIssues = json["total_count"].get<int>();
        _openToCloseIssues /= double(_closedIssues);
    } else {
        _closedIssues = 0;
        _openToCloseIssues = 0;
    }
}

std::string Plugin::getFormattedPluginName() {
	std::string formatted = _pluginName;
	std::size_t pos = formatted.find('/');
	if (pos != std::string::npos)
		formatted = formatted.substr(pos+1);
	pos = formatted.find("vim-");
	if (pos != std::string::npos)
		formatted = formatted.substr(4);
	pos = formatted.find('-');
	if (pos != std::string::npos)
		formatted.replace(pos,1, "%20");
	return formatted;
}

void Plugin::parseVimAwesomePluginClassification() {
    const std::string githubURLBase = "https://github.com/";

    std::string formattedPluginName = getFormattedPluginName();

    std::string url = API::VIMAWESOME_SEARCH_API_ENTRY + formattedPluginName;
    std::string jsonHTTP = httpQuery(url,_username, _password);
    std::string githubURL = githubURLBase + _pluginName;
    _category = "none";
    if (jsonHTTP != "empty") {
        auto json = nlohmann::json::parse(jsonHTTP);
        for (auto& x : json["plugins"]) {
            if (x["github_url"].get<std::string>() == githubURL) {
                _category = x["category"].get<std::string>();
                break;
            }
        }
    }
}
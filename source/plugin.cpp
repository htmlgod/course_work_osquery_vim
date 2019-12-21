#include <nlohmann/json.hpp>
#include <plugin.h>

Plugin::Plugin() {
    _pluginName = "none";
}

int Plugin::getStarsCount() {
    const std::string url = API::GITHUB_API_ENTRY + "repos/"
	+ _pluginName;

	std::string jsonHTTP = httpQuery(url);
	if (jsonHTTP != "empty") {
		auto json = nlohmann::json::parse(jsonHTTP);
		return json["stargazers_count"].get<int>();
	}
	return 0;
}
int Plugin::getOpenedIssues() {
	const std::string search_query = "+type:issue+state:open";
	const std::string url = 
	API::GITHUB_API_ENTRY + "search/issues?q=repo:" + _pluginName + search_query;

	std::string jsonHTTP = httpQuery(url);
	if (jsonHTTP != "empty") {
		auto json = nlohmann::json::parse(jsonHTTP);
		return json["total_count"].get<int>();
	}
	return 0;
}

int Plugin::getClosedIssues() {
	const std::string search_query = "+type:issue+state:closed";
	const std::string url = 
	API::GITHUB_API_ENTRY + "search/issues?q=repo:" + _pluginName + search_query;

	std::string jsonHTTP = httpQuery(url);
	if (jsonHTTP != "empty") {
		auto json = nlohmann::json::parse(jsonHTTP);
		return json["total_count"].get<int>();
	}
	return 0;
}

std::string Plugin::getFormattedPluginName() {
	std::string formatted = _pluginName;
	std::size_t pos = formatted.find("/");
	if (pos != std::string::npos)
		formatted = formatted.substr(pos+1);
	pos = formatted.find("vim-");
	if (pos != std::string::npos)
		formatted = formatted.substr(4);
	pos = formatted.find("-");
	if (pos != std::string::npos)
		formatted.replace(pos,1, "%20");
	return formatted;
}

std::string Plugin::getVimAwesomePluginClassification() {
	const std::string vimAwesomeAPIQuery = "https://vimawesome.com/api/plugins?query=";
	const std::string githubURLBase = "https://github.com/";

	std::string formattedPluginName = getFormattedPluginName();

	std::string url = vimAwesomeAPIQuery + formattedPluginName;
	std::string jsonHTTP = httpQuery(url);
	std::string githubURL = githubURLBase + _pluginName;
	std::string category = "null";
	if (jsonHTTP != "empty") {
		auto json = nlohmann::json::parse(jsonHTTP);
		for (auto& x : json["plugins"]) {
			if (x["github_url"].get<std::string>() == githubURL) {
				category = x["category"].get<std::string>();
				break;
			}			

		}
	}
	return category;
}

double Plugin::getAmountOfOpenedIssuesToClosed() {
	return double(getOpenedIssues())/double(getClosedIssues());
}

void printGroup(std::vector<Plugin>& group) {
	for(const auto& plug : group) {
		std::cout << plug._pluginName << std::endl;
	}
	std::cout << std::endl;
}

double Plugin::countForGroupOfPluginAmountOfStars(std::vector<Plugin>& group) {
    int starsSum = 0;
    for(Plugin plug : group) {
         starsSum += plug.getStarsCount();
    }
    return double(starsSum)/double(group.size());
}
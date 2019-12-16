#include <nlohmann/json.hpp>
#include <pluginfo.h>

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

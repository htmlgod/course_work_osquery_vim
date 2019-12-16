#include <nlohmann/json.hpp>
#include <pluginfo.h>

const int Plugin::getStarsCount() {
    const std::string url = API::GITHUB_API_ENTRY + "repos/"
	+ _pluginName;

	std::string jsonHTTP = httpQuery(url);
	if (jsonHTTP != "empty") {
		auto json = nlohmann::json::parse(jsonHTTP);
		return json["stargazers_count"].get<int>();
	}
	return 0;
}
const int Plugin::getOpenedIssues() {
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

const int Plugin::getClosedIssues() {
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

const double Plugin::getAmountOfOpenedIssuesToClosed() {
	return getOpenedIssues()/getClosedIssues();
}

void printGroup(std::vector<Plugin>& group) {
	for(int i = 0; i < group.size(); i++) {
		std::cout << group[i]._pluginName << " ";
	}
	std::cout << std::endl;
}

int Plugin::countForGroupOfPluginAmountOfStars(std::vector<Plugin> &list) {
    return 0;
}

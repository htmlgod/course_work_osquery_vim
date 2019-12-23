#pragma once

#include <vector>
#include <webutils.h>

class Plugin {
public:
	explicit Plugin(std::string name);
	Plugin() = default;

	int getStarsCount();

	int getOpenedIssues();

	int getClosedIssues();
	
	std::string getPluginName();

	std::string getVimAwesomePluginClassification();

	double getAmountOfOpenedIssuesToClosed();

	void parseStarsCount();

	void parseOpenedIssues();

	void parseClosedIssues();

	void parseVimAwesomePluginClassification();

	std::string getFormattedPluginName();

	double countForGroupOfPluginAmountOfStars(std::vector<Plugin>& list);

	friend void printGroup(std::vector<Plugin>& group);
private:
	std::string _pluginName;
	int         _starsCount;
	int         _openIssues;
	int         _closedIssues;
	std::string _category;
	double      _openToCloseIssues;
};


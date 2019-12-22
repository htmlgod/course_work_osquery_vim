#pragma once

#include <vector>
#include <webutils.h>

class Plugin {
public:
	explicit Plugin(std::string name) : _pluginName(std::move(name)) {}
	Plugin();
	int getStarsCount();

	int getOpenedIssues();

	int getClosedIssues();

	double getAmountOfOpenedIssuesToClosed();

	std::string getVimAwesomePluginClassification();

	std::string getFormattedPluginName();

	double countForGroupOfPluginAmountOfStars(std::vector<Plugin>& list);
	
	friend void printGroup(std::vector<Plugin>& group);
private:
	std::string _pluginName;
};



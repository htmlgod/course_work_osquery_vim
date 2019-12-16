#pragma once

#include <curl/curl.h>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <utility>
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

	//std::string getVimAwesomePluginClassification();

	double countForGroupOfPluginAmountOfStars(std::vector<Plugin>& list);
	
	friend void printGroup(std::vector<Plugin>& group);
private:
	std::string _pluginName;
};



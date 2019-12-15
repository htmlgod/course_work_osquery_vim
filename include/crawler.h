#pragma once

#include <tools.h>
#include <gumbo.h>

void getListOfPlugins();

void getListOfSettingForPlugins();

void getListOfSettings();

void getListOfModes();

void getRunTime();

int getStarsForPlugin(std::string plugName);

std::string getClassifyForPlugin(std::string plugName);

int getIssuesAmountForPlugin(std::string plugName);

void getGroupStarsAmount();

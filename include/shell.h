#pragma once

#include <boost/program_options.hpp>
#include <plugin.h>
#include <singleton.h>

namespace Shell {
    // Entry point
    void start(int argc, const char *argv[]);

    // GUI functions
    void printMenu();
    void prompt();

    // Version
    void printVersion();

    // Shell commands
    namespace Command {
        void pluginsList();
        void settingsList();
        void vimRuntime();
        void pluginStars();
        void pluginClass();
        void pluginIssues();
        void groupStars();
        void exportToJSON();
        void findStarredPlugins();
    }
}
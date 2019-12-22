#include <singleton.h>
namespace bp = boost::process;
void VimConfig::init() {
	std::cout << "VimConfig singleton started!" << std::endl;
	std::string homePath = getenv("HOME");
	bp::child c("vim --startuptime $HOME/vim.txt +q");

	c.wait();
	std::ifstream vimLog(homePath + "/vim.txt");
    if(vimLog.is_open()) {
        vimLog.seekg(-2,std::ios_base::end);

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            vimLog.get(ch);                

            if((int)vimLog.tellg() <= 1) {
                vimLog.seekg(0);         
                keepLooping = false;    
            }
            else if(ch == '\n') {      
                keepLooping = false;  
            }
            else {                   
                vimLog.seekg(-2,std::ios_base::cur);
            }
        }

        std::string lastLine;
        getline(vimLog,lastLine);                  
        std::stringstream ss(lastLine);
        ss >> _startupTime;
        vimLog.close();
    }
}
double VimConfig::getStartupTimeinMS() {
    return _startupTime;
}
double VimConfig::getStartupTimeinSec() {
	return _startupTime/1000;
}

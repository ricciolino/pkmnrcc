#ifndef PATHS_H
#define PATHS_H

#include<cstdlib>
#include <filesystem>
namespace fs = std::filesystem;
extern char* home;
extern fs::path pkmn_dir;
extern fs::path sav_dir;
extern fs::path tsav_dir;
 
#endif

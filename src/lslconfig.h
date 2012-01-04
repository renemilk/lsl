#ifndef CONFIG_H
#define CONFIG_H

#define STR_DUMMY(name) std::string name () const { return std::string(); }

#include <string>

namespace LSL {

class Config
{
public:
    Config();
    STR_DUMMY( GetCachePath )
    STR_DUMMY( GetForcedSpringConfigFilePath )
    STR_DUMMY( GetCurrentUsedUnitSync )
    std::string GetCurrentUsedUnitSync() { return "/usr/lib/spring/libunitsync.so";}
};

Config& sett();

} // namespace LSL

#endif // CONFIG_H
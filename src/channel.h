#ifndef CHANNEL_H
#define CHANNEL_H

#include <utils/global_interfaces.h>

class Channel : public HasIndex < std::string >
{
public:
    Channel();

    std::string index() const { return "dummy"; }
};

#endif // CHANNEL_H

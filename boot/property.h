#pragma once

#include <string>

struct PropertyLoadResults{
    bool succeeded;
    std::string reason;
};

//TODO: the signature of both methods will be change once I figure out what to do with them
PropertyLoadResults loadProperties() noexcept;

PropertyLoadResults validateProperties() noexcept;

#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include "include.hpp"


namespace StupidJSON
{
std::string CreateJsonFromTags(std::string* Tags, std::string* Values, size_t n);

std::map<std::string, int> ReadJson(const std::string& Message);
}


#endif
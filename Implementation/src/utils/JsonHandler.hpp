#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include "include.hpp"


namespace StupidJSON
{
std::string CreateJsonFromTags(std::string* Tags, std::string* Values, size_t n);
std::string CreateJsonFromTag(std::string Tag, std::string Value);

std::map<std::string, std::string> ReadJson(const std::string& MessageBody);
}


#endif
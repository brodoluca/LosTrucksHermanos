#include "JsonHandler.hpp"

namespace StupidJSON{


std::string CreateJsonFromTags(std::string* Tags, std::string* Values, size_t n)
{

    std::string result;
    result.append("{");

    for(int i = 0;i<n;i++)
    {
        result.append("\"");
        result.append(Tags[i]);
        result.append("\":\"");
        result.append(Values[i]);
        if(i +1 < n )
            result.append("\",");
        
    }

    result.append("}");
    return result;
}



std::map<std::string, int> ReadJson(const std::string& Message);
    std::map<std::string, int> m;
    
    std::stoi( str )
}

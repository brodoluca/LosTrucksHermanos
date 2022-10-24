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
        else
            result.append("\"");
        
    }

    result.append("}");
    return result;
}


std::string CreateJsonFromTag(std::string Tag, std::string Value)
{
    std::string result;
    result.append("{");
    result.append("\"");
    result.append(Tag);
    result.append("\":\"");
    result.append(Value);
    result.append("\"");
    result.append("}");
    return result;
}

std::map<std::string, std::string> ReadJson(const std::string& MessageBody)
{
    std::map<std::string, std::string> m;
    auto my_str = MessageBody;
    my_str.erase(remove(my_str.begin(), my_str.end(), ':'), my_str.end());
    my_str.erase(remove(my_str.begin(), my_str.end(), ','), my_str.end());
    bool key = true;
    std::string tempKey;
    std::string tempValue;
    for (auto it = my_str.cbegin() ;it != my_str.cend(); it++)
    {
        tempKey.clear();
        tempValue.clear();
        if(*it == '\"')
        {
            auto iter = ++it;
            for (; *iter != '\"' ; iter++){
                if( *iter == '}' )
                        break;
                tempKey.push_back(*iter);
            }
            iter+=2;
            for (; *iter != '\"' ; iter++){
                if( *iter == '}' )
                        break;
                tempValue.push_back(*iter);

            }
            it = iter;
        }
        //std::cout <<tempKey << " Value :"<< tempValue<<std::endl;
        //if(!tempKey.empty() && !tempKey.empty())
            m[tempKey] = tempValue;
    }
    //std::cout << m;
    return m;
    //std::stoi( str )
};
}
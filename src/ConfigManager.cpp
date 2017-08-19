//
// Created by yedong on 8/19/17.
//

#include "ConfigManager.h"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::property_tree::info_parser;
using namespace boost::property_tree;




/// <summary>
/// Initializes the configuration file.
/// </summary>
/// <param name="Filename">The filename.</param>
/// <returns>bool.</returns>
bool ConfigManager::InitConfigFile(const std::string & FileName)
{
    WRITE_LOCK lock(mMutex);
    mPT.clear();
    mFileName=FileName;
    try
    {
        read_info(mFileName,mPT);

    }
    catch(const ptree_error & )
    {
        return false;
    }
    return true;

}

bool ConfigManager::save(boost::property_tree::ptree pt)
{
    WRITE_LOCK lock(mMutex);
    try
    {
        write_info(mFileName, pt);

    }
    catch (const ptree_error &)
    {
        return false;
    }
    return true;

}


/// <summary>
/// Gets the configuration values.
/// </summary>
/// <param name="Key">The key.</param>
/// <returns>std.string.</returns>
/**
@Gets the configuration values.
*/
std::string ConfigManager::GetConfigValues(const std::string& Key)
{
    try
    {
        READ_LOCK lock(mMutex);
        return mPT.get<std::string>(Key);
    }
    catch (std::exception & ex)
    {
        std::cout<<"ConfigManager::GetConfigValues error="<<ex.what()<<std::endl;
    }
    return "";
}

/// <summary>
/// Gets the configuration tree.
/// </summary>
/// <param name="Key">The key.</param>
/// <returns>boost.property_tree.ptree.</returns>
boost::property_tree::ptree ConfigManager::GetConfigTree(const std::string& Key)
{
    READ_LOCK lock(mMutex);
    return mPT.get_child(Key);
}

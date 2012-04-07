#include <cstdio>
#include <string>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include "config.hpp"
#include "../dump/save_dump_manager.hpp"

Config::Config()
{
    //setting default values
    host = "0.0.0.0";
    port = "3000";

    number_of_threads = 16;

    is_append_log_enabled = true;

    dump_file_name = "/home/jaaro/dump.shu";

    is_slow_log_enabled = 1;
    slow_log_file_name = "/home/jaaro/slow_log.log";
    slow_log_miliseconds_bound = 1.0;

    set("save_dump", "1 1");
}

Config::~Config() {}
Config::Config(const Config&) {}
void Config::operator = (const Config&) {}

Config& Config::getInstance()
{
    static Config instance;
    return instance;
};

void Config::set(const std::string& name, const std::string& value)
{
    // setting config value
    if (name == "host") {
        host = value;
    } else if (name == "port") {
        port = value;
    } else if (name == "number_of_threads") {
        number_of_threads = boost::lexical_cast<int>(value);
    } else if (name == "is_append_log_enabled") {
        is_append_log_enabled = boost::lexical_cast<bool>(value);
    } else if (name == "save_dump") {
        std::stringstream my_stream(value);
        //TODO it should be validated
        int period, changes;
        my_stream >> period >> changes;
        SaveDumpManager::getInstance().add_interval_save(period, changes);
    } else {
        printf("No such parameter as %s", name.c_str());
    }
}

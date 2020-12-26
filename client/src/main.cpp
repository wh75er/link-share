#include "presenter.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>


const std::string host = "localhost";
const size_t port = 13201;

class JsonParser {
public:
    explicit JsonParser(std::string& json_str) {
        std::stringstream ss;

        ss << json_str;

        try {
            boost::property_tree::read_json(ss, pt);
        }
        catch (...) {
            throw std::runtime_error("Failed to parse json!");
        }
    }

    template<typename T>
    bool get_value(const char* key, T& value) {
        if (boost::optional<T> v = pt.get_optional<T>(key)) {
            value = *v;
            return true;
            } else {
                return false;
        }
    }

    bool get_value(const char* key, std::vector<std::string>& value) {
        if (pt.get_child_optional(key)) {
        BOOST_FOREACH (boost::property_tree::ptree::value_type& field, pt.get_child(key))
        {
            value.push_back(field.second.data());
        }
        return true;
    }

    return false;
  }

private:
    boost::property_tree::ptree pt;
};


int main() {

    Presenter<JsonParser> pr(host, port);
    pr.run();
    return 0;
}
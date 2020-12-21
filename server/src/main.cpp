#include "server.hpp"
#include "errors.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "pgconnection.hpp"

class Uuid {
public:
  void generate() {
    u = gen();
  }

  std::string to_string(){
    if (u.is_nil()) {
      return "";
    }
    return boost::uuids::to_string(u);
  }

private:
  boost::uuids::uuid u;
  boost::uuids::random_generator gen;
};

class JsonParser {
public:
  explicit JsonParser(std::string& json_str) {
    std::stringstream ss;

    ss << json_str;

    try {
      boost::property_tree::read_json(ss, pt);
    }
    catch (...) {
#ifdef DEBUG
      std::cout << "Failed to parse json!" << std::endl;
#endif
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
  std::string address = "127.0.0.1";
  std::string port = "13201";

  try {
    TCPserver server = TCPserver<PGBackend, Uuid, JsonParser>(address, port);

    std::cout << "Set to listen" << std::endl;

    server.listen();

    std::cout << "Server starting on " << address << ":" << port << std::endl;

    server.accept();
  }
  catch (const BaseException& except){
    std::cout << except.what() << std::endl;
    std::cout << except.msg << std::endl;
  }

}

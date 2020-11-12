#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <memory>

namespace pt = boost::property_tree;

class BodyParser {
public:
  BodyParser();
  ~BodyParser();

  void parse(std::string data);

private:
  pt::ptree root;
};

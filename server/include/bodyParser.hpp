#pragma once

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

#include "errors.hpp"
#include "request.hpp"
#include "formRequest.hpp"
#include "utilities/split.hpp"

class AbstractBodyParser {
public:
//  AbstractBodyParser() {};
  virtual ~AbstractBodyParser() {};

  virtual std::shared_ptr<BaseHandler> parse(std::string data) = 0;
};

template<class JsonParser>
class TcpStringBodyParser : public AbstractBodyParser {
  public:
    TcpStringBodyParser();
    ~TcpStringBodyParser() {};
    
    std::shared_ptr<BaseHandler> parse(std::string data) override;

  private:
    std::vector<std::unique_ptr<AbstractFormRequest<JsonParser>>> registeredRequestFormers;
};

#include "BodyParser.tpp"
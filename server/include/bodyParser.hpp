#pragma once

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

#include "errors.hpp"
#include "request.hpp"
#include "formRequest.hpp"
#include "utilities/split.hpp"

template<class Model>
class AbstractBodyParser {
public:
//  AbstractBodyParser() {};
  virtual ~AbstractBodyParser() {};

  virtual std::shared_ptr<BaseHandler<Model>> parse(std::string data) = 0;
};

template<class Model, class JsonParser>
class TcpStringBodyParser : public AbstractBodyParser<Model> {
  public:
    TcpStringBodyParser();
    ~TcpStringBodyParser() {};
    
    std::shared_ptr<BaseHandler<Model>> parse(std::string data) override;

  private:
    std::vector<std::unique_ptr<AbstractFormRequest<JsonParser, Model>>> registeredRequestFormers;
};

#include "bodyParser.tpp"
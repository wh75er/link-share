#pragma once

/* class AbstractResponseParser {
public:
  virtual ~AbstractResponseParser() {};

  virtual std::shared_ptr<BaseHandler<Model>> parse(std::string data) = 0;
};

template<class Model, class JsonParser>
class TcpStringBodyParser : public AbstractResponseParser {
  public:
    TcpStringBodyParser();
    ~TcpStringBodyParser() {};
    
    std::shared_ptr<BaseHandler<Model>> parse(std::string data) override;

  private:
    std::vector<std::unique_ptr<AbstractFormRequest<JsonParser, Model>>> registeredRequestFormers;
};

#include "bodyParser.tpp" */
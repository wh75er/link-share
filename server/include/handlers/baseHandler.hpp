#pragma once

class BaseHandler {
public:
  BaseHandler();
  virtual ~BaseHandler();

  virtual void execute();

private:
};

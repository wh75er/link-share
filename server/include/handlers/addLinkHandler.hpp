#pragma once

#include <string>
#include <memory>

#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class AddLinkHandler: public BaseHandler<Model> {
public:
  explicit AddLinkHandler(LinkRequest request);
  ~AddLinkHandler() = default;

  void execute() override;

private:
  LinkRequest request_;
};

template<class Model>
AddLinkHandler<Model>::AddLinkHandler(LinkRequest request):
        request_(request)
{
}

template<class Model>
void AddLinkHandler<Model>::execute() {
  return;
}

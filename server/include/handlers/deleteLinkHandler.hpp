#pragma once

#include <string>
#include <memory>

#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class DeleteLinkHandler: public BaseHandler<Model> {
public:
  explicit DeleteLinkHandler(LinkRequest request);
  ~DeleteLinkHandler() = default;

  void execute() override;

private:
  LinkRequest request_;
};

template<class Model>
DeleteLinkHandler<Model>::DeleteLinkHandler(LinkRequest request):
        request_(request)
{
}

template<class Model>
void DeleteLinkHandler<Model>::execute() {
  return;
}

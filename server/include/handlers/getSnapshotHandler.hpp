#pragma once

#include <string>
#include <memory>

#include "webLink.hpp"
#include "response.hpp"
#include "request.hpp"

template<class Model>
class GetSnapshotHandler: public BaseHandler<Model> {
public:
  explicit GetSnapshotHandler(SnapshotRequest request);
  ~GetSnapshotHandler() = default;

  void execute() override;

private:
  SnapshotRequest request_;
};

template<class Model>
GetSnapshotHandler<Model>::GetSnapshotHandler(SnapshotRequest request):
        request_(request)
{
}

template<class Model>
void GetSnapshotHandler<Model>::execute() {
  return;
}

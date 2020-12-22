#pragma once

#include "dbModel.hpp"

template<class DbOps, class Uuid>
class Model {
public:
  explicit Model(std::shared_ptr<DbOps> dbops);
  ~Model() = default;

private:
  Uuid uuid;
  DbApi<DbOps> api{};
};

template<class DbOps, class Uuid>
Model<DbOps, Uuid>::Model(std::shared_ptr <DbOps> dbops):
        api(DbApi(dbops)) {
}

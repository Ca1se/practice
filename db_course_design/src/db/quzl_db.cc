#include "quzl_db.hh"
#include <memory>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/Executor.hpp>

QuzlDb::QuzlDb(const std::shared_ptr<oatpp::orm::Executor>& executor):
        oatpp::orm::DbClient(executor) {
    auto version = executor->getSchemaVersion();
    OATPP_LOGD("QuzlDb", "Migration - OK. Version=%lld.", version);
}
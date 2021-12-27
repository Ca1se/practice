#include "user_db.hh"
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/SchemaMigration.hpp>

UserDb::UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor):
        oatpp::orm::DbClient(executor) {
    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1, SQL_INIT_FILE_PATH "/init.sql");
    migration.migrate();

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);
}
#ifndef _DB_COMPONENT_HH_
#define _DB_COMPONENT_HH_

#include <chrono>
#include <memory>
#include <oatpp-sqlite/ConnectionProvider.hpp>
#include <oatpp-sqlite/Executor.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/core/provider/Provider.hpp>
#include "quzl_db.hh"
#include "user_db.hh"

class DbComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([]() {
        auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

        return oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
                                                           10,
                                                           std::chrono::seconds(5));
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, user_db)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, provider);

        auto executor = std::make_shared<oatpp::sqlite::Executor>(provider);

        return std::make_shared<UserDb>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<QuzlDb>, quzl_db)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, provider);

        auto executor = std::make_shared<oatpp::sqlite::Executor>(provider);

        return std::make_shared<QuzlDb>(executor);
    }());
};

#endif
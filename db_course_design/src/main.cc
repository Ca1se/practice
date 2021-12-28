#include <memory>
#include <oatpp/network/ConnectionHandler.hpp>
#include <oatpp/network/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/network/Server.hpp>
#include "app_component.hh"
#include "ui/ui_controller.hh"
#include "controller.hh"

inline void run() {
    AppComponent component;

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    router->addController(Controller::createShared());
    router->addController(UIController::createShared());

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider,
            connectionHandler);

    OATPP_LOGD("Server", "Running on port %s", connectionProvider->getProperty("port").toString()->c_str());

    server.run();
}

int main() {
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::destroy();
    return 0;
}
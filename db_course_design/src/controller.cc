#include "controller.hh"
#include <memory>
#include <oatpp/web/server/api/ApiController.hpp>

Controller::Controller(
        const std::shared_ptr<ObjectMapper>& objectMapper,
        const std::shared_ptr<Resource>& resource):
        oatpp::web::server::api::ApiController(objectMapper),
        resource_(resource) {}
#include "controller.hh"
#include <oatpp/web/server/api/ApiController.hpp>

Controller::Controller(
        const std::shared_ptr<ObjectMapper>& objectMapper):
        oatpp::web::server::api::ApiController(objectMapper) {}
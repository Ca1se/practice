#include "user_controller.hh"
#include <oatpp/web/server/api/ApiController.hpp>

UserController::UserController(
        const std::shared_ptr<ObjectMapper>& objectMapper):
        oatpp::web::server::api::ApiController(objectMapper) {}
#include "ui_controller.hh"
#include "resource.hh"
#include <memory>
#include <oatpp-1.3.0/oatpp/oatpp/core/macro/component.hpp>
#include <oatpp-1.3.0/oatpp/oatpp/web/server/api/ApiController.hpp>

UIController::UIController(const std::shared_ptr<ObjectMapper>& objectMapper,
        const std::shared_ptr<Resource>& resource):
        oatpp::web::server::api::ApiController(objectMapper),
        resource_(resource) {}
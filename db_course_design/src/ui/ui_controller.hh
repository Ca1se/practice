#ifndef _UI_CONTROLLER_HH_
#define _UI_CONTROLLER_HH_

#include <memory>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include "resource.hh"


class UIController: public oatpp::web::server::api::ApiController {
private:
    std::shared_ptr<Resource> resource_;
public:
    UIController(const std::shared_ptr<ObjectMapper>& objectMapper,
            const std::shared_ptr<Resource>& resource);
        
public:

    /**
    * create shared_ptr to UIController
    * @param resource - shared_ptr to Resource
    * @return - shared_ptr to UIController
    */
    static std::shared_ptr<UIController> createShared(
            OATPP_COMPONENT(std::shared_ptr<Resource>, resource)) {
        auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
        serializerConfig->includeNullFields = false;
        
        auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
        deserializerConfig->allowUnknownFields = false;
        
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
       
        return std::make_shared<UIController>(objectMapper, resource);
    }

#include OATPP_CODEGEN_BEGIN(ApiController) // codegen begin

    ENDPOINT("GET", "/", getUIRoot) {
        return createResponse(Status::CODE_200, resource_->getResource("index.html"));
    }

    ENDPOINT("GET", "/{filename}", getUIResource, PATH(String, filename)) {
        return createResponse(Status::CODE_200, resource_->getResource(filename->c_str()));
    }

#include OATPP_CODEGEN_END(ApiController) // codegen end

};


#endif
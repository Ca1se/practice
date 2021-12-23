#ifndef _UI_COMPONENT_HH_
#define _UI_COMPONENT_HH_

#include <memory>
#include <oatpp/core/macro/component.hpp>
#include "resource.hh"
class UIComponent {
public:
    /**
    * UI Resource ({project_path}/res/)
    */
    OATPP_CREATE_COMPONENT(std::shared_ptr<Resource>, ui_resource)([] {
        return Resource::loadResources(kResDirPath);
    }());
};

#endif
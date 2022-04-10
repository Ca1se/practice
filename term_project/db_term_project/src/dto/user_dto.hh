#ifndef _USER_DTO_HH_
#define _USER_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class UserDto: public oatpp::DTO {
    DTO_INIT(UserDto, DTO);

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(String, user_name, "username");
    DTO_FIELD(String, password, "password");
};


#include OATPP_CODEGEN_END(DTO) // codegen end

#endif
#ifndef _OPTION_DTO_HH_
#define _OPTION_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class OptionDto: public oatpp::DTO {
    DTO_INIT(OptionDto, DTO);

    DTO_FIELD(String, option_content, "optcontent");
};

#include OATPP_CODEGEN_END(DTO) // codegen end

#endif
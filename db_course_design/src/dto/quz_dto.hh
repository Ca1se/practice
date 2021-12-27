#ifndef _QUZ_DTO_HH_
#define _QUZ_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>
#include "option_dto.hh"

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class QuzDto: public oatpp::DTO {
    DTO_INIT(QuzDto, DTO);

    DTO_FIELD(String, quz_content, "quzcontent");
    DTO_FIELD(Vector<Object<OptionDto>>, option_list, "optlist");
};

#include OATPP_CODEGEN_END(DTO) // codegen end

#endif
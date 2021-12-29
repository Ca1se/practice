#ifndef _UTIL_DTO_HH_
#define _UTIL_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class QuzlNameDto: public oatpp::DTO {
    DTO_INIT(QuzlNameDto, DTO);

    DTO_FIELD(String, quzl_name, "quzlname");
};

class QuzIdNameDto: public oatpp::DTO {
    DTO_INIT(QuzIdNameDto, DTO);

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(String, quz_name, "quzcontent");
};

#include OATPP_CODEGEN_END(DTO) // codegen end

#endif
#ifndef _QUZL_DTO_HH_
#define _QUZL_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>
#include "quz_dto.hh"

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class QuzlDto: public oatpp::DTO {
    DTO_INIT(QuzlDto, DTO);

    DTO_FIELD(String, quzl_name, "quzlname");
    DTO_FIELD(Vector<Object<QuzDto>>, quz_list, "quzlist");
};

#include OATPP_CODEGEN_END(DTO) // codegen end

#endif
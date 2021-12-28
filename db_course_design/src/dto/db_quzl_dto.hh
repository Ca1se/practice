#ifndef _DB_QUZL_DTO_HH_
#define _DB_QUZL_DTO_HH_

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO) // codegen begin

class DbQuzlDto: public oatpp::DTO {
    DTO_INIT(DbQuzlDto, DTO);

    DTO_FIELD(Int32, id, "id");
    DTO_FIELD(String, quzl_name, "quzlname");
    DTO_FIELD(String, owner_name, "username");
};

#include OATPP_CODEGEN_END(DTO) // codegen begin

#endif
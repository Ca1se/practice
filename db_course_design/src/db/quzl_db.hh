#ifndef _QUZL_DB_HH_
#define _QUZL_DB_HH_

#include <memory>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/Executor.hpp>
#include "../dto/quzl_dto.hh"

class QuzlDb: public oatpp::orm::DbClient {
public:
    QuzlDb(const std::shared_ptr<oatpp::orm::Executor>& executor);

#include OATPP_CODEGEN_BEGIN(DbClient) // codegen begin

    QUERY(createQuzl,
            "insert into quzl_table"
            "(quzlname, ownerid) values"
            "(:name, :id);",
            PARAM(oatpp::String, name), PARAM(oatpp::Int32, id))

#include OATPP_CODEGEN_END(DbClient) // codegen end
};

#endif
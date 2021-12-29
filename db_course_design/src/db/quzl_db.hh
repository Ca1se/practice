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
        
    QUERY(createQuz,
            "insert into quz_table"
            "(quzcontent, quzlid) values"
            "(:content, :id);",
            PARAM(oatpp::String, content), PARAM(oatpp::Int32, id))

    QUERY(createOption,
            "insert into option_table"
            "(optcontent, quzid) values"
            "(:content, :id);",
            PARAM(oatpp::String, content), PARAM(oatpp::Int32, id))
        
    QUERY(getAllQuzlName,
            "select quzl_table.id, quzlname, username from quzl_table, user_table where quzl_table.ownerid=user_table.id;")
    
    QUERY(getQuzlNameById,
            "select quzlname from quzl_table where id=:id",
            PARAM(oatpp::Int32, id))

    QUERY(getQuzIdNameByQuzlId,
            "select quz_table.id, quzcontent from quzl_table, quz_table where quzl_table.id=:id and quzl_table.id=quz_table.quzlid;",
            PARAM(oatpp::Int32, id))

    QUERY(getOptIdNameByQuzId,
            "select optcontent from quz_table, option_table where quz_table.id=:id and quz_table.id=option_table.quzid;",
            PARAM(oatpp::Int32, id))

#include OATPP_CODEGEN_END(DbClient) // codegen end
};

#endif
#ifndef _USER_DB_HH_
#define _USER_DB_HH_

#include <memory>
#include <oatpp-sqlite/orm.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/Executor.hpp>
#include "../dto/user_dto.hh"

class UserDb: public oatpp::orm::DbClient {
public:
    UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor);

#include OATPP_CODEGEN_BEGIN(DbClient) // codegen begin

    QUERY(createUser,
            "insert into user_table"
            "(username, password) values"
            "(:user.username, :user.password);",
            PARAM(oatpp::Object<UserDto>, user))   

    QUERY(getUserByName,
            "select * from user_table where username=:name;",
            PARAM(oatpp::String, name))
        
    QUERY(getUserById,
            "select * from user_table where id=:id;",
            PARAM(oatpp::Int32, id));


#include OATPP_CODEGEN_END(DbClient) // codegen end

};

#endif
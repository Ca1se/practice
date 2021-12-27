#ifndef _USER_SERVICE_HH_
#define _USER_SERVICE_HH_

#include <cstdint>
#include <memory>
#include <oatpp/core/macro/component.hpp>
#include <unordered_map>
#include <oatpp/core/Types.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include "../db/user_db.hh"

class UserService {
public:
    void createUser(const oatpp::Object<UserDto>& user);

    std::shared_ptr<oatpp::Object<UserDto>> getUserByName(const oatpp::String& name);

    oatpp::Int64 checkUser(const oatpp::Object<UserDto>& user);

    oatpp::Object<UserDto> getUserByCookie(int64_t session);

    std::shared_ptr<oatpp::Object<UserDto>> getUserById(const oatpp::Int32& id);

private:
    typedef oatpp::web::protocol::http::Status Status;

    OATPP_COMPONENT(std::shared_ptr<UserDb>, db_);
    std::unordered_map<int64_t, oatpp::Int32> session_map_;
};

#endif
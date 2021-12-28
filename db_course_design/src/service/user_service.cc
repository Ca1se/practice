#include <memory>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include <system_error>
#include "user_service.hh"
#include "../utils.hh"

void UserService::createUser(const oatpp::Object<UserDto>& user) {
    auto result = getUserByName(user->user_name);
    OATPP_ASSERT_HTTP(!result, Status::CODE_400, "用户名已被使用");

    auto res = db_->createUser(user);
    OATPP_ASSERT_HTTP(res->isSuccess(), Status::CODE_500, "Unknown error");
}

std::shared_ptr<oatpp::Object<UserDto>> UserService::getUserByName(
        const oatpp::String& name) {
    auto result = db_->getUserByName(name);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, "Unknown error");
    if(!result->hasMoreToFetch()) {
        return std::shared_ptr<oatpp::Object<UserDto>>();
    }

    auto ret = result->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
    OATPP_ASSERT_HTTP(ret->size() == 1, Status::CODE_500, "Unknown error");

    return std::make_shared<oatpp::Object<UserDto>>(ret[0]);
}

oatpp::Int64 UserService::checkUser(const oatpp::Object<UserDto>& user) {
    auto result = getUserByName(user->user_name);
    OATPP_ASSERT_HTTP(result, Status::CODE_404, "找不到用户!");

    OATPP_ASSERT_HTTP((user->password == (*result)->password), Status::CODE_401, "错误的用户名或密码");

    int64_t session_id = generateSessionId();
    session_map_[session_id] = (*result)->id;
    return session_id;
}

std::shared_ptr<oatpp::Object<UserDto>> UserService::getUserById(const oatpp::Int32& id) {
    auto result = db_->getUserById(id);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, "Unknown error");
    if(!result->hasMoreToFetch()) {
        return std::shared_ptr<oatpp::Object<UserDto>>();
    }

    auto ret = result->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
    OATPP_ASSERT_HTTP(ret->size() == 1, Status::CODE_500, "Unknown error");

    return std::make_shared<oatpp::Object<UserDto>>(ret[0]);
}

oatpp::Object<UserDto> UserService::getUserByCookie(int64_t session) {
    auto it = session_map_.find(session);
    OATPP_ASSERT_HTTP(it != session_map_.end(), Status::CODE_401, "Invalid session id");

    auto user = getUserById(it->second);
    if(!user) {
        session_map_.erase(it);
        throw oatpp::web::protocol::http::HttpError(Status::CODE_401, "Invalid session id");
    }

    return *user;
}

void UserService::deleteSessionId(int64_t session) {
    auto it = session_map_.find(session);
    if(it != session_map_.end()) {
        session_map_.erase(it);
    }
}
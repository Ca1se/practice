#ifndef _QUZL_SERVICE_HH_
#define _QUZL_SERVICE_HH_

#include <memory>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include "../db/quzl_db.hh"
#include "../dto/db_quzl_dto.hh"

class QuzlService {
public:
    void createQuzlist(const oatpp::Object<QuzlDto>& quzl, const oatpp::Int32& user_id);

    oatpp::Vector<oatpp::Object<DbQuzlDto>> getAllQuzl();

    oatpp::Object<QuzlDto> getQuzlById(const oatpp::Int32& id);

private:
    typedef oatpp::web::protocol::http::Status Status;

    OATPP_COMPONENT(std::shared_ptr<QuzlDb>, db_);
};

#endif
#ifndef _QUZL_SERVICE_HH_
#define _QUZL_SERVICE_HH_

#include <memory>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include "../db/quzl_db.hh"

class QuzlService {
public:
    void 

private:
    typedef oatpp::web::protocol::http::Status Status;

    OATPP_COMPONENT(std::shared_ptr<QuzlDb>, db_);
};

#endif
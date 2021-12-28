#include <oatpp/web/protocol/http/Http.hpp>
#include <oatpp-sqlite/Utils.hpp>
#include "quzl_service.hh"

void QuzlService::createQuzlist(
        const oatpp::Object<QuzlDto>& quzl, 
        const oatpp::Int32& user_id) {
    auto quzl_res = db_->createQuzl(quzl->quzl_name, user_id);
    auto quzl_id = oatpp::sqlite::Utils::getLastInsertRowId(quzl_res->getConnection());
    const auto& quz_vec = quzl->quz_list;
    for(int i = 0; i < quz_vec->size(); i++) {
        auto quz_res = db_->createQuz(quz_vec[i]->quz_content, quzl_id);
        auto quz_id = oatpp::sqlite::Utils::getLastInsertRowId(quz_res->getConnection());
        const auto& opt_vec = quz_vec[i]->option_list;
        for(int k = 0; k < opt_vec->size(); k++) {
            db_->createOption(opt_vec[k]->option_content, quz_id);
        }
    }
}
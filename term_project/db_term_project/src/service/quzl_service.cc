#include <oatpp/core/Types.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include <oatpp-sqlite/Utils.hpp>
#include <iostream>
#include "quzl_service.hh"
#include "../dto/util_dto.hh"

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

oatpp::Vector<oatpp::Object<DbQuzlDto>> QuzlService::getAllQuzl() {
    auto result = db_->getAllQuzlName();
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, "Unknown error");
    if(!result->hasMoreToFetch()) {
        return oatpp::Vector<oatpp::Object<DbQuzlDto>>::createShared();
    }

    auto ret = result->fetch<oatpp::Vector<oatpp::Object<DbQuzlDto>>>();
    return ret;
}

oatpp::Object<QuzlDto> QuzlService::getQuzlById(const oatpp::Int32& id) {
    auto ret = oatpp::Object<QuzlDto>::createShared();
    ret->quzl_name = db_->getQuzlNameById(id)->fetch<oatpp::Vector<oatpp::Object<QuzlNameDto>>>()[0]->quzl_name;
    ret->quz_list = oatpp::Vector<oatpp::Object<QuzDto>>::createShared();
    auto quz_list = db_->getQuzIdNameByQuzlId(id)->fetch<oatpp::Vector<oatpp::Object<QuzIdNameDto>>>();
    for(int i = 0; i < quz_list->size(); i++) {
        auto quz = oatpp::Object<QuzDto>::createShared();
        quz->quz_content = quz_list[i]->quz_name;
        quz->option_list = db_->getOptIdNameByQuzId(quz_list[i]->id)->fetch<oatpp::Vector<oatpp::Object<OptionDto>>>();
        ret->quz_list->push_back(quz);
    }
    return ret;
}
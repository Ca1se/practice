#include <oatpp-1.3.0/oatpp/oatpp/core/IODefinitions.hpp>
#include <oatpp-1.3.0/oatpp/oatpp/core/Types.hpp>
#include <oatpp-1.3.0/oatpp/oatpp/core/async/Coroutine.hpp>
#include <oatpp/core/base/Environment.hpp>
#include "resource.hh"
#include <fstream>

Resource::Resource(const std::string& res_dir_path) {
    setResDirPath(res_dir_path);
}

bool Resource::loadResource(const std::string &res_name) {
    using namespace std;
    string full_name = res_dir_path_ + res_name;

    ifstream file(full_name, ios::in | ios::binary | ios::ate);
    
    if(file.is_open()) {
        oatpp::String result((int32_t) file.tellg());
        file.seekg(0, ios::beg);
        file.read((char*) result->data(), result->size());
        file.close();

        res_map_[res_name] = std::move(result);
        return true;
    }

    OATPP_LOGE("Resource::loadResource()", "%s resource not found,"
            "make sure that resource directory path and resource name are set correctly.", 
            full_name.c_str());
    return false;
}

Resource::ReadCallback::ReadCallback(const oatpp::String& file):
        file_(file), stream_(file->c_str()) {}

oatpp::v_io_size Resource::ReadCallback::read(void* buffer,
        v_buff_size count, oatpp::async::Action& action) {
    return stream_.read(buffer, count, action);
}
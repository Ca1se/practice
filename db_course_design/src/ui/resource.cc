#include <oatpp/core/base/Environment.hpp>
#include "resource.hh"
#include <fstream>

const oatpp::String Resource::kNoResource = "No such resource.";

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
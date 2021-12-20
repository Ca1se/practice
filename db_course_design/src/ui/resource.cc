#include "resource.hh"
#include <fstream>

const std::string Resource::kNoResource = "";

Resource::Resource(const std::string& res_dir_path):
        res_dir_path_(res_dir_path) {}

bool Resource::loadResource(const std::string &res_name) {
    using namespace std;
    string full_name = res_dir_path_ + res_name;

    ifstream file(full_name, ios::in | ios::binary | ios::ate);
    
    if(file.is_open()) {
        string result;

        uint32_t length = file.tellg();
        result.resize(length);

        file.seekg(0, ios::beg);
        file.read((char*) result.data(), length);
        file.close();

        res_map_[res_name] = std::move(result);
        return true;
    }

    OATPP_LOGE("Resource::loadResource()", "%s resource not found,"
            "make sure that resource directory path and resource name are set correctly.", 
            full_name.c_str());
    return false;
}
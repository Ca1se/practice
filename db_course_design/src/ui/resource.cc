#include <dirent.h>
#include <sys/stat.h>
#include <stdexcept>
#include <memory>
#include <cstring>
#include <oatpp/core/base/Environment.hpp>
#include <fstream>
#include "resource.hh"

Resource::Resource(const std::string& res_dir_path) {
    setResDirPath(res_dir_path);
}

bool Resource::loadResourceFromFile(const std::string &res_name) {
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

std::shared_ptr<Resource> Resource::loadResources(
        const std::string &res_dir_path) {
    DIR* dir = opendir(res_dir_path.c_str());
    if(dir == nullptr) {
        throw std::runtime_error("Resource::loadResources(): invalid resource directory path.");
    }

    std::string path = res_dir_path.back() != '/' ?
            res_dir_path + '/' : res_dir_path;

    auto ret = std::make_shared<Resource>(path);

    dirent* p = nullptr;
    while((p = readdir(dir)) != nullptr) {
        struct stat st;
        if(p->d_name[0] != '.') {
            stat((path + std::string{p->d_name}).c_str(), &st);
            if(!S_ISDIR(st.st_mode)) {
                ret->loadResourceFromFile(p->d_name);
            }
        }
    }
    closedir(dir);
    return ret;
}
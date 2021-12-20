#ifndef _RESOURCE_HH_
#define _RESOURCE_HH_

#include <oatpp-1.3.0/oatpp/oatpp/core/base/Environment.hpp>
#include <unordered_map>
#include <string>

class Resource {
public:
    Resource(const std::string& res_dir);
    ~Resource() = default;

    void setResDirPath(const std::string& path) {
        res_dir_path_ = path;
    }

    bool loadResource(const std::string& res_name);

    const std::string& getResource(const std::string& res) const {
        const auto& it = res_map_.find(res);
        if(it != res_map_.end()) {
            return it->second;
        }else {
            return kNoResource;
        }
    }
    
private:
    static const std::string kNoResource;

    std::string res_dir_path_;
    std::unordered_map<std::string, std::string> res_map_;
};

#endif // _RESOURCE_HH_
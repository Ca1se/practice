#ifndef _RESOURCE_HH_
#define _RESOURCE_HH_

#include <stdexcept>
#include <unordered_map>
#include <string>

static const char* const kResDirPath = "/home/ca1se/Documents/practice/db_course_design/res/";

class Resource {
public:
    Resource(const std::string& res_dir);

public:
    /**
    * set the path of ui resource directory 
    * @param path - the path of ui resource directory
    */
    void setResDirPath(const std::string& path) {
        if(path.size() == 0) throw std::runtime_error("Resource::setResDirPath(): empty path");

        res_dir_path_ = path;
        if(path.back() != '/') res_dir_path_.push_back('/');
    }

    /**
    * load resource from local resource file
    * @param res_name - resource name
    * @return - returns True if the resource is loaded successfully
    */
    bool loadResource(const std::string& res_name);

    /**
    * find resource by its name
    * @param res - resource name
    * @return - resource
    */
    const std::string& getResource(const std::string& res) const {
        const auto& it = res_map_.find(res);
        if(it != res_map_.end()) {
            return it->second;
        }else {
            return kNoResource;
        }
    }
    
public:
    static const std::string kNoResource;

private:
    std::string res_dir_path_;
    std::unordered_map<std::string, std::string> res_map_;
};

#endif // _RESOURCE_HH_
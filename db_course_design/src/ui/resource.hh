#ifndef _RESOURCE_HH_
#define _RESOURCE_HH_

#include <memory>
#include <oatpp/core/data/stream/BufferStream.hpp>
#include <oatpp/core/data/stream/FileStream.hpp>
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
    bool loadResourceFromFile(const std::string& res_name);

    /**
    * load all resources from resource directory
    * @param res_dir_path - resource directory path
    * @return - shared_ptr to Resource
    */
    static std::shared_ptr<Resource> loadResources(const std::string& res_dir_path);

    /**
    * find resource by its name
    * @param res - resource name
    * @return - resource
    */
    const oatpp::String& getResource(const std::string& res) const {
        const auto& it = res_map_.find(res);
        if(it != res_map_.end()) {
            return it->second;
        }

        throw std::runtime_error("no such resource");
    }

private:
    std::string res_dir_path_;
    std::unordered_map<std::string, oatpp::String> res_map_;
};

#endif // _RESOURCE_HH_
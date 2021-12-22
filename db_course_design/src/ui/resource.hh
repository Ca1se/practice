#ifndef _RESOURCE_HH_
#define _RESOURCE_HH_

#include <memory>
#include <oatpp-1.3.0/oatpp/oatpp/core/IODefinitions.hpp>
#include <oatpp-1.3.0/oatpp/oatpp/core/base/Environment.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/data/stream/BufferStream.hpp>
#include <oatpp/core/data/stream/FileStream.hpp>
#include <stdexcept>
#include <unordered_map>
#include <string>

static const char* const kResDirPath = "/home/ca1se/Documents/practice/db_course_design/res/";

class Resource {
private:
    class ReadCallback: public oatpp::data::stream::ReadCallback {
    private:
        oatpp::String file_;
        oatpp::data::stream::FileInputStream stream_;
    public:
        ReadCallback(const oatpp::String& file);
        oatpp::v_io_size read(void* buffer, v_buff_size count, oatpp::async::Action& action) override;
    };

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
    const oatpp::String& getResource(const std::string& res) const {
        const auto& it = res_map_.find(res);
        if(it != res_map_.end()) {
            return it->second;
        }

        throw std::runtime_error("no such resource");
    }

    /**
    * return resource stream by its name
    * @param res - resource name
    * @return - resource stream
    */
    std::shared_ptr<Resource::ReadCallback> getResourceStream(
            const std::string& res) const {
        try {
            return std::make_shared<Resource::ReadCallback>(res_dir_path_ + res);
        }catch(std::runtime_error& e) {
            throw std::runtime_error("no such resource");
        }
    }

private:
    std::string res_dir_path_;
    std::unordered_map<std::string, oatpp::String> res_map_;
};

#endif // _RESOURCE_HH_
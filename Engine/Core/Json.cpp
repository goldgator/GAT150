#include "pch.h"
#include "Json.h"
#include <istreamwrapper.h>

namespace nc {
    namespace json {
        bool Load(const std::string& filename, rapidjson::Document& document)
        {
            bool success = false;
            std::ifstream stream(filename);
            ASSERT(stream.good());
            if (stream.is_open()) {
                rapidjson::IStreamWrapper istream(stream);
                document.ParseStream(istream);       
                success = document.IsObject(); 
                ASSERT_MSG(success, "Error json not valid: " + filename);

                stream.close();
            }
            return success;
        }

        bool Get(const rapidjson::Value& value, const std::string& name, int& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()){
                return false;
            }
            // check if type is desired type
            auto& property = iter->value;
            if (property.IsInt() == false){
                return false;
            }
            // set data
            data = property.GetInt();
            return true;
        }

        bool Get(const rapidjson::Value& value, const std::string& name, float& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()){
                return false;
            }
            // check if type is desired type
            auto& property = iter->value;
            if (property.IsNumber() == false){
                return false;
            }
            // set data
            data = property.GetFloat();
            return true;
        }
        bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if type is desired type
            auto& property = iter->value;
            if (property.IsBool() == false) {
                return false;
            }
            // set data
            data = property.GetBool();
            return true;
        }
        bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if type is desired type
            auto& property = iter->value;
            if (property.IsString() == false) {
                return false;
            }
            // set data
            data = property.GetString();
            return true;
        }
        bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false; 
            }
            // check if property has two values
            auto& property = iter->value;
            if (property.IsArray() == false || property.Size() != 2) {
                return false; 
            }
            // check if property has proper typing
            for (rapidjson::SizeType i = 0; i < 2; i++) {
                if (property[i].IsNumber() == false) {
                    return false; 
                } 
            }
            // set data
            data.x = property[0].GetFloat();
            data.y = property[1].GetFloat();
            return true;
        }
        bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if property has two values
            auto& property = iter->value;
            if (property.IsArray() == false || property.Size() != 4) {
                return false;
            }
            // check if property has proper typing
            for (rapidjson::SizeType i = 0; i < 4; i++) {
                if (property[i].IsNumber() == false) {
                    return false;
                }
            }
            // set data
            data.r = property[0].GetFloat();
            data.g = property[1].GetFloat();
            data.b = property[2].GetFloat();
            data.a = property[3].GetFloat();
            return true;
        }
        bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if property has two values
            auto& property = iter->value;
            if (property.IsArray() == false || property.Size() != 4) {
                return false;
            }
            // check if property has proper typing
            for (rapidjson::SizeType i = 0; i < 4; i++) {
                if (property[i].IsNumber() == false) {
                    return false;
                }
            }
            // set data
            data.x = property[0].GetInt();
            data.y = property[1].GetInt();
            data.w = property[2].GetInt();
            data.h = property[3].GetInt();
            return true;
        }

        bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if property is an array
            auto& property = iter->value;
            if (property.IsArray() == false) {
                return false;
            }
            // set data
            for (rapidjson::SizeType i = 0; i < property.Size(); i++) {
                if (property[i].IsString()) {
                    data.push_back(property[i].GetString());
                }
            }
            
            return true;
        }

        bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data) 
        {
            // check if 'name' member exists
            auto iter = value.FindMember(name.c_str());
            if (iter == value.MemberEnd()) {
                return false;
            }
            // check if property is an array
            auto& property = iter->value;
            if (property.IsArray() == false) {
                return false;
            }
            // set data
            for (rapidjson::SizeType i = 0; i < property.Size(); i++) {
                if (property[i].IsInt()) {
                    data.push_back(property[i].GetInt());
                }
            }

            return true;
        }

    }
}

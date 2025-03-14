#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <string_view>

class SvZ_Data {
public:
    SvZ_Data(std::filesystem::path path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return;
        }
        std::string buffer;
        std::string variable;
        std::string value;
        std::string group = ".";

        while (!file.eof()) {
            std::getline(file, buffer);
            // Skip empty lines
            if (buffer.size() < 1) continue;
            // Skip comments
            if (buffer.at(0) == '/') continue;

            // Group
            if (buffer.at(0) == '[') {
                group = "";
                for (int i = 1; buffer.at(i) != ']'; i++) {
                    group += buffer.at(i);
                }
                continue;
            }

            // Variable
            int i = 0;
            for (i = 0; buffer.at(i) == ' ' || buffer.at(i) == '\t'; i++) {}
            variable = "";
            for (i; buffer.at(i) != ' '; i++) {
                variable += buffer.at(i);
            }

            // Value
            for (i; buffer.at(i) == ' ' || buffer.at(i) == '='; i++) {}
            value = "";
            for (i; i < buffer.size() && buffer.at(i) != ' '; i++) {
                value += buffer.at(i);
            }

            add(group, variable, value);
        }
    }

    void add(std::string_view group, std::string_view variable, std::string_view value) {
        data[key_gen(group, variable)] = value;
    }

    std::string fetch(std::string_view group, std::string_view variable) {
        return data[key_gen(group, variable)];
    }
    std::string fetch(std::string_view variable) {
        return data[key_gen(".", variable)]; // default group
    }

private:
    std::unordered_map<std::string, std::string> data;

    std::string key_gen(std::string_view group, std::string_view variable) {
        return std::string(group) + "&&" + std::string(variable);
    }
};
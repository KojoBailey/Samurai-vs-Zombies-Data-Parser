#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string_view>

namespace kojo {

struct SvZ_Price {
    int coins;
    int glu_credits;
};

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
            if (buffer.size() < 3) continue;
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
            for (i; i >= buffer.size() || buffer.at(i) == ' ' || buffer.at(i) == '='; i++) {}
            value = "";
            for (i; i < buffer.size() && buffer.at(i) != ' '; i++) {
                value += buffer.at(i);
            }

            add(group, variable, value);
        }
        file.close();
    }

    void add(std::string_view group, std::string_view variable, std::string_view value) {
        data[key_gen(group, variable)] = value;
        groups.insert(std::string(group));
    }

    std::string fetch(std::string_view group, std::string_view variable) {
        std::string key = key_gen(group, variable);
        if (data.contains(key))
            return data[key];
        return "";
    }
    std::string fetch(std::string_view variable) {
        std::string key = key_gen(".", variable); // default group
        if (data.contains(key))
            return data[key];
        return "";
    }

    size_t group_count() {
        return groups.size();
    }

    static SvZ_Price split(std::string_view value) {
        SvZ_Price result;
        std::string buffer{""};
        int i;
        for (i = 0; value.at(i) != ','; i++)
            buffer += value.at(i);
        result.coins = std::stoi(buffer);
        buffer = "";
        for (i++; i < value.size(); i++)
            buffer += value.at(i);
        result.glu_credits = std::stoi(buffer);
        return result;
    }
private:
    std::unordered_map<std::string, std::string> data;
    std::unordered_set<std::string> groups;

    std::string key_gen(std::string_view group, std::string_view variable) {
        return std::string(group) + "&&" + std::string(variable);
    }
};

}
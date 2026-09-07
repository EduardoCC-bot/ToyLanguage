#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

class Environment {
private:
    std::unordered_map<std::string, int> values;

public:
    Environment() = default;

    void set(const std::string& name, int value) {
        values[name] = value;
    }

    int get(const std::string& name) const {
        auto it = values.find(name);
        if (it != values.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable no definida: '" + name + "'");
    }

    const std::unordered_map<std::string, int>& getValues() const {
        return values;
    }
};
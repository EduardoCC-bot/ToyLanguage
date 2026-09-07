#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

class Environment {
private:
    std::unordered_map<std::string, int> values;
    Environment* enclosing; 

public:
    Environment() : enclosing(nullptr) {}

    Environment(Environment* parent) : enclosing(parent) {}

    bool contains(const std::string& name) const {
        if (values.find(name) != values.end()) return true;
        if (enclosing != nullptr) return enclosing->contains(name);
        return false;
    }

    void set(const std::string& name, int value) {
        if (values.find(name) != values.end()) {
            values[name] = value;
            return;
        }

        if (enclosing != nullptr && enclosing->contains(name)) {
            enclosing->set(name, value);
            return;
        }

        values[name] = value;
    }

    int get(const std::string& name) const {
        auto it = values.find(name);
        if (it != values.end()) {
            return it->second;
        }

        if (enclosing != nullptr) {
            return enclosing->get(name);
        }

        throw std::runtime_error("Variable no definida: '" + name + "'");
    }

    const std::unordered_map<std::string, int>& getValues() const {
        return values;
    }
};
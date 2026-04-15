#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using CommandMap = std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>>;

CommandMap get_builtins();
bool exists_in_path(const std::string&);
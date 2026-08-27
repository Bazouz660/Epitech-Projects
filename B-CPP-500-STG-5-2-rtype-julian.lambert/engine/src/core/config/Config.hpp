#pragma once

#include "common.hpp"
#include "parsing.hpp"
#include "Exception.hpp"
#include "json.hpp"
#include "logger.hpp"
#include <variant>
#include <tuple>
#include <any>

#include "helper/info/logger.hpp"
#include "helper/paths.hpp"

namespace exng
{
    class Config
    {
        public:

            Config() = default;
            ~Config() = default;

            void save(const std::string& path)
            {
                std::ofstream file(path);
                if (!file.is_open()) {
                    logger::error("Failed to create config file: " + path);
                    return;
                }

                file << m_settings.dump(4);
            }

            void load(const std::string& path)
            {
                // the config file lives next to the game, not necessarily in
                // the current working directory
                std::string resolved = paths::resolve(path);

                std::ifstream file(resolved);
                if (!file.is_open()) {
                    exng::logger::warn() << "No config file at " << resolved << ", writing the default one";
                    m_settings = m_defaultSettings;
                    save(resolved);
                    return;
                }

                try {
                    file >> m_settings;
                } catch (const std::exception& e) {
                    exng::logger::error() << "Invalid config file (" << resolved << "): " << e.what()
                                          << " -- falling back to the default settings";
                    m_settings = m_defaultSettings;
                    return;
                }

                // check if all default settings are present
                for (auto& [key, value] : m_defaultSettings.items()) {
                    if (!m_settings.contains(key)) {
                        exng::logger::warn() << "Setting not found: " << key << " (using default value)";
                        m_settings[key] = value;
                    }
                }

                // check if all settings are valid
                for (auto size = 0; size < m_settings.size(); size++) {
                    auto& [key, value] = *std::next(m_settings.items().begin(), size);
                    if (!m_defaultSettings.contains(key)) {
                        exng::logger::warn() << "Unknown setting: " << key << " (ignoring)";
                        m_settings.erase(key);
                    }
                }
            }

            template<typename T>
            T getSetting(const std::string& key)
            {
                if (m_settings.contains(key)) {
                    return m_settings.at(key).get<T>();
                }
                throw std::runtime_error("Setting not found: " + key);
            }

            template<typename T>
            Config& setSetting(const std::string& key, const T& value)
            {
                m_settings[key] = value;
                return *this;
            }

            std::vector<std::string> getAvailableSettings()
            {
                std::vector<std::string> settings;
                for (auto& [key, value] : m_settings.items()) {
                    settings.push_back(key);
                }
                return settings;
            }

            template<typename T>
            Config& setDefaultSetting(const std::string& key, const T& value)
            {
                m_defaultSettings[key] = value;
                return *this;
            }

        private:

            nlohmann::json m_settings;
            nlohmann::json m_defaultSettings;
    };
}
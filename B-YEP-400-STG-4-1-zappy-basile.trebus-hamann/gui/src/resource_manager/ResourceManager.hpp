/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP_
    #define RESOURCEMANAGER_HPP_

    #include "common.hpp"

    namespace zpy {

        #define getResource() ResourceManager::getInstance()

        class ResourceManager {
        public:
            ~ResourceManager();
            void loadResources();
            void unloadAll();
            static ResourceManager& getInstance();
            sptr<Texture> getTexture(const std::string &name);
            sptr<Font> getFont(const std::string& name);
            sptr<Sound> getSoundBuffer(const std::string& name);
            sptr<Image> getTextureImage(const std::string& name);
            sptr<Model> getModel(const std::string& name);

        private:
            void loadTexture(const std::string &name, const std::string &filename);
            void loadTexturesFromFolder(const std::string &folder);
            void loadFont(const std::string& name, const std::string& filePath);
            void loadSoundBuffer(const std::string& name, const std::string& filePath);
            void loadModel(const std::string& name, const std::string& filePath);

            ResourceManager();
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            std::map<std::string, sptr<Texture>> m_textures;
            std::map<std::string, sptr<Font>> m_fonts;
            std::map<std::string, sptr<Sound>> m_sounds;
            std::map<std::string, sptr<Image>> m_images;
            std::map<std::string, sptr<Model>> m_models;
        };

    }

#endif /* !RESOURCEMANAGER_HPP_ */

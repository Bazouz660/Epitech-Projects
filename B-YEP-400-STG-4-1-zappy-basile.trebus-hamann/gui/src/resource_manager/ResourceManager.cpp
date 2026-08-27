/*
** EPITECH PROJECT, 2023
** RPG3
** File description:
** ResourceManager
*/

#include <filesystem>
#include "ResourceManager.hpp"
#include "parsing.hpp"

namespace zpy {

ResourceManager::ResourceManager()
{
}

void ResourceManager::loadResources()
{
    loadTexture("grass", "gui/resources/textures/grass.png");

    loadTexture("apple", "gui/resources/textures/apple.png");
    loadTexture("diamond", "gui/resources/textures/diamond_ore.png");
    loadTexture("emerald", "gui/resources/textures/emerald_ore.png");
    loadTexture("gold", "gui/resources/textures/gold_ore.png");
    loadTexture("iron", "gui/resources/textures/iron_ore.png");
    loadTexture("redstone", "gui/resources/textures/redstone_ore.png");
    loadTexture("lapis", "gui/resources/textures/lapis_ore.png");

    loadModel("player", "gui/resources/models/steve.glb");
}

void ResourceManager::unloadAll()
{
    for (auto &it : m_textures)
        UnloadTexture(*it.second.get());
    for (auto &it : m_images)
        UnloadImage(*it.second.get());
    for (auto &it : m_fonts)
        UnloadFont(*it.second.get());
    for (auto &it : m_sounds)
        UnloadSound(*it.second.get());
    for (auto &it : m_models)
        UnloadModel(*it.second.get());
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadTexture(const std::string &name, const std::string &filename)
{
    // Create a new texture and load it from the specified file.
    Texture texture;
    texture = LoadTexture(filename.c_str());

    GenTextureMipmaps(&texture);
    //if (texture.id < 0)
    //    throw std::runtime_error("Failed to load texture: " + filename);

    std::cout << "Loaded texture as \"" << name << "\" from " << "\"" + filename + "\"" << std::endl;

    // Insert the texture into the map using the name as the key.
    m_textures[name] = std::make_shared<Texture>(texture);
    m_images[name] = std::make_shared<Image>(LoadImage(filename.c_str()));
}

sptr<Texture> ResourceManager::getTexture(const std::string &name)
{
    auto it = m_textures.find(name);
    if (it == m_textures.end())
        throw std::runtime_error("Texture not found: " + name);
    return (m_textures.at(name));
}

sptr<Image> ResourceManager::getTextureImage(const std::string &name)
{
    auto it = m_images.find(name);
    if (it == m_images.end())
        throw std::runtime_error("Texture not found: " + name);
    return (m_images.at(name));
}

void ResourceManager::loadTexturesFromFolder(const std::string& directory)
{
    for (const auto & entry : std::filesystem::directory_iterator(directory))
        loadTexture(parsing::removeExtension(entry.path().filename()), entry.path().string());
}

void ResourceManager::loadFont(const std::string& name,
const std::string& filePath)
{
    auto font = LoadFont(filePath.c_str());
    if(font.texture.id == 0)
        throw std::runtime_error("Failed to load font: " + filePath);
    m_fonts[name] = std::make_shared<Font>(font);
    std::cout << "Loaded font as \"" << name << "\" from " << "\"" + filePath + "\"" << std::endl;
}

sptr<Font> ResourceManager::getFont(const std::string& fontName)
{
    auto it = m_fonts.find(fontName);
    if (it == m_fonts.end())
        throw std::runtime_error("Font not found: " + fontName);
    return (m_fonts.at(fontName));
}

sptr<Model> ResourceManager::getModel(const std::string& name)
{
    auto it = m_models.find(name);
    if (it == m_models.end())
        throw std::runtime_error("Model not found: " + name);
    return (m_models.at(name));
}

void ResourceManager::loadModel(const std::string& name,
const std::string& filePath)
{
    auto model = LoadModel(filePath.c_str());
    if (model.meshes[0].vboId == 0)
        throw std::runtime_error("Failed to load model: " + filePath);
    m_models[name] = std::make_shared<Model>(model);
    std::cout << "Loaded model as \"" << name << "\" from " << "\"" + filePath + "\"" << std::endl;
}

void ResourceManager::loadSoundBuffer(const std::string& name,
const std::string& fileName)
{
    Sound sound = LoadSound(fileName.c_str());
    if (sound.stream.buffer == NULL)
        throw std::runtime_error("Failed to load sound buffer: " + fileName);
    m_sounds[name] = std::make_shared<Sound>(sound);
    std::cout << "Loaded font as \"" << name << "\" from " << "\"" + fileName + "\"" << std::endl;
}

sptr<Sound> ResourceManager::getSoundBuffer(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it == m_sounds.end())
        throw std::runtime_error("Sound buffer not found: " + name);
    return (m_sounds.at(name));
}

ResourceManager::~ResourceManager()
{
    //for (auto& [key, value] : m_textures)
    //    UnloadTexture(*value);
    //for (auto& [key, value] : m_fonts)
    //    UnloadFont(*value);
    //for (auto& [key, value] : m_sounds)
    //    UnloadSound(*value);
    //for (auto& [key, value] : m_images)
    //    UnloadImage(*value);
}

}

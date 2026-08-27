/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** Trantorian
*/

#include "Trantorian.hpp"
#include "ResourceManager.hpp"
#include "Grid.hpp"
#include "context.hpp"
#include "Renderer.hpp"

namespace zpy {

    Trantorian::Trantorian(const Vec2& pos, Orientation orientation, unsigned int level, int id, std::string teamName, Grid& grid)
        : m_orientation(orientation), m_level(level), m_id(id), m_teamName(teamName), m_grid(grid)
    {
        m_model = *getResource().getModel("player");
        m_button = Button3d({Vector3Zero(), Vector3Zero()}, [this]() {
            Renderer&  renderer = context::getRenderer();

            renderer.setFocusedPlayer(this);
        });

        m_rotation = (90 * orientation) + 180;
        setPos(pos);
        setOrientation(orientation);
    }

    Trantorian::~Trantorian()
    {
        if (context::getRenderer().getFocusedPlayer() == this)
            context::getRenderer().setFocusedPlayer(nullptr);
    }

    void Trantorian::setPos(const Vec2& pos)
    {
        Tile& tile = m_grid.getTile(pos);
        Vec2 tmp;
        tmp.x = tile.getWorldPos().x;
        tmp.y = tile.getWorldPos().y;

        m_pos = tmp;

        m_model.transform = MatrixIdentity();

        m_model.transform = MatrixScale(0.05, 0.05, 0.05);
        m_model.transform = MatrixMultiply(m_model.transform, MatrixRotateXYZ({PI * -0.5, 0, m_rotation * PI / 180}));
        m_model.transform = MatrixMultiply(m_model.transform, MatrixTranslate(tmp.x, 2.1, tmp.y));

        BoundingBox box = GetModelBoundingBox(m_model);
        box.min = Vector3Transform(box.min, m_model.transform);
        box.max = Vector3Transform(box.max, m_model.transform);
        m_button.setBox(box);
    }

    Inventory& Trantorian::getInventory()
    {
        return m_inventory;
    }

    void Trantorian::update()
    {
        m_button.update();
    }

    void Trantorian::setOrientation(Orientation orientation)
    {
        m_orientation = orientation;
        m_rotation = (90 * orientation) + 90;
    }

    void Trantorian::setLevel(unsigned int level)
    {
        m_level = level;
    }

    void Trantorian::setTeamName(std::string teamName)
    {
        m_teamName = teamName;
    }

    void Trantorian::setId(int id)
    {
        m_id = id;
    }

    Vec2 Trantorian::getPos() const
    {
        return m_pos;
    }

    Trantorian::Orientation Trantorian::getOrientation() const
    {
        return m_orientation;
    }

    unsigned int Trantorian::getLevel() const
    {
        return m_level;
    }

    std::string Trantorian::getTeamName() const
    {
        return m_teamName;
    }

    int Trantorian::getId() const
    {
        return m_id;
    }

    void Trantorian::draw(Shader* shader)
    {
        for (int i = 0; i < m_model.materialCount; i++) {
            m_model.materials[i].shader = *shader;
        }
        DrawModelEx(m_model, {0, 0, 0}, {0, 0, 0}, 0, {1.0, 1.0, 1.0}, context::getTeamColor(m_teamName));
        //m_button.draw();
    }

}

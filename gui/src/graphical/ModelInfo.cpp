/*
** EPITECH PROJECT, 2025
** ModelInfo.cpp
** File description:
** ModelInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "ModelInfo.hpp"
#include "Logs.hpp"
#include "VarManager.hpp"
#include "Lib.hpp"
#include <raymath.h>

namespace Gui {
    ModelInfo::ModelInfo(const std::string &modelPath, float scale)
    : _model(LoadModel(modelPath.c_str())), _collision()
    {
        DEBUG << "Loading model: " << modelPath << " at scale: " << scale << std::endl;
        _scale = scale;
        // setPos({0.0f, 0.0f, 0.0f});
        init();
    }

    ModelInfo::~ModelInfo()
    {
        // DEBUG << "Unloading model: " << this;
        // UnloadModel(_model);
        // for (auto &texture : _textures) {
        //     UnloadTexture(texture);
        // }
    }

    void ModelInfo::init()
    {
        _boundingBox = GetModelBoundingBox(_model);
        _dimensions = {getWidth(), getHeight(), getLength()};
    }

    const Model& ModelInfo::getModel() const
    {
        return _model;
    }

    Model& ModelInfo::getModel()
    {
        return _model;
    }

    void ModelInfo::setModel(const Model &model)
    {
        _model = model;
    }

    const float& ModelInfo::getScale() const
    {
        return _scale;
    }

    void ModelInfo::setScale(float scale)
    {
        _scale = scale;
        init();
    }
    const Vector3& ModelInfo::getDimensions() const
    {
        return _dimensions;
    }

    void ModelInfo::setDimensions(const Vector3 &dimensions)
    {
        _dimensions = dimensions;
    }

    const std::vector<Texture2D>& ModelInfo::getTextures() const
    {
        return _textures;
    }

    void ModelInfo::setTextures(const std::vector<Texture2D> &textures)
    {
        _textures = textures;
    }
    const BoundingBox& ModelInfo::getBoundingBox() const
    {
        return _boundingBox;
    }
    BoundingBox& ModelInfo::getBoundingBox()
    {
        return _boundingBox;
    }

    void ModelInfo::setBoundingBox(const BoundingBox &boundingBox)
    {
        _boundingBox = boundingBox;
    }


    BoundingBox ModelInfo::getTransformedBoundingBox(const Vector3 &position, float rotationDeg) const
    {
        // Calcul du centre du modèle dans son espace local
        Vector3 center = {
            (_boundingBox.min.x + _boundingBox.max.x) / 2.0f,
            (_boundingBox.min.y + _boundingBox.max.y) / 2.0f,
            (_boundingBox.min.z + _boundingBox.max.z) / 2.0f
        };

        // Construction de la matrice complète :
        // Scale -> Translate pour centrer -> Rotate -> Translate dans le monde
        Matrix scaleMat = MatrixScale(_scale, _scale, _scale);
        Matrix translateToOrigin = MatrixTranslate(-center.x, -center.y, -center.z);
        Matrix rotationMat = MatrixRotateY(DEG2RAD * rotationDeg);
        Matrix worldTranslation = MatrixTranslate(position.x, position.y, position.z);

        // Ordre : T * R * T(-center) * S
        Matrix transform = MatrixMultiply(
            MatrixMultiply(
                MatrixMultiply(worldTranslation, rotationMat),
                translateToOrigin),
            scaleMat
        );

        // Les 8 coins de la bounding box d'origine
        Vector3 corners[8] = {
            _boundingBox.min,
            _boundingBox.max,
            {_boundingBox.min.x, _boundingBox.min.y, _boundingBox.max.z},
            {_boundingBox.min.x, _boundingBox.max.y, _boundingBox.min.z},
            {_boundingBox.max.x, _boundingBox.min.y, _boundingBox.min.z},
            {_boundingBox.min.x, _boundingBox.max.y, _boundingBox.max.z},
            {_boundingBox.max.x, _boundingBox.min.y, _boundingBox.max.z},
            {_boundingBox.max.x, _boundingBox.max.y, _boundingBox.min.z}
        };

        // Transformation de tous les coins
        Vector3 transformed[8];
        for (int i = 0; i < 8; ++i) {
            transformed[i] = Vector3Transform(corners[i], transform);
        }

        // Construction de la AABB englobante finale
        Vector3 min = transformed[0];
        Vector3 max = transformed[0];

        for (int i = 1; i < 8; ++i) {
            min = Vector3Min(min, transformed[i]);
            max = Vector3Max(max, transformed[i]);
        }

        return {min, max};
    }

    BoundingBox ModelInfo::getBoundingBoxForCollision(const Vector3 &position, float rotationDeg) const
    {
        // Pour la collision, on peut utiliser une approche simplifiée qui fonctionne bien
        // même avec rotation : utiliser le plus grand côté comme "rayon" pour une collision cylindrique

        float width = (_boundingBox.max.x - _boundingBox.min.x) * _scale;
        float height = (_boundingBox.max.y - _boundingBox.min.y) * _scale;
        float length = (_boundingBox.max.z - _boundingBox.min.z) * _scale;

        // Prendre la plus grande dimension horizontale pour compenser la rotation
        float maxHorizontal = std::max(width, length);

        Vector3 min = {
            position.x - maxHorizontal / 2.0f,
            position.y + _boundingBox.min.y * _scale, // Garder l'offset Y original
            position.z - maxHorizontal / 2.0f
        };

        Vector3 max = {
            position.x + maxHorizontal / 2.0f,
            position.y + _boundingBox.max.y * _scale,
            position.z + maxHorizontal / 2.0f
        };

        return {min, max};
    }

    RayCollision& ModelInfo::getCollision()
    {
        return _collision;
    }

    const RayCollision& ModelInfo::getCollision() const
    {
        return _collision;
    }

    void ModelInfo::setCollision(const RayCollision &collision)
    {
        _collision = collision;
    }

    const Vector3& ModelInfo::getPos() const
    {
        return _pos;
    }
    Vector3& ModelInfo::getPos()
    {
        return _pos;
    }
    void ModelInfo::setPos(const Vector3 &pos)
    {
        _pos = pos;

    }

    inline void ModelInfo::updateTransformedBoundingBox()
    {
    _transformedBoundingBox.min = {
            _pos.x + _boundingBox.min.x * _scale,
            _pos.y + _boundingBox.min.y * _scale,
            _pos.z + _boundingBox.min.z * _scale
        };
        _transformedBoundingBox.max = {
            _pos.x + _boundingBox.max.x * _scale,
            _pos.y + _boundingBox.max.y * _scale,
            _pos.z + _boundingBox.max.z * _scale
        };
    }



    ////////////////////////////////////// UTILITY //////////////////////////////////////

    float ModelInfo::scaleToSize(float size)
    {
        float scaleX = size / (_boundingBox.max.x - _boundingBox.min.x);
        float scaleY = size / (_boundingBox.max.z - _boundingBox.min.z);
        return std::min(scaleX, scaleY);
    }

    float ModelInfo::getWidth()
    {
        float width = (_boundingBox.max.x - _boundingBox.min.x) * _scale;
        float xOffset = width;

        return xOffset;
    }

    float ModelInfo::getHeight()
    {
        float height = (_boundingBox.max.y - _boundingBox.min.y) * _scale;
        float yOffset = height;

        return yOffset;
    }

    float ModelInfo::getLength()
    {
        float length = (_boundingBox.max.z - _boundingBox.min.z) * _scale;
        float zOffset = length;

        return zOffset;
    }

    float ModelInfo::getAligned(float min, float target)
    {
        return target - (min * _scale);
    }

    float ModelInfo::getFloatingOffset()
    {
        static float floatDegree = 0.0f;
        static std::chrono::steady_clock::time_point lastFloatTime = std::chrono::steady_clock::now();

        if (Lib::delay(16, lastFloatTime)) {
            floatDegree += 2.0f;
            if (floatDegree > 360.0f) floatDegree -= 360.0f;
        }

        return sinf(DEG2RAD * floatDegree) * 0.1f;
    }

    void ModelInfo::applyRotationEffect(float angle, float speed)
    {
        static float rotationDegree = 0.0f;
        static std::chrono::steady_clock::time_point lastRotationTime = std::chrono::steady_clock::now();

        if (Lib::delay(16, lastRotationTime)) {
            rotationDegree += speed;
            if (rotationDegree > 360.0f) rotationDegree -= 360.0f;
        }

        float rotationAngle = angle == 0.0f ? rotationDegree : angle;
        _model.transform = MatrixRotateY(DEG2RAD * rotationAngle);
    }

    void ModelInfo::draw(const Vector3 &position, const Color &color)
    {
        setPos(position);
        updateTransformedBoundingBox();
        DrawModel(_model, _pos, _scale, color);
        if (VarManager::getInstance().getVar(VarManager::DEBUG_VAR)) {
            DrawModelWires(_model, _pos, _scale, GREEN);
            DrawBoundingBox(_transformedBoundingBox, YELLOW);
        }
    }

    void ModelInfo::drawBoundingBox(const Color &color)
    {
        DrawBoundingBox(_transformedBoundingBox, color);
    }
}
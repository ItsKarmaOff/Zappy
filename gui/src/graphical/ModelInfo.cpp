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
    : _model(LoadModel(modelPath.c_str()))
    {
        DEBUG << "Loading model: " << modelPath << " at scale: " << scale << std::endl;
        _scale = scale;
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

    void ModelInfo::draw(const Vector3 &position, const Color &color) const
    {
        DrawModel(_model, position, _scale, color);
        if (VarManager::getInstance().getVar(VarManager::DEBUG_VAR)) {
            DrawModelWires(_model, position, _scale, GREEN);
            BoundingBox transformedBox;
            transformedBox.min = {
                position.x + _boundingBox.min.x * _scale,
                position.y + _boundingBox.min.y * _scale,
                position.z + _boundingBox.min.z * _scale
            };
            transformedBox.max = {
                position.x + _boundingBox.max.x * _scale,
                position.y + _boundingBox.max.y * _scale,
                position.z + _boundingBox.max.z * _scale
            };

            DrawBoundingBox(transformedBox, YELLOW);
            // DrawBoundingBox(_boundingBox, YELLOW);
        }
    }
}
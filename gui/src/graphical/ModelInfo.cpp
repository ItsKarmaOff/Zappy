/*
** EPITECH PROJECT, 2025
** ModelInfo.cpp
** File description:
** ModelInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "ModelInfo.hpp"
#include "Logs.hpp"

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

    float ModelInfo::scaleToSize(float size)
    {
        BoundingBox bbox = GetModelBoundingBox(_model);
        float scaleX = size / (bbox.max.x - bbox.min.x);
        float scaleY = size / (bbox.max.z - bbox.min.z);
        init();
        return std::min(scaleX, scaleY);
    }

    float ModelInfo::getWidth()
    {
        BoundingBox modelBox = GetModelBoundingBox(_model);
        float width = (modelBox.max.x - modelBox.min.x) * _scale;
        float xOffset = width;

        return xOffset;
    }

    float ModelInfo::getHeight()
    {
        BoundingBox modelBox = GetModelBoundingBox(_model);
        float height = (modelBox.max.y - modelBox.min.y) * _scale;
        float yOffset = height;

        return yOffset;
    }

    float ModelInfo::getLength()
    {
        BoundingBox modelBox = GetModelBoundingBox(_model);
        float length = (modelBox.max.z - modelBox.min.z) * _scale;
        float zOffset = length;

        return zOffset;
    }


    void ModelInfo::draw(const Vector3 &position, const Color &color) const
    {

    }
}
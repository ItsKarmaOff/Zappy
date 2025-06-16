/*
** EPITECH PROJECT, 2025
** ModelInfo.hpp
** File description:
** ModelInfo declaration
*/


#ifndef MODELINFO_HPP
    #define MODELINFO_HPP

#include <memory>
#include <raylib.h>
#include <string>
#include <vector>
#include <chrono>

namespace Gui {
    class   ModelInfo {
        public:
            ModelInfo(const std::string &modelPath, float scale = 1.0f);
            // move constructor

            ~ModelInfo();

            void init();

            ////////////////////////////////////// GETTERS / SETTERS //////////////////////////////////////
            const Model &getModel() const;
            Model &getModel();
            void setModel(const Model &model);

            const BoundingBox &getBoundingBox() const;
            BoundingBox &getBoundingBox();
            void setBoundingBox(const BoundingBox &boundingBox);

            // for collision
            BoundingBox getTransformedBoundingBox(const Vector3 &position, float rotationDeg) const;
            BoundingBox getBoundingBoxForCollision(const Vector3 &position, float rotationDeg) const;


            const float &getScale() const;
            void setScale(float scale);

            const Vector3 &getDimensions() const;
            void setDimensions(const Vector3 &dimensions);

            const std::vector<Texture2D> &getTextures() const;
            void setTextures(const std::vector<Texture2D> &textures);

            RayCollision &getCollision();
            const RayCollision &getCollision() const;
            void setCollision(const RayCollision &collision);

            const Vector3 &getPos() const;
            Vector3 &getPos();
            void setPos(const Vector3 &pos);

            ////////////////////////////////////// UTILITY //////////////////////////////////////
            void draw(const Vector3 &position, const Color &color = WHITE);
            void drawBoundingBox(const Color &color = RED);

            float scaleToSize(float size);
            float getFloatingOffset();
            void applyRotationEffect(float angle = 0.0f, float speed = 1.0f);
            float getAligned(float min, float target = 0.0f);
            float getWidth();
            float getHeight();
            float getLength();

            inline void updateTransformedBoundingBox();

        private:
            Model _model;
            BoundingBox _boundingBox;
            BoundingBox _transformedBoundingBox;
            float _scale;
            Vector3 _dimensions;
            std::vector<Texture2D> _textures;
            RayCollision _collision;
            Vector3 _pos;
    };


}

#endif // MODELINFO_HPP
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
namespace Gui {
    class ModelInfo {
        public:
            ModelInfo(const std::string &modelPath, float scale = 1.0f);
            // move constructor

            ~ModelInfo();

            void init();

            ////////////////////////////////////// GETTERS / SETTERS //////////////////////////////////////
            const Model &getModel() const;
            Model &getModel();
            void setModel(const Model &model);
            const float &getScale() const;
            void setScale(float scale);
            const Vector3 &getDimensions() const;
            void setDimensions(const Vector3 &dimensions);
            const std::vector<Texture2D> &getTextures() const;
            void setTextures(const std::vector<Texture2D> &textures);

            float scaleToSize(float size);
            float getWidth();
            float getHeight();
            float getLength();

            ////////////////////////////////////// UTILITY //////////////////////////////////////
            void draw(const Vector3 &position, const Color &color = WHITE) const;

        private:
            Model _model;
            float _scale;
            Vector3 _dimensions;
            std::vector<Texture2D> _textures;
    };


}

#endif // MODELINFO_HPP
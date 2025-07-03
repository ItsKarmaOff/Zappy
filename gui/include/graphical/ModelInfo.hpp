/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The ModelInfo class declaration
*/
/**
 * @file ModelInfo.hpp
 * @brief The ModelInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef MODELINFO_HPP
    #define MODELINFO_HPP

    #include "VarManager.hpp"
    #include <raylib.h>
    #include <raymath.h>

namespace Gui
{
    /**
     * @class ModelInfo
     * @brief Manages 3D model data, transformations, and rendering operations
     */
    class ModelInfo {
        public:

            //////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Constructor for the ModelInfo class
             * @param modelPath Path to the 3D model file
             * @param scale Initial scale factor for the model (default: 1.0)
             */
            ModelInfo(const std::string &modelPath, float scale = 1.0f);
            // move constructor

            /**
             * @brief Destructor for the ModelInfo class
             * Unloads model and texture resources
             */
            ~ModelInfo();

            /**
             * @brief Initializes the model by calculating bounding boxes and dimensions
             */
            void init();



            //////////////// Getters ///////////////////////////////////////////

            /**
             * @brief Gets the model as a constant reference
             * @return Constant reference to the Model object
             */
            const Model &getModel() const;

            /**
             * @brief Gets the model as a mutable reference
             * @return Reference to the Model object
             */
            Model &getModel();


            /**
            * @brief Gets the bounding box as a constant reference
            * @return Constant reference to the BoundingBox object
            */
            const BoundingBox &getBoundingBox() const;

            /**
            * @brief Gets the bounding box as a mutable reference
            * @return Reference to the BoundingBox object
            */
            BoundingBox &getBoundingBox();

            /**
            * @brief Calculates a transformed bounding box based on position and rotation
            * @param position The position vector in world space
            * @param rotationDeg The rotation in degrees
            * @return BoundingBox object transformed according to position and rotation
            */
            BoundingBox getTransformedBoundingBox(const Vector3 &position, float rotationDeg) const;

            /**
             * @brief Gets a simplified collision bounding box that works with rotation
             * @param position The position vector in world space
             * @param rotationDeg The rotation in degrees
             * @return BoundingBox object suitable for collision detection
             */
            BoundingBox getBoundingBoxForCollision(const Vector3 &position, float rotationDeg) const;
            
            /**
            * @brief Gets the scale factor as a constant reference
            * @return Constant reference to the scale factor
            */
            const float &getScale() const;

            /**
             * @brief Gets the dimensions as a constant reference
             * @return Constant reference to the Vector3 containing the model dimensions
             */
            const Vector3 &getDimensions() const;

            /**
             * @brief Gets the position as a constant reference
             * @return Constant reference to the Vector3 containing position
             */
            const Vector3 &getPos() const;

            /**
             * @brief Gets the position as a mutable reference
             * @return Reference to the Vector3 containing position
             */
            Vector3 &getPos();

            /**
             * @brief Aligns the model to a target height
             * @param min The minimum Y value of the model
             * @param target The target Y value to align to (default: 0.0f)
             * @return The offset value needed for alignment
             */
            float getAligned(float min, float target = 0.0f);

            /**
             * @brief Gets the scaled width of the model
             * @return The width of the model considering scale factor
             */
            float getWidth();

            /**
            * @brief Gets the scaled height of the model
            * @return The height of the model considering scale factor
            */
            float getHeight();
            
            /**
            * @brief Gets the scaled length of the model
            * @return The length of the model considering scale factor
            */
            float getLength();

            /**
             * @brief Gets the ray collision information as a mutable reference
             * @return Reference to the RayCollision object
             */
            RayCollision &getCollision();

            /**
             * @brief Gets the ray collision information as a constant reference
             * @return Constant reference to the RayCollision object
             */
            const RayCollision &getCollision() const;



            //////////////// Setters ///////////////////////////////////////////

            /**
             * @brief Sets the model
             * @param model The Model object to set
             */
            void setModel(const Model &model);

            /**
            * @brief Sets the bounding box
            * @param boundingBox The BoundingBox object to set
            */
            void setBoundingBox(const BoundingBox &boundingBox);

            /**
             * @brief Sets the scale factor
             * @param scale The new scale factor value
             */
            void setScale(float scale);

            /**
             * @brief Sets the dimensions
             * @param dimensions The Vector3 containing new dimension values
             */
            void setDimensions(const Vector3 &dimensions);

            /**
             * @brief Gets the model textures as a constant reference
             * @return Constant reference to the vector of Texture2D objects
             */
            const std::vector<Texture2D> &getTextures() const;

            /**
             * @brief Sets the model textures
             * @param textures Vector of Texture2D objects to set
             */
            void setTextures(const std::vector<Texture2D> &textures);

            /**
             * @brief Sets the ray collision information
             * @param collision The RayCollision object to set
             */
            void setCollision(const RayCollision &collision);

            /**
             * @brief Sets the position
             * @param pos The Vector3 containing the new position
             */
            void setPos(const Vector3 &pos);



            //////////////// Main Methods //////////////////////////////////////

            /**
             * @brief Draws the model at the specified position with the given color
             * @param position The position vector in world space
             * @param color The color to tint the model (default: WHITE)
             */
            void draw(const Vector3 &position, const Color &color = WHITE);

            /**
             * @brief Draws the model's bounding box with the specified color
             * @param color The color to draw the bounding box (default: RED)
             */
            void drawBoundingBox(const Color &color = RED);

            /**
             * @brief Calculates the scale factor needed to make the model fit a specific size
             * @param size The target size
             * @return The calculated scale factor
             */
            float scaleToSize(float size);

            /**
             * @brief Calculates a vertical offset for floating animation effect
             * @return The calculated offset value
             */
            float getFloatingOffset();

            /**
             * @brief Applies a rotation effect to the model
             * @param angle The rotation angle in degrees (0.0f for continuous rotation)
             * @param speed The rotation speed (default: 1.0f)
             */
            void applyRotationEffect(float angle = 0.0f, float speed = 1.0f);

            /**
             * @brief Updates the transformed bounding box based on current position
             */
            inline void updateTransformedBoundingBox();



        private:

            //////////////// Private Attributes ////////////////////////////////

            Model _model;                        ///< The 3D model
            BoundingBox _boundingBox;            ///< Original bounding box of the model
            BoundingBox _transformedBoundingBox; ///< Bounding box after transformations
            float _scale;                        ///< Scale factor for the model
            Vector3 _dimensions;                 ///< Dimensions of the model
            std::vector<Texture2D> _textures;    ///< Textures used by the model
            RayCollision _collision;             ///< Ray collision information
            Vector3 _pos;                        ///< Current position of the model
    };
}

#endif // MODELINFO_HPP
/*
** EPITECH PROJECT, 2024
** my_libs
** File description:
** The my_swap_endian_color.c
*/
/**
 * @file my_swap_endian_color.c
 * @brief The my_swap_endian_color.c
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Swap the endian of a color
 * @param color The color to swap
 * @return <b>uint32_t</b> The color with the endian swapped
 * @author Nicolas TORO
 */
uint32_t my_swap_endian_color(uint32_t color)
{
    color_argb_t argb = {.color = color};
    uint8_t tmp = argb.alpha;

    argb.alpha = argb.blue;
    argb.blue = tmp;
    tmp = argb.red;
    argb.red = argb.green;
    argb.green = tmp;
    return argb.color;
}

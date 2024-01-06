#include "main.h"

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float FixAng(float angle)
{
    if (angle < 0)
        angle += 2 * PI;
    if (angle > 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void draw_rays(SDL_Instance instance)
{
    int ray, map_x, map_y, map_position, dof, num_rays = 60, horizontal_map_tile, vertical_map_tile;
    float ray_x, ray_y, ray_angle, x_offset, y_offset, disT;
    ray_angle = FixAng(square.player_angle - DR * (num_rays / 2));

    for (ray = 0; ray < num_rays; ray++)
    {

        /* horisontal line check */
        dof = 0;
        horizontal_map_tile = 0;
        float disH = 0, horizontal_x = square.pos_x, horizontal_y = square.pos_y;
        float horizontal_tan = -1 / tan(ray_angle);

        if (ray_angle > PI)
        {
            ray_y = (((int)square.pos_y / 45) * 45) - 0.0001;
            ray_x = (square.pos_y - ray_y) * horizontal_tan + square.pos_x;
            y_offset = -45;
            x_offset = -y_offset * horizontal_tan;
        }
        if (ray_angle < PI)
        {
            ray_y = (((int)square.pos_y / 45) * 45) + 45;
            ray_x = (square.pos_y - ray_y) * horizontal_tan + square.pos_x;
            y_offset = 45;
            x_offset = -y_offset * horizontal_tan;
        }
        if (ray_angle == 0 || ray_angle == PI)
        {
            ray_x = square.pos_x;
            ray_y = square.pos_y;
            dof = 28;
        }

        while (dof < 28)
        {

            map_x = (int)(ray_x) / 45;
            map_y = (int)(ray_y) / 45;
            map_position = map_y * 28 + map_x;
            if (map_position >= 0 && map_position < 28 * 16 && map_grid[map_position] == 1)
            {
                horizontal_x = ray_x;
                horizontal_y = ray_y;
                disH = dist(square.pos_x, square.pos_y, horizontal_x, horizontal_y, ray_angle);
                horizontal_map_tile = map_position;
                dof = 28;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                dof += 1;
            }
        }

        /* vertical line check */
        dof = 0;
        vertical_map_tile = 0;
        float vertical_Tan = -tan(ray_angle);
        float disV = 100000, vertical_x = square.pos_x, vertical_y = square.pos_y;

        if (ray_angle > PI2 && ray_angle < PI3)
        {
            ray_x = (((int)square.pos_x / 45) * 45) - 0.0001;
            ray_y = (square.pos_x - ray_x) * vertical_Tan + square.pos_y;
            x_offset = -45;
            y_offset = -x_offset * vertical_Tan;
        }
        if (ray_angle < PI2 || ray_angle > PI3)
        {
            ray_x = (((int)square.pos_x / 45) * 45) + 45;
            ray_y = (square.pos_x - ray_x) * vertical_Tan + square.pos_y;
            x_offset = 45;
            y_offset = -x_offset * vertical_Tan;
        }
        if (ray_angle == 0 || ray_angle == PI)
        {
            ray_x = square.pos_x;
            ray_y = square.pos_y;
            dof = 16;
        }

        while (dof < 16)
        {

            map_x = (int)(ray_x) / 45;
            map_y = (int)(ray_y) / 45;
            map_position = map_y * 28 + map_x;
            if (map_position >= 0 && map_position < 28 * 16 && map_grid[map_position] == 1)
            {
                vertical_x = ray_x;
                vertical_y = ray_y;
                disV = dist(square.pos_x, square.pos_y, vertical_x, vertical_y, ray_angle);
                vertical_map_tile = map_position;
                dof = 16;
            }
            else
            {
                ray_x += x_offset;
                ray_y += y_offset;
                dof += 1;
            }
        }

        /* saves the nearest ray */

        if (disV < disH)
        {
            horizontal_map_tile = vertical_map_tile;
            ray_x = vertical_x;
            ray_y = vertical_y;
            disT = disV;
            wall_color(1, instance);
        }
        if (disV > disH)
        {
            ray_x = horizontal_x;
            ray_y = horizontal_y;
            disT = disH;
            wall_color(2, instance);
        }

        /* if the ray hits a wall next to spawn or end it will change color to signal the end or start of the map */

        if (map_grid[horizontal_map_tile + 1] == 2 || map_grid[horizontal_map_tile + 28] == 2 || map_grid[horizontal_map_tile - 1] == 2 || map_grid[horizontal_map_tile - 28] == 2)
        {
            wall_color(3, instance);
        }
        else if (map_grid[horizontal_map_tile + 1] == 3 || map_grid[horizontal_map_tile + 28] == 3 || map_grid[horizontal_map_tile - 1] == 3 || map_grid[horizontal_map_tile - 28] == 3)
        {
            wall_color(4, instance);
        }

        /* activating this line will show a 2D representation of the rays hitting the map */
        // SDL_RenderDrawLine(instance.renderer, square.pos_x, square.pos_y, ray_x, ray_y);

        /* draw 3D  walls*/
        float ca = square.player_angle - ray_angle;
        if (ca < 0)
            ca += 2 * PI;
        if (ca > 2 * PI)
            ca -= 2 * PI;
        disT = disT * cos(ca);

        float lineH = (45 * 720) / disT;

        if (lineH > 720)
        {
            lineH = 720;
        }
        float lineO = 360 - lineH / 2;

        int y;
        float texture_y = 0;

        SDL_Rect box[1] = {ray * (1260 / num_rays), lineO, (1260 / num_rays), lineH};
        SDL_RenderFillRect(instance.renderer, &box[0]);

        /* draw floor */
        float tx, ty;

        /* add new ray */
        ray_angle += DR;
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
    }
}

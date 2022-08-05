#include"keyboard.h"

bool is_fire = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
        switch (action)
        {
            case GLFW_PRESS:
            {
                is_fire = true;
                break;
            }
            case GLFW_RELEASE:
            {
                is_fire = false;
                break;
            }
        }
    return;
}

void Plane_speed_change(GLFWwindow* window, object* Plane)
{
    GLfloat speedup = 2.5f;
    double Mousex, Mousey;
    glfwGetCursorPos(window, &Mousex, &Mousey);
    int PlaneY = Plane->position.y + Plane->size.y / 2, MouseY = Mousey;    // convert to int for switch
    // workaround. Operator ... did not compiles
    int l = ((PlaneY - MouseY) >= -5 && (PlaneY - MouseY) <= 5) * 1 |
            ((PlaneY - MouseY) > 5 && (PlaneY - MouseY) <= 20) * 2 |
            ((PlaneY - MouseY) > 20 && (PlaneY - MouseY) <= 100) * 3 |
            ((PlaneY - MouseY) > 100) * 4 |
            ((PlaneY - MouseY) >= -20 && (PlaneY - MouseY) < -5) * 5 |
            ((PlaneY - MouseY) >= -100 && (PlaneY - MouseY) < -20) * 6 |
            ((PlaneY - MouseY) < -100) * 7;
    switch (l)
    {
        case 1:
        {
            // on mouse
            Plane->speed.y = 0.0f;
            break;
        }
        case 2:
        {
            // close to mouse
            if (Plane->speed.y <= -speedup)
                Plane->speed.y = -speedup;
            else Plane->speed.y -= speedup;
            break;
        }
        case 3:
        {
            if (Plane->speed.y >= -10 * speedup)
                Plane->speed.y = -10 * speedup;
            else Plane->speed.y -= speedup;
            break;
        }
        case 4:
        {
            // far from mouse
            Plane->speed.y -= speedup;
            break;
        }
        case 5:
        {
            // close to mouse
            if (Plane->speed.y >= speedup)
                Plane->speed.y = speedup;
            else Plane->speed.y += speedup;
            break;
        }
        case 6:
        {
            if (Plane->speed.y >= 10 * speedup)
                Plane->speed.y = 10 * speedup;
            else Plane->speed.y += speedup;
            break;
        }
        case 7:
        {
            // far from mouse
            Plane->speed.y += speedup;
            break;
        }
    }
}
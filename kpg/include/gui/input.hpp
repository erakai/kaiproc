#include "SDL_keycode.h"
#include <functional>
#include <vector>

namespace input
{

extern std::vector<std::function<void(SDL_Keycode key)>> key_callbacks;
extern std::vector<std::function<void(int type, int button, int x, int y)>>
    mouse_callbacks;

bool poll_event_loop();

} // namespace input

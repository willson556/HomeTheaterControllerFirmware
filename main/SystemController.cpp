#include "SystemController.hpp"

namespace HTSystem
{

void SystemController::initialize()
{
    if (thread_running)
    {
        return;
    }

    thread_running = true;
    thread = std::thread([this]{ thread_func(); });
    thread.detach();
}

void SystemController::thread_func()
{
    while (thread_running)
    {
        // Do stuff
    }
}

} // namespace HTSystem
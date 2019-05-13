#pragma once

#include <thread>
#include <functional>
#include <vector>

#include <CEC.h>
#include <AVR.hpp>

#include "ObservableVariable.hpp"

namespace HTSystem
{

class SystemController
{
public:
    enum class Task
    {
        Standby,
        AudioVideo,
        Audio,
    };

    SystemController(CEC_LogicalDevice &cec_device, AVR::DenonAVR receiver)
      : cec_device{cec_device},
        receiver{receiver}
    {
    }

    void initialize();

    void set_task(Task task);
    void set_volume(float volume);

    void add_current_task_observer(ObservableVariable<Task>::Callback c)
    {
        current_task.add_observer(c);
    }

    void add_target_task_observer(ObservableVariable<Task>::Callback c)
    {
        target_task.add_observer(c);
    }

private:
    CEC_LogicalDevice &cec_device;
    AVR::DenonAVR &receiver;

    ObservableVariable<Task> current_task{Task::Standby};
    ObservableVariable<Task> target_task{Task::Standby};

    std::thread thread;
    void thread_func();
    volatile bool thread_running{false};
};

} // namespace System
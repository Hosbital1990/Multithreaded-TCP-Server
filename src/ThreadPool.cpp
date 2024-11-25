#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t deepOfPool)
    : deepOfPool(deepOfPool), appRunning(false)
{
    threadHolder.reserve(deepOfPool);

}

ThreadPool::~ThreadPool()
{
        stop();
            for (auto &thread : threadHolder) {
        if (thread.joinable()) {
            thread.join();
        }
    }

}

void ThreadPool::start() {
        appRunning=true;
    for (int i = 0; i < threadHolder.capacity(); ++i) {
        threadHolder.emplace_back(&ThreadPool::workerThread, this);
    }
}

void ThreadPool::stop() {
        appRunning=false;
    poolCv.notify_all();

}
void ThreadPool::taskEnqueuer(std::function<void()> task)
{

    {
        std::unique_lock<std::mutex> lock(poolQueue_Mutex);
        taskHolder.push(task);
    }
    poolCv.notify_one();

}

void ThreadPool::workerThread()
{
    while (true)
    {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(poolQueue_Mutex);
            poolCv.wait(lock, [this] {
                return !taskHolder.empty() || !appRunning;
            });

            if (!appRunning && taskHolder.empty()) {
                break; // Exit if app is not running and no tasks remain
            }

            task = std::move(taskHolder.front());
            taskHolder.pop();
        }

        task();
    }

    while (appRunning) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(poolQueue_Mutex);
            poolCv.wait(lock, [this]() { return !taskHolder.empty() || !appRunning; });
            if (!appRunning && taskHolder.empty()) return;
            task = taskHolder.front();
            taskHolder.pop();
        }
        task();
    }


}

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>


class ThreadPool{

public:

ThreadPool(size_t deepOfPool);
    ~ThreadPool();

void taskEnqueuer (std::function<void()> task);
    void start();
    void stop();

private:

void workerThread();
size_t deepOfPool;

std::vector<std::thread> threadHolder;   // pool of thread
std::queue<std::function<void()>> taskHolder;  // holds ready tasks
std::mutex poolQueue_Mutex;
std::condition_variable poolCv;

bool appRunning;  // potential for atomic bool



};



#endif // THREADPOOL_H

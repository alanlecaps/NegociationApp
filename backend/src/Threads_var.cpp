#include "Threads_var.h"
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <memory>

int num_childs = 0;

std::mutex mtx;
 std::vector<std::unique_ptr<std::condition_variable>> child_Achet_cvs;
 std::vector<std::unique_ptr<std::condition_variable>> child_Vend_cvs;
 std::vector<std::unique_ptr<std::atomic<bool>>> child_ready_flags_Achet;
 std::vector<std::unique_ptr<std::atomic<bool>>> child_ready_flags_Vend;
 std::unique_ptr<std::atomic<bool>> termination_flag;
std::atomic<int> next_child;

void init_shared_resources_Acheteur(int num_threads) {
    std::lock_guard<std::mutex> lock(mtx);  // Ensure thread safety while initializing
    num_childs = num_threads;

    // Resize vectors and initialize with unique_ptr instances
    child_Achet_cvs.resize(num_threads);
    child_ready_flags_Achet.resize(num_threads);

    for (int i = 0; i < num_threads; ++i) {
        // Initialize each element of child_cvs and child_ready_flags
        child_Achet_cvs[i] = std::make_unique<std::condition_variable>();
        child_ready_flags_Achet[i] = std::make_unique<std::atomic<bool>>(false);
    }

    next_child = 0;  // Reset next_child index
}

void init_shared_resources_Vendeur(int num_threads) {
    std::lock_guard<std::mutex> lock(mtx);  // Ensure thread safety while initializing
    num_childs = num_threads;

    // Resize vectors and initialize with unique_ptr instances
    child_Vend_cvs.resize(num_threads);
    child_ready_flags_Vend.resize(num_threads);

    // Add a shared termination flag for all threads
    termination_flag = std::make_unique<std::atomic<bool>>(false);

    for (int i = 0; i < num_threads; ++i) {
        // Initialize each element of child_cvs and child_ready_flags
        child_Vend_cvs[i] = std::make_unique<std::condition_variable>();
        child_ready_flags_Vend[i] = std::make_unique<std::atomic<bool>>(false);
    }

    next_child = 0;  // Reset next_child index
}

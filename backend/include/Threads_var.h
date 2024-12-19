#ifndef THREADS_VAR_H
#define THREADS_VAR_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

extern int num_childs;

extern std::mutex mtx;
extern std::vector<std::unique_ptr<std::condition_variable>> child_Achet_cvs;
extern std::vector<std::unique_ptr<std::condition_variable>> child_Vend_cvs;
extern std::vector<std::unique_ptr<std::atomic<bool>>> child_ready_flags_Achet;
extern std::vector<std::unique_ptr<std::atomic<bool>>> child_ready_flags_Vend;
extern std::unique_ptr<std::atomic<bool>> termination_flag;
//extern std::atomic<int> next_child; 

void init_shared_resources_Acheteur(int num_threads);
void init_shared_resources_Vendeur(int num_threads);
#endif  

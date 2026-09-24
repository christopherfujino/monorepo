#ifndef __MONOREPO_SRC_FARMSIM_INCLUDE_WORKER_H
#define __MONOREPO_SRC_FARMSIM_INCLUDE_WORKER_H

typedef enum : int {
  jobLoadMap,
} JobType;

typedef enum {
  jobQueued,
  jobSucceeded,
  jobFailed,
} JobStatus;

struct _Job;
typedef struct _Job *Job;

JobStatus jobGetStatus(Job);

struct _Worker;
typedef struct _Worker *Worker;

Worker workerSpawn();
Job workerJobEnqueue(Worker, JobType);
void workerDispose(Worker);

#endif // __MONOREPO_SRC_FARMSIM_INCLUDE_WORKER_H

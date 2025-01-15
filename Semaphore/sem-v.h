#ifndef __sem_v_h__
#define __sem_v_h__

#define SHM_SIZE 1024
#define SEM_KEY  1234
#define SHM_KEY  5678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


extern void sem_wait(int semid, int sem_num);
extern void sem_signal(int semid, int sem_num);



#endif

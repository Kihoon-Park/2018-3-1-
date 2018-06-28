#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define SEMPERM 0600
#define TRUE 1
#define FALSE 0

typedef union   _semun {
             int val;
             struct semid_ds *buf;
             ushort *array;
             } semun;

int initsem (key_t semkey, int n) {
   int status = 0, semid;
   if ((semid = semget (semkey, 1, SEMPERM | IPC_CREAT | IPC_EXCL)) == -1)
   {
       if (errno == EEXIST)
                semid = semget (semkey, 1, 0);
   }
   else
   {
       semun arg;
       arg.val = n;
       status = semctl(semid, 0, SETVAL, arg);
   }
   if (semid == -1 || status == -1)
   {
       perror("initsem failed");
       return (-1);
   }
   return (semid);
}

int p (int semid) {
   struct sembuf p_buf;
   p_buf.sem_num = 0;
   p_buf.sem_op = -1;
   p_buf.sem_flg = SEM_UNDO;
   if (semop(semid, &p_buf, 1) == -1)
   {
      printf("p(semid) failed");
      exit(1);
   }
   return (0);
}

int v (int semid) {
   struct sembuf v_buf;
   v_buf.sem_num = 0;
   v_buf.sem_op = 1;
   v_buf.sem_flg = SEM_UNDO;
   if (semop(semid, &v_buf, 1) == -1)
   {
      printf("v(semid) failed");
      exit(1);
   }
   return (0);
}

// Shared variable by file
reset(char *fileVar) {
// fileVar라는 이름의 텍스트 화일을 새로 만들고 0값을 기록한다.
}

Store(char *fileVar,int i) {
// fileVar 화일 끝에 i 값을 append한다.
}

Load(char *fileVar) {
// fileVar 화일의 마지막 값을 읽어 온다.
}

add(char *fileVar,int i) {
// fileVar 화일의 마지막 값을 읽어서 i를 더한 후에 이를 끝에 append 한다.

}

sub(char *fileVar,int i) {
// fileVar 화일의 마지막 값을 읽어서 i를 뺀 후에 이를 끝에 append 한다.
}

// Class Lock
typedef struct _lock { 
   int semid;
} Lock;

initLock(Lock *l, key_t semkey) {
   if ((l->semid = initsem(semkey,1)) < 0)    
   // 세마포를 연결한다.(없으면 초기값을 1로 주면서 새로 만들어서 연결한다.)
      exit(1);
}

Acquire(Lock *l) {
   p(l->semid);
}

Release(Lock *l) {

   v(l->semid);
}

// Class CondVar
typedef struct _cond {
   int semid;
   char *queueLength;
} CondVar;

initCondVar(CondVar *c, key_t semkey, char *queueLength) {
   c->queueLength = queueLength;
   reset(c->queueLength); // queueLength=0
   if ((c->semid = initsem(semkey,0)) < 0)    
   // 세마포를 연결한다.(없으면 초기값을 0로 주면서 새로 만들어서 연결한다.)
      exit(1); 
}

Wait(CondVar *c, Lock *lock) {
   
}

Signal(CondVar *c) {

}

Broadcast(CondVar *c) {

}

void main() {
   key_t semkey = 0x200; 
   //  서버에서 작업할 때는 자기 학번 등을 이용하여 다른 사람의 키와 중복되지 않게 해야 한다.
   //  실행하기 전에 매번 세마포들을 모두 지우거나 아니면 다른 semkey 값을 사용해야 한다.
   //  $ ipcs                 // 남아 있는 세마포 확인
   //  $ ipcrm -s <semid>     // <semid>라는 세마포 제거

   int semid;
   pid_t pid;
   Lock lock;

   pid = getpid();
   initLock(&lock,semkey);
   prinff("\nprocess %d before critical section\n", pid);
   Acquire(&lock);   // lock.Acquire()
   printf("process %d in critical section\n",pid);
    /* 화일에서 읽어서 1 더하기 */
   printf("process %d leaving critical section\n", pid);
   Release(&lock);   // lock.Release()
   printf("process %d exiting\n",pid);
   exit(0);
}


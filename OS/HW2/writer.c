#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
  int isfile = access(fileVar,0);
  if(isfile == -1){
      FILE *fp = fopen(fileVar, "a");
      fprintf(fp,"0");
      fclose(fp);
  }

  FILE *fp = fopen(fileVar, "a");
  int n;


  n = fgetc(fp);
  if(n == "-1"){
    fprintf(fp,"0");
  }
  fclose(fp);
}


Store(char *fileVar,int i) {
// fileVar 화일 끝에 i 값을 append한다.

  int n;
  FILE *fp = fopen(fileVar, "a");

  fprintf(fp,"PID: %ld ",getpid());
  fprintf(fp,"%d\n",i);

  fclose(fp);
}

int Load(char *fileVar) {
    int tmp,id;
    char timet;
    int n;

    FILE *fp = fopen(fileVar, "r");

    fscanf(fp,"%d",&n);
    while(!feof(fp)){
      fscanf(fp,"%s %s %s %d", &tmp,&id,&timet, &n);
    }

    fclose(fp);
    return n;
}

add(char *fileVar,int i) {
// fileVar 화일의 마지막 값을 읽어서 i를 더한 후에 이를 끝에 append 한다.
    int tmp,id;
    char timet;
    int n;

    time_t t;
    t = time(NULL);
    struct tm* ti;
    ti = localtime(&t);

    FILE *fp = fopen(fileVar, "r");

    fscanf(fp,"%d",&n);
    while(!feof(fp)){
      fscanf(fp,"%s %s %s %d", &tmp,&id,&timet, &n);
    }

    fclose(fp); //store n

    n = n + i;
    fp = fopen(fileVar, "a");

    fprintf(fp,"PID: %ld ",getpid());
    fprintf(fp,"TIME:%d:%d:%d ",ti->tm_hour,ti->tm_min,ti->tm_sec);
    fprintf(fp,"%d\n",n);

    fclose(fp);
}

sub(char *fileVar,int i) {
// fileVar 화일의 마지막 값을 읽어서 i를 뺀 후에 이를 끝에 append 한다.
    int tmp,id;
    char timet;
    int n;

    time_t t;
    t = time(NULL);
    struct tm* ti;
    ti = localtime(&t);

    FILE *fp = fopen(fileVar, "r");

    fscanf(fp,"%d",&n);
    while(!feof(fp)){
      fscanf(fp,"%s %s %s %d", &tmp,&id,&timet, &n);
    }

    fclose(fp); //store n

    n = n - i;
    fp = fopen(fileVar, "a");

    fprintf(fp,"PID: %ld ",getpid());
    fprintf(fp,"TIME:%d:%d:%d ",ti->tm_hour,ti->tm_min,ti->tm_sec);
    fprintf(fp,"%d\n",n);

    fclose(fp);
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
  add(c->queueLength,1);
  Release(lock);
  p(c->semid);
  Acquire(lock);
}

Signal(CondVar *c) {
  if(Load(c->queueLength) > 0) {
    v(c->semid);
    sub(c->queueLength,1);
  }
}

Broadcast(CondVar *c) {
  while(Load(c->queueLength) > 0){
    v(c->semid);
    sub(c->queueLength,1);
  }
}

void main(int argc, char* argv[]) {
   int sleepT =  atoi(argv[1]);

   int runningT = atoi(argv[2]);

   key_t semkey = 0x200;
   key_t semkey2 = 0x210;
   key_t semkey3 = 0x220;
   //  서버에서 작업할 때는 자기 학번 등을 이용하여 다른 사람의 키와 중복되지 않게 해야 한다.
   //  실행하기 전에 매번 세마포들을 모두 지우거나 아니면 다른 semkey 값을 사용해야 한다.
   //  $ ipcs                 // 남아 있는 세마포 확인
   //  $ ipcrm -s <semid>     // <semid>라는 세마포 제거

   sleep(sleepT);

   int semid;
   pid_t pid;
   Lock lock;
   CondVar okToRead;
   CondVar okToWrite;
   char *queueREAD = "READQfile.txt";
   char *queueWRITE = "WRITEQfile2.txt";

   char *AR = "ARfile.txt";
   char *WR = "WRfile.txt";
   char *AW = "AWfile.txt";
   char *WW = "WWfile.txt";

   reset(AR);
   reset(WR);
   reset(AW);
   reset(WW);


   pid = getpid();
   initLock(&lock,semkey);

   initCondVar(&okToRead, semkey2,queueREAD);
   initCondVar(&okToWrite, semkey3,queueWRITE);

   printf("process %d before critical section\n", pid);
   Acquire(&lock);   // lock.Acquire()
   printf("process %d in critical section\n",pid);
    /* 화일에서 읽어서 1 더하기 */
   while((Load(AW) + Load(AR)) > 0){
     add(WW,1);
     Wait(&okToWrite,&lock);
     sub(WW,1);
   }
   add(AW,1);
   printf("process %d leaving critical section\n", pid);
   Release(&lock);   // lock.Release()
   //ACCESS DB
   printf("I ACCESS IN DB to WRITE %d seconds\n",runningT);
   sleep(runningT);

   Acquire(&lock);   // lock.Acquire()
   printf("process %d in critical section\n",pid);

   sub(AW,1);

   if(Load(WW) > 0){
      Signal(&okToWrite);
   }
   else if(Load(WR) > 0){
      Broadcast(&okToRead);
   }
   printf("process %d leaving critical section\n", pid);
   Release(&lock);   // lock.Release()


   printf("process %d exiting\n",pid);
   exit(0);
}

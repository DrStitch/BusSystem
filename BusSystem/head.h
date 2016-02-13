#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define getch() _getch()

#define OK 1
#define ERROR 0
typedef int status;

#define HASHSIZE 10007
#define MAXFEE (2147483647)
#define NAMESIZE 80

#define NOSTATION -1
#define NOROUTE -1

bool modified = false;

int routeTotal;
int stationTotal;

//�洢·����Ϣ�Ľṹ��
typedef struct {
    int id;
    char name[NAMESIZE];
    char startTime[10];
    char endTime[10];
    float price;
    int stationNum;
    int *stations;
} rInfo;

typedef struct _rHash{
    char name[NAMESIZE];
    int id;
    _rHash * next;
} rHash;

//�洢վ����Ϣ�Ľṹ��
typedef struct {
    char name[NAMESIZE];
    int routeNum;
    int routes[60];
    int index[60];
} sInfo;

typedef struct _sHash{
    char name[NAMESIZE];
    int id;
    _sHash * next;
} sHash;

int *distMat;       //���ڽӾ��󱣴�վ�����

unsigned hash(char *str);

status loadStationData(char *filename);
status loadRouteData(char *filename);
status initDistMat(char *filename);

status modifyRoute(void);
status saveRoute(char *filename);

rInfo *routeInfo;                   //�洢·����Ϣ
rHash routeNameId[HASHSIZE];      //�洢·����������Ŷ�Ӧ��Ϣ�Ĺ�ϣ��
sInfo *stationInfo;                 //�洢վ����Ϣ
sHash stationNameId[HASHSIZE];    //�洢վ����������Ŷ�Ӧ��Ϣ�Ĺ�ϣ��

struct sortStruct
{
    bool sorted;
    int *arr;
} sortRoute, sortStation;

int getRouteIdbyName(char *name);
int getStationIdbyName(char *name);

int findCrossStation(int route1, int route2);

status sortResult(int type);
status inquireSpecificRoute(void);      //��ѯָ����·����
status inquireSpecificStation(void);    //��ѯ;��ĳһλ�õ����й�����·
status shortestDist(void);              //ָ��������յ㣬�Ƽ����·�̳˳�����
status leastTransfer(void);             //ָ��������յ㣬�Ƽ����ٻ��˳˳�����

void quickSort(int *arr, int low, int high, int type);
int partitionbyRoute(int *arr, int low, int high);
int partitionbyStation(int *arr, int low, int high);

int distSPFA(int start, int end, int *stations, int &stationNum);
float showResultbyStations(int *stations, int stationNum);

int transDijkstra(int start, int end, int *stations, int *routes, int &routeNum);
float showResultbyRoutes(int *stations, int *routes, int routeNum);
bool emptyQ(bool *Q, int num);
int searchMin(int *arr, bool *Q, int num, int &index);
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define getch() _getch()

typedef int status;
#define OK 1
#define ERROR 0

#define HASHSIZE 10007          //��ϣ����
#define MAXFEE (2147483647)     //�����
#define NAMESIZE 80             //���Ƴ���

#define NOSTATION -1    //�޴�վ��
#define NOROUTE -1      //�޴�·��

//�洢·����Ϣ�Ľṹ��
typedef struct {
    int id;
    char name[NAMESIZE];
    char startTime[10];     //��ʼʱ��
    char endTime[10];       //����ʱ��
    float price;
    int stationNum;         //վ������
    int *stations;          //վ������
} rInfo;

//·����Ϣ��hash�ṹ��
typedef struct _rHash{
    char name[NAMESIZE];
    int id;
    _rHash * next;
} rHash;

//�洢վ����Ϣ�Ľṹ��
typedef struct {
    char name[NAMESIZE];
    int routeNum;
    int routes[60];     //·������
    int index[60];      //��·�ߵĵڼ�վ
} sInfo;

//վ����Ϣ��hash�ṹ��
typedef struct _sHash{
    char name[NAMESIZE];
    int id;
    _sHash * next;
} sHash;

//��������Ľṹ��
struct sortStruct
{
    bool sorted;    //��¼�Ƿ�������
    int *arr;       //��¼������վ������
} sortRoute, sortStation;

bool modified = false;  //�Ƿ��޸������ݣ����޸Ĺ������˳�ʱѯ���Ƿ񱣴�

int routeTotal;     //·������
int stationTotal;   //վ������

int *distMat;       //���ڽӾ��󱣴�վ�����

rInfo *routeInfo;                   //�洢·����Ϣ
rHash routeNameId[HASHSIZE];      //�洢·����������Ŷ�Ӧ��Ϣ�Ĺ�ϣ��
sInfo *stationInfo;                 //�洢վ����Ϣ
sHash stationNameId[HASHSIZE];    //�洢վ����������Ŷ�Ӧ��Ϣ�Ĺ�ϣ��

unsigned hash(char *str);
int getRouteIdbyName(char *name);
int getStationIdbyName(char *name);

status loadStationData(char *filename);
status loadRouteData(char *filename);
status initDistMat(char *filename);

status modifyRoute(void);

status sortResult(int type);
void quickSort(int *arr, int low, int high, int type);
int partitionbyRoute(int *arr, int low, int high);
int partitionbyStation(int *arr, int low, int high);

status inquireSpecificRoute(void);
status inquireSpecificStation(void);

status shortestDist(void);
int distSPFA(int start, int end, int *stations, int &stationNum);
float showResultbyStations(int *stations, int stationNum);

status leastTransfer(void);
int transDijkstra(int start, int end, int *stations, int *routes, int &routeNum);
float showResultbyRoutes(int *stations, int *routes, int routeNum);
bool emptyQ(bool *Q, int num);
int searchMin(int *arr, bool *Q, int num, int &index);

status saveRoute(char *filename);
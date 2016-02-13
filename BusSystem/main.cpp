#include "head.h"

int main(void)
{
    sortRoute.sorted = false;
    sortStation.sorted = false;
    loadStationData("map.txt");
    loadRouteData("route.txt");
    initDistMat("distance.txt");
    int op = 9;
    while (op)
    {
        system("cls");
        printf("--------------------��ѡ����-----------------\n");
        printf("   1.¼�빫����·��Ϣ\n");
        printf("   2.�޸Ĺ�����·��Ϣ\n");
        printf("   3.��ѯ������·��Ϣ������·������\n");
        printf("   4.��ѯ������·��Ϣ�������վ������\n");
        printf("   5.��ѯָ����·����\n");
        printf("   6.��ѯ;��ĳһλ�õ����й�����·\n");
        printf("   7.ָ��������յ㣬�Ƽ����·�̳˳�����\n");
        printf("   8.ָ��������յ㣬�Ƽ����ٻ��˳˳�����\n");
        printf("   0.�˳�ϵͳ\n");
        printf("------------------------------------------------\n");
        printf("��ѡ���ܣ�����0~8: ");
        scanf("%d", &op);
        getchar();
        putchar('\n');
        switch (op)
        {
        case 1:/*
            if (loadStationData("map.txt") &&
                loadRouteData("route.txt") &&
                initDistMat("distance.txt") &&
                initRouteMat())
            {
                printf("¼��ɹ���\n");
            }
            else
            {
                printf("¼��ʧ�ܣ�\n");
            }*/
            system("pause");
            break;
        case 2:
            modifyRoute();
            system("pause");
            break;
        case 3:
            sortResult(1);
            break;
        case 4:
            sortResult(2);
            break;
        case 5:
            inquireSpecificRoute();
            system("pause");
            break;
        case 6:
            inquireSpecificStation();
            system("pause");
            break;
        case 7:
            shortestDist();
            system("pause");
            break;
        case 8:
            leastTransfer();
            system("pause");
            break;
        case 0:
            if (modified)
            {
                printf("�Ƿ�Ҫ�������ݣ�y/n��");
                if (tolower(getchar()) == 'y')
                {
                    rename("route.txt", "route_backup.txt");
                    saveRoute("route.txt");
                }
            }
            break;
        default:
            printf("�Բ���������������\n");
            system("pause");
            break;
        }
    }
   
    return 0;
}

status modifyRoute(void)
{
    char name[NAMESIZE];
    int id;

    printf("��������Ҫ�޸ĵ���·����·����");
    scanf("%s", name);
    if ((id = getRouteIdbyName(name)) == NOROUTE)
    {
        printf("�Բ���û���ҵ�����·��\n");
        return ERROR;
    }
    printf("�������µ���ʼʱ�䣺");
    scanf("%s", routeInfo[id].startTime);
    printf("�������µĽ���ʱ�䣺");
    scanf("%s", routeInfo[id].endTime);
    printf("�������µļ۸�");
    scanf("%f", &routeInfo[id].price);
    modified = true;
    printf("�޸ĳɹ���\n");
    return OK;
}

status sortResult(int type)
{
    sortStruct *s = (type == 1) ? &sortRoute : &sortStation;
    if (!s->sorted)
    {
        s->arr = (int *)calloc(routeTotal, sizeof(int));
        for (int i = 0; i < routeTotal; i++)
        {
            s->arr[i] = i;
        }
        quickSort(s->arr, 0, routeTotal - 1, type);
    }
    char opt = 's';
    int i = 0;
    while (true)
    {
        system("cls");
        printf("��q���أ���w�鿴��һ·�ߣ����������鿴��һ·��\n\n");
        rInfo route = routeInfo[s->arr[i]];
        printf("��·��  ��%s\n", route.name);
        printf("����ʱ�䣺%s--%s\n", route.startTime, route.endTime);
        printf("Ʊ��    ��%.2f\n", route.price);
        printf("��վ��  ��%d\n", route.stationNum);
        printf(";��վ�㣺\n");
        for (int i = 0; i < route.stationNum; i++)
        {
            printf("  %d.%s\n", i + 1, stationInfo[route.stations[i]].name);
        }
        opt = getch();
        switch (opt)
        {
        case 'q':
            return OK;
            break;
        case 'w':
            if (i > 0) i--;
            break;
        default:
            if (i < routeTotal - 1) i++;
            break;
        }
    }
}

status saveRoute(char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d\n", routeTotal);
    for (int i = 0; i < routeTotal; i++)
    {
        rInfo route = routeInfo[i];
        fprintf(fp, "%s %s %s %.2f %d", route.name, route.startTime, route.endTime, route.price, route.stationNum);
        for (int j = 0; j < route.stationNum; j++)
        {
            fprintf(fp, " %d", route.stations[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return OK;
}

status inquireSpecificRoute(void)
{
    char route_name[NAMESIZE];
    int id;
    printf("��������·����");
    scanf("%s", route_name);
    if ((id = getRouteIdbyName(route_name)) == NOROUTE)
    {
        printf("δ�ҵ�����·��\n");
        return ERROR;
    }
    rInfo route = routeInfo[id];
    printf("��·��  ��%s\n", route_name);
    printf("����ʱ�䣺%s--%s\n", route.startTime, route.endTime);
    printf("Ʊ��    ��%.2f\n", route.price);
    printf("��վ��  ��%d\n", route.stationNum);
    printf(";��վ�㣺\n");
    for (int i = 0; i < route.stationNum; i++)
    {
        printf("  %d.%s\n", i + 1, stationInfo[route.stations[i]].name);
    }
    return OK;
}

status inquireSpecificStation(void)
{
    char station_name[NAMESIZE];
    int id;
    printf("������վ������");
    scanf("%s", station_name);
    if ((id = getStationIdbyName(station_name)) == NOSTATION)
    {
        printf("δ�ҵ���վ�㣡\n");
        return ERROR;
    }
    sInfo station = stationInfo[id];
    printf("����·��Ϊ��\n");
    for (int i = 0; i < station.routeNum; i++)
    {
        printf("%s\n", routeInfo[station.routes[i]].name);
    }
    return OK;
}

status shortestDist(void)
{
    char startName[NAMESIZE], endName[NAMESIZE];
    int startStationId, endStationId;
    int stations[100];
    int num;
    int totalDist;
    float totalPrice;

    printf("���������վ����");
    scanf("%s", startName);
    if ((startStationId = getStationIdbyName(startName)) == NOSTATION)
    {
        printf("δ�ҵ���վ�㣡\n");
        return ERROR;
    }
    printf("�������յ�վ����");
    scanf("%s", endName);
    if ((endStationId = getStationIdbyName(endName)) == NOSTATION)
    {
        printf("δ�ҵ���վ�㣡\n");
        return ERROR;
    }
    if (totalDist = distSPFA(startStationId, endStationId, stations, num))
    {
        totalPrice = showResultbyStations(stations, num);
        printf("�ܾ���Ϊ%d��, ��վ��Ϊ%d����Ʊ��Ϊ%.2f��\n", totalDist, num, totalPrice);
    }
    else
    {
        printf("�Բ�����ѡ����վ�㲻��ͨ��\n");
    }
    return OK;
}

status leastTransfer(void)
{
    char startName[NAMESIZE], endName[NAMESIZE];
    int startStationId, endStationId;
    int routes[100];
    int stations[100];
    int num;
    float totalPrice;

    printf("���������վ����");
    scanf("%s", startName);
    if ((startStationId = getStationIdbyName(startName)) == NOSTATION)
    {
        printf("δ�ҵ���վ�㣡\n");
        return ERROR;
    }
    printf("�������յ�վ����");
    scanf("%s", endName);
    if ((endStationId = getStationIdbyName(endName)) == NOSTATION)
    {
        printf("δ�ҵ���վ�㣡\n");
        return ERROR;
    }

    if (transDijkstra(startStationId, endStationId, stations, routes, num))
    {
        totalPrice = showResultbyRoutes(stations, routes, num);
        printf("\n�ܴ����Ϊ%d����Ʊ��Ϊ%.2fԪ��\n", num, totalPrice);
    }
    else
    {
        printf("�Բ�����ѡ����վ�㲻��ͨ��\n");
    }
    return OK;
}

void quickSort(int *arr, int low, int high, int type)
{
    if (low < high)
    {
        int p = (type == 1) ? partitionbyRoute(arr, low, high) : partitionbyStation(arr, low, high);
        quickSort(arr, low, p - 1, type);
        quickSort(arr, p + 1, high, type);
    }
}

int partitionbyRoute(int *arr, int low, int high)
{
    int tmp = arr[low];
    char *pivname = routeInfo[tmp].name;
    while (low < high)
    {
        while (low < high && strcmp(routeInfo[arr[high]].name, pivname) >= 0) high--;
        arr[low] = arr[high];
        while (low < high && strcmp(routeInfo[arr[low]].name, pivname) <= 0) low++;
        arr[high] = arr[low];
    }
    arr[low] = tmp;
    return low;
}

int partitionbyStation(int *arr, int low, int high)
{
    int tmp = arr[low];
    char *pivname = stationInfo[routeInfo[tmp].stations[0]].name;
    while (low < high)
    {
        while (low < high && strcmp(stationInfo[routeInfo[arr[high]].stations[0]].name, pivname) >= 0) high--;
        arr[low] = arr[high];
        while (low < high && strcmp(stationInfo[routeInfo[arr[low]].stations[0]].name, pivname) <= 0) low++;
        arr[high] = arr[low];
    }
    arr[low] = tmp;
    return low;
}

float showResultbyStations(int *stations, int stationNum)
{
    if (stationNum == 0 || stationNum == 1)
    {
        return 0;
    }
    int bestRoute = NOROUTE;
    int bestNum = 0;
    for (int i = 0; i < stationInfo[*stations].routeNum; i++)
    {
        //Ѱ���ܾ������վ�����·
        int route = stationInfo[*stations].routes[i];
        int index = stationInfo[*stations].index[i];
        int num = 1;
        while (routeInfo[route].stations[index + num] == stations[num])
        {
            num++;
        }
        if (num > bestNum)
        {
            bestRoute = route;
            bestNum = num;
        }
    }
    printf("%s��;��%d��վ�㣬Ʊ��%.2f:\n", routeInfo[bestRoute].name, bestNum, routeInfo[bestRoute].price);
    for (int i = 0; i < bestNum - 1; i++)
    {
        printf("%s-->", stationInfo[stations[i]].name);
    }
    printf("%s\n", stationInfo[stations[bestNum - 1]].name);
    return routeInfo[bestRoute].price + showResultbyStations(stations + bestNum - 1, stationNum - bestNum + 1);      //������Ʊ��
}

//����Ʊ��
float showResultbyRoutes(int *stations, int *routes, int routeNum)
{
    int station = stations[0];
    float price = 0;
    for (int i = 0; i < routeNum; i++)
    {
        rInfo route = routeInfo[routes[i]];
        price += route.price;
        printf("\n���%s��Ʊ��%.2f:\n", route.name, route.price);
        for (int j = 0; j < route.stationNum; j++)
        {
            int curSta = route.stations[j];
            if (station == stations[i+1])
            {
                printf("%s\n", stationInfo[curSta].name);
                break;
            }
            else if (station == route.stations[j])
            {
                printf("%s --> ", stationInfo[station].name);
                station = route.stations[j + 1];
            }
        }
    }
    return price;
}

unsigned hash(char *str)
{
    long long sum;
    for (sum = 0; *str; str++)
    {
        sum = sum * 31 + abs(*str);
    }
    return abs(sum % HASHSIZE);
}

status loadStationData(char *filename)
{
    /*��ʼ��վ���ϣ��*/
    for (int i = 0; i < HASHSIZE; i++)
    {
        stationNameId[i].next = NULL;
    }
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &stationTotal);
    stationInfo = (sInfo *)calloc(stationTotal, sizeof(sInfo));
    for (int i = 0; i < stationTotal; i++)
    {
        char name[80];
        int id;
        unsigned hash_value;
        fscanf(fp, "%d %s", &id, name);
        //����վ����Ϣ
        strcpy(stationInfo[id].name, name);
        stationInfo[id].routeNum = 0;
        //�������Ϣ�����ϣ��
        hash_value = hash(name);
        sHash *node = (sHash *)malloc(sizeof(sHash));
        node->id = id;
        strcpy(node->name, name);
        node->next = stationNameId[hash_value].next;
        stationNameId[hash_value].next = node;
    }
    fclose(fp);
    return OK;
}

status loadRouteData(char *filename)
{
    /*��ʼ����·��ϣ��*/
    for (int i = 0; i < HASHSIZE; i++)
    {
        routeNameId[i].next = NULL;
    }
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &routeTotal);
    routeInfo = (rInfo *)calloc(routeTotal, sizeof(rInfo));
    for (int i = 0; i < routeTotal; i++)
    {
        /*����·����Ϣ*/
        fscanf(fp, "%s %s %s %f %d", routeInfo[i].name, routeInfo[i].startTime, routeInfo[i].endTime, &routeInfo[i].price, &routeInfo[i].stationNum);
        routeInfo[i].stations = (int *)calloc(routeInfo[i].stationNum, sizeof(int));
        for (int j = 0; j < routeInfo[i].stationNum; j++)
        {
            int station;
            fscanf(fp, "%d", &station);
            routeInfo[i].stations[j] = station;
            /*����վ����Ϣ*/
            stationInfo[station].routes[stationInfo[station].routeNum] = i;
            stationInfo[station].index[stationInfo[station].routeNum++] = j;
        }
        /*�������Ϣ�����ϣ��*/
        unsigned hash_value = hash(routeInfo[i].name);
        rHash *node = (rHash *)malloc(sizeof(rHash));
        node->id = i;
        strcpy(node->name, routeInfo[i].name);
        node->next = routeNameId[hash_value].next;
        routeNameId[hash_value].next = node;
    }
    fclose(fp);
    return OK;
}

status initDistMat(char *filename)
{
    distMat = (int *)calloc(stationTotal * stationTotal, sizeof(int));
    for (int i = 0; i < stationTotal * stationTotal; i++)
    {
        distMat[i] = MAXFEE;
    }
    FILE *fp = fopen(filename, "r");
    int num;
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++)
    {
        int u, v;
        int distance;
        fscanf(fp, "%d %d %d", &u, &v, &distance);
        int u_v = u * stationTotal + v;
        distMat[u_v] = distance;
    }
    fclose(fp);
    return OK;
}
/*
status initRouteMat(void)
{
    routeMat = (int *)calloc(routeTotal * routeTotal, sizeof(int));
    for (int i = 0; i < routeTotal; i++)
    {
        for (int j = 0; j < routeTotal; j++)
        {
            routeMat[i*routeTotal + j] = findCrossStation(i, j);
        }
    }
    return OK;
}*/

int getRouteIdbyName(char *name)
{
    unsigned hash_value = hash(name);
    rHash *node;
    for (node = routeNameId[hash_value].next; node; node = node->next)
    {
        if (!strcmp(name, node->name))
        {
            return node->id;
        }
    }
    return NOROUTE;
}

int getStationIdbyName(char *name)
{
    unsigned hash_value = hash(name);
    sHash *node;
    for (node = stationNameId[hash_value].next; node; node = node->next)
    {
        if (!strcmp(name, node->name))
        {
            return node->id;
        }
    }
    return NOSTATION;
}

//�ҵ�����·���洦�ĵ�һ��վ��
int findCrossStation(int route1, int route2)
{
    for (int m = 0; m < routeInfo[route1].stationNum; m++)
    {
        for (int n = 0; n < routeInfo[route2].stationNum; n++)
        {
            if (routeInfo[route1].stations[m] == routeInfo[route2].stations[n])
            {
                return m;
            }
        }
    }
    return NOSTATION;
}

//����·������
int distSPFA(int start, int end, int *stations, int &stationNum)
{
    /*��ʼ������*/
    int q_front = 0, q_rear = 0, *Q = (int *)calloc(stationTotal, sizeof(int));
    Q[0] = end;
    q_rear++;
    /*��¼վ���Ƿ��ڶ�����*/
    bool *inQ = (bool *)calloc(stationTotal, sizeof(bool));
    for (int i = 0; i < stationTotal; i++)
    {
        inQ[i] = false;
    }
    inQ[end] = true;
    /*��ʼ��·����ֵ���飬��endΪ0�⣬����Ϊ�����*/
    int *d = (int *)calloc(stationTotal, sizeof(int));
    for (int i = 0; i < stationTotal; i++)
    {
        d[i] = MAXFEE;
    }
    d[end] = 0;
    /*���վ��ĺ�һվ�㣬�������ǳ�ʼ��Ϊû��վ��*/
    int *next = (int *)calloc(stationTotal, sizeof(int));
    for (int i = 0; i < stationTotal; i++)
    {
        next[i] = NOSTATION;
    }
    
    while (q_front != q_rear)
    {
        int u = Q[q_front++];
        inQ[u] = false;
        for (int v = 0; v < stationTotal; v++)
        {
            int v_u = v*stationTotal + u;
            if (distMat[v_u] < MAXFEE && d[v] > d[u] + distMat[v_u])
            {
                d[v] = d[u] + distMat[v_u];
                next[v] = u;
                if (!inQ[v])
                {
                    Q[q_rear++] = v;
                    inQ[v] = true;
                }
            }
        }
    }

    /*�����վ������*/
    stationNum = 0;
    int next_station;
    stations[0] = start;
    while ((next_station = next[stations[stationNum++]]) != NOSTATION)
    {
        stations[stationNum] = next_station;
    }

    int distance = d[start];
    free(Q);
    free(inQ);
    free(d);
    free(next);
    return distance;
}

status transDijkstra(int start, int end, int *stations, int *routes, int &routeNum)
{
    bool *Q = (bool *)calloc(stationTotal, sizeof(int));   //
    int *next_station = (int *)calloc(stationTotal, sizeof(int)); //��һ��תվ��
    int *next_route = (int *)calloc(stationTotal, sizeof(int)); //��һ��·��
    int *d = (int *)calloc(stationTotal, sizeof(int));    //תվ����
    int u, v;

    for (int i = 0; i < stationTotal; i++)
    {
        next_station[i] = NOSTATION;
        next_route[i] = NOROUTE;
        d[i] = MAXFEE;
        Q[i] = true;
    }
    d[end] = 0;

    while (!emptyQ(Q, stationTotal))
    {
        if (searchMin(d, Q, stationTotal, v) == MAXFEE)
        {
            free(d);
            free(Q);
            free(next_station);
            free(next_route);
            return ERROR;
        }
        Q[v] = false;
        if (d[start] < MAXFEE)
        {
            break;
        }
        int alt = d[v] + 1;

        for (int i = 0; i < stationInfo[v].routeNum; i++)
        {
            int route = stationInfo[v].routes[i];
            for (int j = 0; routeInfo[route].stations[j] != v; j++)
            {
                u = routeInfo[route].stations[j];
                if (d[u] > alt)
                {
                    d[u] = alt;
                    next_station[u] = v;
                    next_route[u] = route;
                }
            }
        }
    }

    /*�����վ�㡢·������*/
    routeNum = d[start];
    stations[0] = start;
    for (int i = 0; i < routeNum; i++)
    {
        stations[i + 1] = next_station[stations[i]];
        routes[i] = next_route[stations[i]];
    }
    free(d);
    free(Q);
    free(next_station);
    free(next_route);
    return OK;
}

bool emptyQ(bool *Q, int num)
{
    for (int i = 0; i < num; i++)
    {
        if (Q[i])
        {
            return false;
        }
    }
    return true;
}

//�ҵ�һ����������С����
//�����С��������
//������С����ֵ
int searchMin(int *arr, bool *Q, int num, int &index)
{
    int min = MAXFEE;
    index = -1;
    for (int i = 0; i < num; i++)
    {
        if (Q[i] && arr[i] < min)
        {
            min = arr[i];
            index = i;
        }
    }
    return min;
}
#include <pthread.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/procfs.h>
using namespace std;

void *studentAllocation(void *);
int NumberOfStudents, NumberOfCourses;

int branch;

vector<int> remainingStudents;

int comm, manag, arts, comp;

vector<string> compositionCommerce;
vector<string> compositionManagement;
vector<string> compositionArts;
vector<string> compositionScience;

int Cap_commerce, Cap_management, Cap_arts, Cap_science;

int x = 1;

int main(int argc, char *argv[])
{
    pthread_t stu;
    int i, m, x, y, z, ct;
    NumberOfStudents = atoi(argv[1]);
    NumberOfCourses = atoi(argv[2]);
    ct = 1;
    int comm, manag, comp, arts;
    m = NumberOfCourses % 4; // no of courses jo repeat hai.
    comm = NumberOfCourses / 4;
    manag = NumberOfCourses / 4;
    comp = NumberOfCourses / 4;
    arts = NumberOfCourses / 4;
    comm += m;
    Cap_commerce = ((NumberOfCourses / 4) + (NumberOfCourses % 4)) * 60; // Initial Capacity of Commerce Course;
    Cap_science = ((NumberOfCourses / 4)) * 60;                          // Initial Capacity of science Course;
    Cap_arts = ((NumberOfCourses / 4)) * 60;                             // Initial Capacity of arts Course;
    Cap_management = ((NumberOfCourses / 4)) * 60;
    string str = "0,0,0,0";
    for (int i = 0; i < comm; i++)
    {
        compositionCommerce.push_back(str);
    }
    for (int i = 0; i < manag; i++)
    {
        compositionManagement.push_back(str);
    }
    for (int i = 0; i < comp; i++)
    {
        compositionScience.push_back(str);
    }
    for (int i = 0; i < arts; i++)
    {
        compositionArts.push_back(str);
    }
    for (int i = 1; i <= NumberOfStudents; i++)
    {
        pthread_create(&stu, NULL, &studentAllocation, NULL);
        pthread_join(stu, NULL);
    }
    for (int i = 0; i < remainingStudents.size(); i++)
        cout << "Student " << remainingStudents[i] << " could not be alloted any of the courses" << endl;
}

void printToFile(int a, int b, int c, int d, int e)
{
    int i =1 ;
    FILE *filePointer;
    filePointer = fopen("allocation.txt", "a+");
    fprintf(filePointer,"******************************************************\n");
    fprintf(filePointer, "Student %d has been allocated  all courses \n", a);
    fprintf(filePointer, "%d Number of seats left in Commerce spectrum %d \n",i, b);
    i++;
    fprintf(filePointer, "%d Number of seats left in Management spectrum %d \n",i, c);
    i++;
    fprintf(filePointer, "%d Number of seats left in Arts spectrum %d \n",i, d);
    i++;
    fprintf(filePointer, "%d Number of seats left in Science spectrum %d \n",i, e);
    fprintf(filePointer,"******************************************************");
    fprintf(filePointer, "\n");
    fclose(filePointer);
}
void *studentAllocation(void *t1)
{
    string arr[8];
    random_device rd;
    mt19937 gen(rd());                      // seed the generator
    uniform_int_distribution<> distr(1, 4); // define the range
    branch = distr(gen);
    int ind = 0;
    while (ind < 8)
    {
        random_device rd;
        mt19937 gen(rd());                      // seed the generator
        uniform_int_distribution<> distr(1, 4); // define the range
        int spectrum_option = distr(gen);       // generate numbers
        if (spectrum_option == 1)
        {
            int idx = (std::rand() % (compositionCommerce.size()));
            arr[ind] = to_string(spectrum_option) + "," + to_string(idx);
        }
        else if (spectrum_option == 2)
        {
            int idx = (std::rand() % (compositionManagement.size()));
            arr[ind] = to_string(spectrum_option) + "," + to_string(idx);
        }
        else if (spectrum_option == 3)
        {
            int idx = (std::rand() % (compositionArts.size()));
            arr[ind] = to_string(spectrum_option) + "," + to_string(idx);
        }
        else if (spectrum_option == 4)
        {
            int idx = (std::rand() % (compositionScience.size()));
            arr[ind] = to_string(spectrum_option) + "," + to_string(idx);
        }
        ind++;
    }
    string alloc[4];
    vector<pair<int, int>> st_preferrence(8);
    string strtemp;
    for (int i = 0; i < 8; i++)
    {
        strtemp = "";
        for (int j = 0; j < arr[i].length(); j++)
        {
            if (arr[i][j] != ',')
            {
                strtemp += arr[i][j];
            }
            else
            {
                st_preferrence[i].first = stoi(strtemp);
                strtemp = "";
            }
        }
        st_preferrence[i].second = stoi(strtemp);
    }
    string bitmapalloc = "0000";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int var = 0;
            while(var<4)
            {
                var++;
            }
            if (st_preferrence[j].first == 1 && bitmapalloc[0] != '1')
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q1 < 12)
                    {
                        string str2 = to_string(q1 + 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                        compositionCommerce[st_preferrence[j].second] = str2;
                        Cap_commerce -= 1;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        index++;
                        bitmapalloc[0] = '1';
                        break;
                    }
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q2 < 12)
                    {
                        string str2 = to_string(q1) + "," + to_string(q2 + 1) + "," + to_string(q3) + "," + to_string(q4);
                        compositionCommerce[st_preferrence[j].second] = str2;
                        Cap_commerce -= 1;
                        index++;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        bitmapalloc[0] = '1';
                        index++;
                        break;
                    }
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q3 < 24)
                    {
                        Cap_commerce -= 1;
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3 + 1) + "," + to_string(q4);
                        compositionCommerce[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        index++;
                        st_preferrence[j].first = -1;
                        bitmapalloc[0] = '1';
                        break;
                        index++;
                    }
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q4 < 12)
                    {
                        Cap_commerce -= 1;
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 + 1);
                        compositionCommerce[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        bitmapalloc[0] = '1';
                        index++;
                        break;
                    }
                }
            }
            if (st_preferrence[j].first == 2 && bitmapalloc[1] != '1')
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q1 < 12)
                    {
                        Cap_management -= 1;
                        index++;
                        string str2 = to_string(q1 + 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                        compositionManagement[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        bitmapalloc[1] = '1';
                        index++;
                        break;
                        index++;
                    }
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q2 < 12)
                    {
                        Cap_management -= 1;
                        string str2=  to_string(q1) + "," + to_string(q2 + 1) + "," + to_string(q3) + "," + to_string(q4);
                        compositionManagement[st_preferrence[j].second] =str2;
                        alloc[i] = arr[j];
                        index++;
                        st_preferrence[j].first = -1;
                        bitmapalloc[1] = '1';
                        break;
                        index++;
                    }
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q3 < 24)
                    {
                        index++;
                        Cap_management -= 1;
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3 + 1) + "," + to_string(q4);
                        compositionManagement[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        bitmapalloc[1] = '1';
                        index++;
                        break;
                    }
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q4 < 12)
                    {
                        index++;
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 + 1);
                        compositionManagement[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_management -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[1] = '1';
                        index++;
                        break;
                    }
                }
            }
            if (st_preferrence[j].first == 3 && bitmapalloc[2] != '1')
            {
                if (branch == 1)
                {
                    int index;
                    index++;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q1 < 12)
                    {
                        Cap_arts -= 1;
                        index++;
                        string str2 = to_string(q1 + 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                        compositionArts[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        st_preferrence[j].first = -1;
                        bitmapalloc[2] = '1';
                        index++;
                        break;
                    }
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q2 < 12)
                    {
                        index++;
                        string str2 =to_string(q1 + 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                        compositionArts[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_arts -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[2] = '1';
                        index++;
                        break;
                    }
                }
                else if (branch == 3)
                {
                    int index;
                    index++;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q3 < 24)
                    {
                        string str2 =to_string(q1) + "," + to_string(q2) + "," + to_string(q3 + 1) + "," + to_string(q4);
                        compositionArts[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        index++;
                        Cap_arts -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[2] = '1';
                        index++;
                        break;
                    }
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q4 < 12)
                    {
                        string str2= to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 + 1);
                        compositionArts[st_preferrence[j].second] = 
                        alloc[i] = arr[j];
                        Cap_arts -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[2] = '1';
                        index++;
                        break;
                    }
                }
            }
            if (st_preferrence[j].first == 4 && bitmapalloc[3] != '1')
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q1 < 12)
                    {
                        string str2 =to_string(q1 + 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                        compositionScience[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_science -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[3] = '1';
                        break;
                    }
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q2 < 12)
                    {
                        string str2 = to_string(q1) + "," + to_string(q2 + 1) + "," + to_string(q3) + "," + to_string(q4);
                        compositionScience[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_science -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[3] = '1';
                        break;
                    }
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q3 < 24)
                    {
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3 + 1) + "," + to_string(q4);
                        compositionScience[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_science -= 1;
                        index++;
                        st_preferrence[j].first = -1;
                        bitmapalloc[3] = '1';
                        break;
                        index++;
                    }
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[st_preferrence[j].second];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    if (q4 < 12)
                    {
                        index++;
                        string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 + 1);
                        compositionScience[st_preferrence[j].second] = str2;
                        alloc[i] = arr[j];
                        Cap_science -= 1;
                        st_preferrence[j].first = -1;
                        bitmapalloc[3] = '1';
                        index++;
                        break;
                    }
                }
            }
            /*if(st_preferrence[j].first ==0)
            {
                continue;
            }*/
        }
    }
    /*for(int i=0;i<4;i++)
              cout << alloc[i] <<"\t";
          cout << endl;*/
    if (alloc[0] != "" && alloc[1] != "" && alloc[2] != "" && alloc[3] != "")
        printToFile(x, Cap_commerce, Cap_management, Cap_arts, Cap_science);
    else
    {
        remainingStudents.push_back(x);
        for (int i = 0; i < 4; i++)
        {
            string temp = alloc[i];
            int subject = 0, course = 0;
            string h = "";
            if (temp != "")
            {
                for (int b = 0; b < temp.length(); b++)
                {
                    if (temp[b] == ',')
                    {
                        subject = stoi(h);
                        h = "";
                    }
                    else
                        h += temp[b];
                }
                course = stoi(h);
            }
            // cout<<"subject"<<subject<<"\n";
            if (subject == 1)
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1 - 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                    compositionCommerce[course] = str2;
                    Cap_commerce += 1;
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1) + "," + to_string(q2 - 1) + "," + to_string(q3) + "," + to_string(q4);
                    compositionCommerce[course] = str2 ; 
                    Cap_commerce += 1;
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3 - 1) + "," + to_string(q4);
                    compositionCommerce[course] = str2;
                    Cap_commerce += 1;
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionCommerce[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 - 1);
                    compositionCommerce[course] = str2;
                    Cap_commerce += 1;
                }
            }
            else if (subject == 2)
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 =  to_string(q1 - 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                    compositionManagement[course] =str2 ; 
                    Cap_management += 1;
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1) + "," + to_string(q2 - 1) + "," + to_string(q3) + "," + to_string(q4);
                    compositionManagement[course] = str2 ;
                    Cap_management += 1;
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 =  to_string(q1) + "," + to_string(q2) + "," + to_string(q3 - 1) + "," + to_string(q4);
                    compositionManagement[course] =str2 ;
                    Cap_management += 1;
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionManagement[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 - 1);
                    compositionManagement[course] = str2;
                    Cap_management += 1;
                }
            }
            else if (subject == 3)
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_arts += 1;
                    string str2 =  to_string(q1 - 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                    compositionArts[course] = str2;
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_arts += 1;
                    string str2 = to_string(q1) + "," + to_string(q2 - 1) + "," + to_string(q3) + "," + to_string(q4);
                    compositionArts[course] = str2; 
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_arts += 1;
                    string str2= to_string(q1) + "," + to_string(q2) + "," + to_string(q3 - 1) + "," + to_string(q4);
                    compositionArts[course] = str2;
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionArts[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_arts += 1;
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 - 1);
                    compositionArts[course] = str2;
                }
            }
            else if (subject == 4)
            {
                if (branch == 1)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_science += 1;
                    string str2 = to_string(q1 - 1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4);
                    compositionScience[course] = str2;
                }
                else if (branch == 2)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_science += 1;
                    string str2= to_string(q1) + "," + to_string(q2 - 1) + "," + to_string(q3) + "," + to_string(q4);
                    compositionScience[course] = str2;
                }
                else if (branch == 3)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_science += 1;
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3 - 1) + "," + to_string(q4);
                    compositionScience[course] = str2;
                }
                else if (branch == 4)
                {
                    int index;
                    int option = 0;
                    string str4;
                    int q1;
                    int q2;
                    int q3;
                    int q4;
                    str4 = compositionScience[course];
                    string temp = "";
                    for (int j = 0; j < str4.length(); j++)
                    {
                        if (str4[j] == ',' && option == 0)
                        {
                            q1 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 1)
                        {
                            q2 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 2)
                        {
                            q3 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                        }
                        else if (str4[j] == ',' && option == 3)
                        {
                            q4 = stoi(temp);
                            temp = "";
                            option++;
                            index++;
                            break;
                        }
                        else
                        {
                            temp = temp + str4[j];
                        }
                    }
                    Cap_science += 1;
                    string str2 = to_string(q1) + "," + to_string(q2) + "," + to_string(q3) + "," + to_string(q4 - 1);
                    compositionScience[course] = str2;
                }
            }
        }
    }

    x++;
    return NULL;
}
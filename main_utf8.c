#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINEMAXLENGTH 255
typedef struct Student {
    char name[16];
    char id[16];
    int class;
    int term;
    int gender; // 1 to male, 0 to female
    int math;
    int chinese;
    int english;
}Student;


Student MakeStudentInfo(const char* name, const char* id, int class,
        int term, int gender, int math, int chinese, int english);
void DeleteMenu();

int DeleteInfo(const char* fileName, const char* id);
void DisplayMenu();

void DisplayAll(const char* fileName);

void InfoDump(Student* stuInfo, const char* fileName);

void ReplaceLineByPos(FILE* fp, int pos, const char* fileName, const char* str);
void CreateFileByName(const char* fileName);
void UpdateAverageScore(const char* fileName);
int GetNum(const char* begin, const char* end);
void InsertInfo(const char* name, const char* id, int class,
                int term, int gender, int math, int chinese, int english);
void InsertMenu();
void ModifyMenu();

void ModifyInfo(const char* fileName, int line, Student* stu);
void SearchMenu();

int SearchInfo(const char* fileName, const char* id, Student* res);

void PrintStudentInfo(Student* stu);

void PraseInfoString(const char* infoStr, Student* stu);

int main() {
    int c, d;

    while(1) {
		d = 0;
        printf("                欢迎使用本学生信息管理系统                    \n");
        printf("                1. 添加一个同学的信息                         \n");
        printf("                2. 删除一个同学的信息                         \n");
        printf("                3. 查询一个同学的信息                         \n");
        printf("                4. 修改一个同学的信息                         \n");
        printf("                5. 显示所有同学的信息                         \n");
        printf("                6. 退出程序                                   \n");
        printf("                                                              \n");

        scanf("%d", &c);

        switch (c) {
            case 1: {
                InsertMenu();
                break;
            }
            case 2: {
                DeleteMenu();
                break;
            }
            case 3: {
                SearchMenu();
                break;
            }
            case 4: {
                ModifyMenu();
                break;
            }
            case 5: {
                DisplayMenu();
                break;
            }
            default: {
				d = 1;
                break;
            }
        }
		if(d) break;
    }
    return 0;
}

Student MakeStudentInfo(const char* name, const char* id, int class,
                        int term, int gender, int math, int chinese, int english) {
    Student t;
    strcpy(t.name, name);
    strcpy(t.id, id);
    t.class = class;
    t.term = term;
    t.gender = gender;
    t.math = math;
    t.chinese = chinese;
    t.english = english;
    return  t;
}
void DeleteMenu() {
    char id[16];
    char fileName[64];
    int class, term, result;
    printf("请输入学生学号:");
    scanf("%s", id);
    printf("请输入学生班级:");
    scanf("%d", &class);
    printf("请输入学生现在学期:");
    scanf("%d", &term);

    sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", class, term);

    result = DeleteInfo(fileName, id);
    if(result) {
        printf("删除成功!\n");
    }else {
        printf("删除失败!查无此人\n");
    }
}

int DeleteInfo(const char* fileName, const char* id) {
    FILE* fp = fopen(fileName, "r+");
    int done = 0, lineCount = 0;
    char buf[LINEMAXLENGTH + 1], idBuf[16], *idPos = NULL;

    memset(buf, 0, sizeof buf);
    if(fp != NULL) {
        while (fgets(buf, LINEMAXLENGTH, fp) != NULL) {
            if(buf[0] != '-') {
                idPos = strchr(buf, ' ');
                strncpy(idBuf, buf, (size_t) (idPos - buf));
                idBuf[(size_t) (idPos - buf)] = 0;

                if(!strcmp(id, idBuf)) {
                    ReplaceLineByPos(fp, lineCount, fileName, "");
                    done = 1;
                    break;
                }
                lineCount++;
            }
            memset(buf, 0, sizeof buf);
        }
    }
    if(done)    UpdateAverageScore(fileName);
    return done;
}

void DisplayMenu() {
    char fileName[64];
    int class, term;
    printf("请输入要显示的班级:");
    scanf("%d", &class);
    printf("请输入要显示的学期:");
    scanf("%d", &term);

    sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", class, term);

    DisplayAll(fileName);
}

void DisplayAll(const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    char buf[LINEMAXLENGTH + 1];
    Student t;

    memset(buf, 0, sizeof buf);
    memset(&t, 0, sizeof(Student));
    if (fp != NULL) {
        while (fgets(buf, LINEMAXLENGTH, fp) != NULL) {
            if(buf[0] != '-'){
                PraseInfoString(buf, &t);
                PrintStudentInfo(&t);
            }else{
                printf("%s", buf);
            }
        }
        memset(buf, 0, sizeof buf);
    }else {
        printf("没有此班级的信息!\n");
    }

    if(fp != NULL)  fclose(fp);
}
void InfoDump(Student* stuInfo, const char* fileName) {
    FILE* fp = NULL;
    char buf[64];
    char infoBuf[LINEMAXLENGTH + 1];
    char tmpBuf[LINEMAXLENGTH + 1];
    char* target = NULL;
    int pos = 0, lVal, rVal;

    CreateFileByName(fileName);
    fp = fopen(fileName, "r+");

    memset(infoBuf, 0, sizeof infoBuf);
    while (fgets(infoBuf, LINEMAXLENGTH, fp) != NULL) {
        if (infoBuf[0] != '-') {
            target = strchr(infoBuf, ' ');
            strncpy(buf, infoBuf, (size_t) (target - infoBuf));
            buf[(size_t) (target - infoBuf)] = 0;

            sscanf(stuInfo->id, "%d", &lVal);
            sscanf(buf, "%d", &rVal);
            if (lVal < rVal) {
                break;
            }
            pos++;
        }
        memset(infoBuf, 0, sizeof infoBuf);
    }

    strcpy(tmpBuf, infoBuf);
    sprintf(infoBuf, "%s %s %d %d %d %d %d %d\n", stuInfo->id, stuInfo->name, stuInfo->class,
            stuInfo->term, stuInfo->gender, stuInfo->math, stuInfo->chinese, stuInfo->english);
    strncpy(infoBuf + strlen(infoBuf), tmpBuf, strlen(tmpBuf));

    ReplaceLineByPos(fp, pos, fileName, infoBuf);
}

void ReplaceLineByPos(FILE* fp, int pos, const char* fileName, const char* str) {
    FILE* tfp = fopen("temp.txt", "w+");
    int linePos = 0;
    char infoBuf[LINEMAXLENGTH + 1];

    fseek(fp, 0, SEEK_SET);
    while (fgets(infoBuf, LINEMAXLENGTH, fp) != NULL) {
        fprintf(tfp, "%s", linePos != pos ? infoBuf : str);
        memset(infoBuf, 0 ,sizeof infoBuf);
        linePos++;
    }
    if(!linePos)    fprintf(tfp, "%s", str);
    fclose(fp);
    fclose(tfp);
    remove(fileName);
    rename("temp.txt", fileName);
}


void CreateFileByName(const char* fileName) {
    FILE* fp = fopen(fileName, "a+");
    fclose(fp);
}

void UpdateAverageScore(const char* fileName) {
    FILE* fp = fopen(fileName, "r+");
    char infoBuf[256], average[256];
    int mathSum = 0, chineseSum = 0, englishSum = 0;
    int mathMax = 0, chineseMax = 0, englishMax = 0;
    int mathMin = 0x3f3f, chineseMin = 0x3f3f, englishMin = 0x3f3f;
    int score, lineCount = 0, hasAverage = 0;
    const char* scorePos = NULL;

    memset(infoBuf, 0, sizeof infoBuf);
    while (fgets(infoBuf, LINEMAXLENGTH, fp) != NULL) {
        if(infoBuf[0] != '-') {
            int i = 0;
            const char* pos = infoBuf;
            for(; i < 5; i++)   pos = strchr(pos + 1, ' ');
            scorePos = strchr(pos + 1, ' ');
            score = GetNum(pos + 1, scorePos);
            mathMax = mathMax < score ? score : mathMax;
            mathMin = mathMin > score ? score : mathMin;
            mathSum += score;
            pos = scorePos;
            scorePos = strchr(pos + 1, ' ');
            score = GetNum(pos + 1, scorePos);
            chineseMax = chineseMax < score ? score : chineseMax;
            chineseMin = chineseMin > score ? score : chineseMin;
            chineseSum += score;
            pos = scorePos;
            scorePos = strchr(pos + 1, '\n');
            score = GetNum(pos + 1, scorePos);
            englishMax = englishMax < score ? score : englishMax;
            englishMin = englishMin > score ? score : englishMin;
            englishSum += score;
            lineCount++;
        }else {
            hasAverage = 1;
        }
        memset(infoBuf, 0, sizeof infoBuf);
    }

    sprintf(average, "-average Math:%.1f, Chinese:%.1f, English:%.1f, -max Math:%d, Chinese:%d, English:%d, -min Math:%d, Chinese:%d, English:%d\n", lineCount ? mathSum / (double) lineCount : 0.0,
            lineCount ? chineseSum / (double) lineCount : 0.0, lineCount ? englishSum / (double) lineCount : 0.0, mathMax, chineseMax, englishMax,
            mathMin == 0x3f3f ? 0 : mathMin, chineseMin == 0x3f3f ? 0 : chineseMin, englishMin == 0x3f3f ? 0 : englishMin);
    if(hasAverage) {
        ReplaceLineByPos(fp, lineCount, fileName, average);
    }else {
        fprintf(fp, "%s", average);
        fclose(fp);
    }
}

int GetNum(const char* begin, const char* end) {
    char numBuf[16];
    int num;

    memset(numBuf, 0, sizeof numBuf);
    strncpy(numBuf, begin, (size_t) (end - begin));
    numBuf[(size_t) (end - begin)] = 0;
    sscanf(numBuf, "%d", &num);
    return num;
}
void InsertInfo(const char* name, const char* id, int class,
                int term, int gender, int math, int chinese, int english) {
    Student stu = MakeStudentInfo(name, id, class, term, gender, math, chinese, english);
    char fileName[64] = {0};

    sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", stu.class, stu.term);
    InfoDump(&stu, fileName);

    UpdateAverageScore(fileName);
}

void InsertMenu() {
    char name[16], id[16];
    int class, term, gender, math, chinese, english;
    printf("请输入学生姓名:");
    scanf("%s", name);
    printf("请输入学生学号:");
    scanf("%s", id);
    printf("请输入学生班级:");
    scanf("%d", &class);
    printf("请输入学生学期:");
    scanf("%d", &term);
    printf("请输入学生性别(1代表男, 0代表女):");
    scanf("%d", &gender);
    printf("请输入学生数学成绩:");
    scanf("%d", &math);
    printf("请输入学生语文成绩:");
    scanf("%d", &chinese);
    printf("请输入学生英语成绩:");
    scanf("%d", &english);

    InsertInfo(name, id, class, term, gender, math, chinese, english);

    printf("添加成功!\n");
}

void ModifyMenu() {
    char fileName[64] = {0}, id[16], buf[16];
    int class, term, line, c, val;
    Student stu;

    printf("请输入要修改的学生的学号:");
    scanf("%s", id);
    printf("请输入要修改的学生的班级:");
    scanf("%d", &class);
    printf("请输入要修改的学生现在的学期:");
    scanf("%d", &term);

    sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", class, term);

    line = SearchInfo(fileName, id, &stu);
    if(line >= 0) {
        printf("请选择你要修改的信息(用标号代替): 1.姓名 2.学号 3.班级 4.现在学期 5.性别 6.数学成绩 7.语文成绩 8.英语成绩\n");
        scanf("%d", &c);

        printf("请输入修改后的信息(除修改名字外请输入纯数字,如修改的是性别用1代表男, 0代表女):");
        scanf("%s", buf);
        if(c > 2)  sscanf(buf, "%d", &val);
        if(c == 1) {
            strcpy(stu.name, buf);
        }else if(c == 2){
            strcpy(stu.id, buf);
        }else if(c == 3){
            sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", stu.class, stu.term);
            DeleteInfo(fileName, stu.id);
            stu.class = val;
            InsertInfo(stu.name, stu.id, stu.class, stu.term, stu.gender, stu.math, stu.chinese, stu.english);
        }else if(c == 4){
            sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", stu.class, stu.term);
            DeleteInfo(fileName, stu.id);
            stu.term = val;
            InsertInfo(stu.name, stu.id, stu.class, stu.term, stu.gender, stu.math, stu.chinese, stu.english);
        }else if(c == 5){
            stu.gender = val;
        }else if(c == 6){
            stu.math = val;
        }else if(c == 7){
            stu.chinese = val;
        }else{
            stu.english = val;
        }
        if(c != 3 && c != 4) {
            ModifyInfo(fileName, line, &stu);
            if(c > 5)
                UpdateAverageScore(fileName);
        }
        printf("修改成功!\n");
    }else {
        printf("查无此人!\n");
    }
}


void ModifyInfo(const char* fileName, int line, Student* stu) {
    FILE* fp = fopen(fileName, "r+");
    char buf[LINEMAXLENGTH + 1];

    sprintf(buf, "%s %s %d %d %d %d %d %d\n", stu->id, stu->name, stu->class,
            stu->term, stu->gender, stu->math, stu->chinese, stu->english);

    ReplaceLineByPos(fp, line, fileName, buf);
}
void SearchMenu() {
    char fileName[64] = {0}, id[16];
    int class, term;
    Student res;

    printf("请输入学生学号:");
    scanf("%s", id);
    printf("请输入学生班级:");
    scanf("%d", &class);
    printf("请输入学生现在学期:");
    scanf("%d", &term);

    sprintf(fileName, "2016级%d班第%d学期期末成绩.txt", class, term);

    if(SearchInfo(fileName, id, &res) >= 0) {
        PrintStudentInfo(&res);
    }else {
        printf("查无此人!\n");
    }

}

int SearchInfo(const char* fileName, const char* id, Student* res) {
    FILE* fp = fopen(fileName, "r");
    char infoBuf[LINEMAXLENGTH + 1], idBuf[16], *idPos = NULL;
    int done = 0, lineCount = 0;

    memset(infoBuf, 0, sizeof infoBuf);
    if(fp != NULL) {
        while (fgets(infoBuf, LINEMAXLENGTH, fp) != NULL) {
            if(infoBuf[0] != '-') {
                idPos = strchr(infoBuf, ' ');
                strncpy(idBuf, infoBuf, (size_t) (idPos - infoBuf));
                idBuf[(size_t) (idPos - infoBuf)] = 0;

                if(!strcmp(id, idBuf)) {
                    done = 1;
                    PraseInfoString(infoBuf, res);
                    break;
                }
                lineCount++;
            }
            memset(infoBuf, 0, sizeof infoBuf);
        }
    }

    fclose(fp);
    return done ? lineCount : -1;
}

void PraseInfoString(const char* infoStr, Student* stu) {
    char *prePos = NULL, *pos = NULL;

    memset(stu, 0, sizeof(Student));
    pos = strchr(infoStr, ' ');
    strncpy(stu->id, infoStr, (size_t) (pos - infoStr));
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    strncpy(stu->name, prePos + 1, (size_t) (pos - prePos - 1));
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    stu->class = GetNum(prePos + 1, pos);
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    stu->term = GetNum(prePos + 1, pos);
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    stu->gender = GetNum(prePos + 1, pos);
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    stu->math = GetNum(prePos + 1, pos);
    prePos = pos;
    pos = strchr(prePos + 1, ' ');
    stu->chinese = GetNum(prePos + 1, pos);
    prePos = pos;
    pos = strchr(prePos + 1, '\n');
    stu->english = GetNum(prePos + 1, pos);
}

void PrintStudentInfo(Student* stu) {
    printf("姓名:%s\n", stu->name);
    printf("学号:%s\n", stu->id);
    printf("班级:%d班\n", stu->class);
    printf("学期:第%d学期\n", stu->term);
    printf("性别:%s\n", stu->gender ? "男" : "女");
    printf("数学成绩:%d\n", stu->math);
    printf("语文成绩:%d\n", stu->chinese);
    printf("英语成绩:%d\n", stu->english);
    printf("\n");
}

#include "MyDict.h"
#include "MyTask.h"

int main()
{
    wd::MyTask task("word");
    task.queryIndexTable();
    task.response();
    return 0;
}

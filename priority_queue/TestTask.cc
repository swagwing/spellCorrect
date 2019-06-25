#include "MyDict.h"
#include "MyTask.h"

int main()
{
    wd::MyTask task("hello");
    task.queryIndexTable();
    task.print();
    return 0;
}

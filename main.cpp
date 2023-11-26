#include "ServiceCenter.h"

int main(int argc, char const *argv[])
{
    ServiceCenter *srvc = new ServiceCenter("SampleInput.txt");
    srvc->processStudents();
    srvc->getStats();
    return 0;
}
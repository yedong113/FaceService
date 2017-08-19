#include <iostream>

#include "PersistenceI.h"

int main()
{
    PersistenceI persistence;
    persistence.setDBInfo("faceyes","10.20.1.125","root","123456",3306);
    persistence.readCamera();
    persistence.readPersonBasemap();
    persistence.readConfig();
    return 1;
}
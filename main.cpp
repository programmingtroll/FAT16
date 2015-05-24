#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

struct sectorAssignments{
    int sizeOfCluster;
    int fileAllocationTableAdr;
    int rootDirectoryAdr;
    int fileStorageSpaceAdr;
};

struct fatEntry {
    short int high;
    short int low;
};

struct dirEntry {
    char fc;
    char name[10];
    char fileAttributes;
    char reserved;
    char creationTime[2];
    char creationDate[2];
    char accessDate[2];
    unsigned short int highOrder;
    char modifiedTime[2];
    char modifiedDate[2];
    unsigned short int lowOrder;
    int size;
};

bool formatDevice(unsigned short int,unsigned short int,unsigned short);
bool list(string);

int main()
{
    cout << "Hello World!" << endl;
    cout << sizeof(fatEntry)<< endl;
    cout << sizeof(dirEntry)<< endl;
    formatDevice(65535,512,4);
    string line;
    while(true){
        cout<<"actualdirectory: ";
        cin>>line;
        cout<<"Esta fue la linea que se escribio:"<<line<<endl;
        break;
    }
    return 0;
}

bool formatDevice(unsigned short int fatEntriesNumber, unsigned short int rootDirEntriesNumber, unsigned short sizeOfCluster){
            FILE *ptr_myfile;

            ptr_myfile=fopen("device.bin","wb");
            if (!ptr_myfile)
            {
                printf("Unable to open file!");
                return 1;
            }
            //Address of sectors
            sectorAssignments newSector;

            //Size of cluster
            newSector.sizeOfCluster = sizeOfCluster;

            //Address of FAT
            newSector.fileAllocationTableAdr = sizeof(sectorAssignments);

            //Address of root directory
            newSector.rootDirectoryAdr = sizeof(sectorAssignments)
                                       + (sizeof(fatEntry)*fatEntriesNumber);

            //Address of Storage Space
            newSector.fileStorageSpaceAdr = sizeof(sectorAssignments)
                                          + (sizeof(fatEntry)*fatEntriesNumber)
                                          + (sizeof(dirEntry)*rootDirEntriesNumber);

            fwrite(&newSector, sizeof(sectorAssignments),1, ptr_myfile);

            fatEntry newEntry;
            for (int i = 0; i <= fatEntriesNumber; i++)
            {
                fwrite(&newEntry, sizeof(fatEntry),1, ptr_myfile);
            }

            dirEntry newDirEntry;
            for (int i = 0; i < rootDirEntriesNumber; i++)
            {
                fwrite(&newDirEntry, sizeof(dirEntry),1, ptr_myfile);
            }

            char ch;
            int storageSpace = (sizeOfCluster*1024)*pow(2,16);
//            for (int i = 0; i <= storageSpace; i++)
//            {
//                fwrite(&ch, sizeof(char),1, ptr_myfile);
//            }

            fclose(ptr_myfile);

            return true;
}


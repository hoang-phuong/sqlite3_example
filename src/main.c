#include <stdio.h>
#include <sqlite3.h>

sqlite3 *db;
int main(int argc, char* argv[]){
    int error = 0;

    error = sqlite3_open("example.db", &db);
    if(error){
        fprintf(stderr,"Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        fprintf(stderr, "Opened database successfully\n");
    }
    return 0;
}
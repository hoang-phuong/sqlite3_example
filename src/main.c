#include <stdio.h>
#include <sqlite3.h>

sqlite3 *db;
char* data = "Callback function is called";
static int callback(void *NotUsed, int argc, char** argv, char **azColName){
   int i;
   fprintf(stderr,"%s: ",data);
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]){
    int error = 0;
    char* ErrMsg = 0;
    
    /* Open SQLite Database */
    error = sqlite3_open("example.db", &db);
    if(error){
        fprintf(stderr,"Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_free(ErrMsg);
        return 0;
    }
    else{
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create a table */
    
    char* sql = "CREATE TABLE USERS(" \
                "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                "NAME TEXT NOT NULL," \
                "AGE INT NOT NULL," \
                "ADDRESS CHAR(50)," \
                "BALANCE REAL );";
    error = sqlite3_exec(db, sql, callback,data, &ErrMsg);
    if (error != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
        return 0;
    }
    else{
        fprintf(stdout, "Table created successfully\n");
    }

    /* Insert records into table */
    sql = "INSERT INTO USERS (NAME,AGE,ADDRESS,BALANCE) "  \
         "VALUES ('Phuong', 24, 'Tan Binh', 100000000.00 ); " \
         "INSERT INTO USERS (NAME,AGE,ADDRESS,BALANCE) "  \
         "VALUES ('Tan', 34, 'Hoc Mon', 15000.00 ); "     \
         "INSERT INTO USERS (NAME,AGE,ADDRESS,BALANCE)" \
         "VALUES ('Tung', 24, 'Vung Tau', 20000.00 );" \
         "INSERT INTO USERS (NAME,AGE,ADDRESS,BALANCE)" \
         "VALUES ('Sang', 23, 'Binh Dinh', 65000.00 );";
    error = sqlite3_exec(db, sql, callback,data, &ErrMsg);
    if (error != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
        return 0;
    }
    else{
        fprintf(stdout, "Records inserted successfully\n");
    }     

    /* SELECT */
    sql = "SELECT * FROM USERS";
    error = sqlite3_exec(db, sql, callback,data, &ErrMsg);
    if (error != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
        return 0;
    }
    else{
        fprintf(stdout, "Operation done successfully\n");
    }  

    sqlite3_close(db);
    return 0;
}
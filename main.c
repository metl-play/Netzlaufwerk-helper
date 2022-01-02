#include "framework.h"

//!!! only compile in Release configuration if debug is set to 0 !!!
int debug = 0; //0 is off and 1 is on

int main(int argc, char *argv[])
{
    system("@echo off");
    //system("chcp 1252");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    system("@title Netzlaufwerk Helper");
    system("Cls");
    system("color 1D");
    printf("        Willkommen im Netzlaufwerk helper\n\n");
    printf("        Bestätigen sie mit j oder y decline mit n\n\n");
    printf("M\xF6""chten sie Starten?\n");
    start();

    return 0;
}

int start()
{
    char Eingabe1 = _getch();

    if (Eingabe1 == 'n')
    {
        noStart();
    }
    else if (Eingabe1 == 'y'|'j')
    {
        system("if not exist generated\\NUL mkdir generated");
        doStart();
    }
    else if (Eingabe1 != ('y' | 'n'))
    {
        printf("Ungültige Eingabe\n");
        start();
    }
    return 0;
}

int doStart()
{
    char path[27] = "generated\\netzlaufwerk.bat";
    char Server[100]="dump";
    char Ordner[100]="dump";
    FILE *fp;
    
    if (debug==1)
    {
        printf("\ndoStart()\n");
    }
    
    printf("\nenter your server\n");
    gets(Server, stdin);

    printf("\nNow the folder (\\for subfolders)\n");
    gets(Ordner, stdin);
    
    if (debug == 1)
    {
        printf("\nServer is: %s and shared folder is: %s\n", Server, Ordner);
    }
    printf("\npress enter to generate batchfile..\n");
    system("PAUSE\n");
    //"%userprofile%\\Desktop\\generated\\netzlaufwerk.bat"
    fp = fopen(path, "w+");//generate or open file, if file has contet it will get destroyed
    
    if (fp == NULL) //errorhandling zum erstellen/öffnen der datei
    {
        system("color 0c");
        system("Cls");
        printf("Datei konnte NICHT geöffnet werden.\n");
    }
    else
    {
        printf("\nDatei wird generiert..\n");
        fputs("net use X: ", fp);
        fputs("\\", fp);
        fputs("\\", fp);
        fputs(Server, fp);
        fputs("\\", fp);
        fputs(Ordner, fp);
        fputs(" /persistent:yes", fp);
        
        rewind(fp); //sollte als letztes eingesetzt werden
        fclose(fp);// Datei schliessen
        //remove(file);

        printf("\nDie Datei wurde erfolgreich generiert und gespeichert\n"
        "diese befindet sich im ordnerDerEXE/generated\n");
        system("PAUSE");
        if (debug == 1)
        {
            system("rmdir generated /s");
        }
        return 0;
    }
    return 0;
}

int noStart()
{
    if (debug == 1)
    {
        printf("noStart()\n");
    }
    printf("\n");
    printf("Nicht Starten\n");
    system("PAUSE");

    return 0;
}
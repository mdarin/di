/* * * * *
 * Название: di - команда удаления имитаторов
 * Версия: 0.2.0
 * Описание: удаляет комплект файлов описывающих имитатор
 * Программист разработчик: Дарьин М.В.
 * Программист сопровождения:
 * Дата создания: 14.12.2012
 * Дата последнего изменения: 27.03.2013
 * Организация: ЗАО "ОКБ "ИКАР"
 * Лицензия: "AS-IS" "NO WARRENTY"
 * Контакты:
 * почта: 
 * адрес: 
 * 
 * 2012
 * 
 * * */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

//__DEBUG 
// если определён, то отладочный режим = ВКЛ
#define DEBUG 1
// иначе отладочный режим = ВЫКЛ
#undef DEBUG

#define get_vsn() ("0.2.0")
#define get_usage() ("Usage: <cmd> [OPTIONS] IMITATOR|[IMITATORS]\n"\
"\n"\
"Delete IMITATOR(s)"\
"\n"\
"  -c | --complex\n"\
"  -v | --version\n"\
"  -h | --help")

// пути для размещения сгенерированных файлов
#define get_project_root_dir() ("C:\\Project\\ikar2")
#define get_ipanels_dir() ("C:\\Project\\ikar2\\ipanels")
#define get_wrappers_dir() ("C:\\Project\\ikar2\\wrapper")
#define get_virtual_wrappers_dir() ("C:\\Project\\ikar2\\wrappers\\virtual")
#define get_icfg_dir() ("C:\\Project\\ikar2\\icfg")
#define get_complexes_dir() ("C:\\Project\\ikar2\\icfg\\complexes")
#define get_profile_dir() ("C:\\Project\\ikar2\\icfg\\profile")
#define get_scripts_dir() ("C:\\Project\\ikar2\\scripts")

 /* direct.h
int chdir(char* path)
int chdrive(int drive)
char* getcwd(char* buffer, size_t length)
int getdrive(void)
int mkdir(const char* pathname)
int rmdir(const char* pathname)
void fnmerge(char* path, const char* drive, const char* dir, const char* name, const char* ext)
int fnsplit(const char* path, char* drive, char* dir, char* name, char* ext)
char* searchpath(const char* file)
*/

char *ProjectRoot = NULL;
char IpanelsDir[256] = {0};
char WrappersVirtualDir[256] = {0};
char IcfgDir[256] = {0};
char ProfileDir[256] = {0};
char ScriptsDir[256] = {0};
char TemplatesDir[256] = {0};


/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
void initialize_dirstruct(void)
{
  strcpy(IpanelsDir, ProjectRoot);
  strcat(IpanelsDir, "\\ipanels");

  strcpy(IcfgDir, ProjectRoot);
  strcat(IcfgDir, "\\icfg");

  strcpy(ProfileDir, IcfgDir);
  strcat(ProfileDir, "\\profile");

  strcpy(WrappersVirtualDir, ProjectRoot);
  strcat(WrappersVirtualDir, "\\wrappers\\virtual");

  strcpy(ScriptsDir, ProjectRoot);
  strcat(ScriptsDir, "\\scripts");

  strcpy(TemplatesDir, ProjectRoot);
  strcat(TemplatesDir, "\\utils\\ci\\templates");

  printf("ipanels: %s\nicfg: %s\nprofile: %s\nvirtual: %s\nscripts: %s\n", IpanelsDir, IcfgDir, ProfileDir, WrappersVirtualDir, ScriptsDir);

  return;
}


/* *
 * -------------------------------------------------------
 * Function:
 * Input:
 * Output:
 * Description:
 */
int main(int argc, char **argv)
{
  int Status = 0;
  FILE *Stream = stdout;
  #ifdef DEBUG
  printf("argc: %d\n", argc);
  #endif
  ProjectRoot = getenv("IKAR_ROOT");
  if (NULL == ProjectRoot) {
    printf("%s:Can't find IKAR_ROOT env variable, please setup and try again.\n", argv[0]);
    exit(0);
  }
  printf("IKAR_ROOT: [%s]\n", ProjectRoot);
  initialize_dirstruct();
  
  char FullPath[256] = {0};
  char Imitator[256] = {0};
  char Cmd[256] = {0};
  char File[256] = {0};
  switch(argc) {
  case 0:
  case 1:
    printf("\ndelete imitator v.%s\n\n%s", get_vsn(), get_usage());
    break;
  case 2:
    // удалить каталог и файлы виртуальной панели
    strcpy(Imitator, argv[1]);
    strcpy(FullPath, IpanelsDir);
    chdir(FullPath);
    strcpy(File, Imitator);
    strcat(File, ".exp");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(File, Imitator);
    strcat(File, ".lib");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(File, Imitator);
    strcat(File, ".dll");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(FullPath, IpanelsDir);
    strcat(FullPath, "\\"); 
    strcat(FullPath, Imitator);
    strcpy(Cmd, "rmdir /S /Q ");
    strcat(Cmd, FullPath);
    system(Cmd);     
    #ifdef DEBUG
    printf("%s\n", Cmd);
    printf("ipanel: %s\n", FullPath);
    #endif
    // удалить все файлы и каталоги виртуального враппера
    strcpy(FullPath, WrappersVirtualDir);
    chdir(FullPath);
    strcpy(File, Imitator);
    strcat(File, ".exp");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(File, Imitator);
    strcat(File, ".lib");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(File, Imitator);
    strcat(File, ".dll");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    strcpy(FullPath, WrappersVirtualDir);
    strcat(FullPath, "\\"); 
    strcat(FullPath, Imitator);
    strcpy(Cmd, "rmdir /S /Q ");
    strcat(Cmd, FullPath);
    system(Cmd);     
    #ifdef DEBUG
    printf("%s\n", Cmd);
    printf("virtual wrapper: %s\n", FullPath);   
    #endif
    // удалить файл скрипта логики
    chdir(ScriptsDir);
    strcpy(File, Imitator);
    strcat(File, ".js");
    strcpy(Cmd, "del ");
    strcat(Cmd, File);
    system(Cmd);
    
    fprintf(stdout, "\nImitator: %s removed successfull!\n", Imitator);
    
    break; 
  default:    
     
    break;  
  } // eof switch
  
  return Status;
}

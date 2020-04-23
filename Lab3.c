/* =================================================================== *
*                   Directories, Files, and Timestamps                 *
*                                                                      *
*  Name: Lab3.c                                                        *
*                                                                      *
*  Written by: Brianna Drew - February 2020                            *
*                                                                      *
*  Purpose: To read and process directories as well as to extract      *
*           file attributes (basically like an ls command).            *
*                                                                      *
*  Description of Parameters (ALL OPTIONAL):                           *
*  -s int : specifies the age of the oldest files to be listed from    *
*           the target directory. This is followed by an integer       *
*           representing the maximum number of days old the files can  *
*           be in order for them to be included in the listing.        *
*               example: ""-s 3" means list all files that have been   *
*                        modified in the past 3 days from the current  *
*                        system time.                                  *
*  -b int : specifies the age of the newest files to be listed from    *
*           the target directory. This is followed by an integer       *
*           representing the minimum number of days old the files need *
*           to be in order for them to be included in the listing.     *
*               example: "-b 7" means list all files that have been    *
*                         been modified at least before 7 days         *
*                         previous to the current system time.         *
*  directory_path (must be LAST argument on command line) : path to    *
*           the directory you would like to list. If not present,      *
*           current working directory is assumed.                      *
*               example: "/home/COIS/3380/lab3"                        *
*                                                                      *
*  Subroutines/Libraries Required:                                     *
*      See include statements.                                         *
* ==================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// Function to get and print file information
int CheckFile(int b_time, int s_time, const char *FilePath, const char *FileName);

// Main function
int main(int argc, char *argv[])
{
     // Variable declarations
     const char *FilePath;
     struct dirent **namelist;
     char fileName[255];
     char fpath[255];
     int len;
     int q;
     int s_time;
     int b_time;
     char *DirPath;
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------


// Parse arguments provided at command line

    if(argc == 1) // If no arguments provided...
        {
          DirPath = "./"; // Assume current working directory
        }
     if (argc > 1)
        {
           int len = strlen (argv[1]);

           switch(argc)
          {
              case 1:
                     DirPath = "./"; // Assume current working directory
                     break;
              case 2:
                     DirPath = argv[1];
                     break;
              case 3:
	             if (strcmp(argv[1],"-s")==0) // If the first parameter provided was -s...
        	         {
                            s_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[1],"-b")==0) // If the first parameter provided was -b...
                         {
                            b_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
                         }
                     else   // Print error message
		         {
                            system("@cls||clear");
                            printf("Incorrect entry: Usage: '-s time -b time path or: -s time path or: -b time path'");
			    exit (0);
                         }
                     DirPath = "./"; // Assume current working directory
                     break;
             case 4:
	             if (strcmp(argv[1],"-s")==0) // If the first parameter provided was -s...
        	         {
                	    s_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[1],"-b")==0) // If the first parameter provided was -b...
                         {
                            b_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
                         }
                     DirPath = argv[3]; // Third argument is the directory path
                     break;
            case 5:
	             if (strcmp(argv[1],"-s")==0) // If the first parameter provided was -s...
        	         {
                	    s_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[1],"-b")==0) // If the first parameter provided was -b...
                         {
                            b_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
                         }
	             if (strcmp(argv[3],"-s")==0) // If the third parameter provided was -s...
        	         {
                	    s_time = atoi(argv[4])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[3],"-b")==0) // If the third parameter provided was -b...
                         {
                            b_time = atoi(argv[4])*86400; // The following parameter is the corresponding # of days
                         }
                 DirPath = "./"; // Assume current working directory
                 break;

             case 6:
	             if (strcmp(argv[1],"-s")==0) // If the first parameter provided was -s...
        	         {
                	    s_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[1],"-b")==0) // If the first parameter provided was -b...
                         {
                            b_time = atoi(argv[2])*86400; // The following parameter is the corresponding # of days
                         }
                     if (strcmp(argv[3],"-s")==0) // If the third parameter provided was -s...
        	         {
                	    s_time = atoi(argv[4])*86400; // The following parameter is the corresponding # of days
             	         }
                     else if (strcmp(argv[3],"-b")==0) // If the third parameter provided was -b...
                         {
                            b_time = atoi(argv[4])*86400; // The following parameter is the corresponding # of days
                         }
                     DirPath = argv[5]; // Fifth argument is the directory path
                     break;
              }

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

// Add slash to end of path if it doesn't exist
    if ((DirPath[len-1] !='/'))
	{
                 strcat (DirPath,"/");
	}
	else
	{
//        	 printf("There\n");
	}
}

// Clear screen and print directory

    system("@cls||clear");
    printf("\nInformation for %s\n\n",DirPath);

     int n;
     int x;

     if (argc < 1)
        {
           exit(EXIT_FAILURE);
        }
     else if (argc == 1)
        {
// If no arguments provided, search current directory
           n=scandir(".",&namelist,NULL,alphasort);
        }
     else
        {
// Get directory listing based on path provided
           n = scandir(DirPath, &namelist, NULL, alphasort);
        }
     x=n;
     if (n < 0)
        {
           perror("scandir");
           exit(EXIT_FAILURE);
        }
     else
        {
           n=-1; // For descending order - comment out for ascending order

           while (n<x-1) // For descending order - comment out for ascending order
               {
                   n++;
                   strncpy(fileName, namelist[n]->d_name, 254);
                   strcpy (fpath,DirPath);


// Call function to process directory listing with sorts based on -s and -b switched provided
                   int x=CheckFile(b_time,s_time,strcat(fpath,fileName),fileName);
               }
           free(namelist);
        }
printf("\n");
     exit(EXIT_SUCCESS);
}




// Function to print Directory info

int CheckFile(int b_time, int s_time, const char *FilePath, const char *FileName)
{
 // Variable declarations
 static int TitleFlag;
 char* FileType;
 time_t sec;
 sec = time (NULL);


// Get file type
    struct stat fileStat;
    if(stat(FilePath,&fileStat) < 0)
        return 1;

    if (S_ISREG(fileStat.st_mode)) {
        FileType="reg";
    }
    if (S_ISDIR(fileStat.st_mode)) {
           FileType="dir";
    }
    if (S_ISLNK(fileStat.st_mode)) {
           FileType="lnk";
    }


// Print listing header  on first loop
     if (TitleFlag == 0)
     {
         TitleFlag=1;

// listing header
         printf("%-8s%-6s%-6s%-8s%-20s%-24s%s\n","inode","Type","UID","GID","SIZE","Filename","Modification date");
         printf("%-8s%-6s%-6s%-8s%-20s%-24s%s\n","-----","----","---","---","---------------","---------------------","------------------------");
     }

// Do comparision on switches -s and -b for filtering of dates

      if ((s_time!=0)&&(b_time!=0))
          {
      		if ((fileStat.st_mtime < sec-b_time)&&(s_time + fileStat.st_mtime > sec))
 	      		{
         		     printf("%-8d%-6s%-6d%-6d%10d  bytes     %22s  %s",fileStat.st_ino,FileType,fileStat.st_uid,fileStat.st_gid,fileStat.st_size,FileName,ctime(&fileStat.st_mtime));
      			}
          }
      else if ((s_time==0)&&(b_time==0))
          {
         		     printf("%-8d%-6s%-6d%-6d%10d  bytes     %22s  %s",fileStat.st_ino,FileType,fileStat.st_uid,fileStat.st_gid,fileStat.st_size,FileName,ctime(&fileStat.st_mtime));
          }
      else if (b_time == 0)
          {
      		if (s_time + fileStat.st_mtime > sec)
                       {
         		     printf("%-8d%-6s%-6d%-6d%10d  bytes     %22s  %s",fileStat.st_ino,FileType,fileStat.st_uid,fileStat.st_gid,fileStat.st_size,FileName,ctime(&fileStat.st_mtime));
                       }
          }
      else if (s_time == 0)
         {
      		if (fileStat.st_mtime < sec-b_time)
                      {
         		     printf("%-8d%-6s%-6d%-6d%10d  bytes     %22s  %s",fileStat.st_ino,FileType,fileStat.st_uid,fileStat.st_gid,fileStat.st_size,FileName,ctime(&fileStat.st_mtime));
                      }
         }
}

//******************************************************************************************************************************
//********************************************************END*******************************************************************
//******************************************************************************************************************************

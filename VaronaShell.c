#include<conio.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

/********************************************************
*	Author: Varona, Mary Charelene C.
*	----------------------------------
* A simulation of Windows command prompt written in C.
*	Last Modified on: December 4, 2017
*********************************************************/

/*
*	Funtion receive_input
*	----------------------------------------------------
* reads the input of the use and stores it in a
*	character array.
*/
void receive_input( char command[] ){
    gets(command);
}


/*
*	Funtion current_directory
*	----------------------------------------------------
* int type - value is either 0 or 1
*     0 - diplay directory concatinated with '>'
*     1 - simply display the current directory
*
*	displays the current working directory
*/
void current_directory(int type) {
	 char directory[1024];
   if (getcwd(directory, sizeof(directory)) != NULL){
			if(type == 1)
				fprintf(stdout, "%s\n\n", directory);
			else
				fprintf(stdout, "%s>", directory);
   }
}

/*
*	Funtion clear_screen
*	----------------------------------------------------
*  fills out the entire screen with blanks
*  and puts the cursor at its home coordinates
*/
void clear_screen(){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer.
 	if( !GetConsoleScreenBufferInfo( hConsole, &csbi )){
    return;
 	}

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Fill the entire screen with blanks.
  if( !FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten ) ){
    return;
  }

  // Get the current text attribute.
  if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))	{
    return;
  }

  // Set the buffer's attributes accordingly.
  if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten ) ) {
    return;
  }

  // Put the cursor at its home coordinates.
  SetConsoleCursorPosition( hConsole, coordScreen );
}

/*
*	Funtion get_version
*	----------------------------------------------------
*  Displays the system's OS Version
*/
void get_version() {
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.
    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion)) + 400;

    printf("Microsoft Windows [Version %d.%d.%d]\n", dwMajorVersion+4,dwMinorVersion-2,dwBuild+5463);
    printf("2017 Microsoft Corporation. All rights reserved.\n\n");
}

/*
*	Funtion getdate
*	----------------------------------------------------
*  Display's the current date.
*/
void getdate(char *date)	{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("The current date is: %d/%d/%d \n",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	printf("Enter the new date: (dd-mm-yy) ");
	gets(date);

	setdate(date);
}

/*
*	Funtion setdate
*	----------------------------------------------------
*  Prompts the user to enter a new date.
*/
void setdate(char *date) {
	if(strlen(date) != 0) {
		while(strlen(date) != 0 && valid_date_format(date) != 1) {
			printf("The system cannot accept the date entered.\n");
			printf("Enter the new date: (dd-mm-yy) ");
			gets(date);
		}

		if(valid_date_format(date) == 1) {
			printf("A required privilege is not held by the client.\n\n");
		}else{
			printf("\n");
		}
	}else{
		printf("\n");
	}
}

/*
*	Funtion valid_date_format
*	----------------------------------------------------
*  returns 1 if format of string date is a valid date
*  format, else returns 0.
*/
int valid_date_format( char date[] )	{
	char d[20], m[20], y[20];
	int day, month, year;
	int count;

	if(strstr(date, "/") != NULL) {
		if(3 != sscanf(date, "%d/%d/%d", &day, &month, &year)){
			return 0;
		}
	}else{
		if(3 != sscanf(date, "%d-%d-%d", &day, &month, &year)){
			return 0;
		}
	}

	if(strstr(date, "-") == NULL && strstr(date, "/") == NULL){
		return 0;
	}

	if(strlen(date) == 0)
		return 2;

	return (((day >= 1) && (day <= 31)) &&
		((month >= 1) && (month <= 12)) &&
		((year >= 0) && (year <= 9999)));
}

/*
*	Funtion gettime
*	----------------------------------------------------
*  displays the current time.
*/
void gettime(char *time) {
  SYSTEMTIME st;
  GetLocalTime(&st);

  printf("The current time is: %d:%d:%d.%02d\n", st.wHour, st.wMinute,st.wSecond,st.wMilliseconds);
  printf("Enter the new time:");
  gets(time);

  settime(time);
}

/*
*	Funtion settime
*	----------------------------------------------------
*  prompts the user to enter a new time.
*/
void settime(char *time)	{
	if(strlen(time) != 0) {
  	while(strlen(time) != 0 && valid_time_format(time) != 1) {
      printf("The system cannot accept the time entered.\n");
      printf("Enter the new time:");
      gets(time);
    }

    if(valid_time_format(time) != 2) {
        printf("A required privilege is not held by the client.\n\n");
    }else{
    	printf("\n");
    }
	}else{
		printf("\n");
	}
}

/*
*	Funtion valid_time_format
*	----------------------------------------------------
*  returns 1 if format of string time is a valid time
*  format, else returns 0.
*/
int valid_time_format( char time[] )	{
  int hour = 0, minute = 0, second = 0, ms = 0;
	char *h, *m, *s, *mms;

  if(strstr(time, ":") != NULL) {
    sscanf( time, "%d:%d:%d.%d", &hour, &minute, &second, &ms );
    if(contains_letters(time)){
      return 0;
    }
	}else{
		if(!numbers_only(time)){
			return 0;
		}
	}

  if(strlen(time) == 0)
		return 2;

	if(ms >= 0) {
		return (((hour >= 0) && (hour < 24)) &&
		((minute >= 0) && (minute < 60)) &&
		((second >= 0) && (second< 60)));
	} else {
		return 0;
	}
}

/*
*	Funtion open_file
*	----------------------------------------------------
*  opens a file, and displays its contents.
*/
void open_file(char file_name[], int tokens) {
	if(file_exists(file_name)) {
		FILE *ptr_file;
		char buf[1000];

		if(tokens > 2){
			printf("%s\n",file_name);
			printf("\n\n");
		}

		ptr_file =fopen(file_name,"r");
		if (!ptr_file)
			return 1;

		while (fgets(buf,1000, ptr_file)!=NULL)	{
				printf("%s",buf);
		}
		fclose(ptr_file);
		printf("\n");
	}else {
		char directory[1024];
		getcwd(directory, sizeof(directory));
		strcat(directory, "\\");
		strcat(directory, file_name);
		if(is_Directory(directory)){
			printf("Access is denied.\n\n");
		}else{
			if(tokens > 2){
				printf("The system cannot find the file specified.\n");
				printf("Error occurred while processing: %s\n\n",file_name);
			}else{
				printf("The system cannot find the file specified.\n\n");
			}
		}
	}
}

/*
*	Funtion file_exists
*	----------------------------------------------------
*  returns 1 if string file_name exists
*  else returns 0.
*/
int file_exists(char file_name[]) {
  DIR           *directory;
  struct dirent *dir;
  directory = opendir(".");
  int exists = 0;
  if (directory)	{
    while ((dir = readdir(directory)) != NULL)	{
      if(strcmp(file_name, dir->d_name) == 0) {
      	exists = 1;
      }
    }
  }
  closedir(directory);
  return exists;
}

/*
*	Funtion numbers_only
*	----------------------------------------------------
*  returns 1 if string s contains numbers only
*  else returns 0.
*/
int numbers_only(char *s){
  while (*s) {
  	if (isdigit(*s++) == 0)
  		return 0;
  }
  return 1;
}

/*
*	Funtion contains_letters
*	----------------------------------------------------
*  returns 1 if string s contains letters
*  else returns 0.
*/
int contains_letters(char *s) {
  while (*s) {
    if (isalpha(*s++) != 0){
    		return 1;
    }
  }
  return 0;
}

/*
*	Funtion to_lower_case
*	----------------------------------------------------
* converts string command into lowercase and stores
* it in string lc_COMMAND.
*/
void to_lower_case(char command[], char lc_COMMAND[]) {
	char s[strlen(command)];
	char* token;
	int c = 0;

	strcpy(s, command);
	token = strtok(s, " ");

  while (token ) {
		if(c == 0){
			strcpy(lc_COMMAND, token);
			strlwr(lc_COMMAND);
		}
    token = strtok(NULL, " ");
		c++;
	}
}

/*
*	Funtion nth_token
*	----------------------------------------------------
*  stores the n token in string nthToken
*/
void nth_token(char command[], char nthToken[], int n){
  char s[strlen(command)];
	char* token;
	int c = 1;

	strcpy(s, command);
	token = strtok(s, " ");

	while (token ) {
		if(c == n){
			strcpy(nthToken, token);
		}
    token = strtok(NULL, " ");
		c++;
	}
}

/*
*	Funtion no_of_tokens
*	----------------------------------------------------
*  returns the number of tokens in a string
*/
int no_of_tokens(char command[]) {
	char s[strlen(command)];
	char* token;
	int count = 0;

	strcpy(s, command);
	token = strtok(s, " ");
	while (token ) {
    token = strtok(NULL, " ");
		count++;
	}
	return count;
}

/*
*	Funtion occurences
*	----------------------------------------------------
*  returns the number of occurences of a character c
*  in string source.
*/
int occurences(char *source, char c) {
	char *del = &source[strlen(source)]-1;
	int count = 0;

	 while (del > source){
			if( *del == c){
				count++;
			}
        del--;
    }
	return count;
}

/*
*	Funtion all_dots
*	----------------------------------------------------
*  returns 1 if string s only contains the character '.'
*  else returns 0.
*/
int all_dots(char *s) {
	while (*s) {
		if (*s++ != '.')
				return 0;
	}
	return 1;
}

/*
*	Funtion trim_path
*	----------------------------------------------------
*  removes the last string in given source.
*/
void trim_path (char* source){
		char *del = &source[strlen(source)];
		int slash_count = occurences(source, '\\');

    while (del > source && *del != '\\'){
        del--;
    }

    if (*del== '\\'){
				if(slash_count == 1){
					*del++;
				}
        *del= '\0';
    }
    return;
}

/*
*	Funtion change_directory
*	----------------------------------------------------
* moves to another directory
*/
void change_directory(char path[]){
	if(chdir(path) != 0)	{
  	printf("The system cannot find the path specified.\n\n");
  }else{
    printf("\n");
  }
}

/*
*	Funtion make_directory
*	----------------------------------------------------
* creates a new directory.
*/
void make_directory(char *directory, int tokens) {
	if(_mkdir(directory) != 0){
		printf("A subdirectory or file %s already exists.\n",directory);
		if(tokens > 2){
		    printf("Error occured while processing: %s\n", directory);
		}
	}
}

/*
*	Funtion remove_directory
*	----------------------------------------------------
*  deletes a given directory.
*/
void remove_directory(char *directory, int tokens) {
	if(rmdir(directory) != 0){
		if(_mkdir(directory) != 0) {
			printf("Directory is not empty.\n");
		}else{
			rmdir(directory);
			printf("The system cannot find file specified.\n");
		}
	}
}

/*
*	Funtion rename_file
*	----------------------------------------------------
* renames a specific file.
*/
void rename_file(char *original, char *new_name){
	if(file_exists(original)) {
		rename(original, new_name);
	}else{
		printf("The system cannot find file specified.\n");
	}
}

/*
*	Funtion is_Directory
*	----------------------------------------------------
*  returns 1 if a given target is a directory
*  else returns 0.
*/
int is_Directory(char target[]) {
	 struct stat statbuf;
   stat(target, &statbuf);
   return S_ISDIR(statbuf.st_mode);
}

/*
*	Funtion delete_file
*	----------------------------------------------------
*  deletes a specific file.
*/
void delete_file(char *file, int tokens) {
	char directory[1024];
	char path[1024];
	char choice[100];
	int done = 0;
	getcwd(directory, sizeof(directory));
	getcwd(path, sizeof(directory));
	strcat(path, "\\");
	strcat(path, file);

	if(is_Directory(path)){
		strcat(directory, "\\");
		strcat(directory, file);
		strcat(directory, "\\");
		strcat(directory, "*");
		while(done == 0)	{
			printf("%s, Are you sure (Y/N)? ",directory);
			receive_input(choice);
			strlwr(choice);
			if(strcmp(choice, "y") == 0 || strcmp(choice, "n") == 0){
				done = 1;
			}
		}
	}else{
		if(file_exists(file)){
			remove(file);
		}else{
			int result = remove(file);
			if(result != 0) {
				strcat(directory, "\\");
				strcat(directory, file);
				printf("Could Not Find %s\n", directory);
			}
		}
	}
}


/*
*	Funtion display_directory
*	----------------------------------------------------
*  displays metadata of the files found in the
*  current directory.
*/
void display_directory(char *directory) {
	struct dirent *directory_entry;
	struct stat info;
	char path[1024];
	char *dayofWeek, *month, *day, *time, *year;
	int fsize = 0;
	int dsize = 0;
	int fileCount = 0;
	int dirCount = 0;
	strcpy(path, directory);
	DIR *dr = opendir(".");

	printf(" Volume in drive C is OS\n");
	printf(" Volume Serial Number is 98C8-FA90\n\n");
	printf(" Directory of %s\n\n",path);
	if (dr == NULL) {
			printf("Could not open current directory" );
	}

	while ((directory_entry = readdir(dr)) != NULL){
			char date[20];
			char time[20];
			int size;
			strcpy(path, directory);
			strcat(path, "\\");
			strcat(path, directory_entry->d_name);
			stat(path, &info);
			strftime(date, 20, "%d/%m/%y", localtime(&(info.st_ctime)));
			strftime(time, 20, "%I:%M %p", localtime(&(info.st_ctime)));

			if(is_Directory(path)){
				dirCount++;
				printf("%s  %s   <DIR> \t  %s\n",date,time,directory_entry->d_name);
				struct dirent *sub_directory_entry;
				DIR *sub_dr = opendir(path);
				if(sub_dr == NULL){

				}else{

				}
				dsize += info.st_size;
			}else{
				fileCount++;
				size = info.st_size;
				fsize += size;
				printf("%s  %s         %6d %s\n",date,time,size,directory_entry->d_name);
			}
	}
	printf("\t     %d File(s)    %d bytes \n", fileCount, fsize);
	printf("\t     %d Dir(s)     %d bytes free\n\n", dirCount, dsize);

	closedir(dr);
	return 0;
}

/*
*	Funtion copy
*	----------------------------------------------------
*  copies a file to a directory or to another file.
*/
void copy(char command[]) {
	FILE *file_pointer1;
	FILE *file_pointer2;
	int tocopy = 1, ask = 1, current_token = 2, files_copied = 0;
	int nTokens = no_of_tokens(command) - 1;
  char *temp;
	char c;
	char cwd[1024];
	char input[1024];
	char nthToken[strlen(command)];
	char filename[strlen(command)];
  getcwd(cwd, sizeof(cwd));

	if(nTokens == 2) {
		nth_token(command, filename, 2);
		file_pointer1 = fopen(filename, "r");

		if(file_pointer1 == NULL) {
			printf("The system cannot find the file specified.\n\n");
		} else {
			nth_token(command, nthToken, 3);
			file_pointer2 = fopen(nthToken, "r");
			if(file_pointer2 == NULL) {
				if(is_Directory(nthToken)) {
					strcat(cwd, "\\");
					strcat(cwd, nthToken);
					chdir(cwd);
					file_pointer2 = fopen(filename, "r");

					if(file_pointer2) {
						strcat(temp, nthToken);
						strcat(temp, "\\");
						strcat(temp, filename);
						while(ask){
							printf("Overwrite %s? (Yes/No/All): ", temp);
							gets(input);

							if(strstr(input, "yes") != NULL ||
						   		strstr(input, "y")  != NULL ||
						   		strstr(input, "all") != NULL||
						   		strstr(input, "a") != NULL) {
								tocopy = 1;
								ask = 0;
								break;
							}else if(strstr(input, "no") != NULL ||
								strstr(input, "n") != NULL) {
								tocopy = 0;
								ask = 0;
								break;
							} else {
								continue;
							}
						}
					}

					if(tocopy){
						file_pointer2 = fopen(filename, "w+");
						while((c = getc(file_pointer1)) != EOF) {
							fputc(c, file_pointer2);
						}
						files_copied++;
					}
					printf("\t%d file(s) copied.\n\n", files_copied);
					trim_path(cwd);
					change_directory(cwd);
				} else{
					nth_token(command, filename, 3);
					file_pointer2 = fopen(filename, "w+");
					while( (c = getc(file_pointer1)) != EOF) {
						fputc(c, file_pointer2);
					}
					files_copied++;
					printf("\t%d file(s) copied.\n\n", files_copied);
				}
			} else {
				while(ask){
					printf("Overwrite %s? (Yes/No/All): ");
					gets(input);

					if(strstr(input, "yes") != NULL ||
				   		strstr(input, "y")  != NULL ||
				   		strstr(input, "all") != NULL||
				   		strstr(input, "a") != NULL) {
						tocopy = 1;
						ask = 0;
						break;
					}else if(strstr(input, "no") != NULL ||
						strstr(input, "n") != NULL) {
						tocopy = 0;
						ask = 0;
						break;
					} else {
						continue;
					}
				}

				if(tocopy){
					nth_token(command, filename, 3);
					file_pointer2 = fopen(filename, "w+");
					while((c = getc(file_pointer1)) != EOF) {
						fputc(c, file_pointer2);
					}
					files_copied++;
				}
				printf("\t%d file(s) copied.\n\n", files_copied);

			}
		}
	}
	fclose(file_pointer1);
	fclose(file_pointer2);
}

/*
*	Funtion move
*	----------------------------------------------------
*  moves a file to a directory or to another file.
*/
void move(char command[]) {
	FILE *file_pointer1;
	FILE *file_pointer2;
	int tocopy = 1, ask = 1, current_token = 2, files_copied = 0;;
	int nTokens = no_of_tokens(command) - 1;
  char *temp;
	char c;
	char cwd[1024];
	char input[1024];
	char nthToken[strlen(command)];
	char filename[strlen(command)];
  getcwd(cwd, sizeof(cwd));

	nth_token(command, filename, 2);
	file_pointer1 = fopen(filename, "r");

	if(file_pointer1 == NULL) {
		printf("The system cannot find the file specified.\n\n");
		return;
	}
	if(nTokens == 1) {
		files_copied++;
		printf("\t%d file(s) moved.\n\n", files_copied);
	} else {
		nth_token(command, nthToken, 3);
		file_pointer2 = fopen(nthToken, "r");

		if(file_pointer2 == NULL) {
			if(is_Directory(nthToken)) {
				strcat(cwd, "\\");
				strcat(cwd, nthToken);
				chdir(cwd);
				file_pointer2 = fopen(filename, "r");

					if(file_pointer2) {
						strcat(temp, nthToken);
						strcat(temp, "\\");
						strcat(temp, filename);
						while(ask){
							printf("Overwrite %s? (Yes/No/All): ", temp);
							gets(input);

							if(strstr(input, "yes") != NULL ||
						   		strstr(input, "y")  != NULL ||
						   		strstr(input, "all") != NULL||
						   		strstr(input, "a") != NULL) {
								tocopy = 1;
								ask = 0;
								break;
							}else if(strstr(input, "no") != NULL ||
								strstr(input, "n") != NULL) {
								tocopy = 0;
								ask = 0;
								break;
							} else {
								continue;
							}
						}
					}

					if(tocopy){
						file_pointer2 = fopen(filename, "w+");
						while((c = getc(file_pointer1)) != EOF) {
							fputc(c, file_pointer2);
						}
						files_copied++;
					}
					fclose(file_pointer1);
					trim_path(cwd);
					change_directory(cwd);
					remove(filename);
					printf("\t%d file(s) moved.\n\n", files_copied);

			} else {
				nth_token(command, filename, 3);
				file_pointer2 = fopen(filename, "w+");
				while( (c = getc(file_pointer1)) != EOF) {
					fputc(c, file_pointer2);
				}
				files_copied++;
				nth_token(command, filename, 2);
				fclose(file_pointer1);
				remove(filename);
				printf("\t%d file(s) moved.\n\n", files_copied);

			}
		} else {
			while(ask){
					printf("Overwrite %s? (Yes/No/All): ");
					gets(input);

					if(strstr(input, "yes") != NULL ||
				   		strstr(input, "y")  != NULL ||
				   		strstr(input, "all") != NULL||
				   		strstr(input, "a") != NULL) {
						tocopy = 1;
						ask = 0;
						break;
					}else if(strstr(input, "no") != NULL ||
						strstr(input, "n") != NULL) {
						tocopy = 0;
						ask = 0;
						break;
					} else {
						continue;
					}
				}

				if(tocopy){
					nth_token(command, filename, 3);
					file_pointer2 = fopen(filename, "w+");
					while((c = getc(file_pointer1)) != EOF) {
						fputc(c, file_pointer2);
					}
					files_copied++;
					fclose(file_pointer1);
					nth_token(command, filename, 2);
					remove(filename);
				}
				printf("\t%d file(s) moved.\n\n", files_copied);
		}
	}
	fclose(file_pointer2);
}


/*
*	Funtion evaluate
*	----------------------------------------------------
*  evalutes the command inputted by the user.
*/
void evaluate(char command[]){
	char  lc_COMMAND [500];
	int valid_command = 0;
	int tokens = no_of_tokens(command);
	to_lower_case(command,lc_COMMAND);

	/* CD */
	if(strcmp(lc_COMMAND, "cd") == 0 || strcmp(lc_COMMAND, "cd..") == 0) {
		valid_command = 1;
		char *temp;
		char directory[1024];
		int dirCount = sscanf(lc_COMMAND, "cd%s;", &temp);

		getcwd(directory, sizeof(directory));
		if(tokens == 1 ){
			if(dirCount == 1)	{
				trim_path(directory);
				change_directory(directory);
			}else{
				current_directory(1);
			}
		}else {
			char nthToken[strlen(command)];
			nth_token(command, nthToken, 2);
			if(tokens == 2 ) {
				if(strcmp(nthToken, "..") == 0 && dirCount != 1){
					trim_path(directory);
					change_directory(directory);
				}else{
					strcat(directory, "\\");
					strcat(directory, nthToken);
					change_directory(directory);
				}
			} else {
				strcat(directory, "\\");
				strcat(directory, nthToken);
				char nthToken[strlen(command)];
				int validNextTokens;
				int current_n = 2;
				nth_token(command, nthToken, 2);
				validNextTokens = all_dots(nthToken);
				current_n++;

				if(validNextTokens == 0) {
					while(current_n <= tokens && validNextTokens == 1){
						nth_token(command, nthToken, current_n);
						validNextTokens = all_dots(nthToken);
						current_n++;
					}
					if(validNextTokens == 1) {
						change_directory(directory);
					} else {
						printf("The system cannot find the path specified.\n\n");
					}
				}else {
					printf("\n");
				}
			}
		}
	}

	/* CHDIR */
	if(strcmp(lc_COMMAND,"chdir") == 0 || strcmp(lc_COMMAND, "chdir..") == 0) {
		valid_command = 1;
		char *temp;
		char directory[1024];
		int chdirCount = sscanf(lc_COMMAND, "chdir%s;", &temp);
		getcwd(directory, sizeof(directory));
		if(tokens == 1 ){
			if(chdirCount == 1)	{
				trim_path(directory);
				change_directory(directory);
			}else{
				current_directory(1);
			}
		}else {
			char nthToken[strlen(command)];
			nth_token(command, nthToken, 2);
			if(tokens == 2 ) {
				if(strcmp(nthToken, "..") == 0 && chdirCount != 1){
					trim_path(directory);
					change_directory(directory);
				}else{
					strcat(directory, "\\");
					strcat(directory, nthToken);
					change_directory(directory);
				}
			} else {
				strcat(directory, "\\");
				strcat(directory, nthToken);
				int validNextTokens = 1;
				int current_n = 2;
				nth_token(command, nthToken, 2);
				validNextTokens = all_dots(nthToken);
				current_n++;

				if(validNextTokens == 0) {
					while(current_n <= tokens && validNextTokens == 1){
						nth_token(command, nthToken, current_n);
						validNextTokens = all_dots(nthToken);
						current_n++;
					}
					if(validNextTokens == 1) {
						change_directory(directory);
					} else {
						printf("The system cannot find the path specified.\n\n");
					}
				}else {
					printf("\n");
				}
			}
		}
	}

	/* CLS */
	if(strcmp(lc_COMMAND,"cls") == 0) {
		valid_command = 1;
		clear_screen();
		printf("\n");
	}

	/* CMD */
	if(strcmp(lc_COMMAND,"cmd") == 0) {
		valid_command = 1;
		get_version();
	}

	/* DATE */
	if(strcmp(lc_COMMAND,"date") == 0) {
		valid_command = 1;
		char date[10];
		if(tokens <= 2) {
				if(tokens == 1){
					getdate(date);
				}else{
					char nthToken[strlen(command)];
					nth_token(command,nthToken, 2);

					if(valid_date_format(nthToken) == 0){
						setdate(nthToken);
					}else{
						printf("A required privilege is not held by the client.\n\n");
					}

				}
		}
	}

	/* TIME */
	if(strcmp(lc_COMMAND,"time") == 0) {
		valid_command = 1;
		char time[24];

		if(tokens <= 2) {
				if(tokens == 1){
					gettime(time);
				}else{
					char nthToken[strlen(command)];
					nth_token(command,nthToken, 2);

					if(valid_time_format(nthToken) == 0){
						settime(nthToken);
					}else{
						printf("A required privilege is not held by the client.\n\n");
					}

				}
		}
	}

	/* MKDIR */
	if(strcmp(lc_COMMAND,"mkdir") == 0) {
		char nthToken[strlen(command)];
		valid_command = 1;
		if(tokens >= 2) {
			int nTokens = tokens - 1;
			int current_token = 2;
			while(nTokens != 0){
				nth_token(command, nthToken, current_token);
        make_directory(nthToken,tokens);
				nTokens--;
				current_token++;
			}
		} else {
			if(tokens == 1){
				printf("The syntax of the command is incorrect.\n\n");
			}
		}
		printf("\n");
	}

	/* RMDIR */
	if(strcmp(lc_COMMAND,"rmdir") == 0) {
		char nthToken[strlen(command)];
		valid_command = 1;
		if(tokens >= 2) {
			int nTokens = tokens - 1;
			int current_token = 2;
			while(nTokens != 0){
				nth_token(command, nthToken, current_token);
        remove_directory(nthToken,tokens);
				nTokens--;
				current_token++;
			}
		} else {
			if(tokens == 1){
				printf("The syntax of the command is incorrect.\n\n");
			}
		}
		printf("\n");
	}

	/* DEL */
	if(strcmp(lc_COMMAND,"del") == 0) {
		char nthToken[strlen(command)];
		valid_command = 1;
		if(tokens >= 2) {
			int nTokens = tokens - 1;
			int current_token = 2;
			while(nTokens != 0){
				nth_token(command, nthToken, current_token);
        delete_file(nthToken,tokens);
				nTokens--;
				current_token++;
			}
		} else {
			if(tokens == 1){
				printf("The syntax of the command is incorrect.\n\n");
			}
		}
		printf("\n");
	}

	/* RENAME */
	if(strstr(lc_COMMAND,"rename") != NULL) {
		char original[strlen(command)];
		char new_name[strlen(command)];
		char *temp;
		int renameCount = (lc_COMMAND, "rename%s;", &temp);
		valid_command = 1;
		if(tokens == 3) {
			nth_token(command,original, 2);
			nth_token(command,new_name, 3);
			rename_file(original, new_name);
		} else {
			printf("The syntax of the command is incorrect.\n\n");
		}
		printf("\n");
	}

	/* DIR */
	if(strstr(lc_COMMAND, "dir") != NULL) {
		valid_command = 1;
		char *temp;
		char directory[1024];
		int dirCount = sscanf(lc_COMMAND, "dir%s;", &temp);

		getcwd(directory, sizeof(directory));
		if(tokens == 1 ){
			if(strcmp(lc_COMMAND, "dir..") == 0 || strcmp(lc_COMMAND, "dir") == 0){
				display_directory(directory);
			}else{
				printf(" Directory of %s\n");
				printf("File Not Found\n");
			}
			if(dirCount == 1)	{
				trim_path(directory);
				change_directory(directory);
			}else{
				current_directory(1);
			}
		}
	}

	/* COPY */
	if(strstr(lc_COMMAND, "copy") != NULL) {
		valid_command = 1;
		char *temp;
		int copyCount = sscanf(lc_COMMAND, "copy%s;", &temp);

		if(tokens == 1 && copyCount != -1) {
			printf("The syntax of the command is incorrect.\n");
		}

		if(tokens == 2) {
		  printf("The file cannot be copied onto itself.\n");
		} else {
		  copy(command);
		}
	}

	/* MOVE */
	if(strstr(lc_COMMAND, "move") != NULL) {
		valid_command = 1;
		char *temp;
		int moveCount = sscanf(lc_COMMAND, "move%s;", &temp);

		if(tokens == 1 && moveCount != -1) {
			printf("The syntax of the command is incorrect.\n");
		} else {
		  move(command);
		}
	}

	/* TYPE */
	if(strcmp(lc_COMMAND,"type") == 0) {
		valid_command = 1;
		if(tokens >= 2) {
			int nTokens = tokens - 1;
			int nthToken = 2;
			while(nTokens != 0){
				char file_name[strlen(command)];

				nth_token(command,file_name, nthToken);
				open_file(file_name, tokens);
				nTokens--;
				nthToken++;
			}
		} else {
			if(tokens == 1){
				printf("The syntax of the command is incorrect.\n\n");
			}
		}
	}

	/* EXIT */
	if(strcmp(lc_COMMAND,"exit") == 0) {
		valid_command = 1;
		return 0;
	}

	if(valid_command !=	 1){
		printf("'%s' is not recognized as an internal or external command,\noperable program or batch file.\n\n", lc_COMMAND);
	}
	run_program();
}

/*
*	Funtion run_program
*	----------------------------------------------------
*  handles the flow of the program.
*/
void run_program() {
	char command[1000];

	/*
	*	By default, the path of the current directory is always displayed.
	*/
	current_directory(0);
	receive_input(command);
	evaluate(command);
}

int main()	{
	get_version();
	run_program();
	return 0;
}

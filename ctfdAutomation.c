#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


void movingCharsRight(char *textPosition, int ending, int length){
	char *data = textPosition;
	data[length]='\0';
    length-1;
	for (length; length>ending; length-=1){
		data[length]=data[length-1];
	}

}
void movingCharsLeft(char *textPosition, int starting, int length){
        char *data = textPosition;
        for (starting; starting<=length; starting+=1){

                data[starting]=data[starting+1];
        }
}


void addingBackslash(char *textPosition){
	char *data = textPosition;
	int countend = strlen(data);
	for (int count=0; count<=countend; count+=1){
		if(data[count]=='\n'){
			data[count]='\\';
			movingCharsRight(textPosition, count, countend);
			countend+=1;
			data[count+1]='n';
		}else if(data[count]=='\t'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='t';
                }else if(data[count]=='\"'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='\"';
                }else if(data[count]=='\r'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='r';
                }else if(data[count]=='\a'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='a';
                }else if(data[count]=='\b'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='b';
                }else if(data[count]=='\f'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='f';
                }else if(data[count]=='\v'){
                        data[count]='\\';
                        movingCharsRight(textPosition, count, countend);
                        countend+=1;
                        data[count+1]='v';
                }
	}
}


void removeSpecialChars(char *textPosition){
        char *data = textPosition;
        int countend = strlen(data);
        for (int count=0; count<=countend; count+=1){
                if(data[count]=='\n' || data[count]=='\t' || data[count]=='\v' || data[count]=='\f' || data[count]=='\b' || data[count]=='\a' ||data[count]=='\r' || data[count]==' '){
                        movingCharsLeft(textPosition, count, countend);
                        countend-=1;
		}
	}
}


int extractData(FILE *filePointer, char charitor, char *pos, char start[], char end[]){
        int titleLength=0;
	int startPosition=0;
	int endPosition=0;
        int hashFlag = 0;
	char *title = pos;
        //loop through entire file
        while (hashFlag != 2 && charitor != EOF){

        	if (hashFlag==1){
        		if (charitor == end[endPosition] && end[endPosition+1]=='\0'){
				title[titleLength]='\0';
                                hashFlag+=1;
        		}
			else if (charitor == end[endPosition]){
				endPosition+=1;
				charitor = getc(filePointer);
			}
			else {
				endPosition=0;
                		title[titleLength]=charitor;
                                titleLength+=1;
				charitor = getc(filePointer);
                	}
        	}
        	else if (charitor == start[startPosition]){
			startPosition+=1;
			charitor = getc(filePointer);
			if (start[startPosition]=='\0'){
        			hashFlag = 1;
			}
        	}else {
			charitor = getc(filePointer);
			startPosition = 0;
		}
	}
	if (hashFlag == 2){
		return 0;
	}
	else {
		return 1;
	}
}




int main(){
	char challanges[500000]="{\"count\":,\"results\":[";
    char flags[100000]="{\"count\":,\"results\":[";
	int challangeCount = 0;

	struct dirent *dpCatagory;
        char *path="./"; // Directory target
        DIR *catagory = opendir(path); // Open the directory - dir contains a pointer to manage the dir
        while (dpCatagory=readdir(catagory)){ // if dp is null, there's no more content to read
                if (dpCatagory->d_name[0]!='.' && strcmp(dpCatagory->d_name,"README.md") && strcmp(dpCatagory->d_name,"a.out") && strcmp(dpCatagory->d_name,"test.c") && strcmp(dpCatagory->d_name,"Trivia")){
			printf("\n\n%s\n",dpCatagory->d_name);
			char fileCatagory[20]="";
			strcat(fileCatagory,dpCatagory->d_name);


			struct dirent *dpChallange;
                        char pathchallange[30]="./"; // Directory target
                        strcat(pathchallange,dpCatagory->d_name);
                        DIR *challange = opendir(pathchallange); // Open the directory - dir contains a pointer to manage the dir
			int agin=0;
                        while (dpChallange=readdir(challange)){
                                if (dpChallange->d_name[0]!='.' && strcmp(dpChallange->d_name,"README.md")){
					char readmePath[50]="";
					strcat(readmePath, pathchallange);
					strcat(readmePath,"/");

					strcat(readmePath,dpChallange->d_name);
					strcat(readmePath,"/README.md");
					//Open File and asign the begining to a pointer
					FILE *filePointer=NULL;
					filePointer = fopen(readmePath, "r");
					//check file has opened
					if (filePointer == NULL){
						printf("failed to open file %s", readmePath);
					}else{
						char title[50]="";
						char *titlePosition;
						titlePosition=&title[0];

						//get first charitor
						char charitor = getc(filePointer);

						//Extract the title
						extractData(filePointer,charitor, titlePosition, "# ", "\n");
						//set up strings that will concatanate with the chalanges and flags var to become  challanges.json and flags.json
						char chalangeinfo[9000]="{\"id\":";
						char flaginfo[1000]="{\"id\":";

						//add and increment id's
						challangeCount += 1;
						char id[4];
						sprintf(id, "%d", challangeCount);

						strcat(flaginfo,id);
						strcat(flaginfo,",\"challenge_id\":");
						strcat(flaginfo,id);
						strcat(flaginfo,",");

						strcat(chalangeinfo,id);
						strcat(chalangeinfo,",\"name\":\"");
						strcat(chalangeinfo,title);
						strcat(chalangeinfo,"\",");

						//flag data strings
						char regex[20]= "\"type\":\"";
						char flag[50]= "\"content\":\"";
						char caseSensitivity[30]= "\"data\":\"";

						//challange data strings
						int count=0;
						char description[900]="\"description\":\"";
						char maxAttempts[20] = "\"max_attempts\":";
						char points[15] = "\"value\":";
						char category[30]="\"category\":\"";
						strcat(category,fileCatagory);
						strcat(category,"\",");
						char type[30]="\"type\":\"";
						char state[30]="\"state\":\"";
						char requirements[40] = "\"requirements\":";
						char connection[40] = "\"connection_info\":";
						char nextId[30]="\"next_id\":";

						int endofFile = 0;

						while (!endofFile){
							count+=1;
							//get next feild
							char feildName[70]="";
							char *feildPosition;

							char feildContent[955]="";
							char *contentPosition;

		                			feildPosition=&feildName[0];
							contentPosition=&feildContent[0];

							endofFile = extractData(filePointer,charitor, feildPosition, "## ", ":");
							endofFile = extractData(filePointer,charitor, contentPosition, "```", "```");
							if (endofFile){

							}else if (!strcmp(feildName,"discription") || !strcmp(feildName,"Description") ){
								addingBackslash(contentPosition);
								strcat(description, feildContent);
								strcat(description, "\",");
							}else if (!strcmp(feildName,"soulution") || !strcmp(feildName,"Solution")){
							}else if (!strcmp(feildName,"flag") || !strcmp(feildName,"Flag")){
								removeSpecialChars(contentPosition);
								addingBackslash(contentPosition);
								strcat(flag,feildContent);
								strcat(flag,"\",");
       		                			}else if (!strcmp(feildName,"points") || !strcmp(feildName,"Points")){
								removeSpecialChars(contentPosition);
								strcat(points,contentPosition);
								strcat(points,",");

               		        			}else if (!strcmp(feildName,"hints") || !strcmp(feildName,"Hints")){
               		                			 printf("not implemented %s yet",feildName);
	               	        			}else if (!strcmp(feildName,"files") || !strcmp(feildName,"Files")){
        	       	                			 printf("not implemented %s yet",feildName);
               	        				}else{
								printf("error %s not reconised\n",feildName);
							}
						}
						/*set defaults if no data has been specified.*/
						if (strlen(caseSensitivity)==8){
							strcat(caseSensitivity,"case_insensitive\"},");
						}
						if (strlen(regex)==8){
							strcat(regex, "static\",");
						}
						if (strlen(flag)==11){
							printf("file Missing Flag");
							fclose(filePointer);
  					                closedir(challange);
        						closedir(catagory);
							return 1;
						}



						if ( strlen(description)==15){
							printf("youve missed a discription buddy");
							fclose(filePointer);
                                                        closedir(challange);
                                                        closedir(catagory);
							return 1;
						}
						if ( strlen(maxAttempts)==15){
							strcat(maxAttempts, "0,");
						}
						if( strlen(points)==8){
							strcat(points,"7,");
						}
						if ( strlen(category)==12){
                				        strcat(category,"Misc\",");
						}
						if ( strlen(type)==8){
                				        strcat(type,"standard\",");
						}
						if( strlen(state)==9){
                				        strcat(state,"hidden\",");
						}
						if ( strlen(requirements)==15){
                				        strcat(requirements,"null,");
						}
						if ( strlen(connection)==18){
                				        strcat(connection,"null,");
						}
						if ( strlen(nextId)==10){
                        				strcat(nextId,"null},");
						}


						//make challange and flag strings for hte challange
						strcat(flaginfo,regex);
                				strcat(flaginfo,flag);
                				strcat(flaginfo,caseSensitivity);

						strcat(chalangeinfo,description);
						strcat(chalangeinfo,maxAttempts);
						strcat(chalangeinfo,points);
                				strcat(chalangeinfo,category);
						strcat(chalangeinfo,type);
                				strcat(chalangeinfo,state);
						strcat(chalangeinfo,requirements);
                				strcat(chalangeinfo,connection);
						strcat(chalangeinfo,nextId);

						strcat(challanges,chalangeinfo);
        					strcat(flags,flaginfo);
						agin=1;
					}
					fclose(filePointer);
				}
			}
        		closedir(challange);
		}
	}
        closedir(catagory); // close the handle (pointer)


	//post file crawl processing
	char amount[4];
        sprintf(amount, "%d", challangeCount);
	int flagLength=strlen(flags);
	int challangeLength=strlen(challanges);


	challanges[challangeLength-1]='\0';
        flags[flagLength-1]='\0';

	char *flagPosition;
        flagPosition=&flags[0];

        char *challangePosition;
        challangePosition=&challanges[0];

	for (int i=0; i<strlen(amount);i+=1){
		movingCharsRight(flagPosition,9,flagLength);
		movingCharsRight(challangePosition,9,challangeLength);
		flags[9+i]=amount[i];
		challanges[9+i]=amount[i];
	}
	strcat(challanges, "],\"meta\":{}}");
	strcat(flags, "],\"meta\":{}}");
	printf("\n\n\n%s\n\n\n\n", challanges);
        printf("\n\n\n%s\n\n\n\n", flags);
	return 0;
}

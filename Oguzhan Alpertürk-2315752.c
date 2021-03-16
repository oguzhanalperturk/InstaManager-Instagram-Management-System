#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct node{
	int uniqueID;
	char accountName[25];
	int noPosts;
	int noFollowing;
	int noFollowers;
	char date[25];
	char time[15];
	struct node *next;
};

struct ListRecord{
 	struct node *head;
 	struct node *tail;
 	int size;
};
typedef struct ListRecord *List;

struct datetime{
	char date[25];
	char time[15];
};

List initialiseMyAccount(char name[25]);

struct datetime MakeIntegerDateTimeString();

void addAccount(List temp,char name[25],int post,int following,int follower);

void printMyAccount(List temp);

void searchAccount(List temp,char name[25]);

void deleteAccount(List temp,int idnum);

void OverwriteMyAccount(char file[15],List temp);
	
	
int main(){
   
	List followers,followings;  
	int command;
	int post,follower,following;
	char n[25];
	char name[25];
	int first,second,third,fourth;
	int id,i;
	struct node *control;
	
	followers = initialiseMyAccount("followers.txt");
	followings = initialiseMyAccount("following.txt");
	printf("The following.txt file has been loaded successfully\n");
	printf("The followers.txt file has been loaded successfully");
	
	while(1){

		printf("\n\n----- MENU-----\n");
		printf("1. Add a new Account\n");
		printf("2. Print My Account Info\n");
		printf("3. Search Account\n");
		printf("4. Delete Account\n");
		printf("5. Exit\n\n");
		printf("Enter your option: ");
		scanf("%d",&command);
		
		if(command == 1){
			
			printf("(1) Add a following account\n");
			printf("(2) Add a follower account\n");
			printf("Enter your option ");
			scanf("%d",&first);
			if(first == 1){
				printf("\nEnter name of the account: ");
				scanf("%s",name);
				printf("Enter number of posts: ");
				scanf("%d",&post);
				printf("Enter number of followers: ");
				scanf("%d",&follower);
				printf("Enter number of following: ");
				scanf("%d",&following);
				i=0;
				for(control = followings->head->next;control != NULL;control = control->next){
					if(strcmp(control->accountName,name) == 0){
						i++;	
					}
				}
				if(i==0){
					addAccount(followings,name,post,following,follower);
					printf("\nThe account has been added to following list!!");
				}
				else{
					printf("\nThe account already exists!!!");	
				}		
			}
		
		
			else if(first == 2){
				printf("\nEnter name of the account: ");
				scanf("%s",name);
				printf("Enter number of posts: ");
				scanf("%d",&post);
				printf("Enter number of followers: ");
				scanf("%d",&follower);
				printf("Enter number of following: ");
				scanf("%d",&following);
				i=0;
				for(control = followers->head->next;control != NULL;control = control->next){
					if(strcmp(control->accountName,name) == 0){
						i++;	
					}
				}
				if(i==0){
					addAccount(followers,name,post,following,follower);
					printf("\nThe account has been added to followers list!!");
				}
				else{
					printf("\nThe account already exists!!!");	
				}	
			}	
		}
		
		
		else if(command == 2){
			printf("(1) Print following list\n");
			printf("(2) Print follower list");
			printf("\nEnter your option: ");
			scanf("%d",&second);
			if(second == 1){
				printf("\n-----My following list----");
				printMyAccount(followings);
			}
			else if(second == 2){
				printf("\n-----My followers list----");
				printMyAccount(followers);
			}
			
		}
		
	
		else if(command == 3){
			
			printf("(1) Search following list\n");
			printf("(2) Search follower list\n");
			printf("Enter your option: ");
			scanf("%d",&third);
			printf("Enter the name of the account: ");
			scanf("%s",n);
			if(third == 1){
				searchAccount(followings,n);
			}
			else if(third == 2){
				searchAccount(followers,n);
			}	
		}
			
		
		else if(command == 4){
	
			printf("(1) Delete account from following list\n");
			printf("(2) Delete account from followers list\n");
			printf("Enter your option: ");
			scanf("%d",&fourth);
			printf("Enter account ID: ");
			scanf("%d",&id);
			if(fourth == 1){
				deleteAccount(followings,id);
			}
			else if(fourth == 2){
				deleteAccount(followers,id);
			}		
		}
		
		
		else if(command == 5){
			
			printf("Goodbye!!!\n\n");
			OverwriteMyAccount("following.txt",followings);
			printf("The following.txt has been updated successfully\n");
			OverwriteMyAccount("followers.txt",followers);
			printf("The followers.txt has been updated successfully");
			break;
		}
		
		
		else{
			printf("Enter proper command!\n");
		}		
	}
	
	free(followers);
	free(followings);
	free(control);
	
	return 0;
}

List initialiseMyAccount(char name[25]){
	
	List temp;
	struct node *iter;
	temp = (List )malloc(sizeof(List));
	temp->head = (struct node *)malloc(sizeof(struct node));
	temp->tail = temp->head;
	temp->size = 0;
	iter = temp->head;
	
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(name,"r");
	int i = 0;
 
while(1){
	
	if(fgets(str,sizeof(str),ffile) == NULL){
		iter->next = NULL;
		temp->tail = iter;
		break;
	}
	else{
		iter->next = (struct node *)malloc(sizeof(struct node));
		iter = iter->next;
		
		strcpy(line,strtok(str,";"));
		iter->uniqueID = atoi(line);
		        
		i=0;
		while(1){
			if(i==0){
			piece = strtok(NULL, ";");
			strcpy(iter->accountName,piece);
				if(piece == NULL){
					break;
			}	}
			
			else if(i==1){
			piece = strtok(NULL, ";");
			iter->noPosts = atoi(piece);
				if(piece == NULL){
					break;
			}}	
			
			else if(i==2){
			piece = strtok(NULL, ";");
			iter->noFollowing = atoi(piece);
				if(piece == NULL){
					break;
			}}	
			
			else if(i==3){
			piece = strtok(NULL, ";");
			iter->noFollowers = atoi(piece);
				if(piece == NULL){
					break;
			}}	
			
			else if(i==4){
			piece = strtok(NULL, " ");
			strcpy(iter->date,piece);
				if(piece == NULL){
					break;
			}}
			else if(i==5){
			piece = strtok(NULL, " ");	
			piece[strlen(piece) - 1] = '\0';
			strcpy(iter->time,piece);
				if(piece == NULL){
					break;
			}}
			
			else break;
			
		i++;
		}	
	}
    temp->size ++;	
}
	fclose(ffile);

	return temp;
}


void addAccount(List temp,char name[25],int post,int following,int follower){
	
		struct node *n;
		struct node *iter;
		int id = 0;
		struct datetime dt;
		n = (struct node *)malloc(sizeof(struct node));
		n->next = NULL;
		for(iter = temp->head->next;iter != NULL;iter = iter->next){
			if(iter->uniqueID > id){
				id = iter->uniqueID;
			}
		}
		
		id ++;
		
		n->uniqueID = id;
		dt = MakeIntegerDateTimeString();
		strcpy(n->date,dt.date);
		strcpy(n->time,dt.time);
		strcpy(n->accountName,name);
		n->noPosts = post;
		n->noFollowers = follower;
		n->noFollowing = following;
		temp->tail->next = n;
		temp->tail = temp->tail->next;
		temp->size ++;			
}


void printMyAccount(List temp){
	
	int i = 1;
	struct node *iter;
	iter = temp->head;
	iter = iter->next;
	
	while(iter != NULL){

		printf("\nAccount ID: %d\n",iter->uniqueID);
		printf("Account name: %s\n",iter->accountName);
		printf("Number of Posts: %d\n",iter->noPosts);
		printf("Number of Following: %d\n",iter->noFollowing);
		printf("Number of Followers: %d\n",iter->noFollowers);
		printf("Date: %s\n",iter->date);
		printf("Time: %s\n",iter->time);
		printf("----------------------------");
		i++;
		iter = iter->next;
		}
}


void searchAccount(List temp,char name[25]){
	
	struct node *iter;
	int i = 0;
	for(iter = temp->head->next;iter != NULL;iter = iter->next){
		if(strcmp(iter->accountName,name) == 0){
			printf("\nAccount ID: %d\n",iter->uniqueID);
			printf("Account name: %s\n",iter->accountName);
			printf("Number of Posts: %d\n",iter->noPosts);
			printf("Number of Following: %d\n",iter->noFollowing);
			printf("Number of Followers: %d\n",iter->noFollowers);
			printf("Date: %s\n",iter->date);
			printf("Time: %s\n",iter->time);
			i++;
			break;
		}
	}
	if(i==0){
		printf("\nThere is no account with this name in the list!!!!");
	}
}


void deleteAccount(List temp,int idnum){
	
	struct node *iter;
	struct node *back;
	iter = temp->head->next;
	back = temp->head;
	int control = 0;
	
	while(iter != NULL){
		if(iter->uniqueID == idnum){
			control++;
			break;
		}
		iter = iter->next;
		back = back->next;
	}
	
	if(temp->tail == iter){
		temp->tail = back;
	}
	
	if(control==0){
		printf("\nAccount with ID %d does not exist.",idnum);
	}
	else{
		back->next = back->next->next;
		free(iter);
		printf("\nAccount with ID %d has been deleted successfully.",idnum);
	}
}


void OverwriteMyAccount(char file[15],List temp){
	
	struct node *iter;
	FILE *f1;
	
	f1 = fopen(file,"w");
	
	for(iter = temp->head->next; iter!=NULL;iter = iter->next){
		fprintf(f1,"%d;%s;%d;%d;%d;%s %s\n",iter->uniqueID,iter->accountName,iter->noPosts,iter->noFollowing,iter->noFollowers,iter->date,iter->time);	
	}
	
	fclose(f1);
}	


struct datetime MakeIntegerDateTimeString(){
	
	struct datetime dt;
	char x[15];
	
	time_t ti = time(NULL);
	struct tm t = *localtime(&ti);

	sprintf(x,"%d",t.tm_mday);
	strcpy(dt.date,x);
	strcat(dt.date,"/");
	sprintf(x,"%d",t.tm_mon+1);
	strcat(dt.date,x);
	strcat(dt.date,"/");
	sprintf(x,"%d",t.tm_year+1900);
	strcat(dt.date,x);
	
	sprintf(x,"%d",t.tm_hour);
	strcpy(dt.time,x);
	strcat(dt.time,":");
	sprintf(x,"%d",t.tm_min);
	strcat(dt.time,x);

	return dt;
}
	
	
	



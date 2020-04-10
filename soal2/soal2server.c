#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <asm-generic/socket.h>
#define PORT 8080

int opponenthealth;
int myhealth;
int server_fd, new_socket, new_socket2, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
FILE *listakun;
pthread_t tid[2];
pthread_mutex_t lock;	
struct Akun Acc;
struct Player Player_data;

struct Akun
{
    char username[12];
    char password[50];
};

struct Player
{
    int ready;
    int health1;
    int health2;
};

int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}

void* clientthread(void *arg)
{
	pthread_t id = pthread_self();
	if(pthread_equal(id,tid[0])) //thread 1
	{
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        main1:;
            memset(buffer, 0, 1024);
            valread = read(new_socket, buffer, 1024);
            if(strcmp(buffer, "register") == 0 || strcmp(buffer, "Register") == 0 || strcmp(buffer, "REGISTER") == 0)
            {
                //read from client
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(Acc.username, buffer);
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(Acc.password, buffer);
                //append data
                listakun  = fopen ("akun.txt", "a");
                fwrite(&Acc,sizeof(Acc),1,listakun);
                fclose(listakun);
                //read data
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    printf("\nUsername: %12s\t\tPassword: %12s\n",Acc.username,Acc.password);
                    fflush(stdout);
                }
                fclose(listakun);
                goto main1;
            }
            else if(strcmp(buffer, "login") == 0 || strcmp(buffer, "Login") == 0 || strcmp(buffer, "LOGIN") == 0)
            {
                //read from client
                char user[12];
                char pass[50];
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(user, buffer);
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(pass, buffer);
                memset(buffer, 0, 1024);
                //read data
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    if(strcmp(user, Acc.username) == 0 && strcmp(pass, Acc.password) == 0)
                    {
                        fclose(listakun);
                        printf("\nAuth Success\n");
                        fflush(stdout);
                        char *success = "Login Success";
                        send(new_socket, success, strlen(success), 0);
                        goto find1; 
                    }
                }
                fclose(listakun);
                printf("\nAuth Failed\n");
                fflush(stdout);
                char *failed = "Login Failed";
                send(new_socket , failed , strlen(failed) , 0 );
                goto main1;
            }
            else if(strcmp(buffer, "exit") == 0 || strcmp(buffer, "Exit") == 0 || strcmp(buffer, "EXIT") == 0)
            {
                return 0;
            }
            else
            {
                goto main1;
            }
        find1:;
            memset(buffer, 0, 1024);
            valread = read(new_socket, buffer, 1024);
            if(strcmp(buffer, "logout") == 0 || strcmp(buffer, "Logout") == 0 || strcmp(buffer, "LOGOUT") == 0)
            {
                memset(buffer, 0, 1024);
                sleep(1);
                goto main1;
            }
            else if(strcmp(buffer, "find") == 0 || strcmp(buffer, "Find") == 0 || strcmp(buffer, "FIND") == 0)
            {
                memset(buffer, 0, 1024);
                Player_data.health1 = 0;
                Player_data.health2 = 0;
                Player_data.ready = Player_data.ready + 1;
                to1:;
                    if(Player_data.ready == 2)
                    {
                        char *start = "Game dimulai, silahkan tap tap secepat mungkin!!";
                        send(new_socket , start , strlen(start) , 0 );
                        memset(buffer, 0, 1024);
                        Player_data.health1 = Player_data.health1 + 100;
                        char health1[3];
                        sleep(1);
                        hit1:;
                            if (Player_data.health1 > 0 && Player_data.health2 > 0)
                            {
                                Player_data.health2 = Player_data.health2 - 10;
                                char *detected = "detected";
                                send(new_socket , detected , strlen(detected) , 0 );
                                miss1:;
                                memset(buffer, 0, 1024);
                                valread = read(new_socket, buffer, 1024);
                                if (strcmp(buffer, "attack") == 0)
                                {
                                    memset(buffer, 0, 1024);
                                    sprintf(health1, "%d", Player_data.health1);
                                    send(new_socket , health1 , strlen(health1) , 0 );
                                    msleep(100);
                                    goto hit1;
                                }
                                else
                                {
                                    goto miss1;
                                }
                                
                                goto hit1;
                            }
                            else if(Player_data.health1 <= 0 || Player_data.health2 <= 0)
                            {
                                char *reward = "reward";
                                send(new_socket , reward , strlen(reward) , 0 );
                                memset(buffer, 0, 1024);
                                msleep(100);
                                if(Player_data.health1 <= 0 && Player_data.health2 > 0)
                                {
                                    char *rewardo = "Pertandingan Berakhir, Kamu Kalah";
                                    send(new_socket , rewardo , strlen(rewardo) , 0 );
                                    Player_data.ready = Player_data.ready - 1;
                                    goto find1;
                                }
                                else if(Player_data.health2 <= 0 && Player_data.health1 > 0)
                                {
                                    char *rewardo = "Pertandingan Berakhir, Kamu Menang";
                                    send(new_socket , rewardo , strlen(rewardo) , 0 );
                                    Player_data.ready = Player_data.ready - 1;
                                    goto find1;
                                }
                            }
                            else
                            {
                                goto hit1;
                            }
                    }
                    else
                    {
                        char *wait = "wait";
                        send(new_socket , wait , strlen(wait) , 0 );
                        memset(buffer, 0, 1024);
                        sleep(1);
                        goto to1;
                    }
            }
            else
            {
                goto find1;
            }
            
        pthread_exit(NULL);
	}

    if(pthread_equal(id,tid[1])) //thread 2
	{
        if ((new_socket2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        main2:;
            memset(buffer, 0, 1024);
            valread = read(new_socket2, buffer, 1024);
            if(strcmp(buffer, "register") == 0 || strcmp(buffer, "Register") == 0 || strcmp(buffer, "REGISTER") == 0)
            {
                //read from client
                memset(buffer, 0, 1024);
                valread = read(new_socket2, buffer, 1024);
                strcpy(Acc.username, buffer);
                memset(buffer, 0, 1024);
                valread = read(new_socket2, buffer, 1024);
                strcpy(Acc.password, buffer);
                //append data
                listakun  = fopen ("akun.txt", "a");
                fwrite(&Acc,sizeof(Acc),1,listakun);
                fclose(listakun);
                //read data
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    printf("\nUsername: %12s\t\tPassword: %12s\n",Acc.username,Acc.password);
                    fflush(stdout);
                }
                fclose(listakun);
                goto main2;
            }
            else if(strcmp(buffer, "login") == 0 || strcmp(buffer, "Login") == 0 || strcmp(buffer, "LOGIN") == 0)
            {
                //read from client
                char user[12];
                char pass[50];
                memset(buffer, 0, 1024);
                valread = read(new_socket2, buffer, 1024);
                strcpy(user, buffer);
                valread = read(new_socket2, buffer, 1024);
                strcpy(pass, buffer);
                //read data
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    if(strcmp(user, Acc.username) == 0 && strcmp(pass, Acc.password) == 0)
                    {
                        memset(buffer, 0, 1024);
                        fclose(listakun);
                        printf("\nAuth Success\n");
                        fflush(stdout);
                        char *success = "Login Success";
                        send(new_socket2, success, strlen(success), 0);
                        goto find2;
                    }
                }
                fclose(listakun);
                printf("\nAuth Failed\n");
                fflush(stdout);
                char *failed = "Login Failed";
                send(new_socket2 , failed , strlen(failed) , 0 );
                goto main2;
            }
            else if(strcmp(buffer, "exit") == 0 || strcmp(buffer, "Exit") == 0 || strcmp(buffer, "EXIT") == 0)
            {
                return 0;
            }
            else
            {
                goto main2;
            }

        find2:;
            memset(buffer, 0, 1024);
            valread = read(new_socket2, buffer, 1024);
            if(strcmp(buffer, "logout") == 0 || strcmp(buffer, "Logout") == 0 || strcmp(buffer, "LOGOUT") == 0)
            {
                memset(buffer, 0, 1024);
                sleep(1);
                goto main2;
            }
            else if(strcmp(buffer, "find") == 0 || strcmp(buffer, "Find") == 0 || strcmp(buffer, "FIND") == 0)
            {
                memset(buffer, 0, 1024);
                Player_data.health1 = 0;
                Player_data.health2 = 0;
                Player_data.ready = Player_data.ready + 1;
                to2:;
                    if(Player_data.ready == 2)
                    {
                        char *start = "Game dimulai, silahkan tap tap secepat mungkin!!";
                        send(new_socket2 , start , strlen(start) , 0 );
                        memset(buffer, 0, 1024);
                        Player_data.health2 = Player_data.health2 + 100;
                        char health2[3];
                        sleep(1);
                        hit2:;
                            if (Player_data.health1 > 0 && Player_data.health2 > 0)
                            {
                                Player_data.health1 = Player_data.health1 - 10;
                                char *detected = "detected";
                                send(new_socket2 , detected , strlen(detected) , 0 );
                                miss2:;
                                memset(buffer, 0, 1024);
                                valread = read(new_socket2, buffer, 1024);
                                if (strcmp(buffer, "attack") == 0)
                                {
                                    memset(buffer, 0, 1024);
                                    sprintf(health2, "%d", Player_data.health2);
                                    send(new_socket2 , health2 , strlen(health2) , 0 );
                                    msleep(100);
                                    goto hit2;
                                }
                                else
                                {
                                    goto miss2;
                                }
                                
                                goto hit2;
                            }
                            else if(Player_data.health1 <= 0 || Player_data.health2 <= 0)
                            {
                                char *reward = "reward";
                                send(new_socket2 , reward , strlen(reward) , 0 );
                                memset(buffer, 0, 1024);
                                msleep(100);
                                if(Player_data.health1 <= 0 && Player_data.health2 > 0)
                                {
                                    char *rewardo = "Pertandingan Berakhir, Kamu Menang";
                                    send(new_socket2 , rewardo , strlen(rewardo) , 0 );
                                    Player_data.ready = Player_data.ready - 1;
                                    goto find2;
                                }
                                else if(Player_data.health2 <= 0 && Player_data.health1 > 0)
                                {
                                    char *rewardo = "Pertandingan Berakhir, Kamu Kalah";
                                    send(new_socket2 , rewardo , strlen(rewardo) , 0 );
                                    Player_data.ready = Player_data.ready - 1;
                                    goto find2;
                                }
                            }
                            else
                            {
                                goto hit2;
                            }
                    }
                    else
                    {
                        char *wait = "wait";
                        send(new_socket2 , wait , strlen(wait) , 0 );
                        memset(buffer, 0, 1024);
                        sleep(1);
                        goto to2;
                    }
            }
            else
            {
                goto find2;
            }
        pthread_exit(NULL);
	}
}

int main(int argc, char const *argv[])
{
    int j = 0;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    while(j<2)
    {
        pthread_create(&(tid[j]), NULL, &clientthread, NULL);
        j++;
        sleep(1);
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}
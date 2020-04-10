#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#define PORT 8080

int opponenthealth;
int myhealth;
int hit;

int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}

/* TERMIOS */
static struct termios old, current;

void initTermios()
{
  tcgetattr(0, &old);
  current = old;
  current.c_lflag &= ~ICANON;
  current.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &current);
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch()
{
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
   
    char choice[8];
    //Screen 1 (LOGIN, REGISTER, CHOICES)
    screen1:;
        char username[12];
        char password[50];
        printf("\e[2J\e[?25h\e[?1049l");
        printf("\nWELCOME TO TAPTAP GAME");
        printf("\n1. Login");
        printf("\n2. Register");
        printf("\n3. Exit");
        printf("\nChoice : ");
        scanf("%s", choice);
        if(strcmp(choice, "login") == 0 || strcmp(choice, "Login") == 0 || strcmp(choice, "LOGIN") == 0 )
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto loginscreen;
        }
        else if(strcmp(choice, "register") == 0 || strcmp(choice, "Register") == 0 || strcmp(choice, "REGISTER") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto registerscreen;
        }
        else if(strcmp(choice, "exit") == 0 || strcmp(choice, "Exit") == 0 || strcmp(choice, "EXIT") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            return 0;
        }
        else
        {
            printf("\e[2J\e[?25h\e[?1049l");
            printf("Your Choice Not Found\n");
            goto screen1;
        }
        //Login Sub-Screen
        loginscreen:;
            printf("\nInput Your Username & Password");
            printf("\nUsername: ");
            scanf("%s", username);
            send(sock, username, strlen(username), 0);
            printf("Password: ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);
            memset(buffer, 0, 1024);
            valread = read(sock, buffer, 1024);
            printf("\e[2J\e[?25h\e[?1049l");
            printf("%s\n", buffer);
            if(strcmp(buffer, "Login Success") == 0)
            {
                goto screen2;
            }
            else if(strcmp(buffer, "Login Failed") == 0)
            {
                goto screen1;
            }
            else
            {
                printf("Error");
                return 0;
            }
        //Register Sub-Screen
        registerscreen:;
            printf("\nCreate New Username & Password");
            printf("\nUsername (Max. 12 Character): ");
            scanf("%s", username);
            send(sock, username, strlen(username), 0);
            printf("Password (Max. 50 Character): ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            printf("Register Success\n");
            goto screen1;
    //Screen 2 (FIND MATCH & LOGOUT)
    screen2:;
        printf("\nHELLO DOCTOR, LET'S PLAY TOGETHER!");
        printf("\n1. Find Match");
        printf("\n2. Logout");
        printf("\nChoice : ");
        scanf("%s", choice);
        if(strcmp(choice, "logout") == 0 || strcmp(choice, "Logout") == 0 || strcmp(choice, "LOGOUT") == 0 )
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto screen1;
        }
        else if(strcmp(choice, "find") == 0 || strcmp(choice, "Find") == 0 || strcmp(choice, "FIND") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto match;
        }
        else
        {
            printf("\e[2J\e[?25h\e[?1049l");
            printf("Your Choice Not Found\n");
            send(sock, choice, strlen(choice), 0);
            goto screen2;
        }
        //Match Sub-Screen
        match:;
            wait:;
                memset(buffer, 0, 1024);
                valread = read(sock, buffer, 1024);
                if(strcmp(buffer, "wait") == 0)
                {
                    memset(buffer, 0, 1024);
                    printf("Waiting for player....\n");
                    sleep(1);
                    memset(buffer, 0, 1024);
                    goto wait;
                }
                else if (strcmp(buffer, "Game dimulai, silahkan tap tap secepat mungkin!!") == 0)
                {
                    printf("\e[2J\e[?25h\e[?1049l");
                    printf("%s\n", buffer);
                    char hit;
                    char detected[1024];
                    memset(buffer, 0, 1024);
                    valread = read(sock, buffer, 1024);
                    hit:;
                    sprintf(detected, "%s", buffer);
                    memset(buffer, 0, 1024);
                    if(strcmp(detected, "reward") == 0)
                    {
                        msleep(100);
                        goto reward;
                    }
                    else if(strcmp(detected, "detected") == 0)
                    {
                        subhit:;
                        hit = getch();
                        if(hit == ' ')
                        {  
                            char *attacking = "attack";
                            send(sock, attacking, strlen(attacking), 0);
                            memset(buffer, 0, 1024);
                            valread = read(sock, buffer, 1024);
                            printf("%s\t", buffer);
                            printf("hit!!");
                            printf("\n");
                            memset(buffer, 0, 1024);
                            valread = read(sock, buffer, 1024);
                            goto hit;
                        }
                        else
                        {
                            goto subhit;
                        }  
                    }
                    else
                    {
                        memset(buffer, 0, 1024);
                        valread = read(sock, buffer, 1024);
                        goto hit;
                    }  
                }
                else
                {
                    goto wait;
                }

            reward:;
                memset(buffer, 0, 1024);
                valread = read(sock, buffer, 1024);
                printf("\e[2J\e[?25h\e[?1049l");
                printf("\n%s\n", buffer);
                goto screen2;
    return 0;
}
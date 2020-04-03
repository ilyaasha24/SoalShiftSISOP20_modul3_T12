//Screen1:
////1. Login
////2. Register
////Choice: [input kata(choice)]
//-----------------
//Login Screen
////Username: [input(username)]
////Password: [input(password)]
////if[check username && password] berhasil (Login Success) atau gagal (Login Failed)
//-----------------
//Register Screen
////New Player
////Username: [input(username)]
////Password: [input(password)]
////if[post/get username && password] berhasil (Register Success)

//Screen2:
////1. Find Match
////2. Logout
////Choice: [input kata(choice)]
//-----------------
//Logout Screen
////go to Screen1
//-----------------
//Find Screen
////Print("Waiting for player ....") delay(5second)
////Get Opponent
//////Print("Game dimulai, silahkan tap tap secepat mungkin!!")
//////Health = 100
//////Tap with space button
//////if[tap detected], print("hit!!"), health -10
//////if[hit detected], print(current health)
//////if[myhealth == 0] print("Game berakhir, kamu kalah")
//////if[opponenthealth == 0] print("Game berakhir, kamu menang")
//////go to Screen2

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// #include <pthread.h>
#define PORT 8080


// pthread_t tid[1]; //inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread
// pid_t child;
int length=5; //inisialisasi jumlah untuk looping
int opponenthealth;
int myhealth;
int hit;

// void* match(void *arg)
// {
// 	unsigned long i = 0;
// 	pthread_t id = pthread_self();
// 	int iter;
// 	if(pthread_equal(id,tid[0])) //thread lawan
// 	{
//         computer:;
//         if(myhealth == 0 && opponenthealth > 0)
//         {
//             system ("/bin/stty cooked");
//             pthread_exit(NULL);
//             // printf("\nGame Berakhir, Kamu Kalah!\n\n");
//         } 
//         else if(opponenthealth == 0 && myhealth > 0)
//         {
//             system ("/bin/stty cooked");
//             pthread_exit(NULL);
//             // printf("\nGame Berakhir, Kamu Menang!\n\n");
//         }
//         else if(myhealth > 0 && opponenthealth > 0){
//             myhealth = myhealth - 10;
//             printf("%d/100 ", myhealth);
//             // system ("/bin/stty cooked");
//             fflush(stdout);
//             sleep(1);
//             goto computer;
//         }
// 	}
//     pthread_exit(NULL);
// }

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
        printf("WELCOME TO TAPTAP GAME");
        printf("\n1. Login");
        printf("\n2. Register");
        printf("\n3. Exit");
        printf("\nChoice : ");
        scanf("%s", choice);
        if(strcmp(choice, "login") == 0 || strcmp(choice, "Login") == 0 || strcmp(choice, "LOGIN") == 0 )
        {
            // system("clear");
            send(sock, choice, strlen(choice), 0);
            goto loginscreen;
        }
        else if(strcmp(choice, "register") == 0 || strcmp(choice, "Register") == 0 || strcmp(choice, "REGISTER") == 0)
        {
            // system("clear");
            send(sock, choice, strlen(choice), 0);
            goto registerscreen;
        }
        else if(strcmp(choice, "exit") == 0 || strcmp(choice, "Exit") == 0 || strcmp(choice, "EXIT") == 0)
        {
            // system("clear");
            send(sock, choice, strlen(choice), 0);
            return 0;
        }
        else
        {
            // system("clear");
            printf("Your Choice Not Found\n\n");
            goto screen1;
        }
        //Login Sub-Screen
        loginscreen:;
            printf("Input Your Username & Password");
            printf("\nUsername: ");
            scanf("%s", username);
            send(sock, username, strlen(username), 0);
            printf("Password: ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);
            memset(buffer, 0, 1024);
            valread = read(sock, buffer, 1024);
            // system("clear");
            printf("%s\n\n", buffer);
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
            printf("Create New Username & Password");
            printf("\nUsername (Max. 12 Character): ");
            scanf("%s", username);
            send(sock, username, strlen(username), 0);
            printf("Password (Max. 50 Character): ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);
            // system("clear");
            printf("Register Success\n\n");
            goto screen1;
    //Screen 2 (FIND MATCH & LOGOUT)
    screen2:;
        printf("HELLO DOCTOR, LET'S PLAY TOGETHER!");
        printf("\n1. Find Match");
        printf("\n2. Logout");
        printf("\nChoice : ");
        scanf("%s", choice);
        if(strcmp(choice, "logout") == 0 || strcmp(choice, "Logout") == 0 || strcmp(choice, "LOGOUT") == 0 )
        {
            // system("clear");
            goto screen1;
        }
        else if(strcmp(choice, "find") == 0 || strcmp(choice, "Find") == 0 || strcmp(choice, "FIND") == 0)
        {
            // system("clear");
            send(sock, choice, strlen(choice), 0);
            goto match;
        }
        else
        {
            // system("clear");
            printf("Your Choice Not Found\n\n");
            send(sock, choice, strlen(choice), 0);
            goto screen2;
        }
        //Match Sub-Screen
        match:;
            memset(buffer, 0, 1024);
            valread = read(sock, buffer, 1024);
            printf("%s\n\n", buffer);
            wait:;
                memset(buffer, 0, 1024);
                valread = read(sock, buffer, 1024);
                if(strcmp(buffer, "wait") == 0)
                {
                    printf("Waiting for player....\n");
                    sleep(3);
                    memset(buffer, 0, 1024);
                    goto wait;
                }
                else if (strcmp(buffer, "Game dimulai, silahkan tap tap secepat mungkin!!") == 0)
                {
                    printf("%s\n", buffer);
                    int hit;
                    char *attacking = "attack";
                    memset(buffer, 0, 1024);
                    valread = read(sock, buffer, 1024);
                    hit:;
                    if(strcmp(buffer, "reward") == 0)
                    {
                        goto reward;
                    }
                    else if(strcmp(buffer, "detected") == 0)
                    {
                        subhit:;
                        system("/bin/stty raw");
                        hit = getchar();
                        if(hit == ' ')
                        {  
                            send(sock, attacking, strlen(attacking), 0);
                            memset(buffer, 0, 1024);
                            valread = read(sock, buffer, 1024);
                            printf("%s\t", buffer);
                            printf("hit!!");
                            system ("/bin/stty cooked");
                            printf("\n");
                            memset(buffer, 0, 1024);
                            valread = read(sock, buffer, 1024);
                            goto hit;
                        }
                        else
                        {
                            system ("/bin/stty cooked");
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
                if(strcmp(buffer, "p1win") == 0)
                {
                    // system("clear");
                    goto screen2;
                    printf("Pertandingan Berakhir, Player 1 Menang\n\n");
                }
                else if (strcmp(buffer, "p2win") == 0)
                {
                    // system("clear");
                    goto screen2;
                    printf("Pertandingan Berakhir, Player 2 Menang\n\n");
                }
                else
                {
                    return 0;
                }
                
                

            
        //     memset(buffer, 0, 1024);
        //     valread = read(sock, buffer, 1024);
        //     printf("\n%s\n\n", buffer);
        //     char *start = "go";
        //     send(sock, start, strlen(start), 0);

        //     //Hit Sub-Sub-Screen
        //     hit:;
        //         int hit;
        //         char *attacking = "attack";
        //         if(strcmp(buffer, "detected") == 0)
        //         {
        //             goto reward;
        //         }

        //         system("/bin/stty raw");
        //         if(hit = getchar() == ' ')
        //         {
        //             send(sock, attacking, strlen(attacking), 0);
        //             printf("hit!!");
        //             system ("/bin/stty cooked");
        //             printf("\n");
        //             memset(buffer, 0, 1024);
        //             valread = read(sock, buffer, 1024);
        //             goto hit;
        //         }
        //             goto reward;
                
            
            // if(opponenthealth != 0 && myhealth !=0)
            // {
            //     system("/bin/stty raw");
            //     hit = getchar();
            //     if(hit == ' ')
            //     {
            //         opponenthealth = opponenthealth - 10;
            //         printf("hit!!");
            //         system ("/bin/stty cooked");
            //         printf("\n");
            //     }
            //     goto hit;
            // }
            // else
            // {
            //     goto reward;
            // }
        //Reward Sub-Sub Screen
        // reward:;
        //     // pthread_join(tid[0], NULL);
        //     if(opponenthealth == 0 && myhealth == 0)
        //     {
        //         printf("\nSeri Gan\n\n");
        //     }
        //     else if (myhealth == 0)
        //     {
        //         printf("\nGame Berakhir, Kamu Kalah!\n\n");
        //         goto screen2;
        //     }
        //     else if (opponenthealth == 0)
        //     {
        //         printf("\nGame Berakhir, Kamu Menang!\n\n");
        //         goto screen2;
        //     }
        //     printf("sampe sini berhasil gan");
    return 0;
}
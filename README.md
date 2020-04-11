# SoalShiftSISOP20_modul3_T12

Nama Anggota Kelompok T12 :

    MUHAMMAD ILYA ASHA SOGONDO - 05311840000010
    MOHAMMAD IFAIZUL HASAN - 05311840000029
    
SOAL 2

Qiqi adalah sahabat MamMam dan Kaka. Qiqi , Kaka dan MamMam sangat senang bermain “Rainbow six” bersama-sama , akan tetapi MamMam sangat Toxic ia selalu melakukan Team killing kepada Qiqi di setiap permainannya. Karena Qiqi orang yang baik hati, meskipun marah Qiqi selalu berkata “Aku nggk marah!!”. Kaka ingin meredam kemarahan Qiqi dengan membuatkannya sebuah game yaitu TapTap Game. akan tetapi Kaka tidak bisa membuatnya sendiri, ia butuh bantuan mu. Ayo!! Bantu Kaka menenangkan Qiqi. 
TapTap Game adalah game online berbasis text console. Terdapat 2 program yaitu tapserver.c dan tapplayer.c 
Syarat : 
- Menggunakan Socket, dan Thread 
Hint : 
- fwrite, fread 
Spesifikasi Game : 

CLIENT SIDE

Screen 1 :

1. Login

2. Register

Choices : {your input}

★ Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter anda diminta untuk menginputkan username dan password seperti berikut

Screen 1 :

1. Login 

2. Register 

Choices : login 

Username : { ex : qiqi } 

Password : { ex : aku nggak marah!! } 

★ Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal 
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek username dan password, maka dapat multi autentikasi dengan username dan password yang sama) 

★ Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan enter anda diminta untuk menginputkan username dan password sama halnya seperti login 

★ Pada register tidak ada pengecekan unique username, maka setelah register akan langsung menampilkan pesan “register success” dan dapat terjadi double account 

★ Setelah login berhasil maka anda berpindah ke screen 2 dimana menampilkan 2 fitur seperti berikut. 

Screen 2 : 

1. Find Match 

2. Logout 

Choices : {your input}

★ Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan kembali ke screen 1

★ Pada screen 2 anda dapat menginputkan “find”, setelah itu akan menampilkan pesan “Waiting for player ...” print terus sampai menemukan lawan 

★ Jika menemukan lawan maka akan menampilkan pesan “Game dimulai silahkan tap tap secepat mungkin !!” 

★ Pada saat game dimulai diberikan variable health = 100,dan anda dapat men-tap (menekan space pada keyboard tanpa harus menekan enter) 

★ Pada saat anda men-tap maka akan menampilkan pesan “hit !!”, dan pada lawan healthnya akan berkurang sebanyak 10 kemudian pada lawan menampilkan pesan status healthnya sekarang. (conclusion : anda tidak bisa melihat status health lawan) 

★ Jika health anda <= 0 maka akan menampilkan pesan “Game berakhir kamu kalah”, apabila lawan anda healthnya <= 0 maka akan menampilkan pesan ”Game berakhir kamu menang” 

★ Setelah menang atau kalah maka akan kembali ke screen 2 

SERVER SIDE 

★ Pada saat program pertama kali dijalankan maka program akan membuat file akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan username dan password 

★ Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika gagal “Auth Failed” 

★ Pada saat user sukses meregister maka akan menampilkan List account yang terdaftar (username dan password harus terlihat) 

PENYELESAIAN:

SERVER
```
//LIBRARY YANG DIPAKAI
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <asm-generic/socket.h>
#define PORT 8080

//DEKLARASI VARIABEL UNTUK KONEKSI SERVER-CLIENT
int server_fd, new_socket, new_socket2, valread;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[1024] = {0};

//VARIABEL UNTUK MENJALANKAN SUATU FILE (BUKA, TULIS, BACA, DKK)
FILE *listakun;

//VARIBEL THREAD
pthread_t tid[2];

//PEMBUATAN STRUCT AKUN UNTUK REGISTRASI DAN LOGIN
struct Akun Acc;

//PEMBUATAN STRUCT PLAYER UNTUK MELAKUKAN PERTEMPURAN
struct Player Player_data;

//STRUCT AKUN BERISI USERNAME DAN PASSWORD
struct Akun
{
    char username[12];
    char password[50];
};

//STRUCT PLAYER BERISI READY (), HEALTH1 (PLAYER1), DAN HEALTH2 (PLAYER2)
struct Player
{
    int ready;
    int health1;
    int health2;
};

//MELAKUKAN DELAY DALAM WAKTU MILISECOND
int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}

//THREAD CLIENT (MAX 2 ORANG)
void* clientthread(void *arg)
{
	pthread_t id = pthread_self();

    //THREAD PERTAMA (PLAYER1)
	if(pthread_equal(id,tid[0])) //thread 1
	{
        //MENGECEK APAKAH CLIENT BERHASIL TERKONEKSI
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        //MAIN BERISI MENU UTAMA
        main1:;
            memset(buffer, 0, 1024);
            valread = read(new_socket, buffer, 1024);

            //APABILA MEMILIH REGISTER
            if(strcmp(buffer, "register") == 0 || strcmp(buffer, "Register") == 0 || strcmp(buffer, "REGISTER") == 0)
            {
                //MEMBACA USERNAME DAN PASSWORD
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(Acc.username, buffer);
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(Acc.password, buffer);

                //MEMASUKKAN USERNAME DAN PASSWORD KEDALAM FILE akun.txt
                listakun  = fopen ("akun.txt", "a");
                fwrite(&Acc,sizeof(Acc),1,listakun);
                fclose(listakun);

                //MENAMPILKAN SELURUH ISI akun.txt DI TERMINAL
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    printf("\nUsername: %12s\t\tPassword: %12s\n",Acc.username,Acc.password);
                    fflush(stdout);
                }
                fclose(listakun);
                goto main1;
            }

            //APABILA MEMILIH LOGIN
            else if(strcmp(buffer, "login") == 0 || strcmp(buffer, "Login") == 0 || strcmp(buffer, "LOGIN") == 0)
            {

                //MEMBACA USERNAME DAN PASSWORD
                char user[12];
                char pass[50];
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(user, buffer);
                memset(buffer, 0, 1024);
                valread = read(new_socket, buffer, 1024);
                strcpy(pass, buffer);
                memset(buffer, 0, 1024);

                //MENCOCOKKANNYA PADA ISI akun.txt
                listakun = fopen("akun.txt","r");
                while(fread(&Acc,sizeof(Acc),1,listakun)>0)
                {
                    //JIKA SUKSES MAKA AKAN PERGI MENUJU FIND (MENCARI LAWAN)
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

                //JIKA GAGAL MAKA AKAN KEMBALI KE MAIN (MENU UTAMA)
                fclose(listakun);
                printf("\nAuth Failed\n");
                fflush(stdout);
                char *failed = "Login Failed";
                send(new_socket , failed , strlen(failed) , 0 );
                goto main1;
            }

            //APABILA MEMILIH EXIT
            else if(strcmp(buffer, "exit") == 0 || strcmp(buffer, "Exit") == 0 || strcmp(buffer, "EXIT") == 0)
            {
                return 0;
            }

            //JIKA TERDETEKSI SELAIN ITU, MAKA AKAN KEMBALI KE MENU UTAMA
            else
            {
                goto main1;
            }

        //MENU UNTUK MENCARI LAWAN    
        find1:;
            memset(buffer, 0, 1024);
            valread = read(new_socket, buffer, 1024);

            //APABILA MEMILIH LOGOUT AKAN KEMBALI KE MAIN1
            if(strcmp(buffer, "logout") == 0 || strcmp(buffer, "Logout") == 0 || strcmp(buffer, "LOGOUT") == 0)
            {
                memset(buffer, 0, 1024);
                sleep(1);
                goto main1;
            }

            //APABILA MEMILIH FIND, AKAN MENCARI LAWAN
            else if(strcmp(buffer, "find") == 0 || strcmp(buffer, "Find") == 0 || strcmp(buffer, "FIND") == 0)
            {
                memset(buffer, 0, 1024);

                //AWAL MENCARI AKAN MENAMBAH PLAYER YANG READY
                Player_data.health1 = 0;
                Player_data.health2 = 0;
                Player_data.ready = Player_data.ready + 1;
                to1:;

                    //APABILA PLAYER YANG READY SUDAH 2 ORANG
                    if(Player_data.ready == 2)
                    {
                        //GAME DAPAT DIMULAI
                        char *start = "Game dimulai, silahkan tap tap secepat mungkin!!";
                        send(new_socket , start , strlen(start) , 0 );
                        memset(buffer, 0, 1024);

                        //PLAYER AKAN MENDAPATKAN DARAH 110 (10 POIN DIGUNAKAN UNTUK MENDETEKSI KESIAPAN CLIENT)
                        Player_data.health1 = Player_data.health1 + 110;
                        char health1[3];
                        sleep(1);
                        hit1:;

                            //APABILA BELUM ADA YANG BERNILAI 0, MELAKUKAN PENYERANGAN TERUS
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
                                    //JIKA TIDAK ADA MASUKAN YANG VALID
                                    goto miss1;
                                }
                                
                                goto hit1;
                            }

                            //SEMISAL SALAH SATU HEALTH ADA YANG BERNILAI 0
                            else if(Player_data.health1 <= 0 || Player_data.health2 <= 0)
                            {
                                char *reward = "reward";
                                send(new_socket , reward , strlen(reward) , 0 );
                                memset(buffer, 0, 1024);
                                msleep(100);

                                //APABILA HEALTH 1 YANG BERNILAI 0, MAKA KALAH
                                if(Player_data.health1 <= 0 && Player_data.health2 > 0)
                                {
                                    char *rewardo = "Pertandingan Berakhir, Kamu Kalah";
                                    send(new_socket , rewardo , strlen(rewardo) , 0 );
                                    Player_data.ready = Player_data.ready - 1;
                                    goto find1;
                                }

                                //APABILA HEALTH 2 YANG BERNILAI 0, MAKA MENANG
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

                    //KETIKA MENCARI PLAYER LAIN
                    else
                    {
                        char *wait = "wait";
                        send(new_socket , wait , strlen(wait) , 0 );
                        memset(buffer, 0, 1024);
                        sleep(1);
                        goto to1;
                    }
            }
            //APABILA TIDAK ADA MASUKAN YANG VALID
            else
            {
                goto find1;
            }
            
        pthread_exit(NULL);
	}

    //THREAD2 HAMPIR SAMA SEPERTI THREAD1, HANYA DIBALIK SAJA
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
    //VARIABEL J UNTUK THREAD YANG DIBUAT
    int j = 0;
    
    //MENDETEKSI APAKAH KONEKSI SERVER-CLIENT SUDAH SIAP
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
    
    //PEMBUATAN THREAD
    while(j<2)
    {
        pthread_create(&(tid[j]), NULL, &clientthread, NULL);
        j++;
        sleep(1);
    }

    //THREAD SALING MENUNGGU
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}

```

CLIENT

```
//LIBRARY YANG DIPAKAI
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

//DELAY DALAM MILISECOND
int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}

//TERMIOS UNTUK INPUT TANPA ENTER
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

//MENDAPATKAN INPUT
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
    //MENDETEKSI KESIAPAN CLIENT-SERVER
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

        //APABILA MEMILIH LOGIN MAKA AKAN MENUJU LOGINSCREEN
        if(strcmp(choice, "login") == 0 || strcmp(choice, "Login") == 0 || strcmp(choice, "LOGIN") == 0 )
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto loginscreen;
        }

        //APABILA MEMILIH REGISTER MAKA AKAN MENUJU REGISTERSCREEN
        else if(strcmp(choice, "register") == 0 || strcmp(choice, "Register") == 0 || strcmp(choice, "REGISTER") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto registerscreen;
        }

        //APABILA MEMILIH EXIT AKAN MENUTUP PROGRAM
        else if(strcmp(choice, "exit") == 0 || strcmp(choice, "Exit") == 0 || strcmp(choice, "EXIT") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            return 0;
        }

        //AKAN KEMBALI KE SCREEN1 JIKA PILIHAN TIDAK VALID
        else
        {
            printf("\e[2J\e[?25h\e[?1049l");
            printf("Your Choice Not Found\n");
            goto screen1;
        }

        //Login Sub-Screen
        loginscreen:;
            //MENGINPUTKAN USERNAME DAN PASSWORD
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

            //JIKA SUKSES MAKA AKAN PERGI KE SCREEN2
            if(strcmp(buffer, "Login Success") == 0)
            {
                goto screen2;
            }

            //JIKA GAGAL MAKA AKAN KEMBALI KE SCREEN1
            else if(strcmp(buffer, "Login Failed") == 0)
            {
                goto screen1;
            }

            //JIKA TIDAK MAKA AKAN MENUTUP APLIKASI
            else
            {
                printf("Error");
                return 0;
            }

        //Register Sub-Screen
        registerscreen:;
            //MENGINPUTKAN USERNAME DAN PASSWORD
            printf("\nCreate New Username & Password");
            printf("\nUsername (Max. 12 Character): ");
            scanf("%s", username);
            send(sock, username, strlen(username), 0);
            printf("Password (Max. 50 Character): ");
            scanf("%s", password);
            send(sock, password, strlen(password), 0);
            printf("\e[2J\e[?25h\e[?1049l");

            //OTOMATIS SUKSES DAN KEMBALI KE SCREEN1
            printf("Register Success\n");
            goto screen1;

    //Screen 2 (FIND MATCH & LOGOUT)
    screen2:;
        printf("\nHELLO DOCTOR, LET'S PLAY TOGETHER!");
        printf("\n1. Find Match");
        printf("\n2. Logout");
        printf("\nChoice : ");
        scanf("%s", choice);

        //JIKA MEMILIH LOGOUT MAKA AKAN KEMBALI KE SCREEN1
        if(strcmp(choice, "logout") == 0 || strcmp(choice, "Logout") == 0 || strcmp(choice, "LOGOUT") == 0 )
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto screen1;
        }

        //JIKA MEMILIH FIND MAKA AKAN MENUJU MATCH
        else if(strcmp(choice, "find") == 0 || strcmp(choice, "Find") == 0 || strcmp(choice, "FIND") == 0)
        {
            send(sock, choice, strlen(choice), 0);
            printf("\e[2J\e[?25h\e[?1049l");
            goto match;
        }

        //JIKA SELAIN ITU MAKA AKAN DIKEMBALIKAN KE SCREEN2
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

                //JIKA BUFFER ADALAH WAIT MAKA AKAN MENUNGGU PLAYER DAN LOOP
                if(strcmp(buffer, "wait") == 0)
                {
                    memset(buffer, 0, 1024);
                    printf("Waiting for player....\n");
                    sleep(1);
                    memset(buffer, 0, 1024);
                    goto wait;
                }

                //JIKA SUDAH ADA PLAYER MAKA AKAN BERPINDAH KESINI DAN MULAI PERTEMPURAN
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

                    //REWARD AKAN TERDETEKSI APABILA SUDAH ADA YANG MENANG
                    if(strcmp(detected, "reward") == 0)
                    {
                        msleep(100);
                        goto reward;
                    }

                    //JIKA BELUM ADA YANG MENANG GAME AKAN TERUS BERLANJUT
                    else if(strcmp(detected, "detected") == 0)
                    {
                        subhit:;
                        //MASUK KE SESI PENYERANGAN
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

                        //JIKA INPUT TIDAK SEPERTI YANG DIHARAPKAN
                        else
                        {
                            goto subhit;
                        }  
                    }

                    //JIKA INPUT TIDAK SEPERTI YANG DIHARAPKAN
                    else
                    {
                        memset(buffer, 0, 1024);
                        valread = read(sock, buffer, 1024);
                        goto hit;
                    }  
                }

                //JIKA INPUT TIDAK SEPERTI YANG DIHARAPKAN
                else
                {
                    goto wait;
                }
            
            //JIKA SUDAH ADA YANG MENANG MAKA AKAN KEMBALI KE SCREEN2
            reward:;
                memset(buffer, 0, 1024);
                valread = read(sock, buffer, 1024);
                printf("\e[2J\e[?25h\e[?1049l");
                printf("\n%s\n", buffer);
                goto screen2;
    return 0;
}
```


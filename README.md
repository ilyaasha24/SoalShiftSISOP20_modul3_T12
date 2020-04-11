# SoalShiftSISOP20_modul3_T12

Nama Anggota Kelompok T12 :

    MUHAMMAD ILYA ASHA SOGONDO - 05311840000010
    MOHAMMAD IFAIZUL HASAN - 05311840000029


SOAL 1

Poke*ZONE adalah sebuah game berbasis text terminal mirip dengan Pokemon GO.
Ketentuan permainan sebagai berikut:
a. Menggunakan IPC-shared memory, thread, fork-exec. b. Kalian bebas berkreasi dengan game ini asal tidak konflik dengan
requirements yang ada. (Contoh: memberi nama trainer, memberi notifikasi kalau barang di shop sudah penuh, dan lain-lain). c. Terdapat 2 code yaitu soal2_traizone.c dan soal2_pokezone.c. d. soal2_traizone.c mengandung fitur:
i. Normal Mode (3 Menu)
1. Cari Pokemon
a. Jika diaktifkan maka setiap 10 detik akan memiliki
60% chance untuk menemui pokemon bertipe normal, rare, legendary dengan encounter rate sesuai pada tabel di bawah (Gunakan Thread). b. Cari pokemon hanya mengatur dia menemukan
pokemon atau tidak. Untuk tipe pokemon dan pokemon tersebut shiny atau tidak diatur oleh soal2_pokezone.c. c. Opsi “Cari Pokemon” akan berubah jadi “Berhenti Mencari” ketika state mencari pokemon aktif. d. State mencari pokemon hanya bisa dihentikan ketika
pokemon sudah ditemukan atau trainer memilih untuk berhenti pada menu. e. Jika menemui pokemon maka akan masuk ke Capture
Mode. f. Untuk mempermudah boleh menambah menu go to capture mode untuk berpindah dari mode normal ke mode capture setelah menemukan pokemon dari thread Cari Pokemon. 2. Pokedex
a. Melihat list pokemon beserta Affection Point (AP) yang
dimiliki. b. Maksimal 7 pokemon yang dimiliki. c. Jika menangkap lebih dari 7 maka pokemon yang baru
saja ditangkap akan langsung dilepas dan mendapatkan pokedollar sesuai dengan tabel dibawah. d. Setiap pokemon yang dimiliki, mempunyai Affection
Point (AP) dengan initial value 100 dan akan terus berkurang sebanyak -10 AP/10 detik dimulai dari waktu ditangkap (Gunakan Thread). e. Jika AP bernilai 0, maka pokemon tersebut memiliki
90% chance untuk lepas tanpa memberikan pokedollar ke trainer atau 10% chance untuk reset AP menjadi 50 AP. f. AP tidak akan berkurang jika dalam Capture Mode.
g. Di Pokedex trainer juga bisa melepas pokemon yang
ditangkap dan mendapat pokedollar sesuai dengan tabel dibawah. h. Bisa memberi berry ke semua pokemon yang dimiliki
untuk meningkatkan AP sebesar +10 (1 berry untuk semua pokemon yang ada di pokedex). 3. Shop a. Membeli item dari soal2_pokezone.
b. Maksimal masing-masing item yang dapat dibeli dan
dipunya oleh trainer adalah 99. ii. Capture Mode (3 Menu)
1. Tangkap → Menangkap menggunakan pokeball. Berhasil
ditangkap maupun tidak, pokeball di inventory -1 setiap digunakan. 2. Item → Menggunakan item sesuai dengan tabel item dibawah
(hanya lullaby powder). 3. Keluar → Keluar dari Capture Mode menuju Normal Mode.
● Pokemon tersebut memiliki peluang untuk lari dari trainer sesuai dengan persentase escape rate pada tabel dibawah (gunakan thread). e. soal2_pokezone.c mengandung fitur:
i. Shutdown game → Mematikan program soal2_pokezone dan
soal2_traizone (Gunakan fork-exec). ii. Jual Item (Gunakan Thread)
1. Stock awal semua item adalah 100. 2. Masing-masing item akan bertambah +10 item/10 detik. 3. Maximum item yang dalam shop adalah 200. 4. List item ada pada tabel dibawah.
No Nama Item Effect Harga
(Pokedollar)
Normal Mode
1 Lullaby
Powder
Durasi (Detik)
Capture Mode
● Meningkatkan chance untuk
60 10 Yes No menangkap sebesar 20% (misal normal pokemon jadi 90% capture ratenya).
● Menurunkan escape rate jadi 0% sehingga Pokemon tidak bisa lari.
2 Pokeball Menangkap pokemon. 5 - Yes No
3 Berry Meningkatkan AP semua
pokemon yang ada di pokedex sebesar +10.
15 - No Yes
5. Gunakan thread untuk implementasi lullaby powder dibuatkan
masing-masing 1 thread.
iii. Menyediakan Random Pokemon (Gunakan Thread)
1. Setiap tipe pokemon memiliki peluang 1/8000 untuk jadi shiny
pokemon. (Random dulu antara normal, rare, legendary sesuai rate mereka, baru setelah itu di random dengan peluang 1/8000 untuk tahu dia shiny atau tidak). 2. Shiny Pokemon meningkatkan escape rate sebesar +5%
(misal: tipe normal jadi 10%), capture rate berkurang menjadi -20% (misal: tipe rare jadi 30%), dan pokedollar dari melepas +5000 (misal: tipe legendary jadi 5200 pokedollar). 3. Setiap 1 detik thread ini akan mengkalkulasi random ulang lagi
untuk nantinya diberikan ke soal2_traizone.

No Pokemon Type Encounter
Rate
Escape Rate
Capture Rate
Capture Rate
Capture Rate
Pokedollar dari melepas
Pokedollar dari melepas
Pokedollar dari melepas
Pokedollar dari melepas
List Nama Pokemon (random)
List Nama Pokemon (random)
List Nama Pokemon (random)
List Nama Pokemon (random)
List Nama Pokemon (random)
1 Normal 80% 5% setiap
20 detik
70% 80 ● Bulbasaur
● Charmander
● Squirtle
● Rattata
● Caterpie
2 Rare 15% 10% setiap
50% 100 ● Pikachu
20 detik
● Eevee
● Jigglypuff
● Snorlax
● Dragonite
3 Legendary 5% 20% setiap
30% 200 ● Mew
20 detik
● Mewtwo
● Moltres
● Zapdos
● Articuno


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
SOAL 3

Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
 File kategori terletak di /home/izone/kategori $ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
Hasilnya adalah sebagai berikut /home/izone |-jpg |--file1.jpg |-c |--file2.c |-zip |--file3.zi
● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual, melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi, maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (`*`) seperti di bawah;
$ ./kategori \*
● Artinya mengkategori seluruh file yang ada di working directory ketika menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
$ ./kategori -d /path/to/directory/
● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau menggunakan (`*`) terdapat folder yang berisi file, maka file dalam folder tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin belum ada di soal3.zip.

LIBRARY & STRUCT
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
struct args {
    char* file;
    char* path;
};
```
# FUNCTION  
A. PASSING ARGUMEN
```
void *mv(void *pass) {
  char *file = ((struct args*)pass)->file, *path = ((struct args*)pass)->path;
  ```
  B. CONVERTING EXTENSION TO LOWERCASE
  ```
  char *ext = strrchr(file, '.');
  if (ext) {
    char n[10];
    strcpy(n, ext);
    for (size_t i = 0; i < strlen(n); i++) n[i] = tolower(n[i]);
    ext = n;
  }
```
C. SPECIAL CASE: UNKNOWN EXTENSION
```
  if (!ext || ext == file || !strcmp(ext + 1, "*")) ext = ".Unknown";
```
D. FOLDER MAKING, PACKING, & MOVING FILE
```
  mkdir(ext + 1, 0755);
  size_t len = strlen(ext + 1) + strlen(file) + sizeof("/"), len2 = strlen(path) + strlen(file) + sizeof("/");
  char *tmp = malloc(len), *tmp2 = malloc(len2);
  sprintf(tmp, "%s/%s", ext + 1, file);
  sprintf(tmp2, "%s/%s", path, file);
  rename(tmp2, tmp);
  free(tmp);
}
```
# MAIN  
A. PASSING ARGUMEN & CHECKING ERRORS
```
int main(int argc, char *argv[]) {
  if (argc < 2) perror("Error: Missing Arguments");
```
B. OPTION `*` & `-d`  
- B1. CHECKING ERRORS
```
  if (!strcmp(argv[1], "*") || !strcmp(argv[1], "-d")) {
    DIR *d;
    struct dirent *dir;
    if (!strcmp(argv[1], "*")) argv[2] = ".";
  ```
- B2. OPEN DIRECTORY
  ```
    d = opendir(argv[2]);
    if (d) {
      int i = 0;
    ```
- B3. CALLING FUNCTION WITH THREADING
    ```
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG && strcmp(dir->d_name, "soal3")) {
          struct args *pass = (struct args *)malloc(sizeof(struct args));
          pass->file = dir->d_name;
          pass->path = argv[2];
          pthread_t tid[i];
          pthread_create(&tid[i++], NULL, &mv, (void *)pass);
        };
      }
    ```
- B4. JOINING THREADS & CLOSING DIRECTORY
    ```
      for (i; i > 0; i--) pthread_join(tid[i], NULL);
    closedir(d);
    }
```

C. OPTION `-f`
- C1. CHECKING ERROR
```
  } else if (!strcmp(argv[1], "-f")) {
    if (argc < 3) perror("Error: Missing Arguments");
  ```
- C2. CALLING FUNCTION WITH THREADING
  ```
    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      struct args *pass = (struct args *)malloc(sizeof(struct args));
      pass->file = argv[2];
      pass->path = ".";
      pthread_create(&tid[i-2], NULL, &mv, (void *)pass);
    }
  ```
-C3. JOINING THREADS
  ```
    for (int i = 2; i < argc; i++) pthread_join(tid[i-2], NULL);
  ```


ELSE & EXIT
  ```
  } else {
    perror("Error: Undefined Arguments");
  }
  return 0;
}

```
SOAL 4

Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
- Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). 2. Tampilkan matriks hasil perkalian tadi ke layar.
- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya adalah:
1. Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory) 2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks.
Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...], maka:
1 2 6 24 120 720 ... ... ... (Catatan! : Harus menggunakan Thread dalam penghitungan faktorial)
- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan teka-teki berikut! 1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat. (Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.
Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut. Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece does exist".

4A.
- 1. LIBRARY
```
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
```
- 2. INITIALIZATION
```
int mat1[4][2] = {{2,2},{2,2},{2,2},{2,2}};
int mat2[2][5] = {{5,5,5,5,5},{5,5,5,5,5}};
int (*mat3)[5];
int row = 0, i, j, k;
```
- 3. FUNCTION
```
void* mult(void* arg) {
  i = row++;
  for (j = 0; j < 5; j++) for (k = 0; k < 2; k++) mat3[i][j] += mat1[i][k] * mat2[k][j];
}
```
- 4. MAIN
```
int main() {
```
- 4.1. SHARED MEMORY ALLOCATION
```
	key_t key = 3737;
  int shmid = shmget(key, sizeof(int[4][5]), IPC_CREAT | 0666);
  mat3 = shmat(shmid, 0, 0);
  ```
- 4.2. THREADS ALLOCATION
  ```
  pthread_t tid[4];
  for (i = 0; i < 4; i++) pthread_create(&(tid[i]), NULL, &mult, NULL);
  for (i = 0; i < 4; i++) pthread_join(tid[i], NULL);
  ```
- 4.3. DISPLAY RESULT
  ```
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      printf("%2d ", mat3[i][j]);
		}
		printf("\n");
  }
  ```
- OPTIONAL
  ```
  // shmdt(mat3);
  // shmctl(shmid, IPC_RMID, NULL);
}
```

4B.
- 1. LIBRARY
```
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
```
- 2. INITIALIZATION
```
int (*mat3)[5];
int row = 0, n, i, j, k;
```
- 3. FUNCTION
```
void* func(void* arg) {
  i = row++;
  for (size_t j = 0; j < 5; j++) {
    n = 0;
    for (k = 1; k < mat3[i][j]; k++) n += k;
    mat3[i][j] += n;
  }
}
```
- 4. MAIN
```
int main() {
```
- 4.1. SHARED MEMORY ALLOCATION
```
	key_t key = 3737;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  mat3 = shmat(shmid, 0, 0);
  ```
- 4.2. THREADS ALLOCATION
  ```
  pthread_t tid[4];
  for (i = 0; i < 4; i++) pthread_create(&(tid[i]), NULL, &func, NULL);
  for (i = 0; i < 4; i++) pthread_join(tid[i], NULL);
  ```
- 4.3. DISPLAY RESULT
  ```
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      printf("%2d ", mat3[i][j]);
		}
		printf("\n");
  }
  ```
- 4.4. CLOSING SHARED MEMORY
  ```
  shmdt(mat3);
  shmctl(shmid, IPC_RMID, NULL);
}

4C.
- 1. LIBRARY
```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef int pipa[2];
```
- 2. INITIALIZATION
```
char *cmd0[] = {"ls", 0}, *cmd1[] = {"wc", "-l", 0};
static char **cmds[] = {cmd0, cmd1};
static int ncmds = sizeof(cmds) / sizeof(cmds[0]);
static void exec_nth_command(int ncmds, char ***cmds);
```
- 3. FUNCTION FOR PASSING OUTPUTS
```
static void exec_pipe_command(int ncmds, char ***cmds, pipa output) {
    dup2(output[1], 1); // 1 = stdout
    close(output[0]);
    close(output[1]);
    exec_nth_command(ncmds, cmds);
}
```
- 4. FUNCTION FOR PASSING INPUTS & EXECUTING COMMANDS
```
static void exec_nth_command(int ncmds, char ***cmds) {
    if (ncmds > 1) {
        pid_t pid;
        pipa input;
        if (pipe(input) != 0) exit(1);
        if ((pid = fork()) < 0) exit(1);
        if (pid == 0) exec_pipe_command(ncmds - 1, cmds, input);
        dup2(input[0], 0); // 0 = stdin
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds - 1][0], cmds[ncmds - 1]);
}
```
- 5. MAIN
```
int main(int argc, char **argv) {
    exec_nth_command(ncmds, cmds);
    return(0);
}
```

# END

> To iterate is human, to recurse divine.

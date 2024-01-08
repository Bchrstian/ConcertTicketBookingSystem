#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONCERTS 10
#define MAX_NAME_LEN 50

// Structure to hold the details of a concert
struct concert_details{
    char name[MAX_NAME_LEN];
    int num_vip_seats;
    int num_normal_seats;
    int num_vip_tickets_sold;
    int num_normal_tickets_sold;
    char location[MAX_NAME_LEN];
    int *vip_seat_status;
    int *normal_seat_status;
}new_concert;
struct ticket_details{
    char client_name[MAX_NAME_LEN];
    char concert_name[MAX_NAME_LEN];
    int kind_of_ticket;
    int seat_number;
    char seat_type[7];
}new_ticket;

// Function prototypes
void admin_login();
void create_concert();
void view_concerts();
void admin_view_concerts();
void update_concert();
void delete_concert();
void buy_ticket();
void general_login();
void view_tickets_details();
void display_menu();


// Global variables
struct concert_details concerts[MAX_CONCERTS];
struct ticket_details tickets[10000];
int num_concerts = 0;
int num_tickets =0;
char inp[100];

int main() {
    printf("\n\n\n\n\n");
    printf("%s\n","Welcome To Concert Booking System");
    printf("%s\n\n","=================================");
    printf("\n");
    general_login();
}

void general_login(){
    printf("%50s\n","Choose from the Option below:");
    printf("%50s\n\n\n","-----------------------------");
    printf("%30s\n\n","1. Login as client");
    printf("%29s\n\n","2. Login as Admin");
    printf("%22s\n","3. To Exit");
    printf("\n");
    printf("\n");
    printf("%40s","Enter your choice:  ");
    int login_choice;
    scanf("%d",&login_choice);

    switch(login_choice){
        case 1:
            system("cls");
            display_menu();
                break;
        case 2:
            system("cls");
            admin_login();
            break;
        case 3:
            printf("\n\n\n");
            printf("%55s","Thank you for using Concert book system\n\n\n\n\n");
            exit(1);
        default:
            system("cls");
            printf("\n\n");
            printf("%30s\n\n\n","Invalid choice");
            printf("\n\n");
            general_login();
    }
}

void display_menu() {
    int choice;
    printf("\n\n%40s\n","Main Menu");
    printf("%41s","---------\n\n");
    printf("%30s","1. Buy a ticket\n\n");
    printf("%40s","2. view concerts' Details\n\n");
    printf("%24s","3. Logout\n\n");
    printf("%23s","4. Exit\n\n\n");
    printf("%25s","Enter an option: ");
    scanf("%d",&choice);

    switch (choice) {
            case 1:
                buy_ticket();
                break;
            case 2:
                view_concerts();
                break;
            case 3:
                system("cls");
                printf("\n\n");
                printf("%30s\n\n\n","Logout Successfull!!!!!");
                printf("\n\n");
                general_login();
                break;
            case 4:
                printf("\n\n\n");
                printf("%55s","Thank you for using Concert book system\n\n\n\n\n");
                exit(1);
            default:
                system("cls");
                printf("Invalid choice. Please try again.\n");
                display_menu();
       }
}

void buy_ticket() {
    FILE * concert_file = fopen("Concerts.txt","r");
    if (concert_file == NULL) {
        system("cls");
        printf("\nNo concerts found.\n");
        display_menu();
    }
    num_concerts=0;

    printf("\n\n\n%40s","List of concerts\n");
    printf("%40s","----------------\n");
    printf("%10s %30s %30s %30s\n","Name","Location","VIP Remain", "Normal seats Remain");
    printf("%10s %30s %30s %30s\n","----","--------","----------", "-------------------");
    while(!feof(concert_file)){
            fscanf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,&new_concert.num_vip_seats,&new_concert.num_vip_tickets_sold,&new_concert.num_normal_seats,&new_concert.num_normal_tickets_sold );
            num_concerts++;
            new_concert.vip_seat_status = (int*) malloc(new_concert.num_vip_seats * sizeof(int));
            memset(new_concert.vip_seat_status, 0, new_concert.num_vip_seats * sizeof(int));
            new_concert.normal_seat_status = (int*) malloc(new_concert.num_normal_seats * sizeof(int));
            memset(new_concert.normal_seat_status, 0, new_concert.num_normal_seats * sizeof(int));

            for(int i=num_concerts-1;i<num_concerts;i++){
                concerts[i]=new_concert;
                printf("%10s %30s %30d %20d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats-concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats-concerts[i].num_normal_tickets_sold );
                break;
            }
    }
    fclose(concert_file);



    FILE *tickets_file=fopen("Tickets records.txt","a+");
    concert_file=fopen("Concerts.txt","w");
    printf("\nBuy ticket\n");

    char name[MAX_NAME_LEN];
    printf("Enter your name: ");
    scanf("%s",new_ticket.client_name);


    printf("Enter the name of the concert you want to attend: ");

    scanf("%s", new_ticket.concert_name);

    int index = -1;
    for (int i = 0; i < num_concerts; i++) {
        if (strcmp(new_ticket.concert_name, concerts[i].name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Concert not found. Please try again.\n");
        display_menu();
    }

    if (concerts[index].num_vip_tickets_sold == concerts[index].num_vip_seats && concerts[index].num_normal_tickets_sold == concerts[index].num_normal_seats) {
        printf("Sorry, the concert is sold out.\n");
        for(int i=0;i<num_concerts;i++){
                fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
        }
        display_menu();

    }

    printf("\nkind of ticket");
    printf("\n1. For VIP");
    printf("\n2. For Normal");
    printf("\nEnter You choice: ");
    scanf("%d",&new_ticket.kind_of_ticket);

    int seat_number = -1;
    switch(new_ticket.kind_of_ticket){
        case 1:
            strcpy(new_ticket.seat_type,"VIP");
            if(concerts[index].num_vip_seats - concerts[index].num_vip_tickets_sold == 0){
                    system("cls");
                    printf("%s VIP concert tickets have sold out\n",new_ticket.concert_name);
                    for(int i=0;i<num_concerts;i++){
                        fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
                    }
                    display_menu();
            }

            for (int i = 0; i < concerts[index].num_vip_seats; i++) {

                if (concerts[index].vip_seat_status[i] == 0) {
                    new_ticket.seat_number = concerts[index].num_vip_tickets_sold+1;
                    seat_number=new_ticket.seat_number;
                    concerts[index].vip_seat_status[i] = 1;
                    break;
                }
            }
            if (seat_number == -1) {
                printf("seat was reserved.Seat not available.\n");
                display_menu();

            }
            concerts[index].num_vip_tickets_sold++;
            break;
        case 2:
            strcpy(new_ticket.seat_type,"Regular");
            if(concerts[index].num_normal_seats-concerts[index].num_normal_tickets_sold==0){
                    system("cls");
                    printf("%s Regular concert tickets have sold out\n",new_ticket.concert_name);
                    for(int i=0;i<num_concerts;i++){
                        fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
                    }
                    display_menu();
            }
            for (int i = 0; i < concerts[index].num_normal_seats; i++) {
                if (concerts[index].normal_seat_status[i] == 0) {
                    new_ticket.seat_number = i+1;
                    seat_number=new_ticket.seat_number;
                    concerts[index].normal_seat_status[i] = 1;
                    break;
                }
            }
            if (seat_number == -1) {
                printf("Sorry, no seats available.\n");
                buy_ticket();
            }
            concerts[index].num_normal_tickets_sold++;
            break;
        default:
            printf("\nInvalid choice Try again\n");
    }
    fprintf(tickets_file,"%s %s %s %d\n",new_ticket.client_name,new_ticket.concert_name,new_ticket.seat_type,new_ticket.seat_number);

    for(int i=0;i<num_concerts;i++){
        if(strcmp(concerts[i].name,concerts[index].name)==0){
            fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[index].name,concerts[index].location,concerts[index].num_vip_seats,concerts[index].num_vip_tickets_sold,concerts[index].num_normal_seats,concerts[index].num_normal_tickets_sold);
        }
        else{
            fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
        }
    }
    fclose(tickets_file);
    fclose(concert_file);

    printf("Ticket bought successfully! Your seat number is %d.\n --- let's meet at the concert ---- \n", new_ticket.seat_number);
    display_menu();
}

// Function to validate the admin credentials
void admin_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    printf("\n\n\n\n\n\n\n");
    printf("%40s\n\n","Admin login\n");
    printf("%30s","Enter Username: ");
    scanf("%s", username);
    printf("\n\n\n");
    printf("%30s","Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            system("cls");
            printf("\n\n\n");
            printf("%35s","Login Successful\n");
            display_admin_menu();
    } else {
        system("cls");
        printf("\n\n\n");
        printf("%30s. %s\n\n","Invalid credentials","Please try again.\n");
        general_login();
    }
}

void display_admin_menu() {
    printf("\n\n\n");
    printf("%40s\n","Admin Menu");
    printf("%40s\n\n","----------");
    printf("%40s","1. Create a new concert\n\n");
    printf("%44s","2. Display list of concerts\n\n");
    printf("%46s","3. Update an existing concert\n\n");
    printf("%36s","4. Delete a concert\n\n");
    printf("%37s","5. View ticket buyer\n\n");
    printf("%27s","6. Logout \n\n");
    printf("%27s","7. Exit \n\n\n\n");
    printf("%40s","choose an option: ");

        int admin_choice;
        scanf("%d",&admin_choice);

        switch (admin_choice) {
            case 1:
                create_concert();
                break;
            case 2:
                system("cls");
                admin_view_concerts();
                break;
            case 3:
                update_concert();
                break;
            case 4:
                delete_concert();
                break;
            case 5:
                view_tickets_details();
                break;
            case 6:
                system("cls");
                printf("\n\n\n");
                printf("%35s","Logout Successful\n\n\n");
                general_login();
                break;
            case 7:
                printf("\n\n\n");
                printf("%55s","Thank you for using Concert book system\n\n\n\n\n");
                exit(1);
            default:
                system("cls");
                printf("Invalid choice. Please try again.\n");
                display_admin_menu();
        }
}

// Function to create a new concert
void create_concert() {

    if (num_concerts == MAX_CONCERTS) {
        printf("\nMaximum concerts limit reached. Cannot create more concerts.\n");
        display_admin_menu();
    }
    system("cls");
    printf("\n\t\tCreate concert\n\n\n");

    FILE *concert_file=fopen("Concerts.txt","a+");
    num_concerts=0;

    printf("%20s","Concert name: ");
    scanf("%s", new_concert.name);

    printf("\n\n%27s","Number of VIP seats: ");
    scanf("%d", &new_concert.num_vip_seats);

    printf("\n\n%30s","Number of normal seats: ");
    scanf("%d", &new_concert.num_normal_seats);

    printf("\n\n%37s","Enter the location of concert: ");
    scanf("%s" ,new_concert.location);


    new_concert.num_vip_tickets_sold = 0;
    new_concert.num_normal_tickets_sold = 0;

    concerts[num_concerts++] = new_concert;

    fprintf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,new_concert.num_vip_seats,new_concert.num_vip_tickets_sold,new_concert.num_normal_seats,new_concert.num_normal_tickets_sold );
    fclose(concert_file);
    num_concerts=0;
    system("cls");
    printf("Concert created successfully!\n");
    display_admin_menu();

}

// Function to display the details of all concerts
void view_concerts() {
    FILE *concert_file;
    concert_file=fopen("Concerts.txt","r");
    num_concerts=0;
    if (concert_file==NULL) {
            system("cls");
            printf("\nError No Data\n");
            display_menu();
    }
    system("\ncls\n");
    printf("\n\n\n%40s","List of concerts\n");
    printf("%40s","----------------\n");
    printf("%10s %30s %30s %30s\n","Name","Location","VIP Remain", "Normal seats Remain");
    printf("%10s %30s %30s %30s\n","----","--------","----------", "-------------------");
    while(!feof(concert_file)){
            fscanf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,&new_concert.num_vip_seats,&new_concert.num_vip_tickets_sold,&new_concert.num_normal_seats,&new_concert.num_normal_tickets_sold );
            num_concerts++;
            for(int i=0;i<num_concerts;i++){
                concerts[i]=new_concert;
                printf("%10s %30s %30d %20d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats-concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats-concerts[i].num_normal_tickets_sold );
                break;
            }
    }
    fclose(concert_file);
    display_menu();
}
//
void admin_view_concerts() {
    FILE *concert_file=fopen("Concerts.txt","r");
    num_concerts=0;
    if (concert_file==NULL) {
            system("cls");
            printf("\n\n\t\tError No Data\n");
            display_admin_menu();
    }

    printf("%40s","List of concerts\n");
    printf("%40s","----------------\n\n");
    printf("%10s %20s %20s %20s %20s %20s\n", "Name","Location","VIP Seats", "VIP Sold", "Normal seats", "Normal seats sold");
    printf("%10s %20s %20s %20s %20s %20s \n\n", "----","--------","---------", "--------", "------------", "-----------------");
    while(!feof(concert_file)){
            fscanf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,&new_concert.num_vip_seats,&new_concert.num_vip_tickets_sold,&new_concert.num_normal_seats,&new_concert.num_normal_tickets_sold );
            num_concerts++;
            for(int i=0;i<num_concerts;i++){
                concerts[i]=new_concert;
                printf("%10s %20s %20d %20d %20d %20d\n\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold );
                break;
            }

    }
    fclose(concert_file);
    display_admin_menu();
}
// Function to update the details of a concert
void update_concert() {
    FILE *concert_file=fopen("Concerts.txt","r");
    if (concert_file==NULL) {
            system("cls");
            printf("\n\n\t\tNo concerts found.\n");
            display_admin_menu();
    }
    system("cls");
    printf("List of concerts\n");
    printf("%s\t\t\t%s\t\t%s\t\t%s\t\t%s\n\n", "Name", "VIP Seats", "VIP Sold", "Normal seats", "Normal seats sold");
    num_concerts=0;
    while(!feof(concert_file)){
            fscanf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,&new_concert.num_vip_seats,&new_concert.num_vip_tickets_sold,&new_concert.num_normal_seats,&new_concert.num_normal_tickets_sold );
            num_concerts++;
            for(int i=num_concerts-1;i<num_concerts;i++){
                concerts[i]=new_concert;
                printf("%s\t\t\t%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold );
                break;
            }

    }
    fclose(concert_file);

    concert_file=fopen("Concerts.txt","w");

    printf("\n\n\n%40s","Update concert");

    char name[MAX_NAME_LEN];
    printf("\n\n%50s","Enter the name of the concert to update: ");
    scanf("%s", name);

    int index = -1;

    for (int i = 0; i <num_concerts; i++) {
        if (strcmp(name, concerts[i].name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Concert not found. Please try again.\n");
        display_admin_menu();
    }


    printf("\n\n%37s","Enter New concert name: ");
    scanf("%s",concerts[index].name);

    printf("\n\n%33s","Enter The location: ");
    scanf("%s",concerts[index].location);

    printf("\n\n%34s","Number of VIP seats: ");
    scanf("%d", &concerts[index].num_vip_seats);

    printf("\n\n%51s","Enter the number of VIP tickets sold: ");
    scanf("%d",&concerts[index].num_vip_tickets_sold);

    printf("\n\n%37s","Number of Normal seats: ");
    scanf("%d",&concerts[index].num_normal_seats);

    printf("\n\n%54s","Enter the number of normal tickets sold: ");
    scanf("%d",&concerts[index].num_normal_tickets_sold);

    for(int i=0;i<num_concerts;i++){
        if(strcmp(concerts[i].name,concerts[index].name)!=0){
            fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
        }
        else
        fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[index].name,concerts[index].location,concerts[index].num_vip_seats,concerts[index].num_vip_tickets_sold,concerts[index].num_normal_seats,concerts[index].num_normal_tickets_sold);

    }
    fclose(concert_file);
    system("cls");
    printf("\n\n%60s","Concert details updated successfully!\n");
    display_admin_menu();
}

// Function to delete a concert
void delete_concert() {
    FILE *concert_file=fopen("Concerts.txt","r");
    if (concert_file==NULL) {
            system("cls");
            printf("\n\n\t\tNo concerts found.\n");
            display_admin_menu();
    }
    system("cls");
    printf("%40s","List of concerts\n");
    printf("%40s","----------------\n\n");
    printf("%10s %20s %20s %20s %20s %20s\n", "Name","Location","VIP Seats", "VIP Sold", "Normal seats", "Normal seats sold");
    printf("%10s %20s %20s %20s %20s %20s \n\n", "----","--------","---------", "--------", "------------", "-----------------");
    while(!feof(concert_file)){
            fscanf(concert_file,"%s %s %d %d %d %d\n",new_concert.name,new_concert.location,&new_concert.num_vip_seats,&new_concert.num_vip_tickets_sold,&new_concert.num_normal_seats,&new_concert.num_normal_tickets_sold );
            num_concerts++;
            for(int i=0;i<num_concerts;i++){
                concerts[i]=new_concert;
                printf("%10s %20s %20d %20d %20d %20d\n\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold );
                break;
            }

    }
    fclose(concert_file);
    concert_file=fopen("Concerts.txt","w");

    printf("\n\n\t\t %s","choose from option below:");
    printf("\n\n\t1.Delete a concert\n\n");
    printf("\n\t2.Delete all concerts\n\n");
    printf("\n\n\tEnter your choice: ");
    int choice;
    scanf("%d",&choice);
    char name[MAX_NAME_LEN];
    switch(choice){
        case 1:
            printf("\n\n\tEnter the name of the concert to delete: ");
            scanf("%s", name);

            int index = -1;
            for (int i = 0; i < num_concerts; i++) {
                    if (strcmp(name, concerts[i].name) == 0) {
                        index = i;
                        break;
                    }
            }

            if (index == -1) {
                    printf("\n\n\t\tConcert not found. Please try again.\n");
                    display_admin_menu();
            }
            free(concerts[index].vip_seat_status);
            free(concerts[index].normal_seat_status);
            for (int i = 0; i < num_concerts; i++) {
                    if(i==index){
                        concerts[i]=concerts[index+1];
                        i=i+1;
                    }
            }
            num_concerts--;
            for(int i=0;i<num_concerts;i++){
                            fprintf(concert_file,"%s %s %d %d %d %d\n",concerts[i].name,concerts[i].location,concerts[i].num_vip_seats,concerts[i].num_vip_tickets_sold,concerts[i].num_normal_seats,concerts[i].num_normal_tickets_sold);
            }
            fclose(concert_file);
            if(num_concerts<=0){
                remove("Concerts.txt");
            }
            system("cls");
            printf("\n\n\t\tConcert deleted successfully!\n");
            break;
        case 2:
            fclose(concert_file);
            if(remove("Concerts.txt") == 0){
                printf("\n\n\t\tAll Concerts deleted successfully!");
            }else{
                printf("Unable to delete the file");
            }
            break;
        default:
            printf("%s","\n\n\t\tInvalid Choice");
    }
    display_admin_menu();
}

void view_tickets_details(){
    FILE *tickets_file=fopen("Tickets records.txt","r");
    if(tickets_file==NULL){
        system("cls");
        printf("\n\n\t\tNo Tickets Found");
        display_admin_menu();
    }
    printf("%15s %30s %30s %30s\n\n","Buyer name","Concert name","Reserved seating","Seat number");
    while(!feof(tickets_file)){
        fscanf(tickets_file,"%s %s %s %d\n",new_ticket.client_name,new_ticket.concert_name,new_ticket.seat_type,&new_ticket.seat_number);
        printf("%10s %30s %30s %30d\n",new_ticket.client_name,new_ticket.concert_name,new_ticket.seat_type,new_ticket.seat_number);
    }
    fclose(tickets_file);
    display_admin_menu();

}





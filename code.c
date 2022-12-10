#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int m = 100, AC_room = 1000, NAC_room = 1100;
struct Menu //For Restaurant
{
    int sno;
    int quantity;
    float price;
    struct Menu *next_i;
    char name_f[30];
};

struct Hotel //For Hotel
{
    char name_c[20]; 
    char address[50];
    char phone[15];
    float payment;
    char type[10];
    int id;
    struct Hotel *next;
};

struct Hotel *newnode, *tail_c = NULL;
struct Hotel *first_c = NULL;
struct Menu *first_m = NULL, *t, *tail_m = NULL, *first_cr = NULL, *tail_cr = NULL, *first_sa = NULL;

//Room types
void room() 
{
    printf("\n\t\t\t\t\t                                AC |  Non AC ");
    printf("\n\t\t\t\t\t         No of beds:           1,2 |   1,2,3 ");
    printf("\n\t\t\t\t\tRent per Room per day:        1200/-|    850/-");
}

//For displaying menu
void display_menu() //Displaying menu
{
    struct Menu *s = first_m;
    printf("\n\n\t\t\t\t\t-----------Menu----------\n");
    while (s != NULL)
    {
        printf("\n\t\t\t\t\t%d\t%s\t%.2f", s->sno, s->name_f, s->price);
        s = s->next_i;
    }
}

//For booking the room
struct Hotel *room_final() 
{
    int c, v;
    newnode = (struct Hotel *)malloc(sizeof(struct Hotel));
    printf("\n\n\t\t\t\t\tEnter your name:");
    fflush(stdin);
    gets(newnode->name_c);
    printf("\n\t\t\t\t\tEnter your address:");
    fflush(stdin);
    gets(newnode->address);
    printf("\n\t\t\t\t\tEnter your phone number:");
    fflush(stdin);
    gets(newnode->phone);
    m++;
    newnode->id = m;
    printf("\n\t\t\t\t\t1. AC room");
    printf("\n\t\t\t\t\t2. Non Ac room");
    printf("\n\t\t\t\t\t -->");
    scanf("%d", &c);
    switch (c)
    {
    case 1:
        strcpy(newnode->type, "AC");
        printf("\n\t\t\t\t\tNo. of person:");
        scanf("%d", &v);
        if (v > 2)
        {
            if (v % 2 == 0)
            {
                AC_room = AC_room + (v / 2);
                newnode->payment = 1200 * (v / 2);
                printf("\n\t\t\t\t\t You have booked %d rooms!", (v / 2));
            }
            else
            {
                AC_room = AC_room + (v / 2) + 1;
                newnode->payment = 1200 * ((v / 2) + 1);
                printf("\n\t\t\t\t\t You have booked %d rooms!", (v / 2) + 1);
            }
        }
        else if (v > 0 && v <= 2)
        {
            AC_room++;
            newnode->payment = v * 1200; 
            printf("\n\t\t\t\t\t You have booked 1 room!");
        }
        else
            printf("\n\t\t\t\t\tYou can't enter '0' or negative number.\n");
        break;
    case 2:
        strcpy(newnode->type, "NON-AC");
        printf("\n\t\t\t\t\tNo. of person:");
        scanf("%d", &v);
        if (v > 3)
        {
            if (v % 3 == 0)
            {
                NAC_room = NAC_room + (v / 3);
                newnode->payment = 850 * (v / 3);
                printf("\n\t\t\t\t\t You have booked %d rooms!", (v / 3));
            }
            else
            {
                NAC_room = NAC_room + (v / 3) + 1;
                newnode->payment = 850 * ((v / 3) + 1);
                printf("\n\t\t\t\t\t You have booked %d rooms!", (v / 3) + 1);
            }
        }
        else if (v > 0 && v <= 3)
        {
            NAC_room++;
            newnode->payment = v * 850; 
            printf("\n\t\t\t\t\t You have booked 1 room!");
        }

        else
            printf("\n\t\t\t\t\tYou can't enter '0' or negative number.\n");

        break;
    }

    if (first_c == NULL)
    {
        first_c = tail_c = newnode;
    }
    else
    {
        tail_c->next=newnode;
        tail_c = newnode;
        newnode->next = NULL;
    }
    return first_c;
}

//For placing the order
struct Menu *place_order() 
{
    display_menu(); 
    t = (struct Menu *)malloc(sizeof(struct Menu));
    printf("\n\n\t\t\t\t\tEnter the serial no:");
    scanf("%d", &t->sno);
    printf("\n\t\t\t\t\tEnter quantity :");
    scanf("%d", &t->quantity);
    t->next_i = NULL;
    struct Menu *r = first_m;
    struct Menu *a = first_cr;
    struct Menu *b = first_cr;
    while (r->sno != t->sno)
    {
        r = r->next_i;
    }
    strcpy(t->name_f, r->name_f);
    t->price = t->quantity * r->price;

    if (first_cr == NULL)
    {
        first_cr = tail_cr = t;
    }
    else
    {
        while (b != NULL)
        {
            if (b->sno == t->sno)
            {
                b->price = b->price + t->price;
                b->quantity = b->quantity + t->quantity;
                return first_cr;
            }
            b = b->next_i;
        }
        while (a->next_i != NULL)
            a = a->next_i;

        a->next_i = t;
        tail_cr = t;
    }
    return first_cr;
}

//Display ordered items
void view_order_item() 
{
    struct Menu *s = first_cr;
    if (first_cr == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
        return;
    }
    printf("\n\t\t\t\t\t-----------   YOUR ITEMS  -----------");
    while (s != NULL)
    {
        printf("\n\t\t\t\t\t%d\t%s\t%d\t%.2f", s->sno, s->name_f, s->quantity, s->price);
        s = s->next_i;
    }
}

//Final bill for restaurant
void final_bill() 
{
    struct Menu *t = first_cr;
    float total = 0;
    printf("\t\t\t\t\t-----------   FINAL BILL  -----------\n");

    if (first_cr == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
        return;
    }

    while (t != NULL)
    {
        printf("\n\t\t\t\t\t%d\t%s\t%d\t%.2f", t->sno, t->name_f, t->quantity, t->price);
        total = total + t->price;
        t = t->next_i;
    }
    printf("\n\t\t\t\t\tTotal = %.2f", total);
}

//Add new item in menu
struct Menu *createMenu(int sno, float price, char name[30]) 
{
    t = (struct Menu *)malloc(sizeof(struct Menu));
    t->sno = sno;
    t->quantity = 0;
    t->price = price;
    strcpy(t->name_f, name);
    t->next_i = NULL;
    struct Menu *q = first_m;
    while (q != NULL)
    {
        if (q->sno == sno)
        {
            printf("\n\t\t\t\t\tSerial No. already exist!!Please enter different Serial No..");
            return first_m;
        }
        q = q->next_i;
    }

    struct Menu *p = first_m;
    if (first_m == NULL)
    {
        first_m = tail_m = t;
    }
    else
    {
        while (p->next_i != NULL)
        {
            p = p->next_i;
        }
        p->next_i = t;
        tail_m = t;
    }
    return first_m;
}

//For removing items for admin
struct Menu *admin_delete() 
{
    int n;
    printf("\n\t\t\t\t\tEnter the serial no.:\t");
    scanf("%d", &n);
    if (first_m == NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct Menu *p;
        struct Menu *q;
        if (n == first_m->sno)
        {
            p = first_m;
            first_m = first_m->next_i;
            free(p);
        }
        else
        {
            p = first_m;
            q = first_m->next_i;
            while (n != q->sno && q->next_i != NULL)
            {
                p = p->next_i;
                q = q->next_i;
            }
            if (q == tail_m)
            {
                p->next_i = NULL;
                tail_m = p;
            }
            else
                p->next_i = q->next_i;

            free(q);
        }
    }
    display_menu();
    return first_m;
}

//For removing items for customers
struct Menu *customer_delete() 
{
    view_order_item();
    if (first_cr == NULL)
        return first_cr;
    int n, u;
    printf("\n\t\t\t\t\tEnter the sr no. :\t");
    scanf("%d", &n);
    printf("\n\t\t\t\t\tEnter the quantity you want to remove:\t");
    scanf("%d", &u);
        struct Menu *p;
        struct Menu *q;
        float s;
        if (n == first_cr->sno)
        {
            p = first_cr;
            if (u < p->quantity)
            {
                s = p->price / p->quantity;
                p->quantity = p->quantity - u;
                p->price = p->quantity * s;
                return first_cr;
            }
            first_cr = first_cr->next_i;
            free(p);
        }

        else
        {
            p = first_cr;
            q = first_cr->next_i;
            while (n != q->sno)
            {
                p = p->next_i;
                q = q->next_i;
            }
            if (u < q->quantity)
            {
                s = q->price / q->quantity;
                q->quantity = q->quantity - u;
                q->price = q->quantity * s;
                return first_cr;
            }
            if (q == tail_cr)
            {
                p->next_i = NULL;
                tail_cr = p;
            }
            else
                p->next_i = q->next_i;

            free(q);
        }
    view_order_item();
    return first_cr;
}

//For displaying customer list of hotel
void display_customerlist()
{
    
    int i = 1;
    struct Hotel *s = first_c;
    if (first_c == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
        return;
    }
    while (s != NULL)
    {
        printf("\n\t\t\t\t\t%d.\t%s\t%s\t%s\t%.2f\t%s\t%d", i, s->name_c, s->address, s->phone, s->payment, s->type, s->id);
        s = s->next;
        i++;
    }
    
}

//For displaying total sales of hotel
void hotel_tsale()
{
    int tnac_room, tac_room;
    float nac_total, ac_total, total;
    tac_room = AC_room - 1000;
    tnac_room = NAC_room - 1100;
    ac_total = tac_room * 1200;
    nac_total = tnac_room * 850;

    total = ac_total + nac_total;
    printf("\t\t\t\t\t-----------   TOTAL SALES  -----------");
    printf("\n\t\t\t\t\tTotal AC Rooms:%d\t\t%.2f", tac_room, ac_total);
    printf("\n\t\t\t\t\tTotal NON-AC Rooms:%d\t\t%.2f", tnac_room, nac_total);
    printf("\n\t\t\t\t\tTotal Sale:\t\t%.2f", total);
    
    
}

//Total sales for restaurant
struct Menu *restaurant_tsale(int srno, int q)
{
    t = (struct Menu *)malloc(sizeof(struct Menu));
    struct Menu *s = first_m;
    while (s->sno != srno)
        s = s->next_i;

    t->sno = srno;
    t->quantity = q;
    t->price = q * (s->price);
    strcpy(t->name_f, s->name_f);
    t->next_i = NULL;
    struct Menu *a = first_sa;
    struct Menu *b = first_sa;
    if (first_sa == NULL)
    {
        first_sa = t;
    }
    else
    {
        while (b != NULL)
        {
            if (b->sno == t->sno)
            {
                b->price = b->price + t->price;
                b->quantity = b->quantity + t->quantity;
                return first_sa;
            }
            b = b->next_i;
        }
        while (a->next_i != NULL)
            a = a->next_i;
        a->next_i = t;
    }
    return first_sa;
}

void calculate()
{
    struct Menu *p = first_cr;
    while (p != NULL)
    {
        first_sa = restaurant_tsale(p->sno, p->quantity);
        p = p->next_i;
    }
}

//Displays room availablity
void room_details()
{
    printf("\t\t\t\t\t-----------   ROOM DETAILS  -----------");
    printf("\n\t\t\t\t\t Room packed(AC):\t%d", AC_room - 1000);
    printf("\n\t\t\t\t\t Room packed(NON-AC):\t%d", NAC_room - 1100);
    printf("\n\t\t\t\t\t Room Available(AC):\t%d", 1100 - AC_room);
    printf("\n\t\t\t\t\t Room Available(NON-AC):\t%d", 1200 - NAC_room);
}

//For deleting whole list
struct Menu *delete_list(struct Menu *a)
{

    if (a == NULL)
        return NULL;

    struct Menu *p;
    struct Menu *q = a;
    while (q->next_i != NULL)
    {
        p = q;
        q = q->next_i;
        free(p);
    }
    free(q);
    a = NULL;

    return a;
}

//Displaying the list
void display(struct Menu *p)
{
    struct Menu *t = p;
    if (p == NULL)
    {
        printf("\n\t\t\t\t\t\tList is empty!!\n\n");
        return;
    }
    printf("\n");
    while (t != NULL)
    {
        if (t->quantity != 0)
        {
            printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n", t->sno, t->name_f, t->quantity, t->price);
        }
        t = t->next_i;
    }
    
}


void customer_restaurant() 
{
    int c;
    while (1)
    {
        int c;
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\n\t\t\t\t\t1. Place your order\n");
        printf("\t\t\t\t\t2. View your ordered items\n");
        printf("\t\t\t\t\t3. Delete an item from order\n");
        printf("\t\t\t\t\t4. Display final bill\n");
        printf("\t\t\t\t\t0. To exit\n");
        printf("\t\t\t\t\t   Enter Your Choice --->");
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        switch (c)
        {
        case 1:
            first_cr = place_order(c); 
            printf("\n");
            break;
        case 2:
            view_order_item(); 
            printf("\n");
            break;
        case 3:
            customer_delete();
            printf("\n");
            break;
        case 4:
            calculate();
            final_bill();
            first_cr = delete_list(first_cr);
            printf("\n");
            break;
        default:
            printf("\n\t\t\t\t\t\t\tPlease Enter Valid Choice!\n");
            break;
        }
    }
}

void admin_restaurant() 
{
    int s;
    float f;
    char v[30];
    while (1)
    {
        int c;
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\t\t\t\t\t1. View total sales\n");
        printf("\t\t\t\t\t2. Add new items in the order menu\n");
        printf("\t\t\t\t\t3. Delete items from the order menu\n");
        printf("\t\t\t\t\t4. Display order menu\n");
        printf("\t\t\t\t\t0. To exit\n");
        printf("\t\t\t\t\t   Enter Your Choice --->");
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        switch (c)
        {
        case 1:
            printf("\t\t\t\t\t-----------   TOTAL SALES  -----------");
            display(first_sa);
            break;
        case 2:
            printf("\n\n\t\t\t\t\tEnter the serial number:");
            scanf("%d", &s);
            printf("\n\t\t\t\t\tEnter the Name of food item:");
            fflush(stdin);
            gets(v);
            printf("\n\t\t\t\t\tEnter the price:");
            scanf("%f", &f);
            first_m = createMenu(s, f, v);
            printf("\n");
            display_menu();
            printf("\n");
            break;
        case 3:
            display_menu();
            admin_delete();
            printf("\n");
            break;
        case 4:
            display_menu();
            printf("\n");
            break;
        default:
            printf("\n\t\t\t\t\t\t\tPlease Enter Valid Choice!\n");
            break;
        }
    }
}

void customer_hotel()
{
    int c;
    while (1)
    {
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\n\t\t\t\t\t1. To see the types of rooms");
        printf("\n\t\t\t\t\t2. To book the room");
        printf("\n\t\t\t\t\t0. Back");
        printf("\n\t\t\t\t\t -->");
        scanf("%d", &c);
        if (c == 0)
            break;

        switch (c)
        {
        case 1:
            room(); 
            break;
        case 2:
            first_c = room_final(); 
            break;
        default:
            break;
        }
    }
}

void admin_hotel()
{
    int c;
    while (1)
    {
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\t\t\t\t\t1. Customer List");
        printf("\n\t\t\t\t\t2. Total Sale");
        printf("\n\t\t\t\t\t3. Room Details");
        printf("\n\t\t\t\t\t0. Back To Main Menu \n\n");
        printf("\n\t\t\t\t\t -->");
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        switch (c)
        {
        case 1:
            display_customerlist();
            printf("\n");
            break;
        case 2:
            hotel_tsale();
            printf("\n");
            break;
        case 3:
            room_details();
            printf("\n");
            break;
        default:
            break;
        }
    }
}

void admin() 
{
    int c;
    while (1)
    {
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\t\t\t\t\t1. For Hotel");
        printf("\n\t\t\t\t\t2. For Restaurant");
        printf("\n\t\t\t\t\t0. Back To Main Menu \n\n");
        printf("\n\t\t\t\t\t -->");
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        switch (c)
        {
        case 1:
            admin_hotel();
            printf("\n");
            break;
        case 2:
            admin_restaurant();
            printf("\n");
            break;

        default:
            break;
        }
    }
}

void customer() 
{
    int c;
    while (1)
    {
        printf("\n\t\t\t\t\t-----------   OPTIONS  -----------");
        printf("\n\n\t\t\t\t\t1. For Hotel");
        printf("\n\t\t\t\t\t2. For Restaurant");
        printf("\n\t\t\t\t\t0. Back \n\n");
        printf("\n\t\t\t\t\t -->");
        scanf("%d", &c);
        if (c == 0)
        {
            break;
        }
        switch (c)
        {
        case 1:
            customer_hotel(); //Details of rooms
            break;
        case 2:
            customer_restaurant();
            break;
        default:
            break;
        }
    }
}

void print_()
{
    printf("\n\n\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t0. Exit--> \n\n");
    printf("\t\t\t\t\tEnter Your Choice --->");
}

void welcome()
{
    printf("\n\t\t\t\t\t--------------------------------------------------------------------");
    printf("\n\t\t\t\t\t------------                                            ------------");
    printf("\n\t\t\t\t\t-----------  Welcome to Green Leaf Hotel with Restaurant -----------");
    printf("\n\t\t\t\t\t------------                                            ------------");
    printf("\n\t\t\t\t\t--------------------------------------------------------------------");
}

int main()
{
    int c;
    welcome();
    first_m = createMenu(1, 120.0, "Pao Bhaji");
    first_m = createMenu(2, 185.0, "Gujrati Full Dish");
    first_m = createMenu(3, 180.0, "Manchow Soup");
    first_m = createMenu(4, 200.0, "Panjabi Full Dish");
    first_m = createMenu(5, 160.0, "Chhole Bhature");
    first_m = createMenu(6, 20.0, "Any Cold Drink");
    while (1)
    {
        print_();
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 0:
            exit(0);
            break;
        }
    }
    return 0;
}
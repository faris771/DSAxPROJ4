/**
 * AUTHOR:FARIS ABUFARHA
 * ID:1200546
 * SEC:3
 * REPO LINK: https://github.com/faris771/DSAxPROJ4
 * IDE: JETBRAINS' CLION
 * COMPILER: gcc
 * OS: LINUX UBUNTU
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
 *
 *        Color Codes
Black: \033[0;30m
Red: \033[0;31m
Green: \033[0;32m
Yellow: \033[0;33m
Blue: \033[0;34m
Magenta: \033[0;35m
Cyan: \033[0;36m
White: \033[0;37m
        Style
Normal: \033[0;3?m
Bold:   \033[1;3?m
Reset: \033[0m
*/


#define null NULL
#define MAX_STRING 250
#define MAX_LINE 1000
#define  INF 99999



typedef long long ll;

typedef char String[MAX_STRING];


//---------------------------------------------GLOBAL VARIABLES-------------------------------------------------------------------------
int V = 0; //VARIABLE TO STORE THE NUMBER OF VERTICES


// avl tree functions in orded to use it as a SET
typedef struct AVLnode *pAvl;

typedef struct AVLnode {

    String cityName;//key
    int indx;//index of the course in the graph
    pAvl left;
    pAvl right;
    int height; //Balance information


} AVLnode;



int height(pAvl P) {
    if (P == NULL) {
        return -1;
    }
    else {
        return P->height;
    }
}


int max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

pAvl singleRotateWithLeft(pAvl K2) {
    pAvl K1;

    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    K2->height = max(height(K2->left), height(K2->right)) + 1;
    K1->height = max(height(K1->left), K2->height) + 1;

    return K1;  /* New root */
}

pAvl singleRotateWithRight(pAvl K1) {
    pAvl K2;

    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;

    K1->height = max(height(K1->left), height(K1->right)) + 1;
    K2->height = max(height(K2->right), K1->height) + 1;

    return K2;  /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

pAvl doubleRotateWithLeft(pAvl K3) {
    /* Rotate between K1 and K2 */
    K3->left = singleRotateWithRight(K3->left);

    /* Rotate between K3 and K2 */
    return singleRotateWithLeft(K3);
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

pAvl doubleRotateWithRight(pAvl K1) {
    /* Rotate between K3 and K2 */
    K1->right = singleRotateWithLeft(K1->right);

    /* Rotate between K1 and K2 */
    return singleRotateWithRight(K1);
}

pAvl insert(AVLnode treeNode, pAvl T) {
    if (T == NULL) {
        /* Create and return a one-listNode tree */
        T = malloc(sizeof(AVLnode));
//        V++;
        if (T == NULL) {
            printf("Out of space!!!");
        }

        else {
            //HERE WE ASSIGN THE VALUES
            // TRY W/OUT *

            *T = treeNode;
//            strcpy(T->cityName, cityName);
            T->height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (strcmp(treeNode.cityName, T->cityName) < 0) {
        T->left = insert(treeNode, T->left);
//        V++;
        if (height(T->left) - height(T->right) == 2) {
            if (strcmp(treeNode.cityName, T->left->cityName) < 0) {
                T = singleRotateWithLeft(T);
            }
            else {
                T = doubleRotateWithLeft(T);
            }
        }
    }
    else if (strcmp(treeNode.cityName, T->cityName) > 0) {

        T->right = insert(treeNode, T->right);
//        V++;
        if (height(T->right) - height(T->left) == 2) {
            if (strcmp(treeNode.cityName, T->right->cityName) > 0) {
                T = singleRotateWithRight(T);
            }
            else {
                T = doubleRotateWithRight(T);
            }
        }
    }
    else{

        T->height = max(height(T->left), height(T->right)) + 1;
        return T;
    }
    /* Else cityName is in the tree already; we'll do nothing */

    T->height = max(height(T->left), height(T->right)) + 1;
    return T;

}
//pAvl findTreeNode(String cityName, pAvl T) {
//    if (T == NULL) {
//        return NULL;
//    }
//    if (strcmp(cityName, T->cityName) < 0) {
//        return findTreeNode(cityName, T->left);
//    }
//    else if (strcmp(cityName, T->cityName) > 0) {
//        return findTreeNode(cityName, T->right);
//    }
//    else {
//        return T;
//    }
//}

int getIndex(String cityName, pAvl T) {
    if (T == NULL) {
        return -1;
    }
//    printf("%s\n", cityName);

    if (strcmp(cityName, T->cityName) < 0) {
        return getIndex(cityName, T->left);
    }
    else if (strcmp(cityName, T->cityName) > 0) {
        return getIndex(cityName, T->right);
    }
    else {
        return T->indx;
    }
}


pAvl SET =  null;

int cnt = 0;
int getVsize(pAvl t) {

    int dummy = 0;
    if (t != NULL) {
        dummy = getVsize(t->left);
        t -> indx = cnt;
        fprintf(stdout, "%s %d\t",
                t->cityName, t->indx);

        cnt++;

        V++;
        dummy = getVsize(t->right);

    }
    printf("\n");
    return V;

}


//---------------------------------------------GLOBAL VARIABLES-------------------------------------------------------------------------



void line();

void welcome();
void menu();
void red();
void reset();
void green();
void blue();
void yellow();
void purple();
void orange();
void pink();
void white();
void black();
void bold();

void art();
void readV();

void assignToGraph(int Graph[V][V]);





int main() {

    readV();
    int tmpV = 0;
    int dummy = getVsize(SET);
    // essential arrays

    int parent[V] ;//parent[i] = parent of i
    for (int i = 0; i < V; ++i) {
        parent[i] = -1;
    }

    bool visited [V];//visited[i] = 1 if vertex i is visited
    for (int i = 0; i < V; ++i) {
        visited[i] = false;
    }
    int distance [V]; //distance from source (VALUE)
    for (int i = 0; i < V; ++i) {
        distance[i] = INF;
    }


    int Graph[V][V]; //Graph[i][j] = x is the edge from i to j
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            Graph[i][j] = INF;
        }

    }



    //==========================================================
//    printf("\nV %d\n", V);



    welcome();
    int selection;

    while(true) {
        menu();
        scanf("%d", &selection);

        if (selection == 1) {

            assignToGraph(Graph);
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    printf("%d\t", Graph[i][j]);
                }
                printf("\n");
            }

        }
        else if (selection == 2) {


        }
        else if (selection == 3) {


        }

        else if (selection == 4) {
            //do stuff



            art();
            break;


        }

        else {

            red();
            printf("Invalid Selection\n");
            reset();
            continue;


        }





    }


}











void green() {
    printf("\033[32m");
}
void red() {
    printf("\033[31m");
}
void blue() {
    printf("\033[34m");
}
void reset() {
    printf("\033[0m");
}


void line() {
    bold();
    blue();
    printf("================================================================\n");
    reset();
}

void yellow() {
    printf("\033[33m");
}
void black() {
    printf("\033[30m");
}
void white() {
    printf("\033[37m");
}
void pink() {
    printf("\033[35m");
}
void orange() {
    printf("\033[33m");
}
void purple() {
    printf("\033[35m");
}

void bold() {
    printf("\033[1m");
}


void welcome() {
    pink();
    printf("                 _                              \n"
           "                | |                             \n"
           " __      __ ___ | |  ___  ___   _ __ ___    ___ \n"
           " \\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\\n"
           "  \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n"
           "   \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n"
           "                                                \n"
           "                                                \n");

    reset();

}

void menu() {
    line();
    pink();

    printf("1. Load cities\n"
           "2. Enter source city:\n"
           "3. Enter destination city:\n"
           "4. Exit:\n");
    reset();
    line();

}

void art() {
    printf("⠀⠀⠘⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀\n"
           "⠀⠀⠀⠑⡀THANK YOU COME AGAIN⠀⠀⠀⠀ ⠀⠀⠀\n"
           "⠀⠀⠀⠀⠈⠢⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠊⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⢀⣀⣀⣀⣀⣀⡀⠤⠄⠒⠈⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠘⣀⠄⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠈⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿\n"
           "⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿\n"
           "⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿\n"
           "⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿\n"
           "⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿\n"
           "⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿\n"
           "⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼\n"
           "⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼\n"
           "⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿\n"
           "⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿\n"
           "⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿\n"
           "⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿\n"
           "⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⡄⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉\n"
           "⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄\n");

}

void readV() {

    FILE *in = fopen("cities.txt", "r");
    if (in == NULL) {
        red();
        printf("Error opening file\n");
        reset();
        exit(1);
    }

    String city1;
    String city2;
    String cost;

    while (fscanf(in, "%s%s%s", city1,city2,cost) != EOF) {
        pAvl tmpNode1 = malloc(sizeof(AVLnode));
        strcpy(tmpNode1->cityName, city1);

        pAvl tmpNode2 = malloc(sizeof(AVLnode));
        strcpy(tmpNode2->cityName, city2);

        SET = insert(*tmpNode1, SET);
        SET = insert(*tmpNode2, SET);

//        printf("%s %s\n",tmpNode1->cityName,tmpNode2->cityName);
//        printf("V : %d\n", V);

    }

    fclose(in);
}

void assignToGraph(int Graph [V][V] ) {
    FILE *in = fopen("cities.txt", "r");
    String  city1, city2 ;
    String  strCost;

    char * num;


    while (fscanf(in, "%s%s%s", city1,city2,strCost) != EOF) {

        num = strtok(strCost, "[Kk][Mm]"); // capital K or k for kilometers and M or m for miters
        int cost = atoi(num);

//        printf("cost : %d\n", cost);


        Graph[getIndex(city1, SET)][getIndex(city2, SET)] = cost;
        Graph[getIndex(city2, SET)][getIndex(city1, SET)] = cost;

    }


    fclose(in);



}


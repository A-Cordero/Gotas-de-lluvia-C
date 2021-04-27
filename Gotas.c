
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>

#define altura 50
#define ancho 160

typedef struct gota
{
    int x;
    int y;
    int z;
    int vel_y;
    int len;
}gota;

void iniciar_mapa( int mapa[altura][ancho] )
{
    int i, j;

        for( i = 0; i < altura; i++)
            for( j = 0; j < ancho ; j++)
                mapa[i][j] = 0;
}
 void dibujar_mapa(int mapa[altura][ancho])
 {
     int i, j;

         for( i = 0; i < altura; i++)
            {
                for( j = 0; j < ancho ; j++)
                    {
                        if( mapa[i][j] == 1 )
                            printf("\u02C8");
                        else if( mapa[i][j] == 2 )
                            printf("\u2502");
                        else if( mapa[i][j] == 3 )
                            printf("\u258A");
                        else
                            printf(" ");
                    }
                printf("\n");
             }
 }

gota* iniciar_gota()
{
    gota *gotas;
    gotas = (gota*)malloc(sizeof(gota));
    gotas->x = rand()%ancho;
    gotas->y = (-1)*rand()%15;
    gotas->z = rand()%3 +1;
    gotas->vel_y = 1;
    gotas->len = rand()%2 +1;

    return gotas;
}
void actualizar_lluvia( gota *gotas, int mapa[altura][ancho] )
{
    int i, j;

    gotas->y = gotas->y + gotas->vel_y;
    if( gotas->y >= altura )
        {
            gotas->y = (-1)*rand()%15;
            gotas->x = rand()%ancho;
            gotas->z = rand()%3 +1;
            gotas->len = rand()%2 +1;
        }

    for( i = 0; i < gotas->len; i++ )
        {
            if( gotas->y - i >= 0 )
                {
                    switch( gotas->z)
                    {
                        case 1 :
                            mapa[gotas->y - i][gotas->x] = 1;
                            break;
                        case 2 :
                            mapa[gotas->y - i][gotas->x] = 2;
                            break;
                        case 3 :
                            mapa[gotas->y - i][gotas->x] = 3;
                            break;
                    }
                }
        }
}
int main()
{
    int mapa[altura][ancho];
    int i, j;
    gota *gotas[120];
    for( i = 0; i < 120; i++)
        gotas[i] = iniciar_gota();

    iniciar_mapa(mapa);
    for( i = 0; i < 5000; i++)
        {
            system("clear");
            for( j = 0; j < 120; j++)
                actualizar_lluvia(gotas[j],mapa);
            dibujar_mapa(mapa);
            usleep(20000);
            iniciar_mapa(mapa);
        }


    return 0;
}

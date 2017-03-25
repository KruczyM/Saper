#include <iostream>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

struct gra
{
	int wartosc;
	bool kurtyna;
};
fstream plik;
gra plansza[10][10];
int flaga=0;

bool genruj_plansze ()
{
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
        {
            plansza[x][y].wartosc = 0;
            plansza[x][y].kurtyna = false;
        }
    
    return true;
}

bool losuj_pozycje ()
{
	int ilosc = 10,x,y;
    time_t t;
    srand((unsigned)time(&t));
    while (ilosc > 0)
    {
        x = rand()%10;
        y = rand()%10;
 
        if (plansza[x][y].wartosc != 9)
        {
    	    	plansza[x][y].wartosc = 9;
	    	    for (int a = -1; a < 2; a++)
	    	    {
            		for (int b = -1; b < 2; b++)
            		{
                		if ((x+a) < 0 || (y+b) < 0 || (x+a) > 9 || (y+b) > 9) continue;
 						if (plansza[x+a][y+b].wartosc == 9) continue;
                		plansza[x+a][y+b].wartosc += 1;
            		}
            	}
            ilosc--;
        }
    }
    return true;
}

void odkrywanie (int x, int y)
{
	if( x < 0 || x > 9 || y < 0 || y > 9) return;
	if ( plansza[x][y].kurtyna == true ) return;
	if ( plansza [x][y].wartosc != 9 && plansza[x][y].kurtyna == false  )
	{
        plansza[x][y].kurtyna=true; 
		if (plansza[x][y].wartosc!=0) return; 
		for ( int a = -1 ; a < 2 ; a++)
    	{
    		for ( int b = -1; b < 2 ; b++)
    		{
    			odkrywanie(x + a,y + b);
			}
		}
	}
}

bool win_lose()
{
    int ilosc = 0;
    for (int a = 0; a<10; a++)
    {
        for (int b = 0; b<10; b++)
        {
            if(plansza[b][a].kurtyna==false)
                ilosc++;
        }
    }
    if (ilosc==10) return true;
    return false;
}

void generuj_obraz()
{
	system("cls");
	cout<<"       SAPER\n\n   X0123456789\nY\n";
	for (int a = 0; a < 10; a++)
    {
    	cout<<a<<"   ";
        for (int b = 0; b < 10; b++)
        {
    		if (plansza[a][b].kurtyna==true) 
    		{
   				if (plansza[a][b].wartosc==0)  
   				{
            		cout << " ";
				}
        		else
        		{
        			cout << plansza[a][b].wartosc;
        		}
    		}
    		if (plansza[a][b].kurtyna==false)
    		{
        		cout << "#";
    		}
    	}
    	cout<<"\n";
    }
}

void poruszanie()
{
	generuj_obraz();
	cout<<"\n Wprowadz wspolrzedne \n";
	int a,b,z=0;
	string a1,b1;
	while(1)
	{
		cout<<"\nX= ";
		cin>>a1;
		cout<<"\nY= ";
		cin>>b1;
		if(a1[0] >= 48 && a1[0] <= 57 && b1[0] >= 48 && b1[0] <= 57  )
		{
			a=a1[0]-48;
			b=b1[0]-48;
			break;
		}
		else
		{
			if(z == 0)
			{
				cout<<"wspolrzedne zle wpisane, wybierz liczby od 0 do 9, malpa by dobrze wpisala... \n";
				z++;
			}
			else if(z == 1)
			{
				cout<<"chyba sobie zartujesz \n";
				z++;
			}
			else
			{
				cout<<"szkoda slow... \n";
			}
		continue;
		}
	}
	
	if(plansza[a][b].wartosc == 9)
	{
		flaga=2;
	}
	else
	{
		odkrywanie (a,b);
		generuj_obraz();
	}
}

int main()
{
	genruj_plansze ();
	losuj_pozycje ();
	string x;
	cout<<"jezeli potrzebujesz pomocy wpisz -> TAK, jezeli nie wpisz -> NIE\n";
	while ( x != "NIE" && x != "nie" && x != "Nie" && x != "NIe" && x != "NiE" && x != "nIe" && x != "nIE")
	{
		cin>>x;
		if(x == "TAK" || x == "tak" || x == "Tak" || x == "TAk" || x == "TaK" || x == "tAk" || x == "tAK" )
		{
			string linia;
			plik.open("pomoc.txt",ios::in);
			if(plik.good() == false)
			{
				cout<<"blad otwarcia!\n";
			}
			else
			{
				while(!plik.eof())
	        {
	            getline(plik, linia);
	            cout << linia << endl;
	        }
	        plik.close();
			}
			cout<<"\n\n Jezeli chcesz przejsc do gry wpisz -> NIE\n";
			cin>>x;
		}
		if( x != "NIE" && x != "nie" && x != "Nie" && x != "NIe" && x != "NiE" && x != "nIe" && x != "nIE")
		{
			system("cls");
			cout<<"jezeli potrzebujesz pomocy wpisz -> TAK, jezeli nie wpisz -> NIE\n";
			
		}
	}
		clock_t start, stop;
		double czas;
		start = clock();
		while(flaga == 0)
		{
			poruszanie();
    	    if (win_lose() == true) flaga = 1;
		}
	
		if (flaga == 1)
		{
			cout << "\n GOOD JOB  :)";
			stop = clock();
			czas = (stop - start)/(double)CLOCKS_PER_SEC;
			cout<< " \n Twoj czas to =  "<<czas<<" sekund \n";
		}
    	if (flaga == 2) cout << "\n MINA :( BOOOOOOM !!!!";
    	system ("pause >nul");
    	return 0;
}

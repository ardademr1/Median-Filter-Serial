/*
	           Hazýrlayan : Osman Arda DEMIR
	           Öðrenci No : 160757053
	               Bölümü : Bilgisayar Mühendisliði
	   Dersin Adý ve Kodu : PARALEL PROGRAMLAMAYA GÝRÝS, BM-308-50-50
   	             Proje No : 1
Dersi Veren Öðretim Üyesi : Dr. Öðr. Üyesi Tolga AYDIN
*/

#include <iostream>// Cout Cin
#include <fstream> // dosya iþlemleri
#include <sys/time.h>//struct timeval ve gettimeofday
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
int main(int argc, char* argv[ ])
{
	void siralamaFonk(int* , int); // Diziyi Küçükten Büyüðe Sýralamamýz Ýçin Fonksiyonu
	ifstream dosyaOku(argv[1]); // Dosya Açma iþlemi
	string arg=argv[1];
	int argumanBoyutu=arg.size(); // Arguman Boyutunu Al
	int satir,sutun;
	dosyaOku>>satir; //Dosyadan Satýr Sayýsýný Oku
	dosyaOku>>sutun; //Dosyadan Sutun Sayýsýný Oku
	int diziBoyutu=satir*sutun;
	int *tekDiziPtr=new int[diziBoyutu];		   //Tek Boyutlu Dinamik Dizi Tanýmlama
	int **matrisPtr=new int*[satir];
	for(int f=0;f<satir;f++){
 		matrisPtr[f]=new int[sutun];         	   //Ýki Boyutlu Dinamik Dizi Tanýmlama
	}
	int **ciktiMatrisPtr=new int*[satir];
	for(int p=0;p<satir;p++){
 		ciktiMatrisPtr[p]=new int[sutun];          //Ýki Boyutlu Dinamik Dizi Tanýmlama
	}
	int sayac,yeniSayi;
	int temp;
	srand(time(0));
	
	for (int i = 0; i < satir; i++){
		for (int j = 0; j < sutun; j++)
	    {
	        dosyaOku>>matrisPtr[i][j];       // Dosyadan Okunan Matris iki Boyutlu Diziye Atýlmasý
	    }
	}
	for (int q = 0; q < satir; q++){
    	for (int t = 0; t < sutun; t++)
	    {
	        tekDiziPtr[q*sutun+t]=matrisPtr[q][t];   // Dinamik Ýki Boyutlu Dizinin Matrisinin Tek Boyutlu Diziye Atýlmasý
	    }
	}
		
	dosyaOku.close();
	int boyut=25;
	int yedekPtr[boyut];   // yedek tek boyutlu dizi bu diziye okuduðumuz 5x5 matrisi atýcaz.
	int a;
	struct timeval currentTime;
	double startTime,endTime,elapsedTime;
	
	// Geçerli saatini alma. 2. argüman NULL çünkü saat dilimini umursamýyoruz
    	gettimeofday(&currentTime, NULL); //dönemden itibaren saniyeler
		startTime=currentTime.tv_sec+(currentTime.tv_usec/1000000.0); 		
			/*Süresini Ölçmek Ýstediðimiz Filtreleme Burada*/	
					int x=0;
					while(x<satir-4)
					{
						int y=0;
						while(y<sutun-4)
						{
								a=0;
								for(int sa=x;sa<x+5;sa++)
								{
									for(int su=y;su<y+5;su++)
									{
										yedekPtr[a]=tekDiziPtr[sa*sutun+su]; // 5x5 matrisin elemanlarýný yedek diziye ata.
										a++; // sayaç 
									}
									
								}
								siralamaFonk(yedekPtr ,25); // Diziyi Küçükten Büyüðe Sýralamamýz Ýçin Fonksiyonu.
								yeniSayi=yedekPtr[12];    // Küçükten Büyüðe sýraladýðýmýz dizinin ortasýndaki sayýyý al.
								tekDiziPtr[(x+2)*sutun+(y+2)]=yeniSayi; // tekDiziPtr ye yeni sayýyý yaz.
								y++;
						}
					x++;	
					}	
				
				
	// Gerçek Zamaný Al
    	gettimeofday(&currentTime, NULL); //Saniyeler
	endTime=currentTime.tv_sec+(currentTime.tv_usec/1000000.0);	
	// Zamaný Hesaplama Ýþlemleri
    	elapsedTime = endTime-startTime;
	cout << "Toplam Gecen Zaman (saniye cinsinden): " << elapsedTime << endl;
	
	
	string uzanti;
	int sayi=22;
	while(sayi<argumanBoyutu-4)
	{
		uzanti=uzanti+arg[sayi];     // Argumandaki dosyanýn ismini alma
		sayi++;
	}
	
	ofstream dosyaCikti(uzanti+"_filtered.txt");
	
	if (dosyaCikti.is_open())
  	{
  	for (int i = 0; i < satir; i++){
		for (int j = 0; j < sutun; j++)
	    {
	        ciktiMatrisPtr[i][j]=tekDiziPtr[i*sutun+j];       // Dosyadan Okunan Matris iki Boyutlu Diziye Atýlmasý
	    }
	}
	for (int q = 0; q < satir; q++){
    	for (int t = 0; t < sutun; t++)
	    {
			dosyaCikti<<ciktiMatrisPtr[q][t]<<"\t";
		}
		dosyaCikti<<endl;
	}
	
	}
	dosyaCikti.close();

	delete []tekDiziPtr;
	for(int f=0;f<satir;f++){
		delete [ ] matrisPtr[f];   // Pointer Dizileri Bellekten Silme
	}
	delete []matrisPtr;
	for(int d=0;d<satir;d++){
		delete [ ] ciktiMatrisPtr[d];
	}
	delete []ciktiMatrisPtr;

	return 0;
}

void siralamaFonk(int dizi[], int x) {
  int tut;
  for(int a=0;a<x;a++)
	{		
		for(int b=a;b<x;b++)				// Sýralama Fonksiyonu
		{
			if(dizi[a]>dizi[b])
			{
				tut  =dizi[a];
				dizi[a]=dizi[b];
				dizi[b]=tut;
			}
		}
	}
}

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <windows.h>
#include <ctime>
using namespace std;

class Init{
	public:
		struct _TABLE{
			struct _TABLE_DOSEN{
				static string _NAMA_DOSEN;
				static string _NID_DOSEN;
				static string _MATKUL_DOSEN;
			};
			struct _TABLE_MHS{
				static string _NAMA_MHS;
				static string _NIM_MHS;
			};
		};
		static string _DB;
//		static string _TABLE;
		static string _PATH;
		static int checkNim(const char *i){
			struct stat info;
			if(stat(i, &info) == 0)
				return 1;
			return 0;
		}
		static void gotoxy(int x, int y) 
		{ 
    		COORD coord;
    		coord.X = x; 
    		coord.Y = y;
    		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
		static string setNimDosen(string usr){
				string nim = usr;
				string patusr = nim+"/";
				string patnim = patusr+"no_induk.txt";
				string savelinenim;
				ifstream f;
				f.open(patnim);
				if(getline(f, savelinenim)){
					return savelinenim;		
				} else {
					return "FAIL TO LOAD";
				} 
		}
		static string setNamaMhs(string usr){
			string nim = usr;
				string patusr = nim+"/";
				string patnama = patusr+"nama.txt";
				string savelinenama;
				ifstream f;
				f.open(patnama);
				if(getline(f, savelinenama)){
					return savelinenama;		
				} else {
					return "FAIL TO LOAD";
				} 
		}
		static string setMatkul(string usr){
			string nim = usr;
			const char *usrtemp = nim.c_str();
			struct stat info;
			if(stat(usrtemp, &info) == 0){
				string patusr = nim+"/";
				string patmatkul = patusr+"matkul.txt";
				string savelinematkul;
				ifstream f;
				f.open(patmatkul);
				if(getline(f, savelinematkul)){
					return savelinematkul;		
				} else {
					return "FAIL TO LOAD";
				} 
			} return "FAIL TO LOAD";
		}
		static string setNimAndPass(string usr, string pass){
			string nim = Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_DOSEN::_NID_DOSEN+usr;
			const char *usrtemp = nim.c_str();
			struct stat info;
			if(stat(usrtemp, &info) == 0){
				string patusr = nim+"/";
				string patpass = patusr+"password.txt";
				string savelinepassword;
				ifstream f;
				f.open(patpass);
				if(getline(f, savelinepassword)){
					if(pass == savelinepassword){
						return "SUCCESSED";
					} else {
						return "FAILED";
					}
				} else {
					return "FAILED";
				}
			} else {
				return "FAILED";
			}
			return "FAILED";
		}
//		MENGAMBIL FIELD DARI FFIELD.TXT RETURN ARRAY
		static string *getField(string str){
			int i=0;
			string strtemp;
			string *field = new string[10];
			string dosen = Init::_PATH+str;
			string s = dosen+"ffield.txt";
			ifstream f;
			f.open(s);
			while (!f.eof()){
				getline(f, strtemp);
				field[i] = strtemp;
//				cout<<field[i];
				i++;
			}
			return field;
		}
//		MENGHITUNG LENGTH FIELD RETURN INT
		static int fieldSize(string str){
			int i=0,x=0;
			string *s = Init::getField(str);
			for(;;){
				if(s[x] == ""){
					break;
				} else if( x > 10){
					break;
				} else {
					i++;
				}
				x++;
			}
			return i;
		}
		static int dataSize(){
			int i=0,x=0;
			string dosen = Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_DOSEN::_NID_DOSEN;
			string *s = Init::readF(dosen);
			int m = 0;
    		while (!s[m].empty()){
				m++;
			}
    		return m;
		}
		static int dataSizeMhs(string patmhs){
			string *s = Init::readF(patmhs);
			int m = 0;
    		while (!s[m].empty()){
				m++;
			}
    		return m;
		}
		static string *getData(){
			string *data = new string[10];
			
			return data;
		}
//		RETURNING NIM ALL USER
		static string *readF(string pat){
			int i=0;
			string *arr = new string[100];
			DIR *g;
			struct dirent *name;
			if(( g = opendir(pat.c_str()) ) != NULL){
				while(( name = readdir(g) ) != NULL){
					if(strcmp(name->d_name, ".") != 0 && strcmp(name->d_name, "..") != 0 && strcmp(name->d_name, "ffield.txt") != 0 ){
						arr[i] = name->d_name;
						i++;
					}
				}
				closedir(g);					
			}
			return arr;
		}
};

string Init::_PATH = "DB/";
string Init::_DB = "amikom/";
string Init::_TABLE::_TABLE_DOSEN::_NID_DOSEN = "dosen/";
string Init::_TABLE::_TABLE_MHS::_NIM_MHS = "mahasiswa/";

class Index{
	
	public:
		Index(){
			drawTable();
		}
		string _USERNAME_DOSEN;
		string _USERNAME_MHS[65];
		string _MATKUL;
		string _PASSWORD_DOSEN;
		int _ABSEN,_NOMOR,TIME;
//		void setAuth(){
//			
//			return;		
//		}
		string err(){
			return "ERROR: ";
		}
		string inpUserMhs(){
			string input;
			if(getline(cin, input)) return input; else return this->err();
		}
		void inpUserDosen(){
			string input;
			if(getline(cin, input)) this->_USERNAME_DOSEN = input; else this->err();
		}
		void inpPwd(){
			string input;
			if(getline(cin, input)) this->_PASSWORD_DOSEN = input; else this->err();
		}
		string getAuth(){
			string status = Init::setNimAndPass(this->_USERNAME_DOSEN, this->_PASSWORD_DOSEN);
			if(status == "FAILED"){
				return "AUTH FAILED";
			} else {
				return "AUTH SUCCESSED";
			}
		}
		string getNidDosen(){
			return Init::setNamaMhs(Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_DOSEN::_NID_DOSEN+this->_USERNAME_DOSEN);
		}
		string getNamaMhs(int index){
			return Init::setNamaMhs(Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_MHS::_NIM_MHS+this->_USERNAME_MHS[index]);
		}
		string getMatkul(){
			return Init::setMatkul(Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_DOSEN::_NID_DOSEN+this->_USERNAME_DOSEN);
		}
		string setAbsen(string strpat){
			time_t t = time(0);
    		struct tm * now = localtime( & t );
			string tim;
			strpat+=".txt";
			return strpat;
		}
		void LoginComponent(){
		for(;;){
			for(int i=0;i<12;i++){
				for(int x=0;x<38;x++){
					if(i == 0 || i == 14){
						Init::gotoxy(20+x,8+i);
						cout<<"=";
					} else if(i == 2){
						Init::gotoxy(20+x,8+i);
						cout<<"=";
					} else if(i == 11){
						if( x != 0 ){
							Init::gotoxy(20+x,8+i);
							cout<<"\\";
						} else if (x != 37){
							Init::gotoxy(20+x,8+i);
							cout<<"\\";	
						} else {
							Init::gotoxy(20+x,8+i);
							cout<<"=";	
						}
					} else if(x == 0 || x == 37){
							Init::gotoxy(20+x,8+i);
							cout<<"|";
					}
				}
				cout<<endl;
			}
			Init::gotoxy(34,9); cout<<"LOGIN DOSEN";
			Init::gotoxy(24,12); cout<<"NID: ";
			Init::gotoxy(34,13); cout<<"----------------------";
			Init::gotoxy(24,15); cout<<"Password: ";
			Init::gotoxy(34,16); cout<<"----------------------";
			Init::gotoxy(34,12); this->inpUserDosen();
			Init::gotoxy(34,15); this->inpPwd();
			string auth = this->getAuth();
			if(auth == "AUTH SUCCESSED"){
				Init::gotoxy(24,17);
				cout<<"Checking "<<".";Sleep(500);cout<<".";Sleep(500);cout<<"."<<endl;Sleep(300);
				system("CLS");
				Init::gotoxy(34,9);
				cout<<"Loading "<<".";Sleep(500);cout<<".";Sleep(500);cout<<"."<<endl;Sleep(300);
				system("CLS");
				break;
			} else {
				Init::gotoxy(24,17);
				cout<<"Checking "<<".";Sleep(500);cout<<".";Sleep(500);cout<<"."<<endl;Sleep(300);
				Init::gotoxy(24,17);
				cout<<"Auth Failed ";
				cin.clear();
				getchar();
				system("CLS");
				continue;
			}
		}} // END LOOPING
		void AbsentComponent(){
			this->LoginComponent();
			for(int i=0;i<75;i++){
				for(int x=0;x<80;x++){
					if(i == 0 || i == 74){
						Init::gotoxy(0+x,0+i);
						cout<<"=";
					} else if(i == 2){
						Init::gotoxy(0+x,0+i);
						cout<<"=";
					} else if( i >= 3 && x == 25 ){
						Init::gotoxy(0+x,0+i);
						cout<<"|";
					} else if( x == 0 || x == 79 ){
						Init::gotoxy(0+x,0+i);
						cout<<"|";
					}
				}
				cout<<endl;
			}
			string th,kelas,id; int count=1;
			time_t t = time(0);
    		struct tm * now = localtime( & t );
			Init::gotoxy(32,1); cout<<"PRESENSI MAHASISWA";
			Init::gotoxy(2,4); cout<<"DOSEN : ";
			Init::gotoxy(5,6); cout<<this->getNidDosen();
			Init::gotoxy(1,8); cout<<"------------------------";
			Init::gotoxy(2,10); cout<<"MATKUL: ";
			Init::gotoxy(5,12); cout<<this->getMatkul();
			Init::gotoxy(1,14); cout<<"------------------------";
			Init::gotoxy(2,16); cout<<"TANGGAL: \tWAKTU: ";
			Init::gotoxy(15,18);cout<<"60 MENIT";
			Init::gotoxy(2,18); cout<<now->tm_mday<<"-"<<(now->tm_mon + 1)<<"-"<<(now->tm_year + 1900);
			Init::gotoxy(1,20); cout<<"------------------------";
			Init::gotoxy(2,22); cout<<"INPUT NIM";
			Init::gotoxy(1,26); cout<<"------------------------";
			Init::gotoxy(2,28);cout<<"JUMLAH MHS (SI-06):";
			Init::gotoxy(5,30);cout<<Init::dataSizeMhs(Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_MHS::_NIM_MHS);
			Init::gotoxy(1,32);cout<<"------------------------";
			Init::gotoxy(2,34);cout<<"MHS YG ABSEN:";
			Init::gotoxy(5,36);cout<<0;
			Init::gotoxy(1,38);cout<<"------------------------";
			Init::gotoxy(2,40);cout<<"RUANG:";
			Init::gotoxy(5,42);cout<<"R.4.4.2";
			Init::gotoxy(1,44);cout<<"------------------------";
			Init::gotoxy(7,46);cout<<"UNIVERSITAS";
			Init::gotoxy(4,48);cout<<"AMIKOM YOGYAKARTA";
			Init::gotoxy(2,50);cout<<"=====================";  
			Init::gotoxy(27,3);cout<<"No.";
			Init::gotoxy(35,3);cout<<"Nama";
			Init::gotoxy(54,3);cout<<"NIM";
			Init::gotoxy(67,3);cout<<"Tanggal";
			Init::gotoxy(26,4); 
			for(int i=0;i<53;i++)
				cout<<"-";
//			INPUT NIM MHS
			for(;;){
				if(count>65){
					Init::gotoxy(41,24);cout<<"MAHASISWA MELEBIHI BATAS";		
				}
				Init::gotoxy(1,24);cout<<"->";
//				cin.clear();
				Init::gotoxy(5,24); this->_USERNAME_MHS[count] = this->inpUserMhs();
				if(this->_USERNAME_MHS[count].find("del") != string::npos){
					if(count-1 > 0){
						this->_USERNAME_MHS[count] = this->_USERNAME_MHS[count].substr(4);
						for(int rangecheck = 0 ;rangecheck < count ; ++rangecheck){
							if(this->_USERNAME_MHS[rangecheck] == this->_USERNAME_MHS[count]){
								for(int repl = rangecheck ; repl < count ; repl++){
									if(repl == count-1){
										Init::gotoxy(27,5+repl);cout<<"       ";
										Init::gotoxy(35,5+repl);cout<<"               ";
										Init::gotoxy(54,5+repl);cout<<"            ";
										Init::gotoxy(67,5+repl);cout<<"           ";
										Init::gotoxy(2,25);cout<<"Absen Berhasil Dihapus";
										getchar();
									} else {
										Init::gotoxy(27,5+repl);cout<<repl<<".";
										Init::gotoxy(35,5+repl);cout<<this->getNamaMhs(repl+1);
										Init::gotoxy(54,5+repl);cout<<this->_USERNAME_MHS[repl+1];
										Init::gotoxy(67,5+repl);cout<<now->tm_mday<<"-"<<(now->tm_mon + 1)<<"-"<<(now->tm_year + 1900);
									}
								}
								break;							
							}
						}
						count-=1;
						Init::gotoxy(5,24);cout<<"                ";
						Init::gotoxy(2,25);cout<<"                      ";
						continue;
					} else {
						Init::gotoxy(5,25);cout<<"NIM TIDAK VALID";getchar();
							for(int ix=0;ix<16;ix++){
								Init::gotoxy(5+ix,24);
								cout<<" ";
							}
							Init::gotoxy(5,25);cout<<"                ";
						continue;
					}
				}
				string cpath = Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_MHS::_NIM_MHS+this->_USERNAME_MHS[count];
				int l = Init::checkNim(cpath.c_str());
				int cekygsudhabsen = 0;
				for(int cek=0;cek<count;cek++){
					if(this->_USERNAME_MHS[cek] == this->_USERNAME_MHS[count]){
						cekygsudhabsen = cek;
						break;
					}
				}
				if(cekygsudhabsen>0){
					Init::gotoxy(5,25);cout<<"SUDAH PRESENSI";
//						NGAPUS OUTPUT
						getchar();
						for(int ix=0;ix<16;ix++){
							Init::gotoxy(5+ix,24);
							cout<<" ";
						}
						Init::gotoxy(5,25);cout<<"                ";
					continue;
				} else if(l == 0){
					Init::gotoxy(5,25);cout<<"NIM TIDAK VALID";
//					NGAPUS OUTPUT
					getchar();
					for(int ix=0;ix<16;ix++){
						Init::gotoxy(5+ix,24);
						cout<<" ";
					}
					Init::gotoxy(5,25);cout<<"                ";
				} else {
					string strpat = this->setAbsen(Init::_PATH+Init::_DB+Init::_TABLE::_TABLE_MHS::_NIM_MHS+this->_USERNAME_MHS[count]+"/"+"kuliah");
					  std::ofstream ofs;
  					ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);
					ofstream f;
					f.open(((strpat.c_str())), ofstream::out | ofstream::app);
					f<<now->tm_mday<<"-"<<(now->tm_mon + 1)<<"-"<<(now->tm_year + 1900)<<"\n";
					f.close();
					Init::gotoxy(27,5+count);cout<<count<<".";
					Init::gotoxy(35,5+count);cout<<this->getNamaMhs(count);
					Init::gotoxy(54,5+count);cout<<this->_USERNAME_MHS[count];
					Init::gotoxy(67,5+count);cout<<now->tm_mday<<"-"<<(now->tm_mon + 1)<<"-"<<(now->tm_year + 1900);
//					NGAPUS OUTPUT
					Init::gotoxy(5,24);cout<<"               ";
					Init::gotoxy(5,25);cout<<"            ";
					Init::gotoxy(5,36);cout<<count;
					count++;
				}
//				NGAPUS INPUT
			}
		}
		void drawTable(){
			this->AbsentComponent();
		}
		
};
int main(void){
	new Index();
//	main.drawTable();
}

#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <windows.h>
#include <direct.h>
#include <algorithm>
#include <iterator> 
#include <bits/stdc++.h> 
#include <fstream>
#include <dirent.h>
#include <cstdlib>
#include <sys/types.h>
//	STRUCT STAT
#include <sys/stat.h>
#include <string>
//#include<string>
using namespace std; 
class Build
{
/*
*	MEMBUAT CONFIGURASI UNTUK DATABASE:
*	SETTING PATH
*	COMMAND DATABASE
*	ACCESS MODIFIER PUBLIC
*/
	public:
	string _PATH;
	string _COMMAND;
	string _AVAILCOMMANDS[6][2];
	string _DB_NAME,_DB_NAME_SELECTED;
//	string _TABLE_NAME[10],_TABLE_NAME_SELECTED;
	struct _TABLE{
		string _TABLE_NAME[5];
		string _TABLE_SELECTED;
		struct _TABLE_LIST{
			string _FIELDS[10];
			string _DATA_MEMBER[10][2];
		}_BUILD_TABLE_LIST;
	}_BUILD_TABLE_NAME;
	
/*
*	CORE FUNCTION
*/
	string error(){
		return "AN ERROR OCCURED!";
	}
	void describeCommands1(){
		this->createLine(79);
		this->createTextLine("COMMANDS: ",17, 79);
		this->createLine(79);
		this->createTextLine(" ",17, 79);
		this->createTextLine("1. create database",22, 79);
		this->createTextLine("2. select db"+this->_AVAILCOMMANDS[1][0],22, 79);
		this->createTextLine("3. list db",22, 79);
		this->createTextLine(" ",17, 79);
		this->createLine(79);
	}
	void describeCommands2(){
		this->createLine(79);
		this->createTextLine("COMMANDS: ",17, 79);
		this->createLine(79);
		this->createTextLine(" ",17, 79);
		this->createTextLine("1. create table",22, 79);
		this->createTextLine("2. select table"+this->_AVAILCOMMANDS[3][0],22, 79);
		this->createTextLine("3. list table",22, 79);
		this->createTextLine(" ",17, 79);
		this->createLine(79);
	}
	void describeCommands3(){
		this->createLine(79);
		this->createTextLine("COMMANDS: ",17, 79);
		this->createLine(79);
		this->createTextLine(" ",17, 79);
		this->createTextLine("1. create field",22, 79);
		this->createTextLine("2. insert"+this->_AVAILCOMMANDS[3][0],22, 79);
		this->createTextLine(" ",17, 79);
		this->createLine(79);
//		oTable("5. "+this->_AVAILCOMMANDS[4][0]+"\t6. "+this->_AVAILCOMMANDS[5][0], 2, 22, false);
	}
	void explode(const string &cmd, char c, vector<string> &elems) {
    	stringstream ss(cmd);
    	string item;
    	while (getline(ss, item, c)) {
        	elems.push_back(item);
    	}
	}
//	EXPLODE STRING
//	vector<string> split(const string &cmd, char c) {
//    	vector<string> elems;
//    	explode(cmd, c, elems);
//    	return elems;
//	}
//	INPUT CONSOLE
	int checkCommand(string cmd)
	{
		string list[] = {"create database","create table","create field","insert","select db","select table", "list db", "list table"};
		int action = 
		cmd == list[0]? 1: 
		cmd == list[1]? 2: 
		cmd == list[2]? 3: 
		cmd == list[3]? 4: 
		cmd == list[4]? 5: 
		cmd == list[5]? 6:
		cmd == list[6]? 7:
		cmd == list[7]? 8:-1;
		return action; 		
	}
//	DOCUMENT ROOT
	string defaultPath(){
    	return "DB/";
	}
//	KALAU MAU GANTI PATH
	void setPath(string path){
		this->_PATH = path;
	}
//	CONVERT STRING KE KONSTANTA CHAR
	const char *conv(string re){
		string temp = re;
//		const char *p = temp.c_str();
		return temp.c_str();
	}
	
	string inp(){
		string str;
		if(getline(cin,str)) return str; else return "error";
	}
	int pathExist(const char *path){
		struct stat info;
		if(stat(path, &info) == 0)
			return 1;
		return 0;
			
	}
	bool fileExist(const char *filename)
	{
  		ifstream ifile(filename);
  		return ifile;
	}
	int fieldSize(){
		int i=0;
		for(string x :this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS){
			if(x == "") break;
			i++;
		}
		return i;
	}
/*
	void oTable(string out, int line, int middle, bool end){
		int strSize = out.size()-1;
		if(end == true){
			for(int i=0;i<2+line;i++){
				cout<<" ";
				for(int x=0;x<78;x++){
					if(i==1){
						if(x==0){
							cout<<"|";
						} else if (x == 77-strSize){
							cout<<"|"<<endl;break;
						}
						else if(x==middle){
							cout<<out;
						}
						else {
							cout<<" ";
						}
					} else {
						cout<<"-";
					}
				}
				if(i != 1 || i != line){
					cout<<endl;
				}
			}
		}
		else {
			for(int i=0;i<2;i++){
				cout<<" ";
				for(int x=0;x<78;x++){
					if(i==0){
						if(x==0){
							cout<<"|";
						} else if (x == 77-strSize){
							cout<<"|"<<endl;break;
						}
						else if(x==middle){
							cout<<out;
						}
						else {
							cout<<" ";
						}
					} else {
						cout<<"-";
					}
				}
				if(i == 2){
					cout<<endl;
				}
			}
		}
	}
*/
	void createLine(int end){
		for(int i=0;i<end;i++){
			if(i==0){
				cout<<" ";
			} else if(i == end-1){
				cout<<"-"<<endl;
			} else {
				cout<<"-";
			}
		}
	}
	void createTextLine(string out, int middle, int end){
		int strSize = out.size();
		cout<<" ";
		for(int x=0;x<end;x++){
			if(x==0){
				cout<<"|";
			} else if (x == (end-1)-strSize){
				cout<<"|"<<endl;break;
			}
			else if(x==middle){
				cout<<out;
			}
			else {
				cout<<" ";
			}
		}
	}
/*
*	FUNGSI CREATE DATABASE
*	FUNGSI SELECT DATABASE
*	FUNGSI LIST DATABASE
*	FUNGSI CREATE TABLE
*	FUNGSI SELECT TABLE
*	FUNGSI LIST TABLE
*	FUNGSI INSERT DATA 
*/
	void setDatabase(){
		cout<<"  NAMA DATABASE: "<<endl<<"  -> ";
		this->_DB_NAME = this->inp();
//		cin.ignore();
		cout<<"  creating db .";Sleep(500);cout<<".";Sleep(100);cout<<"."<<endl;Sleep(100);
		if(!mkdir(this->conv(this->defaultPath()+this->_DB_NAME)) ){
			cout<<endl<<"  DATABASE "<<this->_DB_NAME<<" BERHASIL DIBUAT."<<endl<<endl;
		} else {
			cout<<"  DATABASE EXIST"<<endl<<endl;
		}
	}
	void listDB(){
		cout<<"  melihat database yang ada .";Sleep(500);cout<<".";Sleep(500);cout<<"."<<endl;Sleep(100);
		cout<<"  menghitung jumlah database .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(100);
		int i=0;
		this->createLine(79);
		this->createTextLine("LIST DATABASES: ",17, 79);
		this->createLine(79);
		DIR *ldb;
        struct dirent *entry;
        if( (ldb=opendir(conv(this->defaultPath()))) != NULL ){
            while ((entry = readdir (ldb)) != NULL) {
    			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
					this->createTextLine(to_string(i+1)+". "+entry->d_name,22, 79);
    				i++;
				}
  			}
  			this->createTextLine(" ",17, 79);
			this->createLine(79);
            closedir(ldb);
        }
        cout<<"  DATABASES: "<<i<<endl<<endl;
	}
	void setTable(){
		if(this->_DB_NAME_SELECTED == "") {
			cout<<"  HARUS MEMILIH DATABASE TERLEBIH DAHULU"<<endl<<endl;
			return;
		}
		int i,x,s=0;
		cout<<"  JUMLAH TABLE <int>: "<<endl;
		cout<<"  -> ";
		cin>>i;
		cin.ignore();
		cout<<"  prepare from database "<<this->_DB_NAME_SELECTED<<" .";Sleep(500);cout<<".";Sleep(100);cout<<"."<<endl;Sleep(100);
		for(x=0;x<i;x++){
			cout<<"  NAMA TABLE: "<<endl;
			cout<<"  "<<x+1<<". -> "<<" ";
//			this->_TABLE_NAME[x] = this->inp();
			this->_BUILD_TABLE_NAME._TABLE_NAME[x] = this->inp();
//			string tmp = this->_BUILD_TABLE_NAME._TABLE_NAME[x];
//			tmp[0] = toupper(tmp[0]);
			if(!mkdir(this->conv(this->_PATH+this->_BUILD_TABLE_NAME._TABLE_NAME[x])) ){
				cout<<"  creating table "<<this->_BUILD_TABLE_NAME._TABLE_NAME[x]<<" .";Sleep(600);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(200);
				s++;
			} else {
				cout<<"  TABLE "<<this->_BUILD_TABLE_NAME._TABLE_NAME[x]<<" SUDAH ADA"<<endl<<endl;
			}
		}
		x=0;
		if(s>0){
			cout<<"  "<<s<<" TABEL DITAMBAHKAN ";
			while(x<i){
				cout<<this->_BUILD_TABLE_NAME._TABLE_NAME[x];
				if(x!=i-1){
					cout<<", ";
				}
				x++;
			}
			cout<<endl<<endl;
		} else {
			cout<<"  "<<s<<" TABEL DITAMBAHKAN"<<endl<<endl;
		}
	}
	void listTable(){
		cout<<"  melihat table yang ada .";Sleep(500);cout<<".";Sleep(500);cout<<"."<<endl;Sleep(100);
		cout<<"  menghitung jumlah table .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(100);
		int i=0;
		this->createLine(79);
		this->createTextLine("LIST TABLES: ",17, 79);
		this->createLine(79);
		DIR *ldb;
        struct dirent *entry;
        if( (ldb=opendir(conv(this->defaultPath()+this->_DB_NAME_SELECTED+"/"))) != NULL ){
            while ((entry = readdir (ldb)) != NULL) {
    			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
					this->createTextLine(to_string(i+1)+". "+entry->d_name,22, 79);
    				i++;
				}
  			}
  			this->createTextLine(" ",17, 79);
			this->createLine(79);
            closedir(ldb);
        }
        cout<<"  TABLES: "<<i<<endl<<endl;
	}
	void setField(){
		string id;
		if(this->_BUILD_TABLE_NAME._TABLE_SELECTED == "") {
			cout<<"  HARUS MEMILIH TABLE TERLEBIH DAHULU"<<endl<<endl;
			return;
		}
		int i,x=0;
		cout<<"  JUMLAH FIELDS <int>: "<<endl;
		cout<<"  -> ";
		cin>>i;
		cin.ignore();
		if(i>10){cout<<error();return this->setField();}
		ofstream f;
//		f.open(this->conv(this->_PATH+".txt"), ios_base::app);
		int j[] = {0,0,0,0};
		cout<<"  prepare from table "<<this->_BUILD_TABLE_NAME._TABLE_SELECTED<<" .";Sleep(500);cout<<".";Sleep(100);cout<<"."<<endl;Sleep(100);
		cout<<"  NAMA FIELD: "<<endl;
		for(x;x<i;x++){
			cout<<"  "<<x+1<<". -> ";
			this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] = this->inp();
//			this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][0];
			if(this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] == "tahun_masuk"){
				j[0] = 1;
			}
			else if(this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] == "kode_kelas"){
				j[1] = 1;
			}
			else if(this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] == "id"){
				j[2] = 1;
			}
			else if(this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] == "no_induk"){
				j[3] = 1;
			}
			if(x == (i-1)){
				cout<<"  checking field "<<" .";Sleep(500);cout<<".";Sleep(400);cout<<"."<<endl;Sleep(300);
				for(x=0;x<4;x++){
					if(j[x] == 0) {
						cout<<"  HARUS ADA FIELD tahun_masuk,kode_kelas,id,no_induk"<<endl<<"  PROGRAM TERMINATED"<<endl<<endl;
						return;
					}
				}
				cout<<"  creating fields "<<" .";Sleep(500);cout<<".";Sleep(100);cout<<"."<<endl;Sleep(100);
				const char* createfield = conv(this->_PATH+"ffield"+".txt");
				ofstream f(conv(createfield));
				for(x=0;x<i;x++){
					f<<this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x];
					if(x < (i-1)) f<<"\n";
				}
				break;
			}
//			this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x] = this->inp();
//			f<<this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[x];
//			if(x == (i-1)) f<<"\n"; else f<<",";
		}
		cout<<"  "<<i<<" FIELDS BERHASIL DITAMBAHKAN"<<endl<<endl;
		
	}
	void setData(){
//		int i,x=0,size = my_sizeof(this->_FIELD)/my_sizeof(this->_FIELD[0]); 
//		cout<<"PROCESS"<<endl;
		string readfield[10];
		if(!fileExist(this->conv(this->_PATH+"ffield.txt"))){
			cout<<"  FIELD BELUM DI BUAT"<<endl;
			return;
		} else {
			int tid=0,ttm=0,tkk=0,tnim=0;
			int i,x,l=this->fieldSize(),nid=0;
			cout<<"  prepare fields "<<" .";Sleep(500);cout<<".";Sleep(100);cout<<"."<<endl;Sleep(100);
			cout<<"  JUMLAH DATA max(10): "<<endl;
			cout<<"  -> ";
			cin>>i;
			cin.ignore();
			cout<<"  INSERT DATA INTO "<<this->_BUILD_TABLE_NAME._TABLE_SELECTED<<endl;
//			cout<<fieldSize();
			for(x=0;x<i;x++){
				int fieldSize=0,q=0;
				string id,th,kode,nim;
				while(fieldSize<l){
					readfield[fieldSize] = this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[fieldSize];
					if(readfield[fieldSize] == "id"){
						this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fieldSize] = to_string(100 + rand() % 899);
						tid = q;
					} else if(readfield[fieldSize] == "tahun_masuk"){
						cout<<"  "<<readfield[fieldSize]<<" -> ";this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fieldSize] = this->inp();
						ttm = q;
					} else if(readfield[fieldSize] == "kode_kelas"){
						cout<<"  "<<readfield[fieldSize]<<" -> ";this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fieldSize] = this->inp();
						tkk = q;
					} else if(readfield[fieldSize] == "no_induk"){
						this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fieldSize] = "";
						tnim = q;
					}
					else {
						cout<<"  "<<readfield[fieldSize]<<" -> ";this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fieldSize] = this->inp();
					}
//					this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[fieldSize];
					fieldSize++;q++;
				}
				cout<<"  gettin' tahun_masuk, kode_kelas, id information "<<" .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(300);
				id = this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tid];
				th = this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][ttm];
				kode = this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tkk];
				cout<<"  generatin' no_induk from tahun_masuk, kode_kelas, id information "<<" .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(300);
				this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tnim] = th.substr(2)+"."+kode+"."+"0"+id;
				nim = this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tnim];
				if(!mkdir(conv(this->_PATH+nim))){
					cout<<"  finishin' information "<<" .";Sleep(200);cout<<".";Sleep(200);cout<<"."<<endl;Sleep(200);
					for(int fs=0;fs<l;fs++){
						ofstream ins(this->_PATH+nim+"/"+this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._FIELDS[fs]+".txt");
						ins<<this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][fs];
					}
					cout<<"  DATA BERHASIL DITAMBAHKAN"<<endl<<endl;
				} else {
					cout<<"  finishin' information "<<" .";Sleep(200);cout<<".";Sleep(200);cout<<"."<<endl;Sleep(200);
					cout<<"  GAGAL MENAMBAHKAN"<<endl<<endl;
				}
				nid++;
			}
			
//			string id="",th="",kode="";
//				this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tnim] = th.substr(2)+"."+kode+"."+id+to_string(x+1);
//				cout<<"NIM KE-"<<x<<this->_BUILD_TABLE_NAME._BUILD_TABLE_LIST._DATA_MEMBER[x][tnim]<<endl;
		}
	}
	
	void selectDB(){
//		this->listDB();
		cout<<"  SELECT : "<<endl;
		cout<<"  -> ";
		this->_DB_NAME_SELECTED = this->inp();
		cout<<"  checking database .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(100);
		if(this->pathExist(conv(this->defaultPath()+this->_DB_NAME_SELECTED)) == 1){
			cout<<"  selecting database .";Sleep(400);cout<<".";Sleep(400);cout<<"."<<endl;Sleep(400);
			this->_PATH = this->defaultPath()+this->_DB_NAME_SELECTED+"/";
			cout<<"  "<<this->_DB_NAME_SELECTED<<" SELECTED"<<endl<<endl;	
		} else {
			this->_DB_NAME_SELECTED = "";
			cout<<"  NAMA DATABASE SALAH"<<endl<<endl;
		}
	}
	void selectTable(){
		cout<<"  SELECT : "<<endl;
		cout<<"  -> ";
		this->_BUILD_TABLE_NAME._TABLE_SELECTED = this->inp();
		cout<<"  checking table .";Sleep(500);cout<<".";Sleep(300);cout<<"."<<endl;Sleep(100);
		if(this->pathExist(conv(this->_PATH+this->_BUILD_TABLE_NAME._TABLE_SELECTED)) == 1){
			cout<<"  selecting table .";Sleep(400);cout<<".";Sleep(400);cout<<"."<<endl;Sleep(400);
			this->_PATH+=this->_BUILD_TABLE_NAME._TABLE_SELECTED+"/";
			cout<<"  "<<this->_BUILD_TABLE_NAME._TABLE_SELECTED<<" SELECTED"<<endl<<endl;	
		} else {
			this->_BUILD_TABLE_NAME._TABLE_SELECTED = "";
			cout<<"  NAMA TABLE SALAH"<<endl<<endl;
		}
	}
/*
*	FUNGSI INPUTAN CONSOLE
*	UNTUK PILIH MENU
*/		
	void getCommand()
	{
		this->createLine(79);
		this->createTextLine("MINI DATABASE", 32, 79);
		this->createLine(79);
		for(;;){ 
		int num = -1;
		if(this->_DB_NAME_SELECTED == "" && this->_BUILD_TABLE_NAME._TABLE_SELECTED == ""){
			this->describeCommands1();
			cout<<"  DATABASE Command: ";
			getline(cin,this->_COMMAND);
			num = this->checkCommand(this->_COMMAND);
			if (num == 2 || num == 3 || num == 4 || num == 6) continue;
		} else if(this->_DB_NAME_SELECTED != "" && this->_BUILD_TABLE_NAME._TABLE_SELECTED == ""){
			this->describeCommands2();
			cout<<"  DATABASE Command: "<<_DB_NAME_SELECTED<<"> ";
			getline(cin,this->_COMMAND);
			num = this->checkCommand(this->_COMMAND);
			if(num == 1 || num == 5) continue;
		} else if(this->_DB_NAME_SELECTED != "" && this->_BUILD_TABLE_NAME._TABLE_SELECTED != ""){
			this->describeCommands3();
			cout<<"  DATABASE Command: "<<_DB_NAME_SELECTED<<">"<<this->_BUILD_TABLE_NAME._TABLE_SELECTED<<">";
			getline(cin,this->_COMMAND);
			num = this->checkCommand(this->_COMMAND);
			if(num == 1 || num == 2 || num == 5 || num == 6) continue;
		}
		switch(num){
			case 1:{
				this->setDatabase();
				break;
			}
			case 2:{
				this->setTable();
				break;
			}
			case 3:{
				this->setField();
				break;
			}
			case 4:{
				this->setData();
				break;
			}
			case 5:{
				this->selectDB();
				break;
			}
			case 6:{
				this->selectTable();
				break;
			}
			case 7:{
				this->listDB();
				break;
			}
			case 8:{
				this->listTable();
				break;
			}
			default:{
				cout<<"COMMAND NOT FOUND"<<endl;
				break;
			}
		}
		}
//		cout<<this->COMMAND;	
	}
	
};
int main(void)
{
	Build inp;
//	inp.commands();
	inp.getCommand();
}

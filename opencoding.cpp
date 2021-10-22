#include <iostream>
using namespace std;

int main() {
	int a;
	char* b[3][2] = {
		{
			"",
			"C:\\Users\\A Little Shit\\AppData\\Local\\Programs\\Opera\\launcher.exe" 
		},
		{
			"",
			"C:\\xampp\\xampp-control.exe"
		},
		{
			"",
			"C:\\Program Files\\Sublime Text 3\\sublime_text.exe"		
		},
	};
	
	
	cout << "Program: " << endl;
	cout << "1. Browser " << endl;
	cout << "2. Code Editor " << endl;
	cout << "3. Xampp " << endl;
	cout << "4. All" << endl << endl;
	
	cout << "Program: (1/2/3/4) "; cin >> a;
	
	cout << endl;
	
	if(a == 1) {
		const char* c = new Char(strlen(b[0][0]) + strlen(b[0][1]));
		system(c);	
	} else if(a == 2) {
		c = b[1][0] + b[1][1];
		system(c);
	} else {
		for(int i=0;i<3;i++) {
			for (int j=0;j<2; j++) {
				c += b[i][j];
			}
			system(c);
			c = "";
		}
	}
	return 0;
}

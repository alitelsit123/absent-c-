#include <iostream>
#include "makhlukhidup.h"
#include "submakhlukhidup.h"
#include "submakhlukhidup.cpp"

class tumbuhan: public makhlukhidup
{
	public:
		void berdiri()
		{
			std::cout << "Tumbuhan berdiri menggunakan : " << "Akar" << std::endl;
		}
		void butuh()
		{
			std::cout << "- butuh Makanan" << std::endl;
			std::cout << "- butuh Oksigen" << std::endl;
			std::cout << "- butuh Air" << std::endl;
		};
};

main()
{
	manusia m;
	hewan h;
	tumbuhan t;
	m.berdiri();
	m.butuh();
	h.berdiri();
	h.butuh();
	t.berdiri();
	t.butuh();
}

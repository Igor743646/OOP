#ifndef MONEY_HPP
#define MONEY_HPP

struct Money{
	unsigned long long rubles;
	unsigned char kopeks;
	Money(): rubles(0), kopeks(0) {};
	Money(unsigned long long rub, unsigned char kop): rubles(rub + kop/100), kopeks(kop%100) {};
	Money operator+(const Money &rhv);
	Money operator-(const Money &rhv);
	Money operator*(const Money &rhv);
	Money operator/(const Money &rhv);
	Money operator*(const double &rhv);
	Money operator/(const double &rhv);
	bool operator<=(const Money &rhv);
    bool operator>=(const Money &rhv);
    bool operator<(const Money &rhv);
    bool operator>(const Money &rhv);
    bool operator==(const Money &rhv);
    
};

Money Money::operator+(const Money &rhv) {
	return Money(rubles+rhv.rubles + (kopeks+rhv.kopeks)/100, (kopeks+rhv.kopeks)%100);
}

Money Money::operator-(const Money &rhv) {
	if (rubles<rhv.rubles) {
		std::cout << "\nВычитание из меньшего числа\n";
		throw "Вычитание из меньшего числа";
	}
	if (kopeks<rhv.kopeks) {
		return Money(rubles-rhv.rubles-1, kopeks+100-rhv.kopeks);
	} else {
		return Money(rubles-rhv.rubles, kopeks-rhv.kopeks);
	}
}

Money Money::operator*(const Money &rhv) {
	unsigned int a= (unsigned int) kopeks*(unsigned int) rhv.kopeks;
    return Money(rubles*rhv.rubles + (kopeks*rhv.kopeks)/100, (unsigned char)(a%100));
}

Money Money::operator/(const Money &rhv) {
	if (rhv.kopeks==0 || rhv.rubles==0) {
		std::cout << "\nДеление на ноль!\n";
		throw "Деление на ноль!";
	}
    return Money(rubles/rhv.rubles, kopeks/rhv.kopeks);
}

Money Money::operator*(const double &rhv) {
    return Money(rubles*rhv + (kopeks*rhv)/100, (unsigned char)((unsigned int)(kopeks*rhv)%100));
}

Money Money::operator/(const double &rhv) {
	if (rhv==0) {
		std::cout << "\nДеление на ноль!\n";
		throw "Деление на ноль!";
	}
    return Money(rubles/rhv, kopeks/rhv);
}

bool Money::operator<=(const Money &rhv) {
	return ((rubles<=rhv.rubles && kopeks<=rhv.kopeks) || (rubles<rhv.rubles));
}

bool Money::operator>=(const Money &rhv) {
	return ((rubles>=rhv.rubles && kopeks>=rhv.kopeks) || (rubles>rhv.rubles));
}

bool Money::operator<(const Money &rhv) {
	return (rubles<rhv.rubles || (rubles==rhv.rubles && kopeks<rhv.kopeks));
}

bool Money::operator>(const Money &rhv) {
	return (rubles>rhv.rubles || (rubles==rhv.rubles && kopeks>rhv.kopeks));
}

bool Money::operator==(const Money &rhv) {
	return (rubles==rhv.rubles && kopeks==rhv.kopeks);
}



std::istream& operator>>(std::istream& in, Money &rval) {

    unsigned long long rub;
	unsigned int kop;

    while (1) {
	    in >> rub >> kop;
	    if (std::cin.fail()) {
	        std::cin.clear();
	        std::cin.ignore(32767,'\n');
	        std::cout << "Неправильный ввод. Попробуйте снова: ";
	    } else {
	    	break;
	    }
	}

    rval.rubles = rub + kop/100;
    rval.kopeks = kop%100;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Money &rval) {
	if (rval.kopeks < 10) return out << rval.rubles << ","  << "0" << (short) rval.kopeks;
    return out << rval.rubles << "," << (short) rval.kopeks;
}

Money operator""_mon(const char* string, std::size_t size) {
	unsigned long long rubles = 0;
	unsigned int kopeks = 0;

	int i = 0;
	while (i<(int)size && string[i]!=',') {
		rubles = rubles*10 + string[i] - '0';
		++i;
	}
	++i;
	while (i<(int)size) {
		kopeks = kopeks*10 + string[i] - '0';
		++i;
	}

	return Money(rubles + (unsigned char) (kopeks/100), (unsigned char) (kopeks%100));
}

#endif
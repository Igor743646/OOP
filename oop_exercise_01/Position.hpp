#ifndef POSITION_HPP
#define POSITION_HPP

struct Position {
    int latitude; // широта в диапозоне от -180 до 180
    int longitude; // долгота в диапозоне от -90 до 90
    Position(): latitude(0), longitude(0) {};
    Position(int lat, int lon);
    ~Position(){};
    Position operator+(Position rval);
    Position operator-(Position rval);
    Position operator*(int rval);
    Position operator/(int rval);
    bool operator<=(Position rval);
    bool operator>=(Position rval);
    bool operator<(Position rval);
    bool operator>(Position rval);
    bool operator==(Position rval);
};

int AlignLatitude(int lat) {
    lat%=360;
    if (lat%360>=-180 and lat%360<=180) return lat;
    if (lat>180) return lat - 360;
    if (lat<180) return lat + 360;
    return 0;
}

int AlignLongitude(int lon) {
    lon%=360;
    if (lon>=-90 and lon<=90) return lon;
    if (lon>90 and lon<=270) return 180-lon;
    if (lon>270 and lon<360) return lon-360;
    if (lon>=-360 and lon<=-270) return 360+lon;
    if (lon>-270 and lon<-90) return -(lon+180);
    return 0;
}

Position::Position(int lat, int lon): latitude(AlignLatitude(lat)), longitude(AlignLongitude(lon)) {}

Position Position::operator+(Position rval) {
    return Position(AlignLatitude(latitude+rval.latitude), AlignLongitude(longitude+rval.longitude));
}

Position Position::operator-(Position rval) {
    return Position(AlignLatitude(latitude-rval.latitude), AlignLongitude(longitude-rval.longitude));
}

Position Position::operator*(int rval) {
    return Position(AlignLatitude(latitude*rval), AlignLongitude(longitude*rval));
}

Position Position::operator/(int rval) {
	if (!rval) {
		std::cout << "Деление на ноль! ";
		return Position(AlignLatitude(latitude), AlignLongitude(longitude));
	}
    return Position(AlignLatitude(latitude/rval), AlignLongitude(longitude/rval));
}

std::istream& operator>>(std::istream& in, Position& rval) {
    int a, b;
    while (1) {
	    in >> a >> b;
	    if (std::cin.fail()) {
	        std::cin.clear();
	        std::cin.ignore(32767,'\n');
	        std::cout << "Неправильный ввод. Попробуйте снова: ";
	    } else {
	    	break;
	    }
	}
    
    std::cout << a << b <<std::endl; 
    rval.latitude = AlignLatitude(a);
    rval.longitude = AlignLongitude(b);
    return in;
}

bool Position::operator<(Position rval) {
    return (latitude<rval.latitude) && (longitude<rval.longitude);
}

bool Position::operator>(Position rval) {
    return ((latitude>rval.latitude) && (longitude>rval.longitude));
}

bool Position::operator<=(Position rval) {
    return ((latitude<rval.latitude) && (longitude<rval.longitude)) || ((latitude==rval.latitude) && (longitude==rval.longitude));
}

bool Position::operator>=(Position rval) {
    return ((latitude>rval.latitude) && (longitude>rval.longitude)) || ((latitude==rval.latitude) && (longitude==rval.longitude));
}

bool Position::operator==(Position rval) {
    return (latitude==rval.latitude) && (longitude==rval.longitude);
}

std::ostream& operator<<(std::ostream& out, const Position& rval) {
    return out << rval.latitude << " " << rval.longitude;
}

#endif
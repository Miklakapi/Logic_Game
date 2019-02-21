#include "MapReader.hpp"

MapReader::MapReader(){
	type = new Square::Type[198];
}

void MapReader::loadLV(int lv) {
	string file = "LVs/LV" + to_string(lv) + ".txt";
	fstream stream(file, ios::in);
	if (!stream.is_open()) {
		fstream error("error.txt", ios::out);
		error << file << " is not exist.\n";
		error.close();
		exit(0);
		return;
	}
	int nr(0);
	for (int y = 0; y < 11; y++) {
		string line;
		getline(stream, line);
		for (int x = 0; x < 18; x++) {
			switch (line.at(x)) {
			case '#':
				*(type + nr) = Square::Type::Wall;
				break;
			case '-':
				*(type + nr) = Square::Type::Empty;
				break;
			default:
				fstream error("error.txt", ios::out);
				error << "Error in " << file << " in the " << y << " row.\n";
				stream.close();
				error.close();
				exit(0);
				break;
			}
			nr++;
		}
	}
	stream.close();
	actualLv = lv;
}

void MapReader::renderLV(Square* square) {
	for (int i = 0; i < 198; i++) {
		(square + i)->setType(*(type + i));
	}
}

void MapReader::renderLV(int lv, Square* square) {
	loadLV(lv);
	renderLV(square);
}

int MapReader::getActualLV() {
	return actualLv;
}

MapReader::~MapReader() {
	delete [] type;
}
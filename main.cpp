#include <fstream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <regex>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;

template <typename T> string tostring(const T& t) {
	ostringstream os;
	os << fixed;
	os.precision(1);
	os << t;
	return os.str();
}

class eggs {
protected:
	int id;
	string name;
public:
	eggs(int pid, string pname) {
		id = pid;
		name = pname;
	};
	~eggs() {};
	int rid() { return id; };
	string rname() { return name; };
};

class abilities : public eggs {
	string desc;
public:
	abilities(int pid, string pname, string pdesc) : eggs(pid, pname) {
		desc = pdesc;
	};
	~abilities() {};
	string rdesc() { return desc; };
};

class types : public eggs {
protected:
	vector<char> effect;
public:
	types(int pid, string pname, vector<char> peffect) : eggs(pid, pname) {
		effect = peffect;
	};
	~types() {};
	char reffect(int x) { return effect[x]; };
	int ramount() { return effect.size(); };
};

class table {
protected:
	string number;
	string nameeng;
public:
	table() {};
	table(string pnumber, string pnameeng) {
		number = pnumber;
		nameeng = pnameeng;
	};
	~table() {};

	string rnumber() { return number; };
	string rnameeng() { return nameeng; };

};

class index : public table {
protected:
	string nameger;
	string namefre;
	string namerom; //[ger fre rom]
	int type1;
	int type2;
	float height;
	float weight;
	char gender;

public:
	index(string pnumber, string pnameeng, string pnameger, string pnamefre, string pnamerom, int ptype1, int ptype2, float pheight, float pweight, char pgender) :table(pnumber, pnameeng) {
		nameger = pnameger;
		namefre = pnamefre;
		namerom = pnamerom;
		type1 = ptype1;
		type2 = ptype2;
		height = pheight;
		weight = pweight;
		gender = pgender;
	}
	index() {};
	~index() {};

	string rnameger() { return nameger; };
	string rnamefre() { return namefre; };
	string rnamerom() { return namerom; };
	int rtype(int x) { if (x == 1) { return type1; } else { return type2; }; };
	string rtypename(int x, vector<types> t) {
		if (x == 1) { return (t[type1].rname()); }
		else {
			if (type2 == 0) { return ""; }
			else { return (t[type2].rname()); }
		};
	};
	float rheight() { return height; };
	float rweight() { return weight; };
	char rgenderid() { return gender; };
	string rgender() {
		switch (gender) {
		case '0':
			return "Female only";
		case '1':
			return "7/8 Female";
		case '2':
			return "3/4 Female";
		case '4':
			return "Equal genders";
		case '6':
			return "3/4 Male";
		case '7':
			return "7/8 Male";
		case '8':
			return "Male only";
		default:
			return "No gender";
		}
	};
};

class stats : public table {
protected:
	int abil1;
	int abil2;
	int abilh;
	int stathp;
	int statatk;
	int statdef;
	int statsat;
	int statsdf;
	int statspd;
	int evhp;
	int evatk;
	int evdef;
	int evsat;
	int evsdf;
	int evspd;

public:
	stats(string pnumber, string pnameeng, int pabil1, int pabil2, int pabilh, int pstathp, int pstatatk, int pstatdef, int pstatsat, int pstatsdf, int pstatspd, int pevhp, int pevatk, int pevdef, int pevsat, int pevsdf, int pevspd) : table(pnumber, pnameeng) {
		abil1 = pabil1;
		abil2 = pabil2;
		abilh = pabilh;
		stathp = pstathp;
		statatk = pstatatk;
		statdef = pstatdef;
		statsat = pstatsat;
		statsdf = pstatsdf;
		statspd = pstatspd;
		evhp = pevhp;
		evatk = pevatk;
		evdef = pevdef;
		evsat = pevsat;
		evsdf = pevsdf;
		evspd = pevspd;
	}
	stats() {};
	~stats() {};
	int rability(int x) {
		if (x == 1) { return abil1; }
		else if (x == 2) { return abil2; }
		else { return abilh; };
	}
	string rabilname(int x, vector<abilities> v) {
		int abil = rability(x);
		if (abil == 0) { return ""; }
		else { return (v[abil].rname()); };
	}
	string rabildesc(int x, vector<abilities> v) {
		int abil = rability(x);
		if (abil == 0) { return ""; }
		else { return (v[abil].rdesc()); };
	}
	int rstat(int x) {
		switch (x) {
		case 1:
			return stathp;
		case 2:
			return statatk;
		case 3:
			return statdef;
		case 4:
			return statsat;
		case 5:
			return statsdf;
		case 6:
			return statspd;
		default:
			return 0;
		}
	};
	int rev(int x) {
		switch (x) {
		case 1:
			return evhp;
		case 2:
			return evatk;
		case 3:
			return evdef;
		case 4:
			return evsat;
		case 5:
			return evsdf;
		case 6:
			return evspd;
		default:
			return 0;
		}
	};
};

class misc : public table {
protected:
	int egg1;
	int egg2;
	int cycles;
	int exp;
	int capture;
	int happiness;
	int maxexp;

public:
	misc(string pnumber, string pnameeng, int pegg1, int pegg2, int pcycles, int pexp, int pcapture, int phappiness, int pmaxexp) : table(pnumber, pnameeng) {
		egg1 = pegg1;
		egg2 = pegg2;
		cycles = pcycles;
		exp = pexp;
		capture = pcapture;
		happiness = phappiness;
		maxexp = pmaxexp;
	}
	misc() {};
	~misc() {};

	int regg(int x) {
		if (x == 1) { return egg1; }
		else { return egg2; };
	};
	string reggname(int x, vector<eggs> e) {
		int egg = regg(x);
		if (x != 1 && egg == 0) { return ""; }
		else { return (e[egg].rname()); };
	};
	int rcycles() { return cycles; };
	int rsteps(int x) {
		switch (x) {
		case 2:
		case 7:
			return cycles * 256;
		case 3:
			return (cycles + 1) * 256;
		case 4:
			return (cycles + 1) * 255;
		case 5:
		case 6:
			return cycles * 257;
		default:
			return cycles;
		}
	};
	int rexp() { return exp; };
	int rcapture() { return capture; };
	int rhappiness() { return happiness; };
	int rmaxexp() { return maxexp; };
	string rmaxexpname() {
		if (maxexp == 600000) { return "Erratic"; };
		if (maxexp == 800000) { return "Fast"; };
		if (maxexp == 1000000) { return "Medium fast"; };
		if (maxexp == 1059860) { return "Medium slow"; };
		if (maxexp == 1250000) { return "Slow"; };
		if (maxexp == 1640000) { return "Fluctuating"; };
		return "error";
	};

};

class poke {
protected:
	index itab;
	stats stab;
	misc mtab;

public:
	poke(index pi, stats ps, misc pm) {
		itab = pi;
		stab = ps;
		mtab = pm;
	};
	poke() {};
	~poke() {};

	index ritab() { return itab; };
	stats rstab() { return stab; };
	misc rmtab() { return mtab; };

};


class pokedex {
protected:
	vector<eggs> e;
	vector<abilities> a;
	vector<types> t;
	vector<poke> p;
public:
	pokedex() {};
	~pokedex() {};

	bool pdataload() {
		try { t = typesfileread(); }
		catch (...) { throw 0; }
		try { e = eggsfileread(); }
		catch (...) { throw 0; }
		try { a = abilityfileread(); }
		catch (...) { throw 0; }
		try { p = pokefileread(); }
		catch (...) { throw 0; }
		return true;
	};
	void pdatasave() {
		typesfilesave(t);
		eggsfilesave(e);
		abilityfilesave(a);
		pokefilesave(p);
	};


	vector<eggs> eggsfileread() {
		vector<eggs> egglist;

		fstream eggsfile;
		eggsfile.open("txt/eggs.txt", ios::in);
		if (eggsfile.good() == false) { throw 0; };
		string eggsname;
		int x = 0;

		while (getline(eggsfile, eggsname)) {
			eggs e(x, eggsname);
			egglist.push_back(e);
			x++;
		}
		return egglist;
	}
	void eggsfilesave(vector<eggs> e) {
		fstream eggfile;
		eggfile.open("txt/eggs.txt", ios::out | ios::trunc);
		for (unsigned int i = 0; i<e.size(); i++) {
			eggfile << e[i].rname() << endl;
		};
	}
	vector<abilities> abilityfileread() {
		vector<abilities> abilitylist;

		fstream abilityfile;
		abilityfile.open("txt/ability.txt", ios::in);
		if (abilityfile.good() == false) { throw 0; };
		string abiline;
		string abiname;
		string abidesc;
		int x = 0;

		while (getline(abilityfile, abiline)) {
			stringstream ssin(abiline);
			ssin >> abiname;
			ssin >> abidesc;
			utos(abiname);
			utos(abidesc);
			abilities a(x, abiname, abidesc);
			abilitylist.push_back(a);
			x++;
		}
		return abilitylist;
	}
	void abilityfilesave(vector<abilities> a) {
		fstream abilityfile;
		abilityfile.open("txt/ability.txt", ios::out | ios::trunc);
		for (unsigned int i = 0; i<a.size(); i++) {
			string name = a[i].rname();
			string desc = a[i].rdesc();
			stou(name);
			stou(desc);
			abilityfile << name << " " << desc << endl;
		}
	}
	vector<types> typesfileread() {
		vector<types> typelist;

		fstream typesfile;
		typesfile.open("txt/types.txt", ios::in);
		if (typesfile.good() == false) { throw 0; };
		string typesline;
		string typesname;
		char a;
		vector<char> typeseff;
		int x = 0;

		while (getline(typesfile, typesline)) {
			stringstream ssin(typesline);
			ssin >> typesname;
			while (ssin) {
				ssin >> a;
				typeseff.push_back(a);
			}
			types t(x, typesname, typeseff);
			typelist.push_back(t);
			while (!typeseff.empty()) { typeseff.pop_back(); };
			x++;
		}
		return typelist;
	}
	void typesfilesave(vector<types> t) {
		fstream typefile;
		typefile.open("txt/types.txt", ios::out | ios::trunc);
		for (unsigned int i = 0; i<t.size(); i++) {
			typefile << t[i].rname() << " ";
			for (int j = 0; j<(t[i].ramount() - 1); j++) {
				typefile << t[i].reffect(j) << " ";
			};
			typefile << endl;
		};
	}
	vector<poke> pokefileread() {
		vector<poke> pokelist;

		fstream pokefile;
		pokefile.open("txt/pokedex.txt", ios::in);
		if (pokefile.good() == false) { throw 0; };

		string pokeline;
		string number, nameeng;

		string nameger, namefre, namerom;
		int type1, type2;

		int abil1, abil2, abilh;
		int stat1, stat2, stat3, stat4, stat5, stat6, ev1, ev2, ev3, ev4, ev5, ev6;

		float height, weight;
		char gender;

		int egg1, egg2, cycles, exp, capture, happiness, maxexp;

		while (getline(pokefile, pokeline)) {
			stringstream ssin(pokeline);
			ssin >> number;
			ssin >> nameeng;
			ssin >> nameger;
			ssin >> namefre;
			ssin >> namerom;
			ssin >> type1;
			ssin >> type2;
			ssin >> abil1;
			ssin >> abil2;
			ssin >> abilh;
			ssin >> stat1;
			ssin >> stat2;
			ssin >> stat3;
			ssin >> stat4;
			ssin >> stat5;
			ssin >> stat6;
			ssin >> ev1;
			ssin >> ev2;
			ssin >> ev3;
			ssin >> ev4;
			ssin >> ev5;
			ssin >> ev6;
			ssin >> height;
			ssin >> weight;
			ssin >> gender;
			ssin >> egg1;
			ssin >> egg2;
			ssin >> cycles;
			ssin >> exp;
			ssin >> capture;
			ssin >> happiness;
			ssin >> maxexp;
			index i(number, nameeng, nameger, namefre, namerom, type1, type2, height, weight, gender);
			stats s(number, nameeng, abil1, abil2, abilh, stat1, stat2, stat3, stat4, stat5, stat6, ev1, ev2, ev3, ev4, ev5, ev6);
			misc  m(number, nameeng, egg1, egg2, cycles, exp, capture, happiness, maxexp);
			poke p(i, s, m);
			pokelist.push_back(p);
		};
		return pokelist;
	}
	void pokefilesave(vector<poke> p) {
		fstream pokefile;
		pokefile.open("txt/pokedex.txt", ios::out | ios::trunc);
		for (unsigned int i = 0; i<p.size(); i++) {
			pokefile << p[i].ritab().rnumber() << " ";
			pokefile << p[i].ritab().rnameeng() << " ";
			pokefile << p[i].ritab().rnameger() << " ";
			pokefile << p[i].ritab().rnamefre() << " ";
			pokefile << p[i].ritab().rnamerom() << " ";
			pokefile << p[i].ritab().rtype(1) << " ";
			pokefile << p[i].ritab().rtype(2) << " ";
			pokefile << p[i].rstab().rability(1) << " ";
			pokefile << p[i].rstab().rability(2) << " ";
			pokefile << p[i].rstab().rability(3) << " ";
			pokefile << p[i].rstab().rstat(1) << " ";
			pokefile << p[i].rstab().rstat(2) << " ";
			pokefile << p[i].rstab().rstat(3) << " ";
			pokefile << p[i].rstab().rstat(4) << " ";
			pokefile << p[i].rstab().rstat(5) << " ";
			pokefile << p[i].rstab().rstat(6) << " ";
			pokefile << p[i].rstab().rev(1) << " ";
			pokefile << p[i].rstab().rev(2) << " ";
			pokefile << p[i].rstab().rev(3) << " ";
			pokefile << p[i].rstab().rev(4) << " ";
			pokefile << p[i].rstab().rev(5) << " ";
			pokefile << p[i].rstab().rev(6) << " ";
			pokefile << p[i].ritab().rheight() << " ";
			pokefile << p[i].ritab().rweight() << " ";
			pokefile << p[i].ritab().rgenderid() << " ";
			pokefile << p[i].rmtab().regg(1) << " ";
			pokefile << p[i].rmtab().regg(2) << " ";
			pokefile << p[i].rmtab().rcycles() << " ";
			pokefile << p[i].rmtab().rexp() << " ";
			pokefile << p[i].rmtab().rcapture() << " ";
			pokefile << p[i].rmtab().rhappiness() << " ";
			pokefile << p[i].rmtab().rmaxexp() << endl;
		}
	}


	void stou(string & x) {
		for (int i = 0; x[i] != '\0'; i++) {
			if (x[i] == ' ') { x[i] = '_'; };
		};
	}
	void utos(string & x) {
		for (int i = 0; x[i] != '\0'; i++) {
			if (x[i] == '_') { x[i] = ' '; };
		};
	}

	//public functions for drawing
	void openpokedex();
	void screenflash();
	void viewdraw();
	void detaildraw();
	bool yesno();
	void searchdraw();

	//public variables for functions above for ease of use
	char view; //[s]plash [m]enu [e]dit [d]etails [a]bout searc[h]
	sf::RectangleShape bg;
	sf::RenderWindow window;
	sf::Text menu;
	int ary = 0;
	int arvy = 0;
	int arboost = 1;
	int menuy = 0;
	int menuselect = 1;
	int listselect = 1;
	int viewfirst = 0;
	int sorttype = 0;
	sf::Sprite dex;
	int dselect = 1;
	char dview = 'a';
	int arvd = 0;
	sf::Sprite yn;
	sf::Sprite aryn;
	int aryny = 0;

	sf::Sprite screenshot;
	sf::Sprite ar;
	sf::Sprite ha;

	vector<poke>* pointer = &p;
	vector<poke> searchresult;

	unsigned int pselect = 0;
	bool arrowmenu;
	char menuview = 'a';
	char helpabout = 'x'; //[h]elp, [a]bout, [x]none

	int listlimit = 18;

};

struct namesort
{
	inline bool operator() (poke& a, poke& b)
	{
		return (a.ritab().rnameeng() < b.ritab().rnameeng());
	}
};

struct numbersort
{
	inline bool operator() (poke& a, poke& b)
	{
		return (a.ritab().rnumber() < b.ritab().rnumber());
	}
};

void pokedex::openpokedex() {
	window.create(sf::VideoMode(640, 576), "Chardex", sf::Style::Default);
	bg.setSize(sf::Vector2f(640, 576));
	bg.setFillColor(sf::Color(248, 248, 248, 255));

	sf::Texture ss;
	ss.create(640, 576);

	sf::Texture splashscreen;
	if (!splashscreen.loadFromFile("img/start.png")) { throw 0; };
	sf::Sprite splash;
	splash.setTexture(splashscreen);

	sf::Texture dexbackground;
	if (!dexbackground.loadFromFile("img/dexbg.png")) { throw 0; };
	sf::Sprite dexbg;
	dexbg.setTexture(dexbackground);

	sf::Texture sideline;
	if (!sideline.loadFromFile("img/sideline.png")) { throw 0; };
	sf::Sprite sl;
	sl.setTexture(sideline);

	sf::Texture arrow;
	if (!arrow.loadFromFile("img/arrow.png")) { throw 0; };
	ar.setTexture(arrow);
	ar.setPosition(sf::Vector2f(488, 252 + ary));

	sf::Texture highline;
	if (!highline.loadFromFile("img/highline.png")) { throw 0; };
	sf::Sprite hl;
	hl.setTexture(highline);
	hl.setPosition(sf::Vector2f(452, 0));

	sf::Texture menuline;
	if (!menuline.loadFromFile("img/menuline.png")) { throw 0; };
	sf::Sprite ml;
	ml.setTexture(menuline);
	ml.setPosition(sf::Vector2f(480, 200));

	sf::Texture pokenf;
	if (!pokenf.loadFromFile("img/pokenf.png")) { throw 0; };
	sf::Texture pokemon;
	dex.setTexture(pokenf);
	dex.setPosition(sf::Vector2f(64, 40));

	sf::Texture searchwindow;
	if (!searchwindow.loadFromFile("img/wind.png")) { throw 0; };
	sf::Sprite sw;
	sw.setTexture(searchwindow);
	sw.setPosition(sf::Vector2f(80, 132));

	sf::Texture yesnobox;
	if (!yesnobox.loadFromFile("img/yesno.png")) { throw 0; };
	yn.setTexture(yesnobox);
	yn.setPosition(sf::Vector2f(0, 312));
	aryn.setTexture(arrow);
	aryn.setPosition(sf::Vector2f(32, 312 + 32 + aryny));

	sf::Texture helpaboutbox;
	if (!helpaboutbox.loadFromFile("img/helpabout.png")) { throw 0; };
	ha.setTexture(helpaboutbox);

	sf::Font gbfont;
	if (!gbfont.loadFromFile("img/GB.ttf")) { throw 0; };
	menu.setFont(gbfont);
	menu.setCharacterSize(28 - 8);
	menu.setFillColor(sf::Color::Black);

	view = 's';
	arrowmenu = false;


	while (window.isOpen())
	{
		window.clear();
		window.draw(bg);

		/*
		#################################
		#drawing stuff in specific views#
		#################################
		*/

		switch (view) {
		case 's':
			window.draw(splash);
			break;
		case 'm':
			window.draw(hl);
			window.draw(ml);
			ar.setPosition(sf::Vector2f(0, 52 + arvy));
			window.draw(ar);
			if (arrowmenu) { ar.setPosition(sf::Vector2f(480, 252 + ary)); };
			window.draw(ar);

			viewdraw();
			break;
		case 'd':
			sl.setPosition(sf::Vector2f(0, 256));
			window.draw(sl);
			window.draw(dexbg);

			ar.setPosition(sf::Vector2f(340, 88 + arvd));
			window.draw(ar);

			detaildraw();

			menu.setString("DETAILS");
			menu.setPosition(sf::Vector2f(360, 48));
			window.draw(menu);
			menu.setString("GENERAL");
			menu.setPosition(sf::Vector2f(360, 88));
			window.draw(menu);
			menu.setString("BATTLE");
			menu.setPosition(sf::Vector2f(360, 116));
			window.draw(menu);
			menu.setString("MISC");
			menu.setPosition(sf::Vector2f(360, 144));
			window.draw(menu);
			menu.setString("EXIT");
			menu.setPosition(sf::Vector2f(360, 172));
			window.draw(menu);

			menu.setString("Number " + (*pointer)[pselect].ritab().rnumber() + ": ");
			menu.setPosition(44, 296);
			window.draw(menu);
			menu.setString((*pointer)[pselect].ritab().rnameeng());
			menu.setPosition(360, 296);
			window.draw(menu);
			break;

		case 'h':
			window.draw(hl);
			window.draw(ml);
			ar.setPosition(sf::Vector2f(0, 52 + arvy));
			window.draw(ar);
			if (arrowmenu) { ar.setPosition(sf::Vector2f(480, 252 + ary)); };
			window.draw(ar);
			viewdraw();
			window.draw(sw);

			ss.update(window);
			screenshot.setTexture(ss);
			searchdraw();
			view = 'm';
			break;
		}

		/*
		#################################
		#here lies the event loop thing #
		#################################
		*/

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) { window.close(); break; };
			}
			if (event.type == sf::Event::Closed) { window.close(); break; };

			switch (view) {
			case 's': // #####Splash screen#####

				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Z:

					case sf::Keyboard::X:
						view = 'm';
						screenflash();
						break;
					default:
						break;
					}
				}
				break;
			case 'm': // #####Menu screen#####
				if (event.type == sf::Event::KeyPressed&&helpabout == 'x') {
					switch (event.key.code) {
					case sf::Keyboard::Z:
						if (!arrowmenu) { arrowmenu = true; }
						else {
							if (menuselect == 1) {
								if (menuview == 'a') {
									menuview = 'b'; arboost = 2;
								}
								else if (menuview == 'b') {
									menuview = 'a'; arboost = 1;

								};
								if (viewfirst + listlimit / arboost>(int)(*pointer).size()) {
									viewfirst = (int)(*pointer).size() - listlimit / arboost;
									if (viewfirst<0) { viewfirst = 0; }
								}
								pselect = viewfirst;
								arvy = 0;
								listselect = 1;
							}
							else if (menuselect == 2) {
								view = 'd';
								if (pokemon.loadFromFile("img/dex/" + (*pointer)[pselect].ritab().rnumber() + ".png")) { dex.setTexture(pokemon); }
								else { dex.setTexture(pokenf); };
								screenflash();
							}
							else if (menuselect == 3) {
								view = 'h';
							}
							else if (menuselect == 4) {
								sorttype = (sorttype + 1) % 2;
								if (sorttype == 0) { sort((*pointer).begin(), (*pointer).end(), numbersort()); }
								else if (sorttype == 1) { sort((*pointer).begin(), (*pointer).end(), namesort()); }
							}
							else if (menuselect == 5) {
								helpabout = 'h';
							}
							else if (menuselect == 6) {
								helpabout = 'a';
							}
							else { window.close(); }

						}
						break;
					case sf::Keyboard::X:
						if (arrowmenu) { arrowmenu = false; };
						break;
					case sf::Keyboard::Down:
						if (arrowmenu&&menuselect<7) { ary += (28 - 8) * 2; menuselect++; }
						else if (!arrowmenu&&pselect == (*pointer).size() - 1) {
							arvy = 0;
							viewfirst = 0;
							listselect = 1;
							pselect = 0;
						}
						else if (!arrowmenu&&listselect == listlimit / arboost&&pselect<(*pointer).size() - 1) { viewfirst++; pselect++; }
						else if (!arrowmenu&&listselect<listlimit / arboost) { arvy += 28 * arboost; listselect++; pselect++; }

						break;
					case sf::Keyboard::Up:
						if (arrowmenu&&menuselect>1) { ary -= (28 - 8) * 2; menuselect--; }
						else if (!arrowmenu&&pselect == 0) {
							if (listlimit<(int)(*pointer).size()) {
								arvy = (28)*(listlimit - 1) - 28 * (arboost - 1);
							}
							else {
								arvy = (28)*(((*pointer).size())*arboost - 1) - 28 * (arboost - 1);
							}

							viewfirst = (*pointer).size() - listlimit / arboost;
							if (viewfirst<0) { viewfirst = 0; };
							listselect = listlimit / arboost;
							pselect = (*pointer).size() - 1;
						}
						else if (!arrowmenu&&listselect == 1 && pselect>0) { viewfirst--; pselect--; }
						else if (!arrowmenu&&listselect>1) { arvy -= 28 * arboost; listselect--; pselect--; }
						break;
					case sf::Keyboard::Left:
						if (!arrowmenu) {
							if (viewfirst == 0) {
								arvy = 0;
								viewfirst = 0;
								listselect = 1;
								pselect = 0;
							}
							else if (viewfirst <= listlimit / arboost) {
								pselect = listselect - 1;
								viewfirst = 0;
							}
							else {
								viewfirst -= listlimit / arboost;
								pselect -= listlimit / arboost;
							}
						}
						break;
					case sf::Keyboard::Right:
						if (!arrowmenu) {
							if (viewfirst == (int)(*pointer).size() - listlimit / arboost) {
								arvy = 28 * (listlimit - 1);
								listselect = listlimit / arboost;
								pselect = (int)(*pointer).size() - 1;
							}
							else if (listlimit / arboost > (int)(*pointer).size()) {
								arvy = 28 * ((*pointer).size() - 1)*arboost;
								listselect = listlimit / arboost;
								pselect = (int)(*pointer).size() - 1;
							}
							else if (viewfirst >= (int)(*pointer).size() - 2 * listlimit / arboost) {
								pselect = (int)(*pointer).size() - listlimit / arboost + listselect - 1;
								viewfirst = (int)(*pointer).size() - listlimit / arboost;
							}
							else {
								viewfirst += listlimit / arboost;
								pselect += listlimit / arboost;
							}
						}
						break;
					default:
						break;
					}
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::X) {
						helpabout = 'x';
					}
					else if (event.key.code == sf::Keyboard::Z) {
						if (helpabout == 'h') { helpabout = 'e'; }
						else { helpabout = 'x'; };
					}
				}

				break;
			case 'd': // ##### details screen #####
				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Z:
						if (dselect == 1) { dview = 'a'; break; }
						else if (dselect == 2) { dview = 'b'; break; }
						else if (dselect == 3) { dview = 'c'; break; }

					case sf::Keyboard::X:
						view = 'm';
						dselect = 1;
						dview = 'a';
						arvd = 0;
						arrowmenu = false;
						viewfirst = pselect;
						if (listlimit / arboost > (int)(*pointer).size()) {
							viewfirst = 0;
							listselect = pselect;
							arvy = ((28 * (listselect + arboost - 1)) - 28 * (arboost - 1))*arboost;
						}
						else if (viewfirst>(int)(*pointer).size() - listlimit / arboost) {
							viewfirst = (int)(*pointer).size() - listlimit / arboost;
							listselect = (listlimit / arboost) - ((*pointer).size() - 1 - pselect);
							arvy = ((28 * (listselect - 1)) - 28 * (arboost - 1))*arboost;
						}
						else {
							arvy = 0;
							listselect = 1;
						}
						screenflash();
						break;

					case sf::Keyboard::Up:
						if (dselect != 1) {
							arvd -= 28;
							dselect--;
						}
						break;
					case sf::Keyboard::Down:
						if (dselect != 4) {
							arvd += 28;
							dselect++;
						}
						break;

					case sf::Keyboard::Right:
						if (pselect != (*pointer).size() - 1) { pselect++; }
						else { pselect = 0; }
						if (pokemon.loadFromFile("img/dex/" + (*pointer)[pselect].ritab().rnumber() + ".png")) { dex.setTexture(pokemon); }
						else { dex.setTexture(pokenf); };
						screenflash();
						break;
					case sf::Keyboard::Left:
						if (pselect != 0) { pselect--; }
						else { pselect = (*pointer).size() - 1; };
						if (pokemon.loadFromFile("img/dex/" + (*pointer)[pselect].ritab().rnumber() + ".png")) { dex.setTexture(pokemon); }
						else { dex.setTexture(pokenf); };
						screenflash();
						break;
					default:
						break;
					}
				}
			default:
				break;
			}
		}
		window.display();
	}
	sort(p.begin(), p.end(), numbersort());
}

void pokedex::screenflash() {
	using namespace std::this_thread;
	using namespace std::chrono_literals;
	using std::chrono::system_clock;

	window.clear();
	window.draw(bg);
	window.display();
	sleep_for(50ms);
}

void pokedex::viewdraw() { // drawing menu, also for searchbox

	menu.setString("VIEW:");
	menu.setPosition(sf::Vector2f(480, 32));
	window.draw(menu);
	// the view type here, an if on a variable
	if (menuview == 'a') { menu.setString("Clear"); }
	else if (menuview == 'b') { menu.setString("Types"); }
	menu.setPosition(sf::Vector2f(520, 32 + 8 + 20));
	window.draw(menu);
	menu.setString("SEEN:");
	menu.setPosition(sf::Vector2f(480, 32 + 20 * 4));
	window.draw(menu);
	menu.setString(tostring((*pointer).size()));
	menu.setPosition(sf::Vector2f(520, 32 + 8 + 20 * 5));
	window.draw(menu);
	if (helpabout == 'x') {
		menu.setString("CONTENTS");
		menu.setPosition(sf::Vector2f(20, 12));
		window.draw(menu);
		int vi = 0;
		switch (menuview) {
		case 'a': // concise look, number, name
			while (vi<listlimit / arboost && vi<(int)(*pointer).size()) {
				menu.setString((*pointer)[viewfirst + vi].ritab().rnumber() + ". " + (*pointer)[viewfirst + vi].ritab().rnameeng());

				menuy = vi * 28;
				menu.setPosition(20, 52 + menuy);
				window.draw(menu);
				vi++;
			};

			break;
		case 'b': // normal look, number, name, types
			while (vi<listlimit / arboost && vi<(int)(*pointer).size()) {
				menuy = vi * 56;

				menu.setString((*pointer)[viewfirst + vi].ritab().rnumber() + ". " + (*pointer)[viewfirst + vi].ritab().rnameeng());
				menu.setPosition(20, 52 + menuy);
				window.draw(menu);

				string x = (*pointer)[viewfirst + vi].ritab().rtypename(1, t);
				if ((*pointer)[viewfirst + vi].ritab().rtypename(2, t) == "") {}
				else { x += "/" + (*pointer)[viewfirst + vi].ritab().rtypename(2, t); };
				menu.setString(x);
				menu.setFillColor(sf::Color(128, 128, 128));
				menu.setPosition(160, 80 + menuy);
				window.draw(menu);
				menu.setFillColor(sf::Color::Black);
				vi++;
			}
			break;
		}
	}
	else {
		window.draw(ha);
		if (helpabout == 'h') {
			menu.setString("Chardex v. 1.0\nIt's a Pokedex based\non the original by Prof.\nOak from Pallet Town.\n\nThat brilliant POKéMON\nProfessor spent years\nfrom his life on\ncompleting a POKéMON\nencyclopedia that could\nhelp young trainers\nsuch as you in learning\nall about these\nmagnificent\ncreatures.");
		}
		if (helpabout == 'e') {
			menu.setString("Most of the options\nrequire only 6 buttons.\nUse the Arrow buttons\nto maneuver menus,\n[Z] to confirm\n[X] to cancel.\n\nUse a keyboard for the\nSEARCH functions.\nIt also supports\nRegex for better\nsearches!");
		}
		if (helpabout == 'a') {
			menu.setString("Chardex is a program\nbased on Pokémon Red\nVer. made by Szymon\nPych.\nFont: Pokemon Classic\nby TheLouster115\n\nPokémon (C) 2002-\n2018 Pokémon. (C) \n1995-2018 Nintendo/\nCreatures Inc./\nGAME FREAK inc.\nTM, (R) and Pokemon\ncharacter names are\ntrademarks of\nNintendo.");
		}
		menu.setPosition(32, 32);
		window.draw(menu);
	}



	menu.setString("VIEW");
	menu.setPosition(sf::Vector2f(500, 252));
	window.draw(menu);
	menu.setString("DATA");
	menu.setPosition(sf::Vector2f(500, 252 + 40));
	window.draw(menu);
	menu.setString("SEARCH");
	menu.setPosition(sf::Vector2f(500, 252 + 40 * 2));
	window.draw(menu);
	menu.setString("SORT");
	menu.setPosition(sf::Vector2f(500, 252 + 40 * 3));
	window.draw(menu);
	menu.setString("HELP");
	menu.setPosition(sf::Vector2f(500, 252 + 40 * 4));
	window.draw(menu);
	menu.setString("ABOUT");
	menu.setPosition(sf::Vector2f(500, 252 + 40 * 5));
	window.draw(menu);
	menu.setString("QUIT");
	menu.setPosition(sf::Vector2f(500, 252 + 40 * 6));
	window.draw(menu);
}

void pokedex::detaildraw() { // drawing details menu

	window.draw(dex);
	//draw the menu text
	//arrow shiftable
	string x;
	switch (dview) {
	case 'a':
		menu.setString((*pointer)[pselect].ritab().rtypename(1, t));
		menu.setPosition(64, 324);
		window.draw(menu);
		if ((*pointer)[pselect].ritab().rtypename(2, t) != "") {
			x = (*pointer)[pselect].ritab().rtypename(2, t);
		}
		else { x = "---"; };
		menu.setString(x);
		menu.setPosition(104, 352);
		window.draw(menu);

		menu.setString("Height: " + tostring((*pointer)[pselect].ritab().rheight()) + "m");
		menu.setPosition(64, 408);
		window.draw(menu);
		menu.setString("Weight: " + tostring((*pointer)[pselect].ritab().rweight()) + "kg");
		menu.setPosition(64, 436);
		window.draw(menu);
		menu.setString((*pointer)[pselect].ritab().rgender());
		menu.setPosition(64, 492);
		window.draw(menu);

		menu.setString((*pointer)[pselect].ritab().rnameger());
		menu.setPosition(360, 352);
		window.draw(menu);
		menu.setString((*pointer)[pselect].ritab().rnamefre());
		menu.setPosition(360, 380);
		window.draw(menu);
		menu.setString((*pointer)[pselect].ritab().rnamerom());
		menu.setPosition(360, 408);
		window.draw(menu);
		break;
	case 'b': //battle
		for (int i = 1; i<7; i++) {
			if (i == 1) { x = "HP: "; }
			else if (i == 2) { x = "ATK: "; }
			else if (i == 3) { x = "DEF: "; }
			else if (i == 4) { x = "SAT: "; }
			else if (i == 5) { x = "SDF: "; }
			else { x = "SPD: "; };
			x += tostring((*pointer)[pselect].rstab().rstat(i));
			if (i == 1) { menu.setPosition(84, 324); }
			else if (i % 2 == 0) {
				menu.setPosition(360, 324 + ((i - 2) / 2) * 28);
			}
			else { menu.setPosition(64, 324 + ((i - 1) / 2) * 28); };
			menu.setString(x);
			window.draw(menu);
		};
		for (int i = 1; i<7; i++) {
			if (i % 2 == 0) {
				menu.setPosition(528, 324 + ((i - 2) / 2) * 28);
			}
			else { menu.setPosition(232, 324 + ((i - 1) / 2) * 28); };
			menu.setString("[" + tostring((*pointer)[pselect].rstab().rev(i)) + "]");
			window.draw(menu);
		}
		menu.setString("Abilities:");
		menu.setPosition(64, 436);
		window.draw(menu);
		for (int i = 1; i<4; i++) {
			if ((*pointer)[pselect].rstab().rabilname(i, a) == "") { x = "---"; }
			else { x = (*pointer)[pselect].rstab().rabilname(i, a); };

			menu.setString(x);
			menu.setPosition(64 + i * 20, 436 + i * 28);
			window.draw(menu);
		}
		break;
	case 'c':

		if ((*pointer)[pselect].rmtab().reggname(2, e) != "") {
			x += "/" + (*pointer)[pselect].rmtab().reggname(2, e);
		}
		menu.setString("Egg groups:");
		menu.setPosition(64, 324);
		window.draw(menu);
		menu.setString((*pointer)[pselect].rmtab().reggname(1, e));
		menu.setPosition(84, 352);
		window.draw(menu);
		if ((*pointer)[pselect].rmtab().reggname(2, e) != "") {
			x = (*pointer)[pselect].rmtab().reggname(2, e);
		}
		else { x = "---"; };
		menu.setString(x);
		menu.setPosition(104, 380);
		window.draw(menu);

		menu.setString("Cycles: " + tostring((*pointer)[pselect].rmtab().rcycles()));
		menu.setPosition(64, 324 + 28 * 4);
		window.draw(menu);
		menu.setString(tostring((*pointer)[pselect].rmtab().rsteps(7)) + " steps");
		menu.setPosition(64 + 20 * 12, 324 + 28 * 4);
		window.draw(menu);
		menu.setString("Base experience: " + tostring((*pointer)[pselect].rmtab().rexp()));
		menu.setPosition(64, 324 + 28 * 5);
		window.draw(menu);
		menu.setString("Base happiness: " + tostring((*pointer)[pselect].rmtab().rhappiness()));
		menu.setPosition(64, 324 + 28 * 6);
		window.draw(menu);
		menu.setString("Capture rate: " + tostring((*pointer)[pselect].rmtab().rcapture()));
		menu.setPosition(64, 324 + 28 * 7);
		window.draw(menu);


		menu.setString("Until Lv100:");
		menu.setPosition(360, 324);
		window.draw(menu);
		menu.setString(tostring((*pointer)[pselect].rmtab().rmaxexp()) + "EXP");
		menu.setPosition(360, 324 + 1 * 28);
		window.draw(menu);
		menu.setString((*pointer)[pselect].rmtab().rmaxexpname());
		menu.setPosition(360, 324 + 2 * 28);
		window.draw(menu);

	default:
		break;
	}

}

bool pokedex::yesno() {
	bool yes = true;
	aryny = 0;
	while (window.isOpen()) {
		window.draw(yn);
		aryn.setPosition(sf::Vector2f(32, 312 + 28 + aryny));
		window.draw(aryn);
		menu.setString("YES");
		menu.setPosition(sf::Vector2f(32 + 20, 312 + 28));
		window.draw(menu);
		menu.setString("NO");
		menu.setPosition(sf::Vector2f(32 + 20, 312 + 28 + 40));
		window.draw(menu);
		menu.setString("Would you like to");
		menu.setPosition(sf::Vector2f(20 + 16, 312 + 144 + 12));
		window.draw(menu);
		menu.setString("SAVE this option?");
		menu.setPosition(sf::Vector2f(20 + 16, 312 + 144 + 12 + 48));
		window.draw(menu);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); break; };
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Down:
					if (yes) {
						aryny = 40;
						yes = false;
					}
					break;
				case sf::Keyboard::Up:
					if (!yes) {
						aryny = 0;
						yes = true;
					}
					break;
				case sf::Keyboard::Z:
					return yes;
					break;
				case sf::Keyboard::X:
					return false;
					break;
				default:
					break;
				}
			}

		}
		window.display();
	}
	return false;
}

void pokedex::searchdraw() {

	int arsdpos = 0;
	int lines = 1;
	sf::String se = "";
	sf::String seuse = "";
	bool open = true;
	bool save = false;
	while (open&&window.isOpen()) {
		window.draw(screenshot);
		menu.setString("SEARCH FOR:");
		menu.setPosition(sf::Vector2f(80 + 32 + 20, 132 + 32));
		window.draw(menu);
		menu.setString("CLEAR           SAVE");
		menu.setPosition(sf::Vector2f(80 + 32 + 20, 132 + 32 + 28 * 8));
		window.draw(menu);
		if (arsdpos == 0) { ar.setPosition(sf::Vector2f(80 + 32 + 20 - 20, 132 + 32 + 28)); }
		else if (arsdpos == 1) { ar.setPosition(sf::Vector2f(80 + 32, 132 + 32 + 28 * 8)); }
		else { ar.setPosition(sf::Vector2f(80 + 32 + 200, 132 + 32 + 28 * 8)); }
		window.draw(ar);


		menu.setString(se);
		menu.setPosition(sf::Vector2f(80 + 32 + 20, 132 + 32 + 28));
		window.draw(menu);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); };
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) { window.close(); }
				else if (event.key.code == sf::Keyboard::Down) { if (arsdpos == 0) { arsdpos = 1; }; }
				else if (event.key.code == sf::Keyboard::Up) { arsdpos = 0; }
				else if (event.key.code == sf::Keyboard::Left) { arsdpos = 1; }
				else if (event.key.code == sf::Keyboard::Right) { arsdpos = 2; }
				else if (arsdpos == 1) {
					if (event.key.code == sf::Keyboard::Z) {
						pointer = &p;
						open = false;
					}
					if (event.key.code == sf::Keyboard::X) {
						open = false;
					}
				}
				else if (arsdpos == 2) {
					if (event.key.code == sf::Keyboard::Z) {
						save = yesno();
						open = false;
					}
					else if (event.key.code == sf::Keyboard::X) {
						open = false;
					}
				}
			}
			if (arsdpos == 0) {
				if (event.type == sf::Event::TextEntered) {
					if (lines<7) {
						if (event.text.unicode >= 32 && event.text.unicode <= 126) {
							seuse += (char)event.text.unicode;
							se += (char)event.text.unicode;
						}
					}
					if (event.text.unicode == 8 && seuse.getSize() > 0) {
						seuse.erase(seuse.getSize() - 1, seuse.getSize());
						se.erase(se.getSize() - 1, se.getSize());
						if (se[se.getSize() - 1] == '\n') { se.erase(se.getSize() - 1, se.getSize()); lines--; }

					}
					menu.setString(se);
					if (menu.getGlobalBounds().width > 380) {
						lines++;
						if (lines == 7) {
							seuse.erase(seuse.getSize() - 1, seuse.getSize());
							se.erase(se.getSize() - 1, se.getSize());
							lines--;
						}
						else { se.insert(se.getSize() - 1, "\n"); };
						menu.setString(se);
					}
				}
			}
		}
		window.display();
	}
	viewfirst = 0;
	pselect = 0;
	arrowmenu = false;
	arvy = 0;
	listselect = 1;

	screenflash();
	if (save) {

		searchresult.clear();
		regex reg(seuse.toAnsiString(), std::regex_constants::icase);

		for (int i = 0; i<(int)p.size(); i++) {
			if (regex_search(p[i].ritab().rnameeng(), reg)) {
				searchresult.push_back(p[i]);
			}
		}

		if (searchresult.empty() || seuse.isEmpty()) {
			pointer = &p;
		}
		else {
			pointer = &searchresult;
		}
	};
}

int main()
{
	pokedex red;
	try {
		if (red.pdataload()) {
			red.openpokedex();
			red.pdatasave();
		}
		else { throw 0; };
	}
	catch (int) {
		fstream error;
		error.open("txt/error.txt", ios::out | ios::app);
		error << "Error: File not found.\n	Check the files and redownload if necessary." << endl;
	}
	catch (...) {
		fstream error;
		error.open("txt/error.txt", ios::out | ios::app);
		error << "Error: Unknown error.\n	Contact the creator for more information." << endl;
	}

	return 0;
}

#include <iostream>
#include <ctime>
using namespace std;

class GameObject { //추상클래스
protected:
	int distance; //한번 이동 거리
	int x, y; //현재 위치
public:
	GameObject(int startX, int startY, int distance) { //초기 위치와 이동거리 설정
		this->x = startX;
		this->y = startY;
		this->distance = distance;
	}
	virtual ~GameObject() {}; //가상소멸자
	virtual void move() = 0; //이동한 후 새로운 위치로 x, y 변경
	virtual char getShape() = 0; //객체 모양을 나타내는 문자 리턴(H,M,@)
	int getX() { return x; }
	int getY() { return y; }
	bool collide(GameObject* p) { //이 객체가 객체 p와 충돌했으면 true 리턴
		if (this->x == p->getX() && this->y == p->getY())
			return true;
		else
			return false;
	}
};

class Human :public GameObject {
public:
	Human(int startX, int startY, int distance) :GameObject(startX, startY, distance) {}
	virtual ~Human() {}
	void move() { //키 입력 받는 함수
		char key;
		cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
		cin >> key;
		cout << endl;
		switch (key) {
		case 'a': x -= distance; break; //왼쪽으로 이동
		case 's': y += distance; break; //아래쪽으로 이동
		case 'd': y -= distance; break; //위로 이동
		case 'f': x += distance; break; //오른쪽으로 이동
		default: cout << "다시 입력해주세요." << endl;
		}
	}
	char getShape() { return 'H'; }
};

class Monster :public GameObject {
public:
	Monster(int startX, int startY, int distance) :GameObject(startX, startY, distance) {}
	virtual ~Monster() {}
	void move() {
		int direction = rand() % 4; //0부터 3까지의 난수 생성
		switch (direction) {
		case 0: x -= distance; break; //왼쪽으로 이동
		case 1: y += distance; break; //아래쪽으로 이동
		case 2: y -= distance; break; //위로 이동
		case 3: x += distance; break; //오른쪽으로 이동
		default: break;
		}
	}
	char getShape() { return'M'; }
};

class Food :public GameObject {
public:
	Food(int startX, int startY, int distance) :GameObject(startX, startY, distance) {}
	virtual ~Food() {}
	void move() {
		int stay = rand() % 5; //0부터 4까지의 난수 생성
		if (stay < 3) { return; } //제자리에 있음
		int direction = rand() % 4;
		switch (direction) {
		case 0: x -= distance; break; //왼쪽으로 이동
		case 1: y += distance; break; //아래쪽으로 이동
		case 2: y -= distance; break; //위로 이동
		case 3: x += distance; break; //오른쪽으로 이동
		default: break;
		}
	}
	char getShape() { return '@'; }
};

class Game {
private:
	Human human;
	Monster monster;
	Food food;
public:
	Game() : human(0, 0, 1), monster(5, 5, 2), food(8, 9, 1) {}
	//게임 플레이 함수
	void play() {
		cout << "** Human의 Food 먹기 게임을 시작합니다. **" << endl << endl;
		while (true) {
			print(); //현재 상태 출력
			if (human.collide(&food)) { //Human이 Monster를 피해 Food를 먹으면 성공
				cout << "Human is Winner!!" << endl;
				break;
			}
			if (human.collide(&monster) || monster.collide(&food)) { //Human이 Monster에게 잡히거나 Monster가 Food를 먹으면 실패
				cout << "Game over!!" << endl;
				break;
			}
			//Human, Monster, Food 이동
			human.move();
			monster.move();
			food.move();
		}
	}
	//게임판 출력
	void print() {
		char board[10][20];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				board[i][j] = '-';
			}
		}
		board[human.getY()][human.getX()] = human.getShape(); // Human 위치 표시
		board[monster.getY()][monster.getX()] = monster.getShape(); // Monster 위치 표시
		board[food.getY()][food.getX()] = food.getShape(); // Food 위치 표시
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}

};

int main() {
	srand(time(NULL));
	Game game;
	game.play();
	return 0;
}

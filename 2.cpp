#include <iostream>
#include <ctime>
using namespace std;

class GameObject { //�߻�Ŭ����
protected:
	int distance; //�ѹ� �̵� �Ÿ�
	int x, y; //���� ��ġ
public:
	GameObject(int startX, int startY, int distance) { //�ʱ� ��ġ�� �̵��Ÿ� ����
		this->x = startX;
		this->y = startY;
		this->distance = distance;
	}
	virtual ~GameObject() {}; //����Ҹ���
	virtual void move() = 0; //�̵��� �� ���ο� ��ġ�� x, y ����
	virtual char getShape() = 0; //��ü ����� ��Ÿ���� ���� ����(H,M,@)
	int getX() { return x; }
	int getY() { return y; }
	bool collide(GameObject* p) { //�� ��ü�� ��ü p�� �浹������ true ����
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
	void move() { //Ű �Է� �޴� �Լ�
		char key;
		cout << "����(a), �Ʒ�(s), ��(d), ������(f) >> ";
		cin >> key;
		cout << endl;
		switch (key) {
		case 'a': x -= distance; break; //�������� �̵�
		case 's': y += distance; break; //�Ʒ������� �̵�
		case 'd': y -= distance; break; //���� �̵�
		case 'f': x += distance; break; //���������� �̵�
		default: cout << "�ٽ� �Է����ּ���." << endl;
		}
	}
	char getShape() { return 'H'; }
};

class Monster :public GameObject {
public:
	Monster(int startX, int startY, int distance) :GameObject(startX, startY, distance) {}
	virtual ~Monster() {}
	void move() {
		int direction = rand() % 4; //0���� 3������ ���� ����
		switch (direction) {
		case 0: x -= distance; break; //�������� �̵�
		case 1: y += distance; break; //�Ʒ������� �̵�
		case 2: y -= distance; break; //���� �̵�
		case 3: x += distance; break; //���������� �̵�
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
		int stay = rand() % 5; //0���� 4������ ���� ����
		if (stay < 3) { return; } //���ڸ��� ����
		int direction = rand() % 4;
		switch (direction) {
		case 0: x -= distance; break; //�������� �̵�
		case 1: y += distance; break; //�Ʒ������� �̵�
		case 2: y -= distance; break; //���� �̵�
		case 3: x += distance; break; //���������� �̵�
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
	//���� �÷��� �Լ�
	void play() {
		cout << "** Human�� Food �Ա� ������ �����մϴ�. **" << endl << endl;
		while (true) {
			print(); //���� ���� ���
			if (human.collide(&food)) { //Human�� Monster�� ���� Food�� ������ ����
				cout << "Human is Winner!!" << endl;
				break;
			}
			if (human.collide(&monster) || monster.collide(&food)) { //Human�� Monster���� �����ų� Monster�� Food�� ������ ����
				cout << "Game over!!" << endl;
				break;
			}
			//Human, Monster, Food �̵�
			human.move();
			monster.move();
			food.move();
		}
	}
	//������ ���
	void print() {
		char board[10][20];
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				board[i][j] = '-';
			}
		}
		board[human.getY()][human.getX()] = human.getShape(); // Human ��ġ ǥ��
		board[monster.getY()][monster.getX()] = monster.getShape(); // Monster ��ġ ǥ��
		board[food.getY()][food.getX()] = food.getShape(); // Food ��ġ ǥ��
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

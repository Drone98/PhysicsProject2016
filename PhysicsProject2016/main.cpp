#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#define PI 3.14159265
using namespace sf;
using namespace std;

int main()
{
	int n;
	cout << "Height of the ring - 465cm\n";
	cout << "Amount of experiments: ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		double x, y, v0, alpha, koeftv;
		cout << endl << i << " experiment\n" << "Distance to ring (not more 12.5 meters): ";
		cin >> x;
		x *= 100;
		cout << "Height of throw of the ball (not more 6 meters): ";
		cin >> y;
		y *= 100;
		cout << "The angle of incline (relatively vertical): ";
		cin >> alpha;
		cout << "The started speed ([0; 20] meters per second): ";
		cin >> v0;
		cout << "Type of surface(1 - soft(30%), 2 - medium(20%), 3 - steady(10%), 4 - ideally steady(0%)):";
		cin >> koeftv;
		koeftv = 0.6 + koeftv*0.1;
		RenderWindow window(VideoMode(1300, 650), "project");
		window.setVerticalSyncEnabled(true);
		int r = 10;
		y = 650 - y - 2 * r;
		double v0x, v0y, ay, square_size = 26, koef, t, dot1x, dot1y;
		koef = 1300 / square_size;
		v0 = v0 * koef / 1000;
		v0x = v0 * sin(alpha * PI / 180) * (-1);
		v0y = v0 * cos(alpha * PI / 180);
		ay = 9.8 * koef / 1000000;

		CircleShape ball(r);
		ball.setFillColor(Color(0, 255, 0));
		ball.setPosition(x + 2.7 * r + 5, y);

		RectangleShape shield(Vector2f(5, 50));
		shield.setPosition(Vector2f(0, 150));
		shield.setFillColor(Color(255, 0, 0));

		RectangleShape ring(Vector2f(2 * r * 1.1, 5));
		ring.setFillColor(Color(255, 255, 255));
		ring.setPosition(Vector2f(5 + r / 2, 180));

		RectangleShape shape(Vector2f(r / 2, 2));
		shape.setFillColor(Color(255, 0, 0));
		shape.setPosition(Vector2f(5, 180));

		dot1x = 2 * r*1.1 + 5 + r / 2;
		dot1y = 180;

		Clock time;
		while (window.isOpen()) {
			window.clear();
			window.draw(ball);
			window.draw(shield);
			window.draw(shape);
			window.draw(ring);
			window.display();
			Event event;

			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
			}
			t = time.getElapsedTime().asMilliseconds();
			x = x + v0x * t;
			y = y + v0y * t + ay * t * t / 2;
			if (y >= 630) {
				v0y = v0y * (-1) * koeftv;
				v0x = v0x * koeftv;
				y = 630;
			}
			if ((x <= 5) && (y > 150 - r / 3) && (y < 150 - r / 3 + 50)) {
				v0x = v0x * (-0.9);
				v0y = v0y * 0.9;
				x = 5;
			}
			if (x <= (5 + 2.7 * r) && y >= (180 - r) && y <= (185 - r)) {
				v0x = v0x * (-1);
			}
			if ((y >= 180 - r) && (y <= 180 - r / 2) && (x >= 5) && (x <= 7 + r / 2)) {
				v0x = 0;
			}
			if ((x >= 3 + 1.7 * r) && (x <= 7 + 1.7 * r) && (y >= 180 - r) && (y <= 180 - 0.75 * r)) {
				v0y = v0y * (-1);
			}
			v0y = v0y + ay * t;
			ball.setPosition(x, y);
			if (x < (-5) * r || x > 1400)
				window.close();
			if ((x >= 5 + r / 2) && (x <= 8 + r / 2) && (y >= 650 - 2 * r))
				window.close();
			if (y >= 650 - 2 * r && abs(v0x) <= 0.000001)
				window.close();
			time.restart();
		}
	}
	return 0;
}
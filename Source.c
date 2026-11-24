#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>

typedef struct {
	float x;
	float y;
	char name;
} Point;

typedef struct {
	char brand[50];
	char manufacturer[50];
	char type[50];
	int year;
	int reg_day;
	int reg_month;
	int reg_year;
} Car;

void pointPrint(Point z, Point p);
void put_point(Point z);
float dist(Point z, Point w);
Point point_center(Point z, Point w);
int quarter(Point z);
void put_car(Car c);

int main() {
	setlocale(LC_ALL, "RUS");

	Point a, b, m;

	puts("Введите название и координаты первой точки: ");
	scanf(" %c %f %f", &a.name, &a.x, &a.y);

	puts("Введите название и координаты второй точки:");
	scanf(" %c %f %f", &b.name, &b.x, &b.y);

	pointPrint(a, b);
	printf("Четверть точки %c: %d\n", a.name, quarter(a));
	printf("Четверть точки %c: %d\n", b.name, quarter(b));

	printf("Расстояние между точками равно: %.1f\n", dist(a, b));

	m = point_center(a, b);
	printf("Координаты середины отрезка: ");
	put_point(m);
	printf("\n\n");

	struct tm* mytime;
	time_t t;
	char msg[100];
	char line[85];
	int day = 0;
	char season[20];

	t = time(NULL);
	mytime = localtime(&t);

	printf("Текущее время %02d:%02d:%02d\n\n", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);

	if (mytime->tm_mon == 11) {
		day = mytime->tm_mday;
		strcpy(season, "зимы");
	}
	else if (mytime->tm_mon == 0) {
		day = 31 + mytime->tm_mday;
		strcpy(season, "зимы");
	}
	else if (mytime->tm_mon == 1) {
		day = 62 + mytime->tm_mday;
		strcpy(season, "зимы");
	}
	else if (mytime->tm_mon == 2) {
		day = mytime->tm_mday;
		strcpy(season, "весны");
	}
	else if (mytime->tm_mon == 3) {
		day = 31 + mytime->tm_mday;
		strcpy(season, "весны");
	}
	else if (mytime->tm_mon == 4) {
		day = 61 + mytime->tm_mday;
		strcpy(season, "весны");
	}
	else if (mytime->tm_mon == 5) {
		day = mytime->tm_mday;
		strcpy(season, "лета");
	}
	else if (mytime->tm_mon == 6) {
		day = 30 + mytime->tm_mday;
		strcpy(season, "лета");
	}
	else if (mytime->tm_mon == 7) {
		day = 61 + mytime->tm_mday;
		strcpy(season, "лета");
	}
	else if (mytime->tm_mon == 8) {
		day = mytime->tm_mday;
		strcpy(season, "осени");
	}
	else if (mytime->tm_mon == 9) {
		day = 30 + mytime->tm_mday;
		strcpy(season, "осени");
	}
	else if (mytime->tm_mon == 10) {
		day = 61 + mytime->tm_mday;
		strcpy(season, "осени");
	}

	sprintf(msg, " идет %d день %s ", day, season);

	int len = (int)strlen(msg);
	int left = (80 - len) / 2;
	int right = 80 - len - left;

	for (int row = 0; row < 10; row++) {
		if (row == 0 || row == 9) {
			for (int i = 0; i < 80; i++) line[i] = '*';
			line[80] = '\0';
		}
		else if (row == 4) {
			for (int i = 0; i < left; i++) line[i] = '*';
			sprintf(line + left, "%s", msg);
			for (int i = 0; i < right; i++) line[left + len + i] = '*';
			line[80] = '\0';
		}
		else {
			line[0] = '*';
			for (int i = 1; i < 79; i++) line[i] = ' ';
			line[79] = '*';
			line[80] = '\0';
		}
		printf("%s\n", line);
	}
	printf("\n");

	Car c;
	int current_year = mytime->tm_year + 1900;

	puts("Введите марку автомобиля:");
	scanf("%49s", c.brand);

	puts("Введите производителя:");
	scanf("%49s", c.manufacturer);

	puts("Введите тип автомобиля:");
	scanf("%49s", c.type);

	puts("Введите год выпуска:");
	scanf("%d", &c.year);

	puts("Введите дату регистрации (день месяц год через пробел):");
	scanf("%d %d %d", &c.reg_day, &c.reg_month, &c.reg_year);

	put_car(c);

	if (c.year < 2005 && c.reg_year == current_year) {
		puts("\nАвтомобиль подходит под условие (выпущен до 2005 года и зарегистрирован в этом году):");
		put_car(c);
	}
	else {
		puts("\nАвтомобиль не подходит под условие.");
	}

	return 0;
}

void pointPrint(Point z, Point p) {
	printf("Координаты точки %c = (%.1f %.1f)\n", z.name, z.x, z.y);
	printf("Координаты точки %c = (%.1f %.1f)\n", p.name, p.x, p.y);
}

void put_point(Point z) {
	printf("point %c (%.1f, %.1f)", z.name, z.x, z.y);
}

float dist(Point z, Point w) {
	float x, y, res;
	x = pow(z.x - w.x, 2);
	y = pow(z.y - w.y, 2);
	res = sqrt(x + y);
	return res;
}

Point point_center(Point z, Point w) {
	Point m;
	m.name = 'M';
	m.x = (z.x + w.x) / 2.0;
	m.y = (z.y + w.y) / 2.0;
	return m;
}

int quarter(Point z) {
	if (z.x > 0 && z.y > 0) return 1;
	if (z.x < 0 && z.y > 0) return 2;
	if (z.x < 0 && z.y < 0) return 3;
	if (z.x > 0 && z.y < 0) return 4;
	return 0;
}

void put_car(Car c) {
	printf("\nМарка автомобиля: %s\n", c.brand);
	printf("Производитель: %s\n", c.manufacturer);
	printf("Тип: %s\n", c.type);
	printf("Год выпуска: %d\n", c.year);
	printf("Дата регистрации: %02d.%02d.%d\n", c.reg_day, c.reg_month, c.reg_year);
}
#include <windows.h>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sys/timeb.h>
#include <tchar.h>

using namespace std;

void help_msg();			 // Help message output
void usb_check();			 // Check whether USB is currently mounted
static inline void progress_bar(int, int, int); // Progress bar output
void sleep(int);			// delay sleep() -> cross platform sleep function

int main(int argc, char* argv[]) {
	
	system("DIR /w");

	while (1) {
		if (argc < 3) {
			cout << endl << "[Error] The argument was not entered." << " [" << argc - 1 << " / 2]" << endl << endl;
			help_msg();
			exit(1);
		}
		else {

			// 입력한 인자 출력
			for (int i = 1; i < argc; i++) {
				cout << "argv[" << i << "] = " << argv[i] << endl;
			}
			break;
		}
	}

	/*
	// Progress Bar 함수테스트 라인
	int x, n, r, w;
	w = 30;
	n = 1000;

	cout << "progress_bar() 함수 테스트 시작!" << endl;
	for (int i = 0; i<n; i++) {
		progress_bar(i, n, w);
		sleep(3);
	}

	// Sleep 함수테스트 라인
	cout << "Sleep() 함수 테스트 - 3초 시작!" << endl;
	sleep(3000);
	cout << "3초 끝" << endl;
	*/

	return 0;
}

void help_msg() {
	using namespace std;
	cout << "Help:" << endl;
	cout << " Win : > USBackup [Source_Path] [Destination_Path]" << endl;
	cout << " example : > USBackup E:\\ D:\\Backup" << endl << endl;
	//exit(1);
}

void usb_check() {

}

static inline void progress_bar(int x, int n, int w) {
	// based on:
	// http://www.ross.click/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/
	static int cold = 0;
	static float time_elapsed;
	float time_to_end;
	static struct timeb start;
	struct timeb now;
	int i;

	// get the clock at the starting
	if (cold == 0) ftime(&start);

	// Calculuate the ratio of complete-to-incomplete.
	float ratio = x / (float)n;
	int c = (int)(ratio * w);

	// Only update if a new tick must be added
	if (c == cold) return;
	cold = c;

	// get the clock now
	ftime(&now);
	// calculate the remaining time
	time_elapsed = (now.time - start.time) + (now.millitm - start.millitm) / 1000.0;
	time_to_end = time_elapsed * (1.0 / ratio - 1.0);

	// Show the percentage complete.
	cout << "[";

	// Show the load bar.
	for (i = 0; i < c; i++) cout << "=";
	for (i = c; i < w; i++) cout << " ";

	cout << "] " << (int)(ratio * 100) << "%  " << time_to_end << "sec\r" << flush;

	if (c == w - 1) {
		cout << "[       D   o   n   e   !       ] 100%  0.00000sec" << endl;
	}

}

void sleep(int value) { // cross - platform sleep function
	clock_t time_end;
	time_end = clock() + value * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end) {}
}

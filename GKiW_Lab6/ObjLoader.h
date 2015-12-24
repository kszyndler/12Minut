#pragma once
#include<vector>

using namespace std;

struct SFace {
	int v[3];
	int n[3];
	int t[3];
};

GLuint LoadObj(string file);

// Wywo³anie tak utworzonej display listy w celu jej narysowania:
// glCallList(id_zwrocone_przez_LoadObj);

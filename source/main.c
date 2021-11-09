#include "SuperX.h"

int main() {
	if (InitSuperX()) {
		PrintLog("NOTE: initialization failed. Exiting SuperX...\n");
		return 1;
	}

	RunSuperX();
	CloseSuperX();

	return 0;
}

#include "SuperX.h"

int main() {
	if (InitSuperX())
		return 1;

	RunSuperX();
	CloseSuperX();

	return 0;
}

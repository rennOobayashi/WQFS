#include <iostream>
#include "OpenGLCode.h"
#include "WQFS.h"

int main() {
	OpenGLCode opengl(1000, 1000);
	WQFS wqfs(100);

	//wqfs.Test();

	opengl.update();
}
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL.h>
#include <gl/GL.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	SDL_Window* win = SDL_CreateWindow("Moteur",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		768,
		windowsFlags);

	SDL_GLContext context = SDL_GL_CreateContext(win);
	SDL_GL_MakeCurrent(win, context);

	bool appRunning = true;
	while (appRunning) {
		SDL_Event currEvent;
		while (SDL_PollEvent(&currEvent)) {

		}
		glViewport(0, 0, 1024, 768);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		glEnd();

		SDL_GL_SwapWindow(win);
	}
	
	printf("Hello world");
	return 0;
}
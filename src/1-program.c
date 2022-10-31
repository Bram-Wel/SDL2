#include "demo.h"

/**
 * init_instance - Initialization fxn
 *
 * @instance: SDL instance structure
 * Description: Holds the addresses of window instance & tied
 * renderer instance
 * Return: 0, or 1 on failure
 */
int init_instance(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialise SDL: %s\n",
				SDL_GetError());
		return (1);
	}
	/*New window instance*/
	instance->window = SDL_CreateWindow("SDL \\o/", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL Create new window Error %s\n",
				SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/*New renderer instance linked to new window*/
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL Create Renderer Error %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

/**
 * main - Make a loop
 *
 * Description: Clear the renderer, add info and flush it on each loop
 * Return: 0, 1 on error
 */
int main(void)
{
	/*Make an SDL instance*/
	SDL_Instance instance;

	if (init_instance(&instance) != 0)
		return (1);

	/*
	 * The string[condition] always evaluates true
	 * Makes an infinite loop
	 * EVERY LOOP makes[represents] a frame
	 */
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);

		if (poll_events() == 1)
			break;
		/*
		 * You can draw/add to renderer here
		 */
		draw_stuff(instance);
		SDL_RenderPresent(instance.renderer);
	}
	_quit(&instance);
	return (0);
}

/**
 * draw_stuff - Draws sth in the win
 *
 * @instance: Window and renderer instance
 */
void draw_stuff(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 10, 10, 100, 100);
}

/**
 * poll_events - Retrieve events on every frame. ie: each loop
 *
 * Return: -1 on quit or when escape key is pressed. 0 otherwise.
 */
int poll_events(void)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				/*If the escape key has been pressed*/
				if (key.keysym.scancode == 0x29)
					return (1);
				break;
		}
	}
	return (0);
}

/**
 * _quit - Destroys instances and Quits the program
 *
 * @instance: SDL2 instances
 */
void _quit(SDL_Instance *instance)
{
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	SDL_Quit();        
}

/**
* test - test fxn
*/
void test(void)
{
        printf("Works as expected")
}

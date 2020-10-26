
using namespace std;
#include "../includes/visualizer.hpp"

SDL_Texture		*bckTex;
SDL_Texture		*roomTex;
SDL_Texture		*pipeTex;
SDL_Rect		bckR;
SDL_Rect		roomR;
SDL_Rect		pipeR;

Visualizer::Visualizer()
{}

Visualizer::~Visualizer()
{}

void	Visualizer::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, \
							t_data *v, vector<Ants *> antv)
{
	SDL_Surface		*tmpSurface;
	int				flags;

	flags = 0;

	TTF_Init();
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL initialized!" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			cout << "Window created!" << endl;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
		isRunning = true;
	}
	else
		isRunning = false;
	SDL_GetWindowSize(window, &bckR.w, &bckR.h);
	bckR.x = 0;
	bckR.y = 0;
	roomR.h = ((bckR.h / (find_max(v->coors, 1) + 1) < bckR.w / (find_max(v->coors, 0) + 1)) \
				? bckR.h / (find_max(v->coors, 1) + 1) : bckR.w / (find_max(v->coors, 0) + 1));
	roomR.w = roomR.h;
	for (int i = 0; i < v->coors.size(); i++)
	{
		v->coors[i][0] *= roomR.w;
		v->coors[i][1] *= roomR.w;
	}
	pipeR.h = roomR.h / 5 * 2;
	for (int i = 0; i < antv.size(); i++)
		antv[i]->init(renderer, pipeR.h);
	tmpSurface = IMG_Load("assets/soil.jpg");
	bckTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	tmpSurface = IMG_Load("assets/Crate.png");
	roomTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	tmpSurface = IMG_Load("assets/pipe.jpg");
	pipeTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void	Visualizer::handleEvents()
{
	SDL_Event		event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT || (SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		isRunning = false;
}

void	Visualizer::update(t_data *v, vector<Ants *> *antv, double max_x, double max_y)
{
	count++;

	cout << count << endl;
}

void	Visualizer::render(t_data *v, vector<Ants *> *antv)
{
	double		angle;

	if (!roomR.x)
		scale_coor(v, ((((bckR.w - ((find_max(v->coors, 0) - find_min(v->coors, 0)))) / 2) - 2 * roomR.w)), \
						((((bckR.h - ((find_max(v->coors, 1) - find_min(v->coors, 1)))) / 2)) - 2 * roomR.w), roomR.w / 2);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bckTex, NULL, &bckR);
	for (int j = 0; j < v->links.size(); j++)
	{
		SDL_Point	center = {0, pipeR.h / 2};

		pipeR.x = (v->coors[v->links[j][0]][0]) + (roomR.w / 2);
		pipeR.y = (v->coors[v->links[j][0]][1] + (roomR.h / 2) - pipeR.h / 2);
		pipeR.w = sqrt(pow(abs(v->coors[v->links[j][0]][0] - v->coors[v->links[j][1]][0]), 2) + 
						(pow(abs(v->coors[v->links[j][0]][1] - v->coors[v->links[j][1]][1]), 2)));
		angle = atan2(v->coors[v->links[j][1]][1] - v->coors[v->links[j][0]][1],
						v->coors[v->links[j][1]][0] - v->coors[v->links[j][0]][0]);
		angle *= (180 / M_PI);
		SDL_RenderCopyEx(renderer, pipeTex, NULL, &pipeR, angle, &center, SDL_FLIP_NONE);
	}
	for (int j = 0; j < v->coors.size(); j++)
	{
		roomR.x = v->coors[j][0];
		roomR.y = v->coors[j][1];
		SDL_RenderCopy(renderer, roomTex, NULL, &roomR);
	}
	for (int j = 0; j < v->ants; j++)
	{
		(*antv)[j]->update(v, roomR.w);
		for (int i = 0; i < (*antv).size() && (*antv)[i]->antDone(v->coors[1][0] + ((roomR.w - pipeR.h) / 2), v->coors[1][1] + ((roomR.w - pipeR.h) / 2)); i++)
			if (i == (*antv).size() - 1)
				ants_in_end = true;
		(*antv)[j]->render(renderer);
	}
	if (!antsMoving(antv) && ants_in_end == false)
	{
		stringstream	ss;
		int				ant;
		int				temp;

		ss = stringstream();
		ss << v->moves[0];
		for (int i = 0; i < v->moves.size() - 1; i++)
			v->moves[i].swap(v->moves[i + 1]);
		v->moves.pop_back();
		while (ss >> ant)
		{
			ss >> temp;
			(*antv)[ant - 1]->getDesDir(v->coors[temp][0], v->coors[temp][1], roomR.w);
		}
	}
	SDL_RenderPresent(renderer);
}

void	Visualizer::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

bool	Visualizer::running()
{
	return isRunning;
}


using namespace std;
#include "../includes/visualizer.hpp"

SDL_Texture		*bckTex;
SDL_Texture		*roomTex;
SDL_Texture		*pipeTex;
SDL_Texture		*textTex;
SDL_Rect		bckR;
SDL_Rect		roomR;
SDL_Rect		pipeR;
SDL_Rect		textR;

Visualizer::Visualizer()
{}

Visualizer::~Visualizer()
{}

void	Visualizer::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, \
							t_data *v, vector<Ants *> antv)
{
	double			min_x;
	double			min_y;
	SDL_Surface		*tmpSurface;
	int				flags;

	flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0)
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
		font = TTF_OpenFont("assets/arial-bold.ttf", 16);
		speed > 0;
	}
	else
		speed = 0;
	SDL_GetWindowSize(window, &bckR.w, &bckR.h);
	bckR.x = 0;
	bckR.y = 0;
	roomR.h = ((bckR.h / (find_max(v->coors, 1) + 1) < bckR.w / (find_max(v->coors, 0) + 1)) \
				? bckR.h / (find_max(v->coors, 1) + 1) : bckR.w / (find_max(v->coors, 0) + 1));
	roomR.w = roomR.h;
	min_x = find_min(v->coors, 0) - 1;
	min_y = find_min(v->coors, 1) - 1;
	for (int i = 0; i < v->coors.size(); i++)
	{
		v->coors[i][0] -= min_x;
		v->coors[i][0] *= roomR.w;
		v->coors[i][1] -= min_y;
		v->coors[i][1] *= roomR.w;
	}
	scale_coor(v, ((((bckR.w - ((find_max(v->coors, 0) - find_min(v->coors, 0)))) / 2) - 2 * roomR.w)), \
					((((bckR.h - ((find_max(v->coors, 1) - find_min(v->coors, 1)))) / 2)) - 2 * roomR.w), roomR.w / 2);
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

void	Visualizer::handleEvents(vector<Ants *> *antv)
{
	SDL_Event		event;

	if (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT || (SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			speed = 0;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
		{
			for (int i = 0; i < (*antv).size(); i++)
				(*antv)[i]->changeImage(renderer);
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x)
			speed += 1;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z && speed > 1)
			speed -= 1;
	}
}

void	Visualizer::update(t_data *v, vector<Ants *> *antv)
{
	count++;
	cout << count << endl;
}

void	Visualizer::render(t_data *v, vector<Ants *> *antv)
{
	SDL_Surface	*textSurface;
	double		angle;

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
		SDL_RenderCopyEx(renderer, pipeTex, NULL, &pipeR, angle, &center, (angle <= 90 && angle > -90) ? SDL_FLIP_NONE: SDL_FLIP_VERTICAL);
	}
	for (int j = 0; j < v->coors.size(); j++)
	{
		roomR.x = v->coors[j][0];
		roomR.y = v->coors[j][1];
		if (j == 0)
		{
			TTF_SizeText(font, "START", &textR.w, &textR.h);
			textSurface = TTF_RenderText_Solid(font, "START", {202, 0, 42});
		}
		else if (j == 1)
		{
			TTF_SizeText(font, "**END**", &textR.w, &textR.h);
			textSurface = TTF_RenderText_Solid(font, "**END**", {75, 140, 97});
		}
		else
		{
			TTF_SizeText(font, v->names[j].c_str(), &textR.w, &textR.h);
			textSurface = TTF_RenderText_Solid(font, v->names[j].c_str(), {0, 0, 0});
		}
		textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
		textR.x = v->coors[j][0] + (roomR.w / 7);
		textR.y = v->coors[j][1] + (roomR.w / 7);
		SDL_RenderCopy(renderer, roomTex, NULL, &roomR);
		SDL_RenderCopy(renderer, textTex, NULL, &textR);
	}
	for (int j = 0; j < v->ants; j++)
	{
		(*antv)[j]->update(v, roomR.w, speed);
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
	SDL_FreeSurface(textSurface);
	SDL_RenderPresent(renderer);
}

void	Visualizer::clean()
{
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

bool	Visualizer::running()
{
	return (speed > 0);
}

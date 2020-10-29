
using namespace	std;
#include "../includes/visualizer.hpp"

void	Ants::init(SDL_Renderer *renderer, int dim)
{
	SDL_Surface		*tmpSurface;

	tmpSurface = IMG_Load("assets/ant.png");
	isDog = 0;
	antTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	antR.w = dim;
	antR.h = dim;
	for (int i = 0; i < 2; i++)
	{
		dir[i] = 0;
		des[i] = 0;
	}
	antR.x = 0;
	antR.y = 0;
	isMoving = false;
}

void	Ants::update(t_data *v, int dim, int speed)
{
	if (antR.x == 0 && antR.y == 0)
	{
		antR.x = v->coors[0][0] + ((dim - antR.w) / 2);
		antR.y = v->coors[0][1] + ((dim - antR.w) / 2);
	}
	if ((dir[0] > 0 && antR.x >= des[0]) || (dir[0] < 0 && antR.x <= des[0]) ||\
		(dir[1] > 0 && antR.y >= des[1]) || (dir[1] < 0 && antR.y <= des[1]))
	{
		antR.x = des[0];
		antR.y = des[1];
		isMoving = false;
	}
	else
	{
		antR.x += (dir[0] * speed);
		antR.y += (dir[1] * speed);
	}
}

void	Ants::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, antTex, NULL, &antR);
}

void	Ants::getDesDir(double x, double y, int dim)
{
	double		smallest;
	int			temp;

	temp = 1;
	des[0] = x + ((dim - antR.w) / 2);
	des[1] = y + ((dim - antR.w) / 2);
	smallest = abs(des[0] - antR.x);
	if (abs(des[1] - antR.y) != 0 && (abs(des[0] - antR.x) > abs(des[1] - antR.y) || smallest == 0))
		smallest = abs(des[1] - antR.y);

	dir[0] = (des[0] - antR.x) / smallest;// /10
	dir[1] = (des[1] - antR.y) / smallest;// /10

	// if (dir[0] == 0)
	// 	dir[1] *= ((des[1] - antR.y) / (double)dim / (double)2);
	// if (dir[1] == 0)
	// 	dir[0] *= ((des[0] - antR.x) / (double)dim / (double)2);

	isMoving = true;
}

bool	Ants::antDone(double end_x, double end_y)
{
	return (end_x == antR.x && end_y == antR.y);
}

void	Ants::changeImage(SDL_Renderer *renderer)
{
	SDL_Surface		*tmpSurface;

	if (isDog == 0)
	{
		tmpSurface = IMG_Load("assets/dog.png");
		antTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		isDog = 1;
	}
	else
	{
		tmpSurface = IMG_Load("assets/ant.png");
		antTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		isDog = 0;
	}
}

void	Ants::clean()
{

}

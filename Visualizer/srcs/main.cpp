
using namespace	std;
#include "../includes/visualizer.hpp"

bool	antsMoving(vector<Ants *> *antv)
{
	for (int i = 0; i < (*antv).size(); i++)
	{
		if ((*antv)[i]->moving())
			return (true);
	}
	// SDL_Delay(1000);
	return (false);
}

void	scale_coor(t_data *v, double adjust_x, double adjust_y, int odd)
{
	for (int i = 0; i < v->coors.size(); i++)
	{
		v->coors[i][0] += adjust_x + odd;
		v->coors[i][1] += adjust_y + odd;
	}
}

double	find_min(vector<vector<double>> coors, int pos)
{
	double		min;

	min = coors[0][pos];
	for (int i = 0; i < coors.size(); i++)
	{
		if (coors[i][pos] < min)
			min = coors[i][pos];
	}
	return (min);
}

double	find_max(vector<vector<double>> coors, int pos)
{
	double		max;

	max = 0;
	for (int i = 0; i < coors.size(); i++)
	{
		if (coors[i][pos] > max)
			max = coors[i][pos];
	}
	return (max);
}

int		main(int argc, char **argv)
{
	Visualizer 		*vis = nullptr;
	const int		FPS = 60;
	const int		frameDelay = 1000 / FPS;

	Uint32			frameStart;
	int				frameTime;

	t_data				v;
	vector<Ants *>		antv;

	get_input(&v);
	// for (int j = 0; j < v.moves.size(); j++)
	// 	cout << v.moves[j] << endl;
	// while (1);

	for (int i = 0; i < v.ants; i++)
		antv.push_back(new Ants);
	vis = new Visualizer();
	vis->init("Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false, &v, antv);
	// cout << v.coors[0][0] << ' ' << v.coors[0][1] << endl;

	while (vis->running())
	{
		frameStart = SDL_GetTicks();
		
		vis->handleEvents();
		vis->update(&v, &antv);
		vis->render(&v, &antv);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	vis->clean();
	return (0);
}

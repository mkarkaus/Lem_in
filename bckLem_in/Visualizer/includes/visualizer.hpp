
#ifndef		VISUALIZER_HPP
# define	VISUALIZER_HPP

# include <iostream>
# include <cmath>
# include <math.h>
# include <sstream>
# include <vector>
# include <bits/stdc++.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

typedef struct	s_data
{
	vector<vector<int>>		links;
	vector<vector<double>>	coors;
	vector<string>			names;
	vector<string>			moves;
	vector<string>			bckMoves;
	int						ants;
}				t_data;

# include "ants.hpp"

class	Visualizer {
	public:
		Visualizer();
		~Visualizer();

		void	init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, \
						t_data *v, vector<Ants *> antv);
		void	handleEvents(t_data *v, vector<Ants *> *antv);
		void	update(t_data *v, vector<Ants *> *antv);
		void	restart(t_data *v, vector<Ants *> *antv);
		void	drawLegend(SDL_Renderer *renderer, int dim);
		void	render(t_data *v, vector<Ants *> *antv);
		void	clean();
		bool	running();

	private:
		int				count = 0;
		bool			ants_in_end = false;
		int				speed = 1;
		TTF_Font		*font;
		SDL_Window		*window;
		SDL_Renderer	*renderer;
};

bool	antsMoving(vector<Ants *> *antv);
void	scale_coor(t_data *v, double mult_x, double mult_y, int odd);
double	find_min(vector<vector<double>> coors, int pos);
double	find_max(vector<vector<double>> coors, int pos);
void	get_input(t_data *v);

# endif

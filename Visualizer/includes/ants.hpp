
#ifndef		ANTS_HPP
# define	ANTS_HPP

# include "visualizer.hpp"

class	Ants {
	public:
		Ants()
		{};
		~Ants()
		{};

		void		init(SDL_Renderer *renderer, int dim);
		void		update(t_data *v, int dim, int speed);
		void		render(SDL_Renderer *renderer);
		void		getDesDir(double x, double y, int dim);
		void		changeImage(SDL_Renderer *renderer);
		void		clean();

		bool		antDone(double end_x, double end_y);
		bool		moving() { return (isMoving); };

	private:
		SDL_Texture	*antTex;
		SDL_Rect	antR;
		int			isDog = 0;
		double		dir[2] = {0, 0};
		double		des[2] = {0, 0};
		bool		isMoving;
};

#endif

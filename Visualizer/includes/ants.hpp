
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
		bool		character() { return (isDog); };
		bool		moving() { return (isMoving); };

	private:
		SDL_Texture	*antTex;
		SDL_Rect	antR;
		int			isDog;
		double		dir[2];
		double		des[2];
		bool		isMoving;
};

#endif

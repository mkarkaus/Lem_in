
using namespace	std;
#include "../includes/visualizer.hpp"

string	convert_moves(vector<string> names, string str)
{
	string				fresh;
	int					j;
	
	j = 0;
	fresh = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
			fresh.push_back(str[i]);
		else if (str[i] == ' ')
			fresh.push_back(str[i]);
		else if (str[i] == '-' && i++)
		{
			fresh.push_back(' ');
			j = 0;
			while (j < names.size() && str.compare(i, names[j].length(), names[j]) != 0)
				j++;
			fresh.append(to_string(j));
			while (i < str.length() && str[i + 1] != ' ')
				i++;
		}
	}
	return (fresh);
}

void	get_input(t_data *v)
{
	double					num;
	vector<int>				temp_int;
	vector<double>			temp_dbl;
	string					str;
	int						i;
	int						k;
	stringstream			ss;

	cin >> v->ants;
	getline(cin, str);
	v->coors.push_back({-1, -1});
	v->coors.push_back({-1, -1});
	v->names.push_back("start");
	v->names.push_back("end");

	while (getline(cin, str))
	{
		i = 0;
		k = 0;
		ss = stringstream();
		ss << str;

		if (str[0] == 'L')
			v->moves.push_back(convert_moves(v->names, str));
		else if (str.compare("##start") == 0 && getline(cin, str))
		{
			ss = stringstream();
			ss << str;
			ss >> v->names[0] >> v->coors[0][0] >> v->coors[0][1];
			v->coors[0][0] += 1;
			v->coors[0][1] += 1;
		}
		else if (str.compare("##end") == 0 && getline(cin, str))
		{
			ss = stringstream();
			ss << str;
			ss >> v->names[1] >> v->coors[1][0] >> v->coors[1][1];
			v->coors[1][0] += 1;
			v->coors[1][1] += 1;
		}
		else if (str.find(' ') <= str.length() && str[0] != '#')
		{
			str.clear();
			ss >> str;
			v->names.push_back(str);
			while (!ss.eof())
			{
				ss >> num;
				temp_dbl.push_back(num + 1);
			}
			v->coors.push_back(temp_dbl);
			temp_dbl.clear();
		}
		else if ((i = str.find('-')) > 0 && str[0] != '#')
		{
			while (v->names[k].compare(str.substr(0, i)))
				k++;
			temp_int.push_back(k);
			k = 0;
			while (v->names[k].compare(str.substr(i + 1)))
				k++;
			temp_int.push_back(k);
			v->links.push_back(temp_int);
			temp_int.clear();
		}
	}

	// for (int j = 0; j < v->moves.size(); j++)
	// 	cout << v->moves[j] << endl;
	// while (1);
	// for (int j = 0; j < v->links.size(); j++)
	// {
	// 	cout << v->links[j][0] << ' ';
	// 	cout << v->links[j][1] << endl;
	// }

	// for (int j = 0; j < v->coors.size(); j++)
	// {
	// 	cout << v->coors[j][0] << ' ';
	// 	cout << v->coors[j][1] << endl;
	// }
}

# Lem_in
Second project of algorithm-branch of 42 coding curriculum in which a colony of ants must move from room 'start' to room 'end' through tunnels and rooms in as few turns as possible. :ant:

![](lem-in.gif)
:warning:**IMPORTANT: In case of severe myrmecophobia: Press 'C' during visualizer execution**:warning:

#### Usage:
``` 
make && ./lem-in [-hlqrs] < maps/subject3.map
```
#### Usage with visualizer:
``` 
make && cp lem-in Visualizer/ && cd Visualizer/ && make && ./lem-in < ../maps/subject3.map | ./visu
```
**Note: the visualizer needs libraries SDL2, SDL2-image and SDL2-ttf to be installed to work.**
#### Options:
```
-h: help
-l: show amount of lines used
-q: quiet mode, only print moves
-r: print routes
-s: print anthill stats
```
#### Output of lem-in executable:
```
11
##start
start 4 0
3 2 2
##end
end 4 6
4 0 4
1 4 2
2 4 4
5 8 2
6 8 4
start-1
3-4
2-4
1-5
6-5
end-6
1-2
2-end
3-start

L2-1 L1-3
L4-1 L3-3 L2-5 L1-4
L6-1 L5-3 L4-5 L3-4 L2-6 L1-2
L8-1 L7-3 L6-5 L5-4 L4-6 L3-2 L2-end L1-end
L10-1 L9-3 L8-5 L7-4 L6-6 L5-2 L4-end L3-end
L11-3 L10-5 L9-4 L8-6 L7-2 L6-end L5-end
L11-4 L10-6 L9-2 L8-end L7-end
L11-2 L10-end L9-end
L11-end
```
The first part of the output before the double newline is the map like it was when it was passed to the program.

The map consists of (in order):
- the amount of ants
- the rooms in the following format: `[name] [x coordinate] [y coordinate]` (commands `##start` and `##end` indicate that the following room is the start and the end room respectively)
- the links (aka tunnels) in following format: `[room1]-[room2]`
- optional comments that are always prepended with one `#` and are irrelevant to the execution of the program

The second part is the moves in following format: `L[number of ant]-[name of the room it moved to]`

## Algorithm
Our final choice of algorithm was Edmonds Karp 'network flow' algorithm because of speed of its execution and excellent results in terms of turns that all ants needed to get to 'end' room. The Edmonds Karp that we implemented was slightly simpler than normal due to all the tunnels being able to occupy only one ant at a time.

One path-finding cycle consists of flow search and set search which both use flow values of the tunnels to seek paths.

Flow values in our implementation are:
- `2` the tunnel has not been used yet by any path in either direction
- `1` path has traversed this tunnel to this same direction
- `-1` path has used this tunnel to the opposite direction
- `0` path has been used to both directions and therefore has been blocked'

Each tunnel of the map gets two flow values, one for each direction. First all the flow values of the tunnels are initiated to `2`.

The algorithm starts new path-finding cycles from flow search as long as there are available rooms (flow is `2` or `-1`) connected to start.

### Flow search

This part of the search can only move through tunnels whose flow value in the direction the path is going is `2` or `-1`. The algorithm starts with searching the shortest path using BFS (Breadth first search). After finding one path all of its tunnels' flow values towards end are set to `1` and towards the start to `-1`. In cases where there is only one path left and it ends up in deadend the flow values of that path are still updated. If the found path goes through tunnels that have `-1` to the direction it is going the flow values of both directions are changed to `0` which essentially means that the tunnel cannot be used anymore in any part of the search. Because all the paths this search has found have modified the flow values of the tunnels, the search can't find the same path again.

### Set search

The set search uses only tunnels that have flow value of `1` to the direction we are moving. After every flow search a set search is performed. Set search uses BFS as well but difference is that now we save every non-intersecting path that we find to the current set. After the first flow search there will be only one path for set search to take. The sets found by set search will become more complex and give a better end result (in terms of how few turns it takes for ants to complete with these paths) after couple of flow searches. The set search does NOT change any flow values.

When the set is complete and all parallel paths have been found the turn count of using the new set is compared to the turn count of using the thus far discovered best set. If the new one yields better result then we replace the old one with the new. This turn count calculation takes into account the amount of ants and the number and lengths of the paths. This concludes one path-finding cycle.

## Visualizer
We decided to build a Visualizer to ease the process of testing different algorithms to find the best one. We chose to go with C++ for the visualizer solely for the purpose of learning its built-in functionalities and the use of classes.

Visuals were created using the SDL2 libraries and functions. They were perfect for our needs and provided tools to explore the basics of graphic libraries.

Sprites and elements were from [freepik](https://freepik.com) and [gameart2d](https://www.gameart2d.com/).

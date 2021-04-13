# Lem_in
Second project of algorithm-branch of 42 coding curriculum in which a colony of ants must move from room 'start' to room 'end' through tunnels and rooms in as few turns as possible.

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

This part of the search can only move through tunnels whose flow value in the direction the path is going is `2` or `-1`. The algorithm starts with searching the shortest path using BFS (Breadth first search). After finding one path all of its tunnels' flow values towards end are set to `1` and towards the start to `-1`. If the found path goes through tunnels that have `-1` to the direction it is going the flow values of both directions are changed to `0` which essentially means that the tunnel cannot be used anymore in any part of the search. Because all the paths this search has found have modified the flow values of the tunnels, the search can't find the same path again.

### Set search

The set search uses only tunnels that have flow value of `1` to the direction we are moving. After every flow search a set search is performed. Set search uses BFS as well but difference is that now we save every non-intersecting path that we find to the current set. After the first flow search there will be only one path for set search to take. The sets found by set search will become more complex and give a better end result (in terms of how few turns it takes for ants to complete with these paths) after couple of flow searches.

When the set is complete and all parallel paths have been found the turn count of using the new set is compared to the turn count of using the thus far discovered best set. If the new one yields better result then we replace the old one with the new. This turn count calculation takes into account the amount of ants and the number and lengths of the paths. This concludes one path-finding cycle.

## Visualizer
We decided to build a Visualizer to ease the process of testing different algorithms to find the best one. We chose to go with C++ for the visualizer solely for the purpose of learning its built-in functionalities and the use of classes.

Visuals were created using the SDL2 libraries and functions. They were perfect for our needs and provided tools to explore the basics of graphic libraries.

Here is what the algorithm in our visualizer looks like in action:

![](lem-in.gif)
**In case of severe myrmecophobia: Press 'C' during execution**

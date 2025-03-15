#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

const void print_graph(const std::vector<std::vector<int>>& graph)
{
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			std::cout << graph[i][j] << " ";
		}
		std::cout<<std::endl;
	}
}

const void print_distances(const std::vector<int>& distances)
{
	for (int i = 0; i < distances.size(); i++)
	{
		std::cout << distances[i] << std::endl;
	}
}

void bfs(const std::vector<std::vector<int>>& graph, const int& source, std::vector<int>& distances)
{
	std::queue<int> vertex_queue;
	std::vector<bool> visited_vertexes(distances.size(), false);

	vertex_queue.push(source);
	distances[source] = 0;
	visited_vertexes[source] = true;

	while (!vertex_queue.empty())
	{
		int v = vertex_queue.front();
		vertex_queue.pop();

		for (int i = 0; i < graph[v].size(); i++) // current vertex neighbours
		{
			if (!visited_vertexes[graph[v][i]])
			{
				distances[graph[v][i]] = distances[v] + 1;
				visited_vertexes[graph[v][i]] = true;
				vertex_queue.push(graph[v][i]);
			}
		}
	}
}

int main()
{
	std::vector<std::vector<int>> graph; // graph as an adjacency list
	int source = 0; // the vertex from which need to calculate all the distances
	int count_vertexes = 0, count_edges = 0;

	std::ifstream file("graph.txt"); // open a file
	if (file.is_open())
	{
		file >> count_vertexes >> count_edges;
		graph.resize(count_vertexes);

		int v1 = 0, v2 = 0;
		for (int i = 0; i < count_edges; i++)
		{
			file >> v1 >> v2;
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}
		file >> source;
		file.close();
	}

	std::vector<int> distances(count_vertexes, 0); // all distances from source vertex
	bfs(graph, source, distances);
	print_distances(distances);

	return 0;
}
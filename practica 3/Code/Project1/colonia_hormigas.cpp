#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <fstream>

class AntColony {
public:
    AntColony(std::vector<std::vector<double>>& distances, int n_ants, int n_best, int n_iterations, double decay, double alpha = 1, double beta = 1)
        : distances(distances), n_ants(n_ants), n_best(n_best), n_iterations(n_iterations), decay(decay), alpha(alpha), beta(beta) {
        all_inds.resize(distances.size());
        for (int i = 0; i < distances.size(); ++i)
            all_inds[i] = i;
        pheromone.assign(distances.size(), std::vector<double>(distances.size(), 1.0 / distances.size()));
    }

    std::pair<std::vector<int>, double> run() {
        std::vector<double> distance_logs;
        std::vector<int> shortest_path;
        double best_distance = std::numeric_limits<double>::max();
        std::vector<int> all_time_shortest_path;
        for (int i = 0; i < n_iterations; ++i) {
            auto all_paths = gen_all_paths();
            spread_pheronome(all_paths, n_best, shortest_path);
            shortest_path = *std::min_element(all_paths.begin(), all_paths.end(), [](const auto& p1, const auto& p2) {
                return p1.second < p2.second;
                }).first;
            if (shortest_path[1] < best_distance) {
                best_distance = shortest_path[1];
                all_time_shortest_path = shortest_path;
            }
            distance_logs.push_back(best_distance);
        }
        return std::make_pair(all_time_shortest_path, distance_logs);
    }

private:
    std::vector<std::vector<double>> distances;
    std::vector<std::vector<double>> pheromone;
    std::vector<int> all_inds;
    int n_ants;
    int n_best;
    int n_iterations;
    double decay;
    double alpha;
    double beta;

    void spread_pheronome(const std::vector<std::pair<std::vector<int>, double>>& all_paths, int n_best, const std::vector<int>& shortest_path) {
        std::vector<std::pair<std::vector<int>, double>> sorted_paths = all_paths;
        std::sort(sorted_paths.begin(), sorted_paths.end(), [](const auto& p1, const auto& p2) {
            return p1.second < p2.second;
            });

        for (int i = 0; i < n_best; ++i) {
            const auto& path = sorted_paths[i].first;
            for (int move : path) {
                pheromone[move][path[1]] += 1.0 / distances[move][path[1]];
            }
        }
    }

    double gen_path_dist(const std::vector<int>& path) {
        double total_dist = 0;
        for (int ele : path) {
            total_dist += distances[ele][path[1]];
        }
        return total_dist;
    }

    std::vector<std::pair<std::vector<int>, double>> gen_all_paths() {
        std::vector<std::pair<std::vector<int>, double>> all_paths;
        for (int i = 0; i < n_ants; ++i) {
            auto path = gen_path(0);
            all_paths.emplace_back(std::make_pair(path, gen_path_dist(path)));
        }
        return all_paths;
    }

    std::vector<int> gen_path(int start) {
        std::vector<int> path;
        std::unordered_set<int> visited;
        visited.insert(start);
        int prev = start;
        for (int i = 0; i < distances.size() - 1; ++i) {
            int move = pick_move(pheromone[prev], distances[prev], visited);
            path.push_back(prev);
            prev = move;
            visited.insert(move);
        }
        path.push_back(prev); // going back to where we started
        return path;
    }

    int pick_move(const std::vector<double>& pheromone, const std::vector<double>& dist, const std::unordered_set<int>& visited) {
        std::vector<double> pheromone_copy = pheromone;
        for (int v : visited) {
            pheromone_copy[v] = 0;
        }

        std::vector<double> row(distances.size());
        for (int i = 0; i < distances.size(); ++i) {
            row[i] = pow(pheromone_copy[i], alpha) * pow(1.0 / dist[i], beta);
        }

        double row_sum = std::accumulate(row.begin(), row.end(), 0.0);
        std::vector<double> norm_row(distances.size());
        for (int i = 0; i < distances.size(); ++i) {
            norm_row[i] = row[i] / row_sum;
        }

        std::discrete_distribution<int> distribution(norm_row.begin(), norm_row.end());
        return distribution(engine);
    }
};

int main() {
    // Load distances from JSON or create your own distances matrix
    // ...

    AntColony ant_colony(distances, 50, 50, 150, 0.7, 1, 1);
    auto result = ant_colony.run();

    std::cout << "Shortest path: ";
    for (int city : result.first) {
        std::cout << city << " ";
    }
    std::cout << "\n";

    for (double dist : result.second) {
        std::cout << dist << " ";
    }
    std::cout << "\n";

    return 0;
}

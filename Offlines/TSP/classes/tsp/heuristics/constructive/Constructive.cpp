#include "Constructive.hpp"

Constructive::Constructive(Graph& graph) : Heuristic(graph),  version(Versions::GREEDY), starting_node(0) {}

void Constructive::set_version(Versions version) {
    this->version = version; 
}
Versions Constructive::get_version() const { return version; }

int Constructive::select_from_candidates(const vector<pair<int, long double>>& candidates) {
    int limit;
    switch (version) {
        case Versions::GREEDY:
            return candidates.front().first;
        
        case Versions::SEMI_GREEDY_3:
            limit = min(3, static_cast<int>(candidates.size()));
            break;

        case Versions::SEMI_GREEDY_5:
            limit = min(5, static_cast<int>(candidates.size()));
            break;
        default:
            limit = 1;
            break;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, limit - 1);
    return candidates[dis(gen)].first;
}

void Constructive::set_starting_node(int node) { this->starting_node = node; }
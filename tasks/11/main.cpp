#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <memory>

using namespace std;

class CGraph{
public:
    CGraph() = default;

    //создание зависимостей вершин
    CGraph & add(const pair<string, string>& depend){
        if (depends.find(depend.first) != depends.end()){
            depends.find(depend.first)->second.insert(depend.second);
        }
        else{
            set<string> newSet;
            newSet.insert(depend.second);
            depends.emplace(depend.first, newSet);
        }

        if (depends.find(depend.second) == depends.end()){
            depends.emplace(depend.second, set<string> ());
        }

        return *this;
    }

    //поиск цикла
    bool hasCycle(){
        map<string, int> inDegree;
        queue<string> toVisit;

        //инициализация массива для подсчета количества входящих эту вершину вершин
        for (const auto& node : depends){
            inDegree.emplace(node.first, 0);
        }

        //подсчет входящих "стрелочек" в конкретную вершину
        for (const auto& node : depends){
            for (const auto& inNode : depends){
                if (inNode.second.find(node.first) != inNode.second.end()){
                    inDegree[node.first]++;
                }
            }
        }

        //начинаем обработку с нижней вершины
        for (const auto& degree : inDegree){
            if (degree.second == 0){
                toVisit.push(degree.first);
            }
        }

        int visited = 0;

        //проход по графу(бфс)
        while (!toVisit.empty()){
            auto degree = toVisit.front();
            toVisit.pop();
            visited++;

            //смотрим на соседей, уменьшаем им значение входящих "стрелок"
            if (depends.find(degree) != depends.end()) {
                for (const auto &neigh: depends.find(degree)->second) {
                    inDegree.find(neigh)->second--;

                    //добавление в очередь
                    if (inDegree.find(neigh)->second == 0){
                        toVisit.push(neigh);
                    }
                }
            }
        }
        //должны обработаться все вершины по разу, в противном случае - цикл
        return visited != depends.size();
    }
private:
    map<string, set<string>> depends;
};

int main() {
    CGraph gr;
    gr.add({"A", "B"});
    gr.add({"B", "C"});
    gr.add({"C", "A"});

    CGraph newGr;
    newGr.add({"A", "B"});
    newGr.add({"B", "C"});
    newGr.add({"A", "C"});

    cout << "Res of gr : " << gr.hasCycle() << endl;
    cout << "Res of newGr : " << newGr.hasCycle() << endl;

    return 0;
}

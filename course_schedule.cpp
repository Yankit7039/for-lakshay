#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Create adjacency list - map each course to its prerequisites
        vector<vector<int>> preMap(numCourses);
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            preMap[course].push_back(prerequisite);
        }
        
        // Set to store courses in current DFS path
        unordered_set<int> visiting;
        
        // DFS function to detect cycles
        auto dfs = [&](int course, auto& dfs_ref) -> bool {
            // If course is in current path, cycle detected
            if (visiting.find(course) != visiting.end()) {
                return false;
            }
            
            // If no prerequisites, course can be completed
            if (preMap[course].empty()) {
                return true;
            }
            
            // Add course to current path
            visiting.insert(course);
            
            // Check all prerequisites
            for (int prerequisite : preMap[course]) {
                if (!dfs_ref(prerequisite, dfs_ref)) {
                    return false;
                }
            }
            
            // Remove course from current path
            visiting.erase(course);
            
            // Clear prerequisites (optimization for future calls)
            preMap[course].clear();
            
            return true;
        };
        
        // Check each course
        for (int course = 0; course < numCourses; course++) {
            if (!dfs(course, dfs)) {
                return false;
            }
        }
        
        return true;
    }
};

// Test function
void testSolution() {
    Solution sol;
    
    // Test case 1: numCourses = 2, prerequisites = [[0,1]]
    vector<vector<int>> prerequisites1 = {{0, 1}};
    cout << "Test 1: " << (sol.canFinish(2, prerequisites1) ? "true" : "false") << endl;
    
    // Test case 2: numCourses = 2, prerequisites = [[1,0],[0,1]]
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    cout << "Test 2: " << (sol.canFinish(2, prerequisites2) ? "true" : "false") << endl;
    
    // Test case 3: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    vector<vector<int>> prerequisites3 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    cout << "Test 3: " << (sol.canFinish(4, prerequisites3) ? "true" : "false") << endl;
    
    // Test case 4: Cycle case - [[1,0],[0,2],[2,1]]
    vector<vector<int>> prerequisites4 = {{1, 0}, {0, 2}, {2, 1}};
    cout << "Test 4: " << (sol.canFinish(3, prerequisites4) ? "true" : "false") << endl;
}

int main() {
    testSolution();
    return 0;
}
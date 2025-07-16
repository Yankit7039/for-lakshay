# Course Schedule Problem - C++ Solution

## Problem Summary
Given `numCourses` and a list of `prerequisites` where `prerequisites[i] = [a, b]` means course `b` must be completed before course `a`, determine if it's possible to complete all courses.

## Solution Approach: DFS Cycle Detection

### Key Insights
1. **Graph Representation**: Treat courses as nodes and prerequisites as directed edges
2. **Cycle Detection**: If there's a cycle in the graph, it's impossible to complete all courses
3. **DFS Traversal**: Use DFS to detect cycles by tracking the current path

### Algorithm Steps

1. **Build Adjacency List**: Create a graph where each course points to its prerequisites
2. **DFS with Cycle Detection**: 
   - Use a `visiting` set to track courses in the current DFS path
   - If we encounter a course already in the current path, a cycle exists
3. **Optimization**: Clear prerequisites after processing to avoid redundant work

### C++ Implementation Details

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 1. Build adjacency list
        vector<vector<int>> preMap(numCourses);
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            preMap[course].push_back(prerequisite);
        }
        
        // 2. Track current DFS path
        unordered_set<int> visiting;
        
        // 3. DFS with cycle detection
        auto dfs = [&](int course, auto& dfs_ref) -> bool {
            // Cycle detected if course is already in current path
            if (visiting.find(course) != visiting.end()) {
                return false;
            }
            
            // Base case: no prerequisites
            if (preMap[course].empty()) {
                return true;
            }
            
            // Add to current path
            visiting.insert(course);
            
            // Check all prerequisites
            for (int prerequisite : preMap[course]) {
                if (!dfs_ref(prerequisite, dfs_ref)) {
                    return false;
                }
            }
            
            // Remove from current path and clear prerequisites
            visiting.erase(course);
            preMap[course].clear();  // Optimization
            
            return true;
        };
        
        // 4. Check all courses
        for (int course = 0; course < numCourses; course++) {
            if (!dfs(course, dfs)) {
                return false;
            }
        }
        
        return true;
    }
};
```

### Time and Space Complexity
- **Time Complexity**: O(V + E) where V = number of courses, E = number of prerequisites
- **Space Complexity**: O(V + E) for the adjacency list and recursion stack

### Test Results
- Test 1: `numCourses = 2, prerequisites = [[0,1]]` → **true**
- Test 2: `numCourses = 2, prerequisites = [[1,0],[0,1]]` → **false** (cycle)
- Test 3: `numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]` → **true**
- Test 4: `numCourses = 3, prerequisites = [[1,0],[0,2],[2,1]]` → **false** (cycle)

### Key C++ Features Used
1. **Lambda Functions**: Used for the DFS recursive function with capture-by-reference
2. **unordered_set**: For O(1) lookup in the visiting set
3. **vector<vector<int>>**: For the adjacency list representation
4. **Auto Parameter**: Used `auto& dfs_ref` for recursive lambda calls

This solution efficiently detects cycles in the course dependency graph using DFS traversal.
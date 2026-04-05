

// // // // #pragma once
// // // // #include <vector>
// // // // #include <string>
// // // // #include "Graph.h"

// // // // class GraphVisualizer {
// // // // public:
// // // //     int numNodes;
// // // //     bool isDirected;
// // // //     AlgoType currentAlgo;
// // // //     struct Edge { int u, v, weight; };
// // // //     std::vector<Edge> allEdges;
// // // //     std::vector<std::vector<int>> adjForLayout;
// // // //     std::vector<int> anim_nodes;
// // // //     std::vector<std::pair<int, int>> anim_edges;
// // // //     std::vector<std::vector<float>> nodes;
// // // //     std::vector<int> nodeGroups;
// // // //     int currentStep;
// // // //     int maxSteps;
// // // //     float rotateX, rotateY, rotateZ, cameraZ;
// // // //     // Member variables mein ye line add karo:
// // // //      int finalDist;
// // // //      int totalSCC = 0;
// // // //      // 🔥 COLORS ARRAY (SCC ke liye)
// // // //     float sccColors[10][3] = {
// // // //         {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
// // // //         {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
// // // //         {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
// // // //     };

// // // //     void assignPositions();
// // // //     void drawNode(float x, float y, float z, int id);
// // // //     void drawEdge(float x1, float y1, float z1, float x2, float y2, float z2, int weight, bool isHighlighted);
// // // //     void addBaseEdge(int u, int v, int weight = 0);

// // // // public:
// // // //     GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
// // // //     GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
// // // //     void visualize(int argc, char** argv);
// // // //     void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
// // // //     void display();
// // // //     void update();
// // // //     void keyboard(unsigned char key, int x, int y);
// // // //     void reshape(int w, int h);
// // // // };

// // // #ifndef VISUALGRAPHDSA_H
// // // #define VISUALGRAPHDSA_H

// // // #include <vector>
// // // #include <string>
// // // #include "Graph.h"

// // // class GraphVisualizer {
// // // public:
// // //     int numNodes;
// // //     bool isDirected;
// // //     AlgoType currentAlgo;
// // //     struct Edge { int u, v, weight; };
// // //     std::vector<Edge> allEdges;
// // //     std::vector<std::vector<int>> adjForLayout;
// // //     std::vector<int> anim_nodes;
// // //     std::vector<std::pair<int, int>> anim_edges;
// // //     std::vector<std::vector<float>> nodes;
    
// // //     int currentStep;
// // //     int maxSteps;
// // //     float rotateX, rotateY, cameraZ;
    
// // //     int finalDist;
// // //     int srcNode;  // 🔥 Added
// // //     int destNode; // 🔥 Added
// // //     int totalSCC = 0;
    
// // //     float sccColors[10][3] = {
// // //         {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
// // //         {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
// // //         {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
// // //     };

// // //     void assignPositions();

// // // public:
// // //     GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
// // //     GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
// // //     void visualize(int argc, char** argv);
// // //     void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
// // //     void display();
// // //     void update();
// // //     void keyboard(unsigned char key, int x, int y);
// // //     void reshape(int w, int h);
// // // };

// // // #endif

// // #pragma once
// // #include <vector>
// // #include <string>
// // #include "Graph.h"

// // class GraphVisualizer {
// // public:
// //     int numNodes;
// //     bool isDirected;
// //     AlgoType currentAlgo;
// //     struct Edge { int u, v, weight; };
// //     std::vector<Edge> allEdges;
// //     std::vector<std::vector<int>> adjForLayout;
// //     std::vector<int> anim_nodes;
// //     std::vector<std::pair<int, int>> anim_edges;
// //     std::vector<std::vector<float>> nodes;
    
// //     int currentStep;
// //     int maxSteps;
// //     float rotateX, rotateY, cameraZ;
    
// //     int finalDist;
// //     int srcNode;  
// //     int destNode; 
// //     int totalSCC = 0;
    
// //     float sccColors[10][3] = {
// //         {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
// //         {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
// //         {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
// //     };

// //     void assignPositions();

// // public:
// //     GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
// //     GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
// //     void visualize(int argc, char** argv);
// //     void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
// //     void display();
// //     void update();
// //     void keyboard(unsigned char key, int x, int y);
// //     void reshape(int w, int h);
// // };
// //
// #ifndef VISUALGRAPHDSA_H
// #define VISUALGRAPHDSA_H

// #include <vector>
// #include <string>
// #include "Graph.h"

// class GraphVisualizer {
// public:
//     int numNodes;
//     bool isDirected;
//     AlgoType currentAlgo;
//     struct Edge { int u, v, weight; };
//     std::vector<Edge> allEdges;
//     std::vector<std::vector<int>> adjForLayout;
//     std::vector<int> anim_nodes;
//     std::vector<std::pair<int, int>> anim_edges;
//     std::vector<std::vector<float>> nodes;
    
//     int currentStep;
//     int maxSteps;
//     float rotateX, rotateY, cameraZ;
    
//     int finalDist;
//     int srcNode;  
//     int destNode; 
//     int totalSCC = 0;
    
//     float sccColors[10][3] = {
//         {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
//         {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
//         {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
//     };

//     void assignPositions();

// public:
//     GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
//     GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
//     void visualize(int argc, char** argv);
//     void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
//     void display();
//     void update();
//     void keyboard(unsigned char key, int x, int y);
//     void reshape(int w, int h);
// };

// #endif
//
// #ifndef VISUALGRAPHDSA_H
// #define VISUALGRAPHDSA_H

// #include <vector>
// #include <string>
// #include "Graph.h"

// class GraphVisualizer {
// public:
//     int numNodes;
//     vector<int> nodeLevels;
//     int currentLevelDisplay = 0;
//     float cameraZ = 28.0f; // Default door rakha hai taaki sab dikhe
//     bool isDirected;
//     bool isWeighted; // 🔥 NAYA VARIABLE: Check karne ke liye ki graph weighted hai ya nahi
//     AlgoType currentAlgo;
//     struct Edge { int u, v, weight; };
//     std::vector<Edge> allEdges;
//     std::vector<std::vector<int>> adjForLayout;
//     std::vector<int> anim_nodes;
//     std::vector<std::pair<int, int>> anim_edges;
//     std::vector<std::vector<float>> nodes;
    
//     int currentStep;
//     int maxSteps;
//     float rotateX, rotateY, cameraZ;
    
//     int finalDist;
//     int srcNode;  
//     int destNode; 
//     int totalSCC = 0;
    
//     float sccColors[10][3] = {
//         {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
//         {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
//         {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
//     };

//     void assignPositions();

// public:
//     GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
//     GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
//     void visualize(int argc, char** argv);
//     void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
//     void display();
//     void update();
//     void keyboard(unsigned char key, int x, int y);
//     void reshape(int w, int h);
// };

// #endif



#ifndef VISUALGRAPHDSA_H
#define VISUALGRAPHDSA_H

#include <vector>
#include <string>
#include "Graph.h"

class GraphVisualizer {
public:
    int numNodes;
    std::vector<int> nodeLevels; // 🔥 FIX 1: std:: add kiya
    int currentLevelDisplay = 0;
    bool isDirected;
    bool isWeighted; 
    AlgoType currentAlgo;
    struct Edge { int u, v, weight; };
    std::vector<Edge> allEdges;
    std::vector<std::vector<int>> adjForLayout;
    std::vector<int> anim_nodes;
    std::vector<std::pair<int, int>> anim_edges;
    std::vector<std::vector<float>> nodes;
    
    int currentStep;
    int maxSteps;
    
    // 🔥 FIX 2: Ek hi line mein saare camera variables aur cameraZ ko 28.0f value de di
    float rotateX = 0.0f, rotateY = 0.0f, cameraZ = 28.0f; 
    
    int finalDist;
    int srcNode;  
    int destNode; 
    int totalSCC = 0;
    
    float sccColors[10][3] = {
        {1.0, 0.2, 0.2}, {0.2, 1.0, 0.2}, {0.2, 0.6, 1.0}, 
        {1.0, 1.0, 0.2}, {1.0, 0.2, 1.0}, {0.2, 1.0, 1.0},
        {1.0, 0.5, 0.0}, {0.5, 0.0, 1.0}, {0.0, 0.5, 0.5}, {0.7, 0.7, 0.7}
    };

    void assignPositions();

public:
    GraphVisualizer(WeightedGraph& wg, int totalNodes, bool directed);
    GraphVisualizer(UnweightedGraph& ug, int totalNodes, bool directed);
    void visualize(int argc, char** argv);
    void drawText(float x, float y, float z, std::string text, float r=1.0f, float g=1.0f, float b=1.0f);
    void display();
    void update();
    void keyboard(unsigned char key, int x, int y);
    void reshape(int w, int h);
};

#endif

// // // // // // // #include "../Include/VisualGraphDSA.h"
// // // // // // // #include <GL/freeglut.h>
// // // // // // // #include <cmath>

// // // // // // // using namespace std;

// // // // // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : wg.adjlist) {
// // // // // // //         for (auto const& nbr : p.second) {
// // // // // // //             if (d || p.first < nbr.first) {
// // // // // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : ug.adjlist) {
// // // // // // //         for (int v : p.second) {
// // // // // // //             if (d || p.first < v) {
// // // // // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // void GraphVisualizer::display() {
// // // // // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // // // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // // // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // // // // //     for (auto& e : allEdges) {
// // // // // // //         bool highlight = false;
// // // // // // //         for (auto& ae : anim_edges) if (ae.first == e.u && ae.second == e.v) highlight = true;
// // // // // // //         if (highlight) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // // // // //             glLineWidth(3);
// // // // // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // // // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]);
// // // // // // //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // // // // //     }

// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         bool active = false;
// // // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) if (anim_nodes[j] == i) active = true;
// // // // // // //         if (active) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // // // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // // // // //             else glColor3f(1, 0, 0);
// // // // // // //         } else glColor3f(0.2, 0.4, 0.8);
// // // // // // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]);
// // // // // // //         glutSolidSphere(0.2, 20, 20); glPopMatrix();
// // // // // // //     }
// // // // // // //     glutSwapBuffers();
// // // // // // // }

// // // // // // // void GraphVisualizer::assignPositions() {
// // // // // // //     nodes.clear(); nodes.resize(numNodes);
// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         float angle = i * 2.0f * 3.14159f / numNodes;
// // // // // // //         nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // // // // //     }
// // // // // // // }

// // // // // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // // // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // // // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // // // // //     glutPostRedisplay();
// // // // // // // }
// // // // // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // // // // //     assignPositions(); glutInit(&argc, argv);
// // // // // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // // // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // // //     glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // // // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback);
// // // // // // //     glutMainLoop();
// // // // // // // }
// // // // // // //
// // // // // // // #include "../Include/VisualGraphDSA.h"
// // // // // // // #include <GL/freeglut.h>
// // // // // // // #include <cmath>
// // // // // // // #include <string>

// // // // // // // using namespace std;

// // // // // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // // // // // ==========================================
// // // // // // // // 🔥 NEW: 2D Dashboard Function (HUD)
// // // // // // // // ==========================================
// // // // // // // void drawDashboardHUD(AlgoType currentAlgo) {
// // // // // // //     glMatrixMode(GL_PROJECTION);
// // // // // // //     glPushMatrix();
// // // // // // //     glLoadIdentity();
// // // // // // //     int w = glutGet(GLUT_WINDOW_WIDTH);
// // // // // // //     int h = glutGet(GLUT_WINDOW_HEIGHT);
// // // // // // //     gluOrtho2D(0, w, 0, h);
// // // // // // //     glMatrixMode(GL_MODELVIEW);
// // // // // // //     glPushMatrix();
// // // // // // //     glLoadIdentity();
// // // // // // //     glDisable(GL_DEPTH_TEST); // Text ko screen ke upar rakhne ke liye

// // // // // // //     string algoName = "Active Algorithm: ";
// // // // // // //     glColor3f(1.0f, 1.0f, 0.0f); // Default Yellow

// // // // // // //     switch(currentAlgo) {
// // // // // // //         case BFS: algoName += "BFS (Shortest Path) | O(V + E)"; break;
// // // // // // //         case DFS: algoName += "DFS Traversal | O(V + E)"; break;
// // // // // // //         case DIJKSTRA: algoName += "Dijkstra's Shortest Path | O(E log V)"; break;
// // // // // // //         case PRIMS: algoName += "Prim's MST | O(E log V)"; break;
// // // // // // //         case KRUSKAL: algoName += "Kruskal's MST | O(E log V)"; break;
// // // // // // //         case TOPOSORT_BFS: algoName += "Kahn's Topological Sort | O(V + E)"; break;
// // // // // // //         case BELLMAN_FORD: algoName += "Bellman-Ford | O(V * E)"; break;
// // // // // // //         case FLOYD: algoName += "Floyd-Warshall | O(V^3)"; break;
// // // // // // //         case BRIDGES: algoName += "Tarjan's Bridges Detection | O(V + E)"; break;
// // // // // // //         case SCC: algoName += "Kosaraju's SCC | O(V + E)"; break;
// // // // // // //         case CYCLE_DETECTED: 
// // // // // // //             algoName += "⚠️ WARNING: Cycle Detected!"; 
// // // // // // //             glColor3f(1.0f, 0.2f, 0.2f); // Red alert for cycle
// // // // // // //             break;
// // // // // // //         default: algoName += "Graph Loaded (Idle)"; break;
// // // // // // //     }

// // // // // // //     glRasterPos2f(20, h - 30);
// // // // // // //     for (char c : algoName) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

// // // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // // //     glMatrixMode(GL_PROJECTION); glPopMatrix();
// // // // // // //     glMatrixMode(GL_MODELVIEW); glPopMatrix();
// // // // // // // }

// // // // // // // // Constructor 1
// // // // // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : wg.adjlist) {
// // // // // // //         for (auto const& nbr : p.second) {
// // // // // // //             if (d || p.first < nbr.first) {
// // // // // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // // Constructor 2
// // // // // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : ug.adjlist) {
// // // // // // //         for (int v : p.second) {
// // // // // // //             if (d || p.first < v) {
// // // // // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // void GraphVisualizer::display() {
// // // // // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // // // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // // // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // // // // //     for (auto& e : allEdges) {
// // // // // // //         bool highlight = false;
// // // // // // //         for (auto& ae : anim_edges) if (ae.first == e.u && ae.second == e.v) highlight = true;
// // // // // // //         if (highlight) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // // // // //             glLineWidth(3);
// // // // // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // // // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]);
// // // // // // //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // // // // //     }

// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         bool active = false;
// // // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) if (anim_nodes[j] == i) active = true;
// // // // // // //         if (active) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // // // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // // // // //             else glColor3f(1, 0, 0);
// // // // // // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // // // // // //         glPushMatrix(); 
// // // // // // //         glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]);
// // // // // // //         glutSolidSphere(0.2, 20, 20); 
// // // // // // //         glPopMatrix();

// // // // // // //         // 🔥 NEW: Node Label Render (Number on Node)
// // // // // // //         glColor3f(1.0f, 1.0f, 1.0f); // White text
// // // // // // //         glRasterPos3f(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2]); // Thoda sphere ke upar
// // // // // // //         string nodeName = to_string(i);
// // // // // // //         for (char c : nodeName) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // // // // //     }

// // // // // // //     // 🔥 NEW: Call 2D HUD at the end
// // // // // // //     drawDashboardHUD(currentAlgo);

// // // // // // //     glutSwapBuffers();
// // // // // // // }

// // // // // // // void GraphVisualizer::assignPositions() {
// // // // // // //     nodes.clear(); nodes.resize(numNodes);
// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         float angle = i * 2.0f * 3.14159f / numNodes;
// // // // // // //         nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // // // // //     }
// // // // // // // }

// // // // // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // // // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // // // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // // // // //     glutPostRedisplay();
// // // // // // // }
// // // // // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // // // // //     assignPositions(); glutInit(&argc, argv);
// // // // // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // // // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // // //     glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // // // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback);
// // // // // // //     glutMainLoop();
// // // // // // // }
// // // // // // //

// // // // // // // #include "../Include/VisualGraphDSA.h"
// // // // // // // #include <GL/freeglut.h>
// // // // // // // #include <cmath>
// // // // // // // #include <string>

// // // // // // // using namespace std;

// // // // // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // // // // // ==========================================
// // // // // // // // 🔥 IMPLEMENTATION: drawText
// // // // // // // // ==========================================
// // // // // // // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// // // // // // //     glColor3f(r, g, b);
// // // // // // //     glRasterPos3f(x, y, z);
// // // // // // //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // // // // // }

// // // // // // // // Constructor for Weighted
// // // // // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     finalDist = wg.lastCalculatedDistance;
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : wg.adjlist) {
// // // // // // //         for (auto const& nbr : p.second) {
// // // // // // //             if (d || p.first < nbr.first) {
// // // // // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // // Constructor for Unweighted
// // // // // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // // // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // // //     currentVisualizer = this;
// // // // // // //     finalDist = -1; 
// // // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // // //     for (auto const& p : ug.adjlist) {
// // // // // // //         for (int v : p.second) {
// // // // // // //             if (d || p.first < v) {
// // // // // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // // // // //             }
// // // // // // //         }
// // // // // // //     }
// // // // // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // // }

// // // // // // // // ==========================================
// // // // // // // // 🔥 CORE: Display Loop
// // // // // // // // ==========================================
// // // // // // // void GraphVisualizer::display() {
// // // // // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // // // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // // // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // // // // //     // 1. Draw Edges
// // // // // // //     for (auto& e : allEdges) {
// // // // // // //         bool highlight = false;
// // // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// // // // // // //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// // // // // // //         }
// // // // // // //         if (highlight) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // // // // //             glLineWidth(3);
// // // // // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // // // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]);
// // // // // // //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // // // // //     }

// // // // // // //     // 2. Draw Nodes and Labels
// // // // // // //     int currentComponent = 0;
// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         bool active = false;
// // // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// // // // // // //             if (anim_nodes[j] == -1) currentComponent++; // SCC component separator check
// // // // // // //             if (anim_nodes[j] == i) active = true;
// // // // // // //         }

// // // // // // //         if (active) {
// // // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // // // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // // // // //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// // // // // // //             else glColor3f(1, 0, 0);
// // // // // // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // // // // // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]);
// // // // // // //         glutSolidSphere(0.2, 20, 20); glPopMatrix();

// // // // // // //         // Node Numbers
// // // // // // //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// // // // // // //     }

// // // // // // //     // 3. Draw 2D HUD / Dashboard
// // // // // // //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// // // // // // //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// // // // // // //     gluOrtho2D(0, w, 0, h);
// // // // // // //     glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
// // // // // // //     glDisable(GL_DEPTH_TEST);

// // // // // // //     string algoName = "Algorithm: ";
// // // // // // //     float r = 1.0f, g = 1.0f, b = 0.0f; // Default Yellow

// // // // // // //     switch(currentAlgo) {
// // // // // // //         case BFS: algoName += "BFS Shortest Path | O(V + E)"; break;
// // // // // // //         case DFS: algoName += "DFS Traversal | O(V + E)"; break;
// // // // // // //         case DIJKSTRA: algoName += "Dijkstra | Distance: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // // // // //         case PRIMS: algoName += "Prim's MST | O(E log V)"; break;
// // // // // // //         case KRUSKAL: algoName += "Kruskal's MST | O(E log V)"; break;
// // // // // // //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | O(V + E)"; break;
// // // // // // //         case BELLMAN_FORD: algoName += "Bellman-Ford | O(V * E)"; break;
// // // // // // //         case FLOYD: algoName += "Floyd-Warshall | O(V^3)"; break;
// // // // // // //         case BRIDGES: algoName += "Tarjan's Bridges Detection | O(V + E)"; break;
// // // // // // //         case SCC: algoName += "Kosaraju's SCC | O(V + E)"; break;
// // // // // // //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// // // // // // //         default: algoName += "Ready"; break;
// // // // // // //     }
// // // // // // //     drawText(20, h - 30, 0, algoName, r, g, b);

// // // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // // //     glMatrixMode(GL_PROJECTION); glPopMatrix();
// // // // // // //     glMatrixMode(GL_MODELVIEW); glPopMatrix();

// // // // // // //     glutSwapBuffers();
// // // // // // // }

// // // // // // // void GraphVisualizer::assignPositions() {
// // // // // // //     nodes.clear(); nodes.resize(numNodes);
// // // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // // //         float angle = i * 2.0f * 3.14159f / numNodes;
// // // // // // //         nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // // // // //     }
// // // // // // // }

// // // // // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // // // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // // // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // // // // //     glutPostRedisplay();
// // // // // // // }
// // // // // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // // // // //     assignPositions(); glutInit(&argc, argv);
// // // // // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // // // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // // //     glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // // // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback);
// // // // // // //     glutMainLoop();
// // // // // // // }
// // // // // // //
// // // // // // #include "../Include/VisualGraphDSA.h"
// // // // // // #include <GL/freeglut.h>
// // // // // // #include <cmath>
// // // // // // #include <string>

// // // // // // using namespace std;

// // // // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // // // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// // // // // //     glColor3f(r, g, b);
// // // // // //     glRasterPos3f(x, y, z);
// // // // // //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // // // // }

// // // // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // //     currentVisualizer = this;
// // // // // //     finalDist = wg.lastCalculatedDistance;
// // // // // //     srcNode = wg.sourceNode; // 🔥 Fetch SRC
// // // // // //     destNode = wg.destNode;  // 🔥 Fetch DEST
    
// // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // //     for (auto const& p : wg.adjlist) {
// // // // // //         for (auto const& nbr : p.second) {
// // // // // //             if (d || p.first < nbr.first) {
// // // // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // // // //             }
// // // // // //         }
// // // // // //     }
// // // // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // }

// // // // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // // //     currentVisualizer = this;
// // // // // //     finalDist = -1; 
// // // // // //     srcNode = ug.sourceNode; // 🔥 Fetch SRC
// // // // // //     destNode = ug.destNode;  // 🔥 Fetch DEST
    
// // // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // // //     for (auto const& p : ug.adjlist) {
// // // // // //         for (int v : p.second) {
// // // // // //             if (d || p.first < v) {
// // // // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // // // //             }
// // // // // //         }
// // // // // //     }
// // // // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // // }

// // // // // // void GraphVisualizer::display() {
// // // // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // // // //     for (auto& e : allEdges) {
// // // // // //         bool highlight = false;
// // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// // // // // //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// // // // // //         }
// // // // // //         if (highlight) {
// // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // // // //             glLineWidth(3);
// // // // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]);
// // // // // //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // // // //     }

// // // // // //     int currentComponent = 0;
// // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // //         bool active = false;
// // // // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// // // // // //             if (anim_nodes[j] == -1) currentComponent++; 
// // // // // //             if (anim_nodes[j] == i) active = true;
// // // // // //         }

// // // // // //         if (active) {
// // // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // // // //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// // // // // //             else glColor3f(1, 0, 0);
// // // // // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // // // // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]);
// // // // // //         glutSolidSphere(0.2, 20, 20); glPopMatrix();

// // // // // //         // 1. Draw Node Number
// // // // // //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);

// // // // // //         // 🔥 2. Draw SRC and DEST Tags
// // // // // //         if (i == srcNode) {
// // // // // //             drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f); // Green SRC
// // // // // //         } else if (i == destNode) {
// // // // // //             drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f); // Red DEST
// // // // // //         }
// // // // // //     }

// // // // // //     // 🔥 3. Draw HUD (TC/SC)
// // // // // //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// // // // // //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// // // // // //     gluOrtho2D(0, w, 0, h);
// // // // // //     glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
// // // // // //     glDisable(GL_DEPTH_TEST);

// // // // // //     string algoName = "Algo: ";
// // // // // //     float r = 1.0f, g = 1.0f, b = 0.0f; // Yellow

// // // // // //     switch(currentAlgo) {
// // // // // //         case BFS: algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)"; break;
// // // // // //         case DFS: algoName += "DFS Traversal | TC: O(V+E) | SC: O(V)"; break;
// // // // // //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // // // //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// // // // // //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// // // // // //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// // // // // //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V)"; break;
// // // // // //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2)"; break;
// // // // // //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// // // // // //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// // // // // //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// // // // // //         default: algoName += "Ready (Graph Loaded)"; break;
// // // // // //     }
    
// // // // // //     drawText(20, h - 30, 0, algoName, r, g, b);

// // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // //     glMatrixMode(GL_PROJECTION); glPopMatrix();
// // // // // //     glMatrixMode(GL_MODELVIEW); glPopMatrix();

// // // // // //     glutSwapBuffers();
// // // // // // }

// // // // // // void GraphVisualizer::assignPositions() {
// // // // // //     nodes.clear(); nodes.resize(numNodes);
// // // // // //     for (int i = 0; i < numNodes; i++) {
// // // // // //         float angle = i * 2.0f * 3.14159f / numNodes;
// // // // // //         nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // // // //     }
// // // // // // }

// // // // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // // // //     glutPostRedisplay();
// // // // // // }
// // // // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // // // //     assignPositions(); glutInit(&argc, argv);
// // // // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // // // //     glEnable(GL_DEPTH_TEST);
// // // // // //     glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback);
// // // // // //     glutMainLoop();
// // // // // // }
// // // // // //
// // // // // #include "../Include/VisualGraphDSA.h"
// // // // // #include <GL/freeglut.h>
// // // // // #include <cmath>
// // // // // #include <string>

// // // // // using namespace std;

// // // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// // // // //     glColor3f(r, g, b);
// // // // //     glRasterPos3f(x, y, z);
// // // // //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // // // }

// // // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // //     currentVisualizer = this;
// // // // //     finalDist = wg.lastCalculatedDistance;
// // // // //     srcNode = wg.sourceNode; destNode = wg.destNode;
    
// // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // //     for (auto const& p : wg.adjlist) {
// // // // //         for (auto const& nbr : p.second) {
// // // // //             if (d || p.first < nbr.first) {
// // // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // // //             }
// // // // //         }
// // // // //     }
// // // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // }

// // // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // // //     currentVisualizer = this;
// // // // //     finalDist = -1; 
// // // // //     srcNode = ug.sourceNode; destNode = ug.destNode;
    
// // // // //     allEdges.clear(); adjForLayout.resize(n);
// // // // //     for (auto const& p : ug.adjlist) {
// // // // //         for (int v : p.second) {
// // // // //             if (d || p.first < v) {
// // // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // // //             }
// // // // //         }
// // // // //     }
// // // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // // }

// // // // // void GraphVisualizer::display() {
// // // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // // //     for (auto& e : allEdges) {
// // // // //         bool highlight = false;
// // // // //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// // // // //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// // // // //         }
// // // // //         if (highlight) {
// // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // // //             glLineWidth(3);
// // // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // // //     }

// // // // //     int currentComponent = 0;
// // // // //     for (int i = 0; i < numNodes; i++) {
// // // // //         bool active = false;
// // // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// // // // //             if (anim_nodes[j] == -1) currentComponent++; 
// // // // //             if (anim_nodes[j] == i) active = true;
// // // // //         }

// // // // //         if (active) {
// // // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // // //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// // // // //             else glColor3f(1, 0, 0);
// // // // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // // // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); glutSolidSphere(0.2, 20, 20); glPopMatrix();

// // // // //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// // // // //         if (i == srcNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// // // // //         else if (i == destNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// // // // //     }

// // // // //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// // // // //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// // // // //     gluOrtho2D(0, w, 0, h); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);

// // // // //     string algoName = "Algo: "; float r = 1.0f, g = 1.0f, b = 0.0f;
// // // // //     switch(currentAlgo) {
// // // // //         case BFS: algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)"; break;
// // // // //         case DFS: algoName += "DFS Traversal | TC: O(V+E) | SC: O(V)"; break;
// // // // //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // // //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// // // // //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// // // // //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// // // // //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // // //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // // //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// // // // //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// // // // //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// // // // //         default: algoName += "Ready (Graph Loaded)"; break;
// // // // //     }
// // // // //     drawText(20, h - 30, 0, algoName, r, g, b);

// // // // //     glEnable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glutSwapBuffers();
// // // // // }

// // // // // void GraphVisualizer::assignPositions() {
// // // // //     nodes.clear(); nodes.resize(numNodes);
// // // // //     for (int i = 0; i < numNodes; i++) {
// // // // //         float angle = i * 2.0f * 3.14159f / numNodes; nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // // //     }
// // // // // }

// // // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // // //     glutPostRedisplay();
// // // // // }
// // // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // // //     assignPositions(); glutInit(&argc, argv);
// // // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // // //     glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback); glutMainLoop();
// // // // // }//
// // // // //
// // // // #include "../Include/VisualGraphDSA.h"
// // // // #include <GL/freeglut.h>
// // // // #include <cmath>
// // // // #include <string>

// // // // using namespace std;

// // // // GraphVisualizer* currentVisualizer = nullptr;

// // // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// // // //     glColor3f(r, g, b);
// // // //     glRasterPos3f(x, y, z);
// // // //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // // }

// // // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // //     currentVisualizer = this;
// // // //     finalDist = wg.lastCalculatedDistance;
// // // //     srcNode = wg.sourceNode; destNode = wg.destNode;
    
// // // //     allEdges.clear(); adjForLayout.resize(n);
// // // //     for (auto const& p : wg.adjlist) {
// // // //         for (auto const& nbr : p.second) {
// // // //             if (d || p.first < nbr.first) {
// // // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // // //             }
// // // //         }
// // // //     }
// // // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // }

// // // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // // //     currentVisualizer = this;
// // // //     finalDist = -1; 
// // // //     srcNode = ug.sourceNode; destNode = ug.destNode;
    
// // // //     allEdges.clear(); adjForLayout.resize(n);
// // // //     for (auto const& p : ug.adjlist) {
// // // //         for (int v : p.second) {
// // // //             if (d || p.first < v) {
// // // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // // //             }
// // // //         }
// // // //     }
// // // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // // }

// // // // void GraphVisualizer::display() {
// // // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // // //     for (auto& e : allEdges) {
// // // //         bool highlight = false;
// // // //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// // // //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// // // //         }
// // // //         if (highlight) {
// // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // // //             glLineWidth(3);
// // // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
// // // //         glBegin(GL_LINES); glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); glEnd();
// // // //     }

// // // //     int currentComponent = 0;
// // // //     for (int i = 0; i < numNodes; i++) {
// // // //         bool active = false;
// // // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// // // //             if (anim_nodes[j] == -1) currentComponent++; 
// // // //             if (anim_nodes[j] == i) active = true;
// // // //         }

// // // //         if (active) {
// // // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // // //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// // // //             else glColor3f(1, 0, 0);
// // // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); glutSolidSphere(0.2, 20, 20); glPopMatrix();

// // // //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// // // //         if (i == srcNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// // // //         else if (i == destNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// // // //     }

// // // //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// // // //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// // // //     gluOrtho2D(0, w, 0, h); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);

// // // //     string algoName = "Algo: "; float r = 1.0f, g = 1.0f, b = 0.0f;
// // // //     switch(currentAlgo) {
// // // //         case BFS: algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)"; break;
// // // //         case DFS: algoName += "DFS Traversal | TC: O(V+E) | SC: O(V)"; break;
// // // //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// // // //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// // // //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// // // //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // // //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// // // //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// // // //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// // // //         default: algoName += "Ready (Graph Loaded)"; break;
// // // //     }
// // // //     drawText(20, h - 30, 0, algoName, r, g, b);

// // // //     glEnable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glutSwapBuffers();
// // // // }

// // // // void GraphVisualizer::assignPositions() {
// // // //     nodes.clear(); nodes.resize(numNodes);
// // // //     for (int i = 0; i < numNodes; i++) {
// // // //         float angle = i * 2.0f * 3.14159f / numNodes; nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // // //     }
// // // // }

// // // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // // //     glutPostRedisplay();
// // // // }
// // // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // // void GraphVisualizer::visualize(int argc, char** argv) {
// // // //     assignPositions(); glutInit(&argc, argv);
// // // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // // //     glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback); glutMainLoop();
// // // // }

// // // //
// // // #include "../Include/VisualGraphDSA.h"
// // // #include <GL/freeglut.h>
// // // #include <cmath>
// // // #include <string>

// // // using namespace std;

// // // GraphVisualizer* currentVisualizer = nullptr;

// // // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// // //     glColor3f(r, g, b);
// // //     glRasterPos3f(x, y, z);
// // //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // // }

// // // // 🔥 NAYA CODE: Arrowhead Draw Karne Ke Liye
// // // void drawArrowHead(float x1, float y1, float z1, float x2, float y2, float z2) {
// // //     // Edge ka angle nikalo
// // //     float angle = atan2(y2 - y1, x2 - x1);
// // //     float arrowSize = 0.25f; // Arrow ka size
    
// // //     // Sphere ka radius 0.2 hai, toh arrow ko thoda bahar rakhenge (0.25 distance par)
// // //     float tipX = x2 - 0.25f * cos(angle);
// // //     float tipY = y2 - 0.25f * sin(angle);
    
// // //     // Arrow ke do peeche wale points (Wings) nikalo
// // //     float leftX = tipX - arrowSize * cos(angle - 0.4f);
// // //     float leftY = tipY - arrowSize * sin(angle - 0.4f);
// // //     float rightX = tipX - arrowSize * cos(angle + 0.4f);
// // //     float rightY = tipY - arrowSize * sin(angle + 0.4f);

// // //     // Solid Triangle Draw karo
// // //     glBegin(GL_TRIANGLES);
// // //     glVertex3f(tipX, tipY, z2);
// // //     glVertex3f(leftX, leftY, z2);
// // //     glVertex3f(rightX, rightY, z2);
// // //     glEnd();
// // // }

// // // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// // //     : numNodes(n), isDirected(d), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // //     currentVisualizer = this;
// // //     finalDist = wg.lastCalculatedDistance;
// // //     srcNode = wg.sourceNode; destNode = wg.destNode;
    
// // //     allEdges.clear(); adjForLayout.resize(n);
// // //     for (auto const& p : wg.adjlist) {
// // //         for (auto const& nbr : p.second) {
// // //             if (d || p.first < nbr.first) {
// // //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// // //             }
// // //         }
// // //     }
// // //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // }

// // // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// // //     : numNodes(n), isDirected(d), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// // //     currentVisualizer = this;
// // //     finalDist = -1; 
// // //     srcNode = ug.sourceNode; destNode = ug.destNode;
    
// // //     allEdges.clear(); adjForLayout.resize(n);
// // //     for (auto const& p : ug.adjlist) {
// // //         for (int v : p.second) {
// // //             if (d || p.first < v) {
// // //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// // //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// // //             }
// // //         }
// // //     }
// // //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// // //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // // }

// // // void GraphVisualizer::display() {
// // //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// // //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// // //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// // //     for (auto& e : allEdges) {
// // //         bool highlight = false;
// // //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// // //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// // //         }
// // //         if (highlight) {
// // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// // //             glLineWidth(3);
// // //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
        
// // //         float x1 = nodes[e.u][0], y1 = nodes[e.u][1], z1 = nodes[e.u][2];
// // //         float x2 = nodes[e.v][0], y2 = nodes[e.v][1], z2 = nodes[e.v][2];

// // //         // 1. Line draw karo
// // //         glBegin(GL_LINES); 
// // //         glVertex3f(x1, y1, z1); 
// // //         glVertex3f(x2, y2, z2); 
// // //         glEnd();

// // //         // 🔥 2. NAYA CODE: Agar Directed Graph hai, toh Arrow bhi draw karo!
// // //         if (isDirected) {
// // //             drawArrowHead(x1, y1, z1, x2, y2, z2);
// // //         }
// // //     }

// // //     int currentComponent = 0;
// // //     for (int i = 0; i < numNodes; i++) {
// // //         bool active = false;
// // //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// // //             if (anim_nodes[j] == -1) currentComponent++; 
// // //             if (anim_nodes[j] == i) active = true;
// // //         }

// // //         if (active) {
// // //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// // //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// // //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// // //             else glColor3f(1, 0, 0);
// // //         } else glColor3f(0.2, 0.4, 0.8);
        
// // //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); glutSolidSphere(0.2, 20, 20); glPopMatrix();

// // //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// // //         if (i == srcNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// // //         else if (i == destNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// // //     }

// // //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// // //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// // //     gluOrtho2D(0, w, 0, h); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);

// // //     string algoName = "Algo: "; float r = 1.0f, g = 1.0f, b = 0.0f;
// // //     switch(currentAlgo) {
// // //         case BFS: algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)"; break;
// // //         case DFS: algoName += "DFS Traversal | TC: O(V+E) | SC: O(V)"; break;
// // //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// // //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// // //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// // //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// // //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// // //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// // //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// // //         default: algoName += "Ready (Graph Loaded)"; break;
// // //     }
// // //     drawText(20, h - 30, 0, algoName, r, g, b);

// // //     glEnable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glutSwapBuffers();
// // // }

// // // void GraphVisualizer::assignPositions() {
// // //     nodes.clear(); nodes.resize(numNodes);
// // //     for (int i = 0; i < numNodes; i++) {
// // //         float angle = i * 2.0f * 3.14159f / numNodes; nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// // //     }
// // // }

// // // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(1000, updateCallback, 0); }
// // // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// // //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// // //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// // //     glutPostRedisplay();
// // // }
// // // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // // void GraphVisualizer::visualize(int argc, char** argv) {
// // //     assignPositions(); glutInit(&argc, argv);
// // //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// // //     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// // //     glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// // //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback); glutMainLoop();
// // // }
// // //

// // #include "../Include/VisualGraphDSA.h"
// // #include <GL/freeglut.h>
// // #include <cmath>
// // #include <string>

// // using namespace std;

// // GraphVisualizer* currentVisualizer = nullptr;

// // void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// // void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// // void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// // void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// // void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
// //     glColor3f(r, g, b);
// //     glRasterPos3f(x, y, z);
// //     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// // }

// // void drawArrowHead(float x1, float y1, float z1, float x2, float y2, float z2) {
// //     float angle = atan2(y2 - y1, x2 - x1);
// //     float arrowSize = 0.25f; 
// //     float tipX = x2 - 0.25f * cos(angle);
// //     float tipY = y2 - 0.25f * sin(angle);
// //     float leftX = tipX - arrowSize * cos(angle - 0.4f);
// //     float leftY = tipY - arrowSize * sin(angle - 0.4f);
// //     float rightX = tipX - arrowSize * cos(angle + 0.4f);
// //     float rightY = tipY - arrowSize * sin(angle + 0.4f);
// //     glBegin(GL_TRIANGLES); glVertex3f(tipX, tipY, z2); glVertex3f(leftX, leftY, z2); glVertex3f(rightX, rightY, z2); glEnd();
// // }

// // // 🔥 WEIGHTED Constructor
// // GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
// //     : numNodes(n), isDirected(d), isWeighted(true), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// //     currentVisualizer = this;
// //     finalDist = wg.lastCalculatedDistance;
// //     srcNode = wg.sourceNode; destNode = wg.destNode;
    
// //     allEdges.clear(); adjForLayout.resize(n);
// //     for (auto const& p : wg.adjlist) {
// //         for (auto const& nbr : p.second) {
// //             if (d || p.first < nbr.first) {
// //                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
// //                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
// //             }
// //         }
// //     }
// //     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
// //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // }

// // // 🔥 UNWEIGHTED Constructor
// // GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
// //     : numNodes(n), isDirected(d), isWeighted(false), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
// //     currentVisualizer = this;
// //     finalDist = -1; 
// //     srcNode = ug.sourceNode; destNode = ug.destNode;
    
// //     allEdges.clear(); adjForLayout.resize(n);
// //     for (auto const& p : ug.adjlist) {
// //         for (int v : p.second) {
// //             if (d || p.first < v) {
// //                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
// //                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
// //             }
// //         }
// //     }
// //     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
// //     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// // }

// // void GraphVisualizer::display() {
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// //     // 1. Edges, Arrows & Weights Draw Karo
// //     for (auto& e : allEdges) {
// //         bool highlight = false;
// //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// //         }
// //         if (highlight) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// //             glLineWidth(3);
// //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
        
// //         float x1 = nodes[e.u][0], y1 = nodes[e.u][1], z1 = nodes[e.u][2];
// //         float x2 = nodes[e.v][0], y2 = nodes[e.v][1], z2 = nodes[e.v][2];

// //         glBegin(GL_LINES); glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); glEnd();

// //         if (isDirected) drawArrowHead(x1, y1, z1, x2, y2, z2);

// //         // 🔥 NAYA CODE: Edge Weight Draw Karo (Sirf tab jab Graph Weighted ho)
// //         if (isWeighted) {
// //             float midX = (x1 + x2) / 2.0f;
// //             float midY = (y1 + y2) / 2.0f + 0.15f; // Line se thoda upar taaki overlap na ho
// //             float midZ = (z1 + z2) / 2.0f;
// //             // Orange/Yellow color mein weight print hoga
// //             drawText(midX, midY, midZ, to_string(e.weight), 1.0f, 0.8f, 0.0f); 
// //         }
// //     }

// //     int currentComponent = 0;
// //     for (int i = 0; i < numNodes; i++) {
// //         bool active = false;
// //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //             if (anim_nodes[j] == -1) currentComponent++; 
// //             if (anim_nodes[j] == i) active = true;
// //         }

// //         if (active) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); 
// //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0, 1, 1);
// //             else if (currentAlgo == SCC) glColor3f(sccColors[currentComponent % 10][0], sccColors[currentComponent % 10][1], sccColors[currentComponent % 10][2]);
// //             else glColor3f(1, 0, 0);
// //         } else glColor3f(0.2, 0.4, 0.8);
        
// //         glPushMatrix(); glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); glutSolidSphere(0.2, 20, 20); glPopMatrix();

// //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// //         if (i == srcNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //         else if (i == destNode) drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //     }

// //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// //     gluOrtho2D(0, w, 0, h); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);

// //     string algoName = "Algo: "; float r = 1.0f, g = 1.0f, b = 0.0f;
// //     switch(currentAlgo) {
// //         case BFS: algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)"; break;
// //         case DFS: algoName += "DFS Traversal | TC: O(V+E) | SC: O(V)"; break;
// //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// //         default: algoName += "Ready (Graph Loaded)"; break;
// //     }
// //     drawText(20, h - 30, 0, algoName, r, g, b);

// //     glEnable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glutSwapBuffers();
// // }

// // void GraphVisualizer::assignPositions() {
// //     nodes.clear(); nodes.resize(numNodes);
// //     for (int i = 0; i < numNodes; i++) {
// //         float angle = i * 2.0f * 3.14159f / numNodes; nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// //     }
// // }

// // void GraphVisualizer::update() { if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } glutTimerFunc(2000, updateCallback, 0); }
// // void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
// //     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
// //     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
// //     glutPostRedisplay();
// // }
// // void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }
// // void GraphVisualizer::visualize(int argc, char** argv) {
// //     assignPositions(); glutInit(&argc, argv);
// //     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
// //     glutInitWindowSize(2000, 700); glutCreateWindow("3D Graph Visualizer Pro");
// //     glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
// //     glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback); glutMainLoop();
// // }  
// // //

// #include "../Include/VisualGraphDSA.h"
// #include <GL/freeglut.h>
// #include <cmath>
// #include <string>

// using namespace std;

// GraphVisualizer* currentVisualizer = nullptr;

// void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
// void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
// void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
// void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

// void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
//     glColor3f(r, g, b);
//     glRasterPos3f(x, y, z);
//     for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
// }

// void drawArrowHead(float x1, float y1, float z1, float x2, float y2, float z2) {
//     float angle = atan2(y2 - y1, x2 - x1);
//     float arrowSize = 0.25f; 
//     float tipX = x2 - 0.25f * cos(angle);
//     float tipY = y2 - 0.25f * sin(angle);
//     float leftX = tipX - arrowSize * cos(angle - 0.4f);
//     float leftY = tipY - arrowSize * sin(angle - 0.4f);
//     float rightX = tipX - arrowSize * cos(angle + 0.4f);
//     float rightY = tipY - arrowSize * sin(angle + 0.4f);
//     glBegin(GL_TRIANGLES); glVertex3f(tipX, tipY, z2); glVertex3f(leftX, leftY, z2); glVertex3f(rightX, rightY, z2); glEnd();
// }

// GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
//     : numNodes(n), isDirected(d), isWeighted(true), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
//     currentVisualizer = this;
//     finalDist = wg.lastCalculatedDistance;
//     srcNode = wg.sourceNode; destNode = wg.destNode;
    
//     allEdges.clear(); adjForLayout.resize(n);
//     for (auto const& p : wg.adjlist) {
//         for (auto const& nbr : p.second) {
//             if (d || p.first < nbr.first) {
//                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
//                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
//             }
//         }
//     }
//     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
//     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// }

// GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
//     : numNodes(n), isDirected(d), isWeighted(false), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(10.0f) {
//     currentVisualizer = this;
//     finalDist = -1; 
//     srcNode = ug.sourceNode; destNode = ug.destNode;
    
//     allEdges.clear(); adjForLayout.resize(n);
//     for (auto const& p : ug.adjlist) {
//         for (int v : p.second) {
//             if (d || p.first < v) {
//                 Edge e; e.u = p.first; e.v = v; e.weight = 0;
//                 allEdges.push_back(e); adjForLayout[p.first].push_back(v);
//             }
//         }
//     }
//     anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
//     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// }

// // void GraphVisualizer::display() {
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// //     gluLookAt(0, 2, cameraZ, 0, 0, 0, 0, 1, 0);
// //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// //     // 1. Draw Edges
// //     for (auto& e : allEdges) {
// //         bool highlight = false;
// //         for (int j = 0; j <= currentStep && j < (int)anim_edges.size(); j++) {
// //             if (anim_edges[j].first == e.u && anim_edges[j].second == e.v) highlight = true;
// //         }
// //         if (highlight) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1, 0, 1); else glColor3f(0, 1, 0);
// //             glLineWidth(3);
// //         } else { glColor3f(0.5, 0.5, 0.5); glLineWidth(1); }
        
// //         float x1 = nodes[e.u][0], y1 = nodes[e.u][1], z1 = nodes[e.u][2];
// //         float x2 = nodes[e.v][0], y2 = nodes[e.v][1], z2 = nodes[e.v][2];

// //         glBegin(GL_LINES); glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); glEnd();

// //         if (isDirected) drawArrowHead(x1, y1, z1, x2, y2, z2);

// //         if (isWeighted) {
// //             float midX = (x1 + x2) / 2.0f;
// //             float midY = (y1 + y2) / 2.0f + 0.15f; 
// //             float midZ = (z1 + z2) / 2.0f;
// //             drawText(midX, midY, midZ, to_string(e.weight), 1.0f, 0.8f, 0.0f); 
// //         }
// //     }

// //     // 2. Draw Nodes
// //      // 2. Draw Nodes (Updated for Level-wise BFS and Depth-wise DFS)
// //     int currentComponent = 0;
// //     for (int i = 0; i < numNodes; i++) {
// //         bool active = false;
// //         int nodeColorIdx = 0;

// //         // Loop through anim_nodes up to currentStep
// //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //             int val = anim_nodes[j];

// //             if (val == -1 || val == -3) {
// //                 currentComponent++; // Component badal gaya
// //                 nodeColorIdx = currentComponent;
// //             } 
// //             else if (val == -2) {
// //                 // BFS Level Marker: Iske aage wale nodes agle step mein dikhenge
// //                 continue; 
// //             }
// //             else if (val == i) {
// //                 active = true;
// //                 nodeColorIdx = currentComponent;
// //             }
// //         }

// //         if (active) {
// //             if (currentAlgo == CYCLE_DETECTED) {
// //                 glColor3f(1.0f, 0.0f, 1.0f); // Magenta for cycles
// //             } else if (currentAlgo == TOPOSORT_BFS) {
// //                 glColor3f(0.0f, 1.0f, 1.0f); // Cyan for Topo
// //             } else if (currentAlgo == SCC) {
// //                 // SCC ke liye component wise color
// //                 glColor3f(sccColors[nodeColorIdx % 10][0], sccColors[nodeColorIdx % 10][1], sccColors[nodeColorIdx % 10][2]);
// //             } else {
// //                 glColor3f(1.0f, 0.0f, 0.0f); // Red for visited nodes (BFS/DFS)
// //             }
// //         } else {
// //             glColor3f(0.2f, 0.4f, 0.8f); // Default Blue for unvisited
// //         }
        
// //         glPushMatrix(); 
// //         glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
// //         glutSolidSphere(0.2, 20, 20); 
// //         glPopMatrix();

// //         // Labels drawing
// //         drawText(nodes[i][0], nodes[i][1] + 0.3f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
        
// //         if (i == srcNode) {
// //             drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //         } else if (i == destNode) {
// //             drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //         }
// //     }

// //     // 3. Draw HUD (MODIFIED LOGIC)
// //     glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
// //     int w = glutGet(GLUT_WINDOW_WIDTH); int h = glutGet(GLUT_WINDOW_HEIGHT);
// //     gluOrtho2D(0, w, 0, h); glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);

// //     string algoName = "Algo: "; float r = 1.0f, g = 1.0f, b = 0.0f;
// //     switch(currentAlgo) {
// //         case BFS: 
// //             if(destNode == -1) algoName += "BFS Traversal (Level-Wise) | TC: O(V+E) | SC: O(V)";
// //             else algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)";
// //             break;
// //         case DFS: 
// //             if(destNode == -1) algoName += "DFS Traversal (Depth-Wise) | TC: O(V+E) | SC: O(V)";
// //             else algoName += "DFS Pathfinding | TC: O(V+E) | SC: O(V)";
// //             break;
// //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// //         case SCC: algoName += "Kosaraju's SCC | TC: O(V+E) | SC: O(V+E)"; break;
// //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; r = 1.0f; g = 0.2f; b = 0.2f; break;
// //         default: algoName += "Ready (Graph Loaded)"; break;
// //     }
    
// //     // 🔥 h-40 use kiya taaki text upar se thoda niche rahe
// //     drawText(20, h - 40, 0, algoName, r, g, b);

// //     glEnable(GL_DEPTH_TEST); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glutSwapBuffers();
// // }
// //
// // void GraphVisualizer::display() {
// // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// //     gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
// //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);

// //     // --- 1. EDGES DRAWING (Perfect Sync Logic Jo Tune Maangi Hai) ---
// //     for (auto& e : allEdges) {
// //         bool highlight = false;

// //         // SYNC FIX: Edge tabhi chamkegi jab uska 'Destination Node' (e.v) 
// //         // anim_nodes ke currentStep par ho.
// //         if (currentStep >= 0 && currentStep < (int)anim_nodes.size()) {
            
// //             // 🔥 Check karo ki kya ye edge humein current node tak laayi hai
// //             for (int k = 0; k <= currentStep && k < (int)anim_edges.size(); k++) {
// //                 if ((anim_edges[k].first == e.u && anim_edges[k].second == e.v && anim_nodes[currentStep] == e.v) ||
// //                     (anim_edges[k].first == e.v && anim_edges[k].second == e.u && anim_nodes[currentStep] == e.u)) {
// //                     highlight = true;
// //                     break;
// //                 }
// //             }
            
// //             // 🔥 Purani edges (jo pehle visit ho chuki hain) ko green hi rehne do
// //             for (int k = 0; k < currentStep && k < (int)anim_edges.size(); k++) {
// //                 if ((anim_edges[k].first == e.u && anim_edges[k].second == e.v) ||
// //                     (anim_edges[k].first == e.v && anim_edges[k].second == e.u)) {
// //                     highlight = true;
// //                 }
// //             }
// //         }

// //         if (highlight) {
// //             glColor3f(0.0f, 1.0f, 0.0f); // Bright Green
// //             glLineWidth(3);
// //         } else { 
// //             glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
// //             glLineWidth(1); 
// //         }
        
// //         glBegin(GL_LINES); 
// //         glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); 
// //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); 
// //         glEnd();
        
// //         if (isDirected) drawArrowHead(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2], nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]);

// //         // Weights logic (if any)
// //         if (isWeighted) {
// //              float midX = (nodes[e.u][0] + nodes[e.v][0]) / 2.0f;
// //              float midY = (nodes[e.u][1] + nodes[e.v][1]) / 2.0f + 0.15f;
// //              float midZ = (nodes[e.u][2] + nodes[e.v][2]) / 2.0f;
// //              drawText(midX, midY, midZ, std::to_string(e.weight), 1.0f, 0.8f, 0.0f);
// //         }
// //     }

// //     // --- 2. Nodes Drawing (With Level & Component Logic) ---
// // // 2. Draw Nodes (Updated for Level-wise and Component Sync)
// //     int currentComponent = 0;
// //     for (int i = 0; i < numNodes; i++) {
// //         bool active = false;
// //         int nodeColorIdx = 0;

// //         // 🔥 Marker Logic: anim_nodes ko currentStep tak scan karo
// //         for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //             int val = anim_nodes[j];
            
// //             // Agar SCC marker (-1) ya Component marker (-3) mile, color index badhao
// //             if (val == -1 || val == -3) {
// //                 currentComponent++; 
// //             } 
// //             // Level marker (-2) ko sirf skip karo, ye update() handle kar raha hai
// //             else if (val == -2) {
// //                 continue; 
// //             }
// //             // Agar node 'i' is step tak visit hua hai
// //             else if (val == i) {
// //                 active = true;
// //                 nodeColorIdx = currentComponent;
// //             }
// //         }

// //         if (active) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); // Magenta
// //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0.0f, 1.0f, 1.0f); // Cyan
// //             else if (currentAlgo == SCC) glColor3f(sccColors[nodeColorIdx % 10][0], sccColors[nodeColorIdx % 10][1], sccColors[nodeColorIdx % 10][2]);
// //             else glColor3f(1.0f, 0.0f, 0.0f); // Red for BFS/DFS active nodes
// //         } else {
// //             glColor3f(0.2f, 0.4f, 0.8f); // Default Blue for unvisited
// //         }
        
// //         glPushMatrix(); 
// //         glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
// //         // 🔥 Sphere size thoda badha diya taaki rectangle grid mein saaf dikhe (0.3)
// //         glutSolidSphere(0.3, 20, 20); 
// //         glPopMatrix();

// //         // Text labels (Node number, SRC, DEST)
// //         drawText(nodes[i][0], nodes[i][1] + 0.4f, nodes[i][2], to_string(i), 1.0f, 1.0f, 1.0f);
// //         if (i == srcNode) drawText(nodes[i][0], nodes[i][1] + 0.7f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //         else if (i == destNode) drawText(nodes[i][0], nodes[i][1] + 0.7f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //     }

// //     // --- 3. HUD Display (Dashboard) ---
// //     glMatrixMode(GL_PROJECTION); 
// //     glPushMatrix(); 
// //     glLoadIdentity();
// //     int w = glutGet(GLUT_WINDOW_WIDTH); 
// //     int h = glutGet(GLUT_WINDOW_HEIGHT);
// //     gluOrtho2D(0, w, 0, h); 
// //     glMatrixMode(GL_MODELVIEW); 
// //     glPushMatrix(); 
// //     glLoadIdentity(); 
// //     glDisable(GL_DEPTH_TEST);

// //     string algoName = "Algo: "; float hr=1.0f, hg=1.0f, hb=0.0f;
// //     switch(currentAlgo) {
// //         case BFS: 
// //             if(destNode == -1) algoName += "BFS Traversal (Level-Wise) | TC: O(V+E) | SC: O(V)";
// //             else algoName += "BFS Shortest Path | TC: O(V+E) | SC: O(V)";
// //             break;
// //         case DFS: 
// //             if(destNode == -1) algoName += "DFS Traversal (Depth-Wise) | TC: O(V+E) | SC: O(V)";
// //             else algoName += "DFS Pathfinding | TC: O(V+E) | SC: O(V)";
// //             break;
// //         case DIJKSTRA: algoName += "Dijkstra | TC: O(E log V) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case BELLMAN_FORD: algoName += "Bellman-Ford | TC: O(V*E) | SC: O(V) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case FLOYD: algoName += "Floyd-Warshall | TC: O(V^3) | SC: O(V^2) | Dist: " + (finalDist == -1 ? "N/A" : to_string(finalDist)); break;
// //         case PRIMS: algoName += "Prim's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case KRUSKAL: algoName += "Kruskal's MST | TC: O(E log V) | SC: O(V)"; break;
// //         case TOPOSORT_BFS: algoName += "Kahn's TopoSort | TC: O(V+E) | SC: O(V)"; break;
// //         case BRIDGES: algoName += "Tarjan's Bridges | TC: O(V+E) | SC: O(V)"; break;
// //         case SCC: algoName += "Kosaraju's SCC | Components: " + to_string(currentComponent); break;
// //         case CYCLE_DETECTED: algoName += "⚠️ WARNING: Cycle Detected!"; hr = 1.0f; hg = 0.2f; hb = 0.2f; break;
// //         default: algoName += "Ready (Graph Loaded)"; break;
// //     }
    
// //     drawText(20, h - 40, 0, algoName, hr, hg, hb);

// //     glEnable(GL_DEPTH_TEST); 
// //     glMatrixMode(GL_PROJECTION); 
// //     glPopMatrix(); 
// //     glMatrixMode(GL_MODELVIEW); 
// //     glPopMatrix(); 
// //     glutSwapBuffers();
// // }
// // void GraphVisualizer::assignPositions() {
// //     nodes.clear(); nodes.resize(numNodes);
// //     for (int i = 0; i < numNodes; i++) {
// //         float angle = i * 2.0f * 3.14159f / numNodes; nodes[i] = { 3.5f * cos(angle), 3.5f * sin(angle), 0.0f };
// //     }
// // }
// // void GraphVisualizer::assignPositions() {
// //     nodes.clear();
// //     nodes.resize(numNodes);

// //     // 🔥 RECTANGLE GRID LOGIC
// //     // Hum decide karenge ki ek row mein kitne nodes honge (Columns)
// //     int cols = ceil(sqrt(numNodes)); // Agar 9 nodes hain, toh 3x3 grid banega
// //     float spacing = 2.5f;           // Nodes ke beech ka gap

// //     for (int i = 0; i < numNodes; i++) {
// //         int row = i / cols;         // Current node kaunsi row mein hai
// //         int col = i % cols;         // Current node kaunsa column mein hai

// //         // Center mein alignment ke liye thoda offset calculation
// //         float x = (col - (cols - 1) / 2.0f) * spacing;
// //         float y = ((row - (ceil(numNodes / (float)cols) - 1) / 2.0f) * -spacing); 
// //         float z = 0.0f;

// //         nodes[i] = { x, y, z };
// //     }
// // }

// // void GraphVisualizer::display() {
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
// //     // Rectangle Grid Layout ke liye camera door rakho (15 units)
// //     gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0); 
// //     glRotatef(rotateX, 1, 0, 0); glRotatef(rotateY, 0, 1, 0);
// //     //
// //     string lvlInfo = "Current BFS Level: " + to_string(currentLevelDisplay);
// //     drawText(-10.0f, 8.5f, 0, lvlInfo, 1.0f, 1.0f, 0.0f); // Bright Yellow

// //     // --- 🧱 [LOCK STEP] Traversal State Calculate karo ---
// //     // Hum ek visited array banayenge jo currentStep tak ke state ko track karega
// //     vector<bool> currentlyVisitedNodes(numNodes, false);
// //     set<pair<int, int>> currentlyActiveEdges;
// //     int currentComponentIdx = 0;

// //     for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //         int val = anim_nodes[j];
// //         if (val == -1 || val == -3) currentComponentIdx++; // Component Marker
// //         else if (val == -2) continue; // Level Marker skip karo
// //         else if (val >= 0 && val < numNodes) {
// //             currentlyVisitedNodes[val] = true; // Node mark as visited
            
// //             // Ab check karo ki kaunsi ACTIVE edge is node tak le kar aayi
// //             if (currentAlgo == BFS || currentAlgo == DFS || currentAlgo == DIJKSTRA) {
// //                 for (int k = 0; k < (int)anim_edges.size(); k++) {
// //                     // Agar ye edge is visited node par khatam ho rahi hai
// //                     if (anim_edges[k].second == val) {
// //                         // Check if source node of this edge was already visited (valid traversal step)
// //                         bool srcVisited = false;
// //                         for(int prev=0; prev < j; prev++) if(anim_nodes[prev] == anim_edges[k].first) srcVisited=true;

// //                         if(srcVisited || anim_edges[k].first == srcNode) {
// //                              currentlyActiveEdges.insert({anim_edges[k].first, anim_edges[k].second});
// //                         }
// //                     }
// //                 }
// //             }
// //         }
// //     }

// //     // --- 1. EDGES DRAWING (Now Perfectly Synced) ---
// //     for (auto& e : allEdges) {
// //         bool highlight = false;
        
// //         // Edge is active if it's in our calculated currentlyActiveEdges set
// //         if (currentlyActiveEdges.count({e.u, e.v}) || currentlyActiveEdges.count({e.v, e.u})) {
// //             highlight = true;
// //         }

// //         if (highlight) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); // Magenta for cycles
// //             else glColor3f(0.0f, 1.0f, 0.0f); // Bright Green for active flow
// //             glLineWidth(3.5f); // Thicker lines for active path
// //         } else { 
// //             glColor3f(0.25f, 0.25f, 0.25f); // Dark Gray for inactive
// //             glLineWidth(1.0f); 
// //         }
        
// //         glBegin(GL_LINES); 
// //         glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); 
// //         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); 
// //         glEnd();

// //         if (isDirected) drawArrowHead(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2], nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]);
// //     }


// //   // --- 2. NODES DRAWING (Updated for SRC/DEST Sync) ---
// //     // for (int i = 0; i < numNodes; i++) {
// //     //     // Color Logic (Same rahega)
// //     //     if (currentlyVisitedNodes[i]) {
// //     //         if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); 
// //     //         else if (currentAlgo == TOPOSORT_BFS) glColor3f(0.0f, 1.0f, 1.0f);
// //     //         else glColor3f(1.0f, 0.0f, 0.0f); // Red for Visited
// //     //     } else {
// //     //         glColor3f(0.2f, 0.4f, 0.8f); // Blue for Unvisited
// //     //     }
        
// //     //     // Node Sphere draw karo
// //     //     glPushMatrix(); 
// //     //     glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
// //     //     glutSolidSphere(0.35, 25, 25); 
// //     //     glPopMatrix();

// //     //     // --- 🏷️ LABELS DRAWING ---
        
// //     //     // 1. Node Number (White color) - Node ke thoda upar
// //     //     drawText(nodes[i][0], nodes[i][1] + 0.5f, nodes[i][2], std::to_string(i), 1.0f, 1.0f, 1.0f);

// //     //     // 🔥 2. SRC Tag (Bright Green) - Node Number ke bhi upar (+0.9f)
// //     //     if (i == srcNode && srcNode != -1) {
// //     //         drawText(nodes[i][0] - 0.2f, nodes[i][1] + 0.9f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //     //     }
        
// //     //     // 3. DEST Tag (Bright Red) - SRC ki height par (+0.9f)
// //     //     else if (i == destNode && destNode != -1) {
// //     //         drawText(nodes[i][0] - 0.3f, nodes[i][1] + 0.9f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //     //     }
// //     // }    

// //     // --- 3. HUD Display (Keep your old code here) ---
// //     // ... tera viejo dash code ...

// //      // --- 2. NODES DRAWING (Synced with SRC/DEST Logic) ---
// //     for (int i = 0; i < numNodes; i++) {
// //         // Color decide karo
// //         if (currentlyVisitedNodes[i]) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); // Magenta
// //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0.0f, 1.0f, 1.0f); // Cyan
// //             else glColor3f(1.0f, 0.0f, 0.0f); // Pure Red for Visited
// //         } else {
// //             glColor3f(0.2f, 0.4f, 0.8f); // Blue for Unvisited
// //         }
        
// //         // Node Sphere (Gola) draw karo
// //         glPushMatrix(); 
// //         glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
// //         glutSolidSphere(0.35, 25, 25); 
// //         glPopMatrix();

// //         // --- 🏷️ LABELS DRAWING ---
        
// //         // 1. Node Number (White)
// //         drawText(nodes[i][0], nodes[i][1] + 0.5f, nodes[i][2], std::to_string(i), 1.0f, 1.0f, 1.0f);

// //         // 🔥 2. SRC Tag (Bright Green)
// //         // Ye tab chamkega jab i hamara start node hoga
// //         if (i == srcNode && srcNode != -1) {
// //             drawText(nodes[i][0] - 0.2f, nodes[i][1] + 0.9f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //         }
        
// //         // 🔥 3. DEST Tag (Bright Red)
// //         // IMPORTANT: 'else if' ki jagah sirf 'if' use karo aur check karo ki destNode -1 na ho
// //         // Isse traversal mein DEST apne aap gayab ho jayega
// //         if (destNode != -1 && i == destNode) {
// //             drawText(nodes[i][0] - 0.3f, nodes[i][1] + 0.9f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //         }
// //     }


// //     glutSwapBuffers();
// // }

// // void GraphVisualizer::assignPositions() {
// //     nodes.clear(); nodes.resize(numNodes);
    
// //     // Level ke hisaab se nodes ko group karo
// //     unordered_map<int, vector<int>> levelsMap;
// //     int maxLevel = 0;
// //     for(int i=0; i<numNodes; i++) {
// //         int lvl = nodeLevels[i]; // Graph object se level uthao
// //         levelsMap[lvl].push_back(i);
// //         if(lvl > maxLevel) maxLevel = lvl;
// //     }

// //     float levelSpacing = 3.5f; // Vertical gap between levels
// //     float nodeSpacing = 2.5f;  // Horizontal gap between nodes in same level

// //     for(int l=0; l <= maxLevel; l++) {
// //         auto& currentLevelNodes = levelsMap[l];
// //         int count = currentLevelNodes.size();
        
// //         for(int i=0; i < count; i++) {
// //             int nodeIdx = currentLevelNodes[i];
            
// //             // X position: Center align nodes in each level
// //             float x = (i - (count - 1) / 2.0f) * nodeSpacing;
            
// //             // Y position: Har level niche shift hota jayega
// //             float y = 5.0f - (l * levelSpacing); 
            
// //             nodes[nodeIdx] = { x, y, 0.0f };
// //         }
// //     }
// // }

// // void GraphVisualizer::assignPositions() {
// //     nodes.clear(); nodes.resize(numNodes);
    
// //     unordered_map<int, vector<int>> levelsMap;
// //     int maxLvl = 0;
// //     for(int i=0; i<numNodes; i++) {
// //         levelsMap[nodeLevels[i]].push_back(i);
// //         if(nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
// //     }

// //     float vGap = 4.5f; // Vertical distance
// //     float hGap = 3.5f; // Horizontal distance

// //     for(int l=0; l <= maxLvl; l++) {
// //         auto& currentLevel = levelsMap[l];
// //         int count = currentLevel.size();
// //         for(int i=0; i < count; i++) {
// //             int idx = currentLevel[i];
// //             float x = (i - (count - 1) / 2.0f) * hGap; // Center align
// //             float y = 7.0f - (l * vGap);               // Top to Bottom
// //             nodes[idx] = { x, y, 0.0f };
// //         }
// //     }
// // }
// //
// // void GraphVisualizer::display() {
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
// //     glLoadIdentity();

// //     // 1. Camera Positioning (Distance set to 20 for better view)
// //     gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0); 
// //     glRotatef(rotateX, 1, 0, 0); 
// //     glRotatef(rotateY, 0, 1, 0);

// //     // 2. 🔥 HUD: Current Level Indicator (Top Left)
// //     string lvlInfo = "Current BFS Level: " + to_string(currentLevelDisplay);
// //     drawText(-10.0f, 8.5f, 0, lvlInfo, 1.0f, 1.0f, 0.0f); // Bright Yellow

// //     // --- 🧱 [LOCK STEP] Traversal State Logic ---
// //     vector<bool> currentlyVisitedNodes(numNodes, false);
// //     set<pair<int, int>> currentlyActiveEdges;

// //     for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //         int val = anim_nodes[j];
// //         if (val == -1 || val == -3 || val == -2) continue; // Markers skip karo
        
// //         if (val >= 0 && val < numNodes) {
// //             currentlyVisitedNodes[val] = true;
            
// //             // Sync Edges: Check karo kaunsi edge is node tak laayi
// //             if (currentAlgo == BFS || currentAlgo == DFS || currentAlgo == DIJKSTRA) {
// //                 for (int k = 0; k < (int)anim_edges.size(); k++) {
// //                     if (anim_edges[k].second == val) {
// //                         bool srcVisited = false;
// //                         if (anim_edges[k].first == srcNode) srcVisited = true;
// //                         else {
// //                             for (int prev = 0; prev < j; prev++) {
// //                                 if (anim_nodes[prev] == anim_edges[k].first) {
// //                                     srcVisited = true;
// //                                     break;
// //                                 }
// //                             }
// //                         }
// //                         if (srcVisited) {
// //                             currentlyActiveEdges.insert({anim_edges[k].first, anim_edges[k].second});
// //                         }
// //                     }
// //                 }
// //             }
// //         }
// //     }

// //     // --- 3. EDGES DRAWING ---
// //     for (auto& e : allEdges) {
// //         bool highlight = (currentlyActiveEdges.count({e.u, e.v}) || currentlyActiveEdges.count({e.v, e.u}));

// //         if (highlight) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); // Magenta
// //             else glColor3f(0.0f, 1.0f, 0.0f); // Green
// //             glLineWidth(3.5f);
// //         } else { 
// //             glColor3f(0.25f, 0.25f, 0.25f); // Gray
// //             glLineWidth(1.0f); 
// //         }
        
// //         glBegin(GL_LINES); 
// //             glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); 
// //             glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); 
// //         glEnd();

// //         if (isDirected) drawArrowHead(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2], nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]);
// //     }

// //     // --- 4. NODES & LABELS DRAWING ---
// //     for (int i = 0; i < numNodes; i++) {
// //         // Sphere Color
// //         if (currentlyVisitedNodes[i]) {
// //             if (currentAlgo == CYCLE_DETECTED) glColor3f(1.0f, 0.0f, 1.0f); 
// //             else if (currentAlgo == TOPOSORT_BFS) glColor3f(0.0f, 1.0f, 1.0f);
// //             else glColor3f(1.0f, 0.0f, 0.0f); // Red
// //         } else {
// //             glColor3f(0.2f, 0.4f, 0.8f); // Blue
// //         }
        
// //         glPushMatrix(); 
// //             glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
// //             glutSolidSphere(0.35, 25, 25); 
// //         glPopMatrix();

// //         // Node Number
// //         drawText(nodes[i][0], nodes[i][1] + 0.5f, nodes[i][2], to_string(i), 1, 1, 1);

// //         // SRC Tag
// //         if (i == srcNode && srcNode != -1) {
// //             drawText(nodes[i][0] - 0.2f, nodes[i][1] + 0.9f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
// //         }
        
// //         // DEST Tag (Sirf Pathfinding mein dikhega)
// //         if (destNode != -1 && i == destNode) {
// //             drawText(nodes[i][0] - 0.3f, nodes[i][1] + 0.9f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
// //         }
// //     }

// //     glutSwapBuffers();
// // }
// //
// // void GraphVisualizer::display() {
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
// //     glLoadIdentity();
    
// //     // Camera: Poora Tree dekhne ke liye door rakho
// //     gluLookAt(0, 0, 22, 0, 0, 0, 0, 1, 0); 

// //     // 🔥 1. SCREEN TEXT: Top Left Corner mein Level print karo
// //     // Coordinates adjust kiye hain taaki text screen se bahar na jaye
// //     // string lvlText = "CURRENT BFS LEVEL: " + to_string(currentLevelDisplay);
// //     // drawText(-10.5f, 9.5f, 0, lvlText, 1.0f, 1.0f, 0.0f); // Bright Yellow

// //     string lvlInfo = "CURRENT BFS LEVEL: " + to_string(currentLevelDisplay);
// //     drawText(-10.0f, 9.0f, 0, lvlInfo, 1.0f, 1.0f, 0.0f); // Bright Yellow

// //     // --- Traversal State Logic ---
// //     vector<bool> currentlyVisitedNodes(numNodes, false);
// //     set<pair<int, int>> currentlyActiveEdges;

// //     for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
// //         int val = anim_nodes[j];
// //         if (val >= 0 && val < numNodes) {
// //             currentlyVisitedNodes[val] = true;
// //             // Edge sync logic (same as before)
// //             for (auto& edge : anim_edges) {
// //                 if (edge.second == val) {
// //                     currentlyActiveEdges.insert(edge);
// //                 }
// //             }
// //         }
// //     }

// //     // --- 2. EDGES DRAWING ---
// //     for (auto& e : allEdges) {
// //         if (currentlyActiveEdges.count({e.u, e.v}) || currentlyActiveEdges.count({e.v, e.u})) {
// //             glColor3f(0.0f, 1.0f, 0.0f); glLineWidth(3.5f);
// //         } else {
// //             glColor3f(0.2f, 0.2f, 0.2f); glLineWidth(1.0f);
// //         }
// //         glBegin(GL_LINES);
// //             glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]);
// //             glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]);
// //         glEnd();
// //     }

// //     // --- 3. NODES & SRC DRAWING ---
// //     for (int i = 0; i < numNodes; i++) {
// //         if (currentlyVisitedNodes[i]) glColor3f(1.0f, 0.0f, 0.0f); // Red
// //         else glColor3f(0.2f, 0.4f, 0.8f); // Blue

// //         glPushMatrix();
// //             glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]);
// //             glutSolidSphere(0.4, 25, 25);
// //         glPopMatrix();

// //         // Labels: Number + SRC
// //         drawText(nodes[i][0], nodes[i][1] + 0.6f, 0, to_string(i), 1, 1, 1);
// //         if (i == srcNode) {
// //             drawText(nodes[i][0] - 0.3f, nodes[i][1] + 1.1f, 0, "SRC", 0, 1, 0);
// //         }
// //     }
// //     glutSwapBuffers();
// // }
// //
// void GraphVisualizer::display() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
//     glLoadIdentity();
    
//     // 🔥 CAMERA / ZOOM: Ab 'cameraZ' variable control karega zoom ko
//     gluLookAt(0, 0, cameraZ, 0, 0, 0, 0, 1, 0); 
//     glRotatef(rotateX, 1, 0, 0); 
//     glRotatef(rotateY, 0, 1, 0);

//     // --- 1. HUD & TABLE LABELS DRAWING ---
//     // Top-Left: Active Level Status
//     string lvlInfo = "ACTIVE BFS LEVEL: " + to_string(currentLevelDisplay);
//     drawText(-12.0f, 9.5f, 0, lvlInfo, 0.0f, 1.0f, 1.0f); // Cyan Color

//     // Left Side: Row Headers (LEVEL 0 ->, LEVEL 1 ->)
//     int maxLvl = 0;
//     for(int i=0; i<numNodes; i++) if(nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
    
//     for(int l = 0; l <= maxLvl; l++) {
//         float yPos = 7.0f - (l * 4.5f); // Row ki height se match kiya hai
//         string rowLabel = "LEVEL " + to_string(l) + " ->";
//         drawText(-12.0f, yPos, 0, rowLabel, 1.0f, 1.0f, 0.0f); // Yellow Color
//     }

//     // --- 2. TRAVERSAL STATE CALCULATION ---
//     vector<bool> currentlyVisitedNodes(numNodes, false);
//     set<pair<int, int>> currentlyActiveEdges;

//     for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
//         int val = anim_nodes[j];
//         if (val == -1 || val == -3 || val == -2) continue; 
        
//         if (val >= 0 && val < numNodes) {
//             currentlyVisitedNodes[val] = true;
//             if (currentAlgo == BFS || currentAlgo == DFS || currentAlgo == DIJKSTRA) {
//                 for (int k = 0; k < (int)anim_edges.size(); k++) {
//                     if (anim_edges[k].second == val) {
//                         bool srcVisited = (anim_edges[k].first == srcNode);
//                         if (!srcVisited) {
//                             for (int prev = 0; prev < j; prev++) {
//                                 if (anim_nodes[prev] == anim_edges[k].first) { srcVisited = true; break; }
//                             }
//                         }
//                         if (srcVisited) currentlyActiveEdges.insert({anim_edges[k].first, anim_edges[k].second});
//                     }
//                 }
//             }
//         }
//     }

//     // --- 3. EDGES DRAWING ---
//     for (auto& e : allEdges) {
//         if (currentlyActiveEdges.count({e.u, e.v}) || currentlyActiveEdges.count({e.v, e.u})) {
//             glColor3f(0.0f, 1.0f, 0.0f); glLineWidth(3.5f); // Active Green
//         } else { 
//             glColor3f(0.25f, 0.25f, 0.25f); glLineWidth(1.0f); // Inactive Gray
//         }
//         glBegin(GL_LINES); 
//         glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); 
//         glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); 
//         glEnd();
//     }

//     // --- 4. NODES DRAWING ---
//     for (int i = 0; i < numNodes; i++) {
//         // Color
//         if (currentlyVisitedNodes[i]) glColor3f(1.0f, 0.0f, 0.0f); // Red
//         else glColor3f(0.2f, 0.4f, 0.8f); // Blue
        
//         // Sphere
//         glPushMatrix(); 
//         glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
//         glutSolidSphere(0.4, 25, 25); 
//         glPopMatrix();

//         // Node Number
//         drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], to_string(i), 1, 1, 1);
        
//         // SRC & DEST Tags
//         if (i == srcNode && srcNode != -1) 
//             drawText(nodes[i][0] - 0.3f, nodes[i][1] + 1.1f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
//         if (destNode != -1 && i == destNode) 
//             drawText(nodes[i][0] - 0.3f, nodes[i][1] + 1.1f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
//     }
//     glutSwapBuffers();
// }





// //
// // void GraphVisualizer::assignPositions() {
// //     nodes.clear();
// //     nodes.resize(numNodes);
    
// //     // Agar tree logic complex lag raha hai, toh pehle simple Circle mein dikhao
// //     // Taaki screen hamesha visible rahe
// //     float radius = 7.0f; 
// //     for (int i = 0; i < numNodes; i++) {
// //         float angle = 2.0f * 3.14159f * i / numNodes;
// //         nodes[i] = { radius * (float)cos(angle), radius * (float)sin(angle), 0.0f };
// //     }
// // }

// // void GraphVisualizer::assignPositions() {
// //     nodes.clear();
// //     nodes.resize(numNodes);
    
// //     // Level wise nodes ko group karo
// //     unordered_map<int, vector<int>> levelsMap;
// //     int maxLvl = 0;
// //     for(int i = 0; i < numNodes; i++) {
// //         int lvl = nodeLevels[i]; 
// //         levelsMap[lvl].push_back(i);
// //         if(lvl > maxLvl) maxLvl = lvl;
// //     }

// //     float vGap = 5.0f; // Ek level se dusre level ki doori
// //     float hGap = 3.5f; // Ek hi level ke nodes ke beech ki doori

// //     for(int l = 0; l <= maxLvl; l++) {
// //         auto& currentLevelNodes = levelsMap[l];
// //         int count = currentLevelNodes.size();
// //         for(int i = 0; i < count; i++) {
// //             int nodeIdx = currentLevelNodes[i];
            
// //             // X-axis: Center aligned layers
// //             float x = (i - (count - 1) / 2.0f) * hGap;
// //             // Y-axis: Level 0 sabse upar (6.0f), baaki niche shift honge
// //             float y = 6.0f - (l * vGap); 
            
// //             nodes[nodeIdx] = { x, y, 0.0f };
// //         }
// //     }
// // }

// void GraphVisualizer::assignPositions() {
//     nodes.clear();
//     nodes.resize(numNodes);
    
//     // Safety check
//     if (nodeLevels.empty() || nodeLevels.size() < numNodes) {
//         for (int i = 0; i < numNodes; i++) nodes[i] = {(float)i, 0, 0};
//         return;
//     }

//     unordered_map<int, vector<int>> levelsMap;
//     int maxLvl = 0;
//     for(int i = 0; i < numNodes; i++) {
//         levelsMap[nodeLevels[i]].push_back(i);
//         if(nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
//     }

//     float rowHeight = 4.5f; // Rows ke beech ki vertical doori
//     float nodeGap = 4.0f;   // Ek hi row mein nodes ke beech ki horizontal doori
//     float startX = -4.0f;   // Nodes thoda center-right se shuru honge, taaki left mein text aa sake

//     for(int l = 0; l <= maxLvl; l++) {
//         auto& rowNodes = levelsMap[l];
//         for(int i = 0; i < rowNodes.size(); i++) {
//             int nodeIdx = rowNodes[i];
            
//             // X: Ek ke baad ek node horizontally
//             float x = startX + (i * nodeGap);
//             // Y: Level 0 sabse upar, baaki rows niche
//             float y = 7.0f - (l * rowHeight); 
            
//             nodes[nodeIdx] = { x, y, 0.0f };
//         }
//     }
// }





// // 🔥 TIMER SET TO 2000ms FOR CLEAR EXPANSION
// // void GraphVisualizer::update() { 
// //     if (currentStep < maxSteps - 1) { currentStep++; glutPostRedisplay(); } 
// //     glutTimerFunc(2000, updateCallback, 0); 
// // }
// //
// // 📂 File: src/VisualGraphDSA.cpp

// // void GraphVisualizer::update() { 
// //     if (currentStep < (int)anim_nodes.size() - 1) { 
// //         currentStep++; 
        
// //         // Agar Level Marker (-2) ya Component Marker (-3) aaye
// //         if (anim_nodes[currentStep] == -2 || anim_nodes[currentStep] == -3) {
// //             // Hum rukenge nahi, bas marker skip karke agla node dikhayenge
// //             // Lekin display() function is marker ko dekh kar frame update karega
// //             currentStep++; 
// //         }
        
// //         glutPostRedisplay(); 
// //     } 
// //     // Timer 2000ms (2 seconds) rakho taaki har level ka gap dikhe
// //     glutTimerFunc(2000, updateCallback, 0); 
// // }
// // void GraphVisualizer::update() { 
// //     // Agar abhi bhi nodes bache hain animate karne ke liye
// //     if (currentStep < (int)anim_nodes.size() - 1) { 
        
// //         // 🔥 Naya Logic: Agle Level ke saare nodes ek saath dikhao
// //         do {
// //             currentStep++;
// //             // Agar marker mile toh break kar do (Level khatam)
// //             if (anim_nodes[currentStep] == -2 || anim_nodes[currentStep] == -3) {
// //                 break;
// //             }
// //         } while (currentStep < (int)anim_nodes.size() - 1 && anim_nodes[currentStep+1] != -2);

// //         glutPostRedisplay(); 
// //     } 
// //     // Timer 2000ms (2 seconds) taaki agla level aane mein gap dikhe
// //     glutTimerFunc(2000, updateCallback, 0); 
// // }
// // void GraphVisualizer::update() { 
// //     if (currentStep < (int)anim_nodes.size() - 1) { 
        
// //         // 🔥 SYNC & LEVEL LOGIC: 
// //         // BFS ke liye pura level ek saath dikhayega (-2 marker tak)
// //         // DFS ke liye ek-ek node dikhayega
// //         do {
// //             currentStep++;
// //             if (anim_nodes[currentStep] == -2 || anim_nodes[currentStep] == -3) {
// //                 break; // Level ya Component khatam, ab wait karo
// //             }
// //         } while (currentStep < (int)anim_nodes.size() - 1 && 
// //                  anim_nodes[currentStep + 1] != -2 && 
// //                  currentAlgo == BFS); 

// //         glutPostRedisplay(); 
// //     } 
// //     glutTimerFunc(1500, updateCallback, 0); // 1.5 Second delay
// // }
// // void GraphVisualizer::update() { 
// //     if (currentStep < (int)anim_nodes.size() - 1) { 
        
// //         // 🔥 ACCURACY FIX: 
// //         // BFS mein marker (-2) tak saare nodes aur unki edges ek saath chamkengi
// //         // DFS mein ek-ek karke sync mein chalega
// //         if (currentAlgo == BFS) {
// //             do {
// //                 currentStep++;
// //                 if (anim_nodes[currentStep] == -2 || anim_nodes[currentStep] == -3) break;
// //             } while (currentStep < (int)anim_nodes.size() - 1 && anim_nodes[currentStep + 1] != -2);
// //         } else {
// //             currentStep++; // DFS ke liye simple step-by-step
// //         }

// //         glutPostRedisplay(); 
// //     } 
// //     // 🔥 Speed tuned to 800ms for fast feedback
// //     glutTimerFunc(800, updateCallback, 0); 
// // }

// void GraphVisualizer::update() { 
//     if (currentStep < (int)anim_nodes.size() - 1) { 
//         if (currentAlgo == BFS) {
//             // Level marker tak jump karo
//             do {
//                 currentStep++;
//                 if (anim_nodes[currentStep] == -2) currentLevelDisplay++;
//             } while (currentStep < (int)anim_nodes.size() - 1 && anim_nodes[currentStep + 1] != -2);
//         } else {
//             currentStep++;
//         }
//         glutPostRedisplay(); 
//     } 
//     // 800ms ka gap
//     glutTimerFunc(800, [](int v){ currentVisualizer->update(); }, 0); 
// }

// void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
//     if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
//     if (key == 'z') cameraZ -= 0.5f; if (key == 'x') cameraZ += 0.5f;
//     glutPostRedisplay();
// }

// void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }

// void GraphVisualizer::visualize(int argc, char** argv) {
//     assignPositions(); glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//     glutInitWindowSize(1000, 700); glutCreateWindow("3D Graph Visualizer Pro");
//     glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
//     glutTimerFunc(2000, updateCallback, 0); // 🔥 START WITH 2 SECONDS
//     glutKeyboardFunc(keyboardCallback); glutMainLoop();
// }
// void GraphVisualizer::specialKeys(int key, int x, int y) {
//     if (key == GLUT_KEY_RIGHT) rotateY += 5;
//     else if (key == GLUT_KEY_LEFT) rotateY -= 5;
//     else if (key == GLUT_KEY_UP) cameraZ -= 2.0f;   // 🔥 ZOOM IN
//     else if (key == GLUT_KEY_DOWN) cameraZ += 2.0f; // 🔥 ZOOM OUT
//     glutPostRedisplay();
// }


#include "../Include/VisualGraphDSA.h"
#include <GL/freeglut.h>
#include <cmath>
#include <string>

using namespace std;

GraphVisualizer* currentVisualizer = nullptr;

void displayCallback() { if (currentVisualizer) currentVisualizer->display(); }
void updateCallback(int value) { if (currentVisualizer) currentVisualizer->update(); }
void reshapeCallback(int w, int h) { if (currentVisualizer) currentVisualizer->reshape(w, h); }
void keyboardCallback(unsigned char key, int x, int y) { if (currentVisualizer) currentVisualizer->keyboard(key, x, y); }

void GraphVisualizer::drawText(float x, float y, float z, std::string text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void drawArrowHead(float x1, float y1, float z1, float x2, float y2, float z2) {
    float angle = atan2(y2 - y1, x2 - x1);
    float arrowSize = 0.25f; 
    float tipX = x2 - 0.25f * cos(angle);
    float tipY = y2 - 0.25f * sin(angle);
    float leftX = tipX - arrowSize * cos(angle - 0.4f);
    float leftY = tipY - arrowSize * sin(angle - 0.4f);
    float rightX = tipX - arrowSize * cos(angle + 0.4f);
    float rightY = tipY - arrowSize * sin(angle + 0.4f);
    glBegin(GL_TRIANGLES); glVertex3f(tipX, tipY, z2); glVertex3f(leftX, leftY, z2); glVertex3f(rightX, rightY, z2); glEnd();
}

// 🔥 WEIGHTED Constructor
// GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
//     : numNodes(n), isDirected(d), isWeighted(true), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(28.0f) { // ZOOM FIXED
//     currentVisualizer = this;
//     finalDist = wg.lastCalculatedDistance;
//     srcNode = wg.sourceNode; destNode = wg.destNode;
    
//     // 🔥 DATA FIX: Graph se levels copy karo
//     if (!wg.nodeLevels.empty()) this->nodeLevels = wg.nodeLevels;
    
//     allEdges.clear(); adjForLayout.resize(n);
//     for (auto const& p : wg.adjlist) {
//         for (auto const& nbr : p.second) {
//             if (d || p.first < nbr.first) {
//                 Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
//                 allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
//             }
//         }
//     }
//     anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
//     maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
// }
//
// 🔥 WEIGHTED Constructor (Error Fixed)
GraphVisualizer::GraphVisualizer(WeightedGraph& wg, int n, bool d) 
    : numNodes(n), isDirected(d), isWeighted(true), currentAlgo(wg.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(28.0f) { 
    currentVisualizer = this;
    finalDist = wg.lastCalculatedDistance;
    srcNode = wg.sourceNode; destNode = wg.destNode;
    
    // (wg.nodeLevels wali line yahan se hata di gayi hai kyunki wo WeightedGraph mein nahi hai)
    
    allEdges.clear(); adjForLayout.resize(n);
    for (auto const& p : wg.adjlist) {
        for (auto const& nbr : p.second) {
            if (d || p.first < nbr.first) {
                Edge e; e.u = p.first; e.v = nbr.first; e.weight = nbr.second;
                allEdges.push_back(e); adjForLayout[p.first].push_back(nbr.first);
            }
        }
    }
    anim_nodes = wg.anim_nodes; anim_edges = wg.anim_edges;
    maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
}

// 🔥 UNWEIGHTED Constructor
GraphVisualizer::GraphVisualizer(UnweightedGraph& ug, int n, bool d) 
    : numNodes(n), isDirected(d), isWeighted(false), currentAlgo(ug.lastAlgo), currentStep(-1), rotateX(0), rotateY(0), cameraZ(28.0f) { // ZOOM FIXED
    currentVisualizer = this;
    finalDist = -1; 
    srcNode = ug.sourceNode; destNode = ug.destNode;
    
    // 🔥 DATA FIX: Graph se levels copy karo
    if (!ug.nodeLevels.empty()) this->nodeLevels = ug.nodeLevels;
    
    allEdges.clear(); adjForLayout.resize(n);
    for (auto const& p : ug.adjlist) {
        for (int v : p.second) {
            if (d || p.first < v) {
                Edge e; e.u = p.first; e.v = v; e.weight = 0;
                allEdges.push_back(e); adjForLayout[p.first].push_back(v);
            }
        }
    }
    anim_nodes = ug.anim_nodes; anim_edges = ug.anim_edges;
    maxSteps = max((int)anim_nodes.size(), (int)anim_edges.size());
}
//
void GraphVisualizer::assignPositions() {
    nodes.clear();
    nodes.resize(numNodes);
    
    if (nodeLevels.empty() || nodeLevels.size() < numNodes) {
        for (int i = 0; i < numNodes; i++) nodes[i] = {(float)i, 0, 0};
        return;
    }

    unordered_map<int, vector<int>> levelsMap;
    int maxLvl = 0;
    for(int i = 0; i < numNodes; i++) {
        levelsMap[nodeLevels[i]].push_back(i);
        if(nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
    }

    float rowHeight = 4.5f; 
    float nodeGap = 4.0f;   

    for(int l = 0; l <= maxLvl; l++) {
        auto& rowNodes = levelsMap[l];
        for(int i = 0; i < rowNodes.size(); i++) {
            int nodeIdx = rowNodes[i];
            
            // 🔥 FIX: Ab saare nodes Screen ke Center mein align honge
            float x = (i - (rowNodes.size() - 1) / 2.0f) * nodeGap; 
            float y = 7.0f - (l * rowHeight); 
            
            nodes[nodeIdx] = { x, y, 0.0f };
        }
    }
}

// void GraphVisualizer::assignPositions() {
//     nodes.clear();
//     nodes.resize(numNodes);
    
//     // Safety check: Fallback layout if levels are missing
//     if (nodeLevels.empty() || nodeLevels.size() < numNodes) {
//         for (int i = 0; i < numNodes; i++) {
//             float angle = i * 2.0f * 3.14159f / numNodes;
//             nodes[i] = { 6.0f * cos(angle), 6.0f * sin(angle), 0.0f };
//         }
//         return;
//     }

//     unordered_map<int, vector<int>> levelsMap;
//     int maxLvl = 0;
//     for(int i = 0; i < numNodes; i++) {
//         levelsMap[nodeLevels[i]].push_back(i);
//         if(nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
//     }

//     float rowHeight = 4.5f; 
//     float nodeGap = 4.0f;   
//     float startX = -4.0f;   

//     for(int l = 0; l <= maxLvl; l++) {
//         auto& rowNodes = levelsMap[l];
//         for(int i = 0; i < rowNodes.size(); i++) {
//             int nodeIdx = rowNodes[i];
//             float x = startX + (i * nodeGap);
//             float y = 7.0f - (l * rowHeight); 
//             nodes[nodeIdx] = { x, y, 0.0f };
//         }
//     }
// }

void GraphVisualizer::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();
    
    gluLookAt(0, 0, cameraZ, 0, 0, 0, 0, 1, 0); 
    glRotatef(rotateX, 1, 0, 0); 
    glRotatef(rotateY, 0, 1, 0);

    // // --- 1. HUD & TABLE LABELS ---
    // string lvlInfo = "ACTIVE BFS LEVEL: " + to_string(currentLevelDisplay);
    // drawText(-12.0f, 9.5f, 0, lvlInfo, 0.0f, 1.0f, 1.0f); 

    // int maxLvl = 0;
    // if (!nodeLevels.empty()) {
    //     for(int i=0; i<numNodes; i++) {
    //         if (i < nodeLevels.size() && nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
    //     }
    // }
    
    // for(int l = 0; l <= maxLvl; l++) {
    //     float yPos = 7.0f - (l * 4.5f); 
    //     string rowLabel = "LEVEL " + to_string(l) + " ->";
    //     drawText(-12.0f, yPos, 0, rowLabel, 1.0f, 1.0f, 0.0f); 
    // }
string lvlInfo = "ACTIVE BFS LEVEL: " + to_string(currentLevelDisplay);
    // Yahan -14.0f aur 10.5f kar diya taaki ekdum corner mein rahe
    drawText(-14.0f, 10.5f, 0, lvlInfo, 0.0f, 1.0f, 1.0f); 

    int maxLvl = 0;
    if (!nodeLevels.empty()) {
        for(int i=0; i<numNodes; i++) {
            if (i < nodeLevels.size() && nodeLevels[i] > maxLvl) maxLvl = nodeLevels[i];
        }
    }
    
    for(int l = 0; l <= maxLvl; l++) {
        float yPos = 7.0f - (l * 4.5f); 
        // Header ko bhi thoda left shift (-10.0f) kar diya
        string rowLabel = "LEVEL " + to_string(l) + " ->";
        drawText(-10.0f, yPos, 0, rowLabel, 1.0f, 1.0f, 0.0f); 
    }


    // --- 2. TRAVERSAL STATE ---
    vector<bool> currentlyVisitedNodes(numNodes, false);
    set<pair<int, int>> currentlyActiveEdges;

    for (int j = 0; j <= currentStep && j < (int)anim_nodes.size(); j++) {
        int val = anim_nodes[j];
        if (val == -1 || val == -3 || val == -2) continue; 
        
        if (val >= 0 && val < numNodes) {
            currentlyVisitedNodes[val] = true;
            if (currentAlgo == BFS || currentAlgo == DFS || currentAlgo == DIJKSTRA) {
                for (int k = 0; k < (int)anim_edges.size(); k++) {
                    if (anim_edges[k].second == val) {
                        bool srcVisited = (anim_edges[k].first == srcNode);
                        if (!srcVisited) {
                            for (int prev = 0; prev < j; prev++) {
                                if (anim_nodes[prev] == anim_edges[k].first) { srcVisited = true; break; }
                            }
                        }
                        if (srcVisited) currentlyActiveEdges.insert({anim_edges[k].first, anim_edges[k].second});
                    }
                }
            }
        }
    }

    // --- 3. EDGES ---
    for (auto& e : allEdges) {
        if (currentlyActiveEdges.count({e.u, e.v}) || currentlyActiveEdges.count({e.v, e.u})) {
            glColor3f(0.0f, 1.0f, 0.0f); glLineWidth(3.5f); 
        } else { 
            glColor3f(0.25f, 0.25f, 0.25f); glLineWidth(1.0f); 
        }
        glBegin(GL_LINES); 
        glVertex3f(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2]); 
        glVertex3f(nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]); 
        glEnd();
        if (isDirected) drawArrowHead(nodes[e.u][0], nodes[e.u][1], nodes[e.u][2], nodes[e.v][0], nodes[e.v][1], nodes[e.v][2]);
    }

    // --- 4. NODES ---
    for (int i = 0; i < numNodes; i++) {
        if (currentlyVisitedNodes[i]) glColor3f(1.0f, 0.0f, 0.0f); 
        else glColor3f(0.2f, 0.4f, 0.8f); 
        
        glPushMatrix(); 
        glTranslatef(nodes[i][0], nodes[i][1], nodes[i][2]); 
        glutSolidSphere(0.4, 25, 25); 
        glPopMatrix();

        drawText(nodes[i][0], nodes[i][1] + 0.6f, nodes[i][2], to_string(i), 1, 1, 1);
        
        if (i == srcNode && srcNode != -1) 
            drawText(nodes[i][0] - 0.3f, nodes[i][1] + 1.1f, nodes[i][2], "SRC", 0.0f, 1.0f, 0.0f);
        if (destNode != -1 && i == destNode) 
            drawText(nodes[i][0] - 0.3f, nodes[i][1] + 1.1f, nodes[i][2], "DEST", 1.0f, 0.0f, 0.0f);
    }
    glutSwapBuffers();
}

void GraphVisualizer::update() { 
    if (currentStep < (int)anim_nodes.size() - 1) { 
        if (currentAlgo == BFS) {
            do {
                currentStep++;
                if (anim_nodes[currentStep] == -2) currentLevelDisplay++;
            } while (currentStep < (int)anim_nodes.size() - 1 && anim_nodes[currentStep + 1] != -2);
        } else {
            currentStep++;
        }
        glutPostRedisplay(); 
    } 
    glutTimerFunc(1000, updateCallback, 0); // Safe timer standard
}

void GraphVisualizer::keyboard(unsigned char key, int x, int y) {
    if (key == 'l') rotateY -= 5; if (key == 'r') rotateY += 5;
    if (key == 'z') cameraZ -= 1.0f; if (key == 'x') cameraZ += 1.0f; // Zoom In/Out
    glutPostRedisplay();
}

void GraphVisualizer::reshape(int w, int h) { glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(45, (float)w/h, 0.1, 100); glMatrixMode(GL_MODELVIEW); }

void GraphVisualizer::visualize(int argc, char** argv) {
    assignPositions(); glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800); glutCreateWindow("3D Graph Visualizer Pro - Submission Build");
    glEnable(GL_DEPTH_TEST); glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
    glutTimerFunc(1000, updateCallback, 0); glutKeyboardFunc(keyboardCallback); glutMainLoop();
}
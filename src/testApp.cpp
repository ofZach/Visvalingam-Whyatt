#include "testApp.h"



//--------------------------------------------------------------
inline float triArea(ofPoint d0, ofPoint d1, ofPoint d2)
{
    double dArea = ((d1.x - d0.x)*(d2.y - d0.y) - (d2.x - d0.x)*(d1.y - d0.y))/2.0;
    return (dArea > 0.0) ? dArea : -dArea;
}


//--------------------------------------------------------------
typedef struct {
    int index;
    ofPoint pos;
} pointWindex;

//--------------------------------------------------------------
void testApp::calcSimplificaiton( ofPolyline & lineToSimplify, vector < ofPoint > & results){

    
    // this function takes a polyline as input and results a point array where z values = importance of the point.
    
    // note: there's likely some optimizations to be made here since I'm doing alot of repetitive triangle area calculations.
    // a smarter approach would know which triangles to reclculate or use a min heap, etc.
    
    // clear the results:
    
    results.clear();
    
    // create a data store that we will remove from.  we need to know the original index of a point
    // to know how to update the results vector, so store index and pos together:
    
    vector < pointWindex > indices;
    
    int total = lineToSimplify.size();
    
    // setup initial data structures:
    for (int i = 0; i < lineToSimplify.size(); i++){
        pointWindex temp;
        temp.index = i;
        temp.pos = lineToSimplify[i];
        indices.push_back(temp);
        results.push_back(temp.pos);
    }
    
    // now let's, in a while loop, go through, find a smallest triangle, record it, delete it and keep going
    
    int count = 0;
    while (indices.size() > 2){
        float minArea = 1000000;
        float minIndex = -1;
        for (int i = 1; i < indices.size()-1; i++){
            float area = triArea( indices[i-1].pos, indices[i].pos, indices[i+1].pos);
            if (area < minArea){
                minArea = area;
                minIndex = i;
            }
        }
        results[ indices[minIndex].index].z = total - count;  // higher z value = less valuable
        indices.erase(indices.begin() + minIndex);
        count++;
    }
    
    
}


//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0);
    
    line.draw();
    
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    for (int i = 0; i < ptsWithSimplificationInfo.size(); i++){
        if (ptsWithSimplificationInfo[i].z < mouseX){
        mesh.addVertex(ofPoint(ptsWithSimplificationInfo[i].x + 300, ptsWithSimplificationInfo[i].y));
        }
    }
    mesh.draw();
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    line.addVertex( ofPoint(x,y));
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
    line.clear();
    line.addVertex( ofPoint(x,y));
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    calcSimplificaiton(line, ptsWithSimplificationInfo);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
